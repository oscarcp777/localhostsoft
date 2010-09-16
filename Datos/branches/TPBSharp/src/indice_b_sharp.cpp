#include "indice_b_sharp.hpp"
#include<typeinfo>
IndiceBSharp::IndiceBSharp(const std::string& nombre_archivo, unsigned int longitud_bloque, const Esquema::puntero& esquema, const Clave::puntero& clave,
	const ComparadorClave::puntero& comparadorClave) throw(): EstrategiaIndice(clave, esquema) {

	this->longitud_bloque = longitud_bloque;
	this->esquema = esquema;
	this->clave = clave;
	this->comparadorClave = comparadorClave;
	this->archivoIndice = new Archivo(this->longitud_bloque, nombre_archivo + ".idx", Bloques);
	this->archivoIndice->abrirModoBinario();
	this->estrategiaEspacioLibre = new EstrategiaEspacioLibreBloque(this->longitud_bloque, 0.85, nombre_archivo + ".freespace");
	this->estrategiaAlmacenamiento = new EstrategiaAlmacenamientoBSharp(this->esquema, this->clave);
	this->leer_bloque_raiz();
}

IndiceBSharp::~IndiceBSharp() throw() {
}

void IndiceBSharp::agregar_registro(Registro::puntero registro) throw() {
	ResultadoInsercion resultadoInsercion;
	bool hubo_sobreflujo = false;
	if (this->bloqueRaiz->es_hoja()) {
		BloqueExternoBSharp::puntero bloqueExterno = static_cast<BloqueExternoBSharp::puntero>(this->bloqueRaiz);
		hubo_sobreflujo = this->insertar_bloque_externo(bloqueExterno, registro, resultadoInsercion);
	} else {
		BloqueInternoBSharp::puntero bloqueInterno = static_cast<BloqueInternoBSharp::puntero>(this->bloqueRaiz);
		hubo_sobreflujo = this->insertar_bloque_interno(bloqueInterno, registro, resultadoInsercion);
	}

	if (hubo_sobreflujo) {
		this->manejar_sobreflujo_raiz(resultadoInsercion);
	}
}

void IndiceBSharp::borrar_registro(Registro::puntero registro) throw() {
	ResultadoBalanceo resultadoBalanceo;
	bool hubo_subflujo = false;
	if (this->bloqueRaiz->es_hoja()) {
		BloqueExternoBSharp::puntero bloqueExterno = static_cast<BloqueExternoBSharp::puntero>(this->bloqueRaiz);
		this->remover_bloque_externo(bloqueExterno, registro);
	} else {
		BloqueInternoBSharp::puntero bloqueInterno = static_cast<BloqueInternoBSharp::puntero>(this->bloqueRaiz);
		hubo_subflujo = this->remover_bloque_interno(bloqueInterno, registro, resultadoBalanceo);
	}

	if (hubo_subflujo) {
		this->manejar_subflujo_raiz();
	}
}

Registro::puntero IndiceBSharp::buscar_registro(Registro::puntero registro) throw() {
	if (this->bloqueRaiz->es_hoja()) {
		BloqueExternoBSharp::puntero bloqueExterno = static_cast<BloqueExternoBSharp::puntero>(this->bloqueRaiz);
		return this->buscar_bloque_externo(bloqueExterno, registro);
	} else {
		BloqueInternoBSharp::puntero bloqueInterno = static_cast<BloqueInternoBSharp::puntero>(this->bloqueRaiz);
		return this->buscar_bloque_interno(bloqueInterno, registro);
	}
}

void IndiceBSharp::imprimir(std::ostream& streamSalida) throw() {
	this->imprimir_recursivo(this->bloqueRaiz, streamSalida, 0);
}

void IndiceBSharp::crear_bloque_raiz() throw() {
	// Instancia un nuevo bloque raiz
	this->bloqueRaiz = new BloqueExternoBSharp(this->longitud_bloque, 0);
	// Ecscribe bloque raiz
	this->escribir_bloque_raiz();
}

void IndiceBSharp::leer_bloque_raiz() throw() {
	this->bloqueRaiz = this->estrategiaAlmacenamiento->leer_bloque(0, this->archivoIndice);
	if (bloqueRaiz == NULL) {
		this->crear_bloque_raiz();
	}
}

void IndiceBSharp::escribir_bloque_raiz() throw() {
	bool exitoso = this->estrategiaAlmacenamiento->escribir_bloque(0, this->bloqueRaiz, this->archivoIndice);
	if (!exitoso) {
		this->estrategiaEspacioLibre->buscar_espacio_libre();
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(0, this->bloqueRaiz->obtener_longitud_ocupada());
		this->estrategiaAlmacenamiento->agregar_bloque(this->bloqueRaiz, this->archivoIndice);
	}
}

void IndiceBSharp::manejar_sobreflujo_raiz(ResultadoInsercion& resultado) throw() {
	// Busca espacio libre para la nueva raiz
	unsigned int posicion_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
	// Establece el nuevo numero de bloque de la raiz
	this->bloqueRaiz->establecer_numero_bloque(posicion_libre);
	// Escribe el espacio ocupado de la raiz
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(posicion_libre, this->bloqueRaiz->obtener_longitud_ocupada());
	// Escribe el bloque raiz en una nueva posicion
	this->estrategiaAlmacenamiento->agregar_bloque(this->bloqueRaiz, this->archivoIndice);
	// Crea una nueva raiz
	BloqueInternoBSharp::puntero nuevoRaiz = new BloqueInternoBSharp(this->longitud_bloque, 0, this->bloqueRaiz->obtener_nivel() + 1);
	nuevoRaiz->agregar_rama(posicion_libre);
	nuevoRaiz->agregar_rama(resultado.obtener_bloque_derecho());
	nuevoRaiz->agregar_componente(resultado.obtener_registro_clave_media());
	// Escribe el bloque raiz
	this->bloqueRaiz = nuevoRaiz;
	this->escribir_bloque_raiz();
}

void IndiceBSharp::manejar_subflujo_raiz() throw() {
	if (!bloqueRaiz->es_hoja()) {
		BloqueInternoBSharp::puntero bloqueRaizInterno = static_cast<BloqueInternoBSharp::puntero>(this->bloqueRaiz);
		// Verifica que la raiz solo tenga una sola rama, la izquierda, si es asi debo tomar al bloque izquierdo como bloque raiz
		if (bloqueRaizInterno->cantidad_ramas() == 1 && bloqueRaizInterno->cantidad_componentes() == 0) {
			// Leo rama izquierda
			unsigned int rama_izquierda = *(bloqueRaizInterno->primer_rama());
			BloqueBSharp::puntero bloqueIzquierdo = this->estrategiaAlmacenamiento->leer_bloque(rama_izquierda, this->archivoIndice);
			// Marco numero de bloque como libre
			this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueIzquierdo->obtener_numero_bloque(), 0);
			// Marco bloque raiz como ocupado
			this->estrategiaEspacioLibre->escribir_espacio_ocupado(0, bloqueIzquierdo->obtener_longitud_ocupada());
			bloqueIzquierdo->establecer_numero_bloque(0);
			// Escribo bloque rqaiz
			this->estrategiaAlmacenamiento->escribir_bloque(0, bloqueIzquierdo, this->archivoIndice);
			// Establezco bloque izquierdo como raiz
			this->bloqueRaiz = bloqueIzquierdo;
		}
	}
}

bool IndiceBSharp::insertar_bloque_externo(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro,
	ResultadoInsercion& resultado) throw() {
	// Consideramos que no hay sobreflujo
	bool hubo_sobreflujo = false;

	// Verifica que el bloque externo puede agregar el registro
	if (bloqueExterno->puede_agregar_componente(registro)) {
		// Agrega el registro en el bloque externo no lleno
		this->insertar_bloque_externo_no_lleno(bloqueExterno, registro);
	} else {
		// Hubo sobreflujo
		hubo_sobreflujo = true;
		// Agrega el registro en el bloque externo lleno
		this->insertar_bloque_externo_lleno(bloqueExterno, registro, resultado);
	}
	// Devuelve si hubo sobreflujo o no
	return hubo_sobreflujo;
}

void IndiceBSharp::insertar_bloque_externo_no_lleno(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro) throw() {
	// Busca posicion de insercion
	unsigned int posicion_insercion = this->buscar_posicion_insercion_externa(registro, bloqueExterno->primer_componente(), bloqueExterno->ultimo_componente());
	// Obtiene iterador al elemento donde insertar.
	BloqueExternoBSharp::iterador_componentes iterador_insercion = bloqueExterno->primer_componente() + posicion_insercion;
	// Inserta el registro en el bloque externo
	bloqueExterno->agregar_componente_antes_de(registro, iterador_insercion);
	// Actualiza espacio ocupado para el bloque
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueExterno->obtener_numero_bloque(), bloqueExterno->obtener_longitud_ocupada());
	// Escribe bloque en disco
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueExterno->obtener_numero_bloque(), bloqueExterno, this->archivoIndice);
}

void IndiceBSharp::insertar_bloque_externo_lleno(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro, ResultadoInsercion& resultado) throw() {
	// Busco numero de bloque libre
	unsigned int numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
	// Creo nuevo bloque externo para dividir bloque..
	BloqueExternoBSharp::puntero nuevoBloqueExterno = new BloqueExternoBSharp(this->longitud_bloque, numero_bloque_libre);

	// Crea contenedor de componentes para insertar ordenado el registro...
	BloqueExternoBSharp::contenedor_componentes lista_registros;

	// Transfiere todos los regsitros del bloque externo a la lista de registros para insertar ordenado el regitro...
	bloqueExterno->transferir_componentes(lista_registros);

	// Busca posicion de insercion para el registro...
	unsigned int posicion_insercion = buscar_posicion_insercion_externa(registro, lista_registros.begin(), lista_registros.end());

	// Inserta ordenado el registro
	lista_registros.insert(lista_registros.begin() + posicion_insercion, registro);

	// Obtiene elemento medio...
	BloqueExternoBSharp::iterador_componentes posicion_medio = lista_registros.begin() + (lista_registros.size() / 2);

	// Establece el elemento medio a subir en el resultado de insercion
	resultado.establecer_registro_clave_media(this->extraer_clave(*posicion_medio));

	// Inserta elementos a la izquierda del medio en bloque a dividir
	for (BloqueExternoBSharp::iterador_componentes actual = lista_registros.begin(); actual != posicion_medio; ++actual) {
		bloqueExterno->agregar_componente(*actual);
	}

	// Inserta elementos a la derecha del medio en bloque nuevo
	for (BloqueExternoBSharp::iterador_componentes actual = posicion_medio; actual != lista_registros.end(); ++actual) {
		nuevoBloqueExterno->agregar_componente(*actual);
	}

	// Enlaza a los bloques
	nuevoBloqueExterno->establecer_bloque_siguiente(bloqueExterno->obtener_bloque_siguiente());
	bloqueExterno->establecer_bloque_siguiente(nuevoBloqueExterno->obtener_numero_bloque());

	// Actualiza espacio ocupado para el bloque a dividir
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueExterno->obtener_numero_bloque(), bloqueExterno->obtener_longitud_ocupada());
	// Escribe bloque a dividir en disco
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueExterno->obtener_numero_bloque(), bloqueExterno, this->archivoIndice);

	// Actualiza espacio ocupado para el bloque nuevo
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueExterno->obtener_numero_bloque(), nuevoBloqueExterno->obtener_longitud_ocupada());
	// Escribe bloque nuevo
	this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueExterno->obtener_numero_bloque(), nuevoBloqueExterno, this->archivoIndice);

	// Establece numero de bloque derecho en resultado de insercion
	resultado.establecer_bloque_derecho(nuevoBloqueExterno->obtener_numero_bloque());
}

bool IndiceBSharp::insertar_bloque_interno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave, ResultadoInsercion& resultado) throw() {
	// Considero que no hay sobreflujo al insertar en el bloque interno
	bool hay_sobreflujo = false;
	// Busco la rama por la cual insertar
	int rama_insertar = this->buscar_rama(bloqueInterno, registroClave);
	// Leo el bloque por el cual insertar
	BloqueBSharp::puntero bloqueRamaInsertar = this->estrategiaAlmacenamiento->leer_bloque(rama_insertar, this->archivoIndice);

	// Si el bloque existe
	if (bloqueRamaInsertar != NULL) {
		// Considero que no hay sobreflujo al insertar en el bloque hijo
		bool hay_sobreflujo_hijo = false;
		if (bloqueRamaInsertar->es_hoja()) {
			BloqueExternoBSharp::puntero bloqueExternoInsertar(bloqueRamaInsertar);
			// Inserto en el bloque externo hijo
			hay_sobreflujo_hijo = this->insertar_bloque_externo(bloqueExternoInsertar, registroClave, resultado);
		} else {
			BloqueInternoBSharp::puntero bloqueInternoInsertar(bloqueRamaInsertar);
			// Inserto en el bloque interno hijo
			hay_sobreflujo_hijo = this->insertar_bloque_interno(bloqueInternoInsertar, registroClave, resultado);
		}

		// Verifico si hubo sobrelujo al insertar en el bloque hijo
		if (hay_sobreflujo_hijo) {
			// Verifico si puedo agregar en el bloque interno
			if (bloqueInterno->puede_agregar_componente(resultado.obtener_registro_clave_media())) {
				// Inserto en el bloque interno no lleno
				this->insertar_bloque_interno_no_lleno(bloqueInterno, resultado.obtener_registro_clave_media(),
					resultado.obtener_bloque_derecho());
			} else {
				// Inserto en el bloque interno lleno
				hay_sobreflujo = true;
				this->insertar_bloque_interno_lleno(bloqueInterno, resultado.obtener_registro_clave_media(),
					resultado.obtener_bloque_derecho(), resultado);
			}
		}
	}
	return hay_sobreflujo;
}

void IndiceBSharp::insertar_bloque_interno_no_lleno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave,
	unsigned int bloque_derecho) throw() {
	unsigned int posicion_insercion = this->buscar_posicion_insercion_interna(registroClave, bloqueInterno->primer_componente(), bloqueInterno->ultimo_componente());

	// Agrego componente
	BloqueInternoBSharp::iterador_componentes iterador_insercion = bloqueInterno->primer_componente() + posicion_insercion;
	bloqueInterno->agregar_componente_antes_de(registroClave, iterador_insercion);

	// Agrego rama
	BloqueInternoBSharp::iterador_ramas iterador_insercion_rama_derecha = bloqueInterno->primer_rama() + posicion_insercion + 1;
	bloqueInterno->agregar_rama_antes_de(bloque_derecho, iterador_insercion_rama_derecha);

	// Actualizo espacio libre
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueInterno->obtener_numero_bloque(), bloqueInterno->obtener_longitud_ocupada());
	// Escribo bloque
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueInterno->obtener_numero_bloque(), bloqueInterno, this->archivoIndice);
}

void IndiceBSharp::insertar_bloque_interno_lleno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave,
	unsigned int bloque_derecho, ResultadoInsercion& resultado) throw() {
	// Busco numero de bloque libre
	unsigned int numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
	// Creo nuevo bloque interno para dividir
	BloqueInternoBSharp::puntero nuevoBloqueInterno = new BloqueInternoBSharp(this->longitud_bloque, numero_bloque_libre, bloqueInterno->obtener_nivel());

        // Crea contenedor de componentes para insertar ordenado el registro...
        BloqueInternoBSharp::contenedor_componentes lista_registros;
	// Crea contenedor de ramas para insertar la rama nueva...
	BloqueInternoBSharp::contenedor_ramas lista_ramas;

        // Transfiere todos los regsitros del bloque interno a la lista de registros para insertar ordenado el regitro...
        bloqueInterno->transferir_componentes(lista_registros);
	// Transfiere todas las ramas del bloque interno a la lista de ramas para insertar la rama...
	bloqueInterno->transferir_ramas(lista_ramas);

        // Busca posicion de insercion para el registro...
        unsigned int posicion_insercion = buscar_posicion_insercion_interna(registroClave, lista_registros.begin(), lista_registros.end());

        // Inserta ordenado el registro
        lista_registros.insert(lista_registros.begin() + posicion_insercion, registroClave);

	// Inserta la rama
	lista_ramas.insert(lista_ramas.begin() + posicion_insercion + 1, bloque_derecho);

        // Obtiene elemento medio...
        BloqueInternoBSharp::iterador_componentes posicion_medio = lista_registros.begin() + (lista_registros.size() / 2);

        // Establece el elemento medio a subir en el resultado de insercion
        resultado.establecer_registro_clave_media(*posicion_medio);

        // Inserta elementos a la izquierda del medio en bloque a dividir
        for (BloqueInternoBSharp::iterador_componentes actual = lista_registros.begin(); actual != posicion_medio; ++actual) {
                bloqueInterno->agregar_componente(*actual);
        }

        // Inserta elementos a la derecha del medio en bloque nuevo
        for (BloqueExternoBSharp::iterador_componentes actual = posicion_medio + 1 ; actual != lista_registros.end(); ++actual) {
                nuevoBloqueInterno->agregar_componente(*actual);
        }

	// Obtiene rama media...
	unsigned int cantidad_ramas_izquierda = (bloqueInterno->cantidad_componentes() + 1);
	unsigned int cantidad_ramas_derecha = lista_ramas.size() - cantidad_ramas_izquierda;

	BloqueInternoBSharp::iterador_ramas actual = lista_ramas.begin();
	unsigned int contador = 0;
	while (contador < cantidad_ramas_izquierda && actual != lista_ramas.end()) {
		bloqueInterno->agregar_rama(*actual);
		++actual;
	        ++contador;
	}

	contador = 0;
	while (contador < cantidad_ramas_derecha && actual != lista_ramas.end()) {
		nuevoBloqueInterno->agregar_rama(*actual);
		++actual;
	        ++contador;
	}

	nuevoBloqueInterno->establecer_bloque_siguiente(bloqueInterno->obtener_bloque_siguiente());
        bloqueInterno->establecer_bloque_siguiente(nuevoBloqueInterno->obtener_numero_bloque());

	// Actualiza espacio ocupado para el bloque a dividir
        this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueInterno->obtener_numero_bloque(), bloqueInterno->obtener_longitud_ocupada());
        // Escribe bloque a dividir en disco
        this->estrategiaAlmacenamiento->escribir_bloque(bloqueInterno->obtener_numero_bloque(), bloqueInterno, this->archivoIndice);

        // Actualiza espacio ocupado para el bloque nuevo
        this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueInterno->obtener_numero_bloque(), nuevoBloqueInterno->obtener_longitud_ocupada());
        // Escribe bloque nuevo
        this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueInterno->obtener_numero_bloque(), nuevoBloqueInterno, this->archivoIndice);

	// Establezco bloque derecho en resultado de insercion
	resultado.establecer_bloque_derecho(nuevoBloqueInterno->obtener_numero_bloque());
}

unsigned int IndiceBSharp::buscar_posicion_insercion_externa(const Registro::puntero& registro, BloqueExternoBSharp::iterador_componentes primer_registro,
	BloqueExternoBSharp::iterador_componentes ultimo_registro) throw() {
	unsigned int posicion_insercion = 0;

	for (BloqueExternoBSharp::iterador_componentes actual = primer_registro; actual != ultimo_registro; ++actual, ++posicion_insercion) {
		Registro::puntero registroIterado = static_cast<Registro::puntero>(*actual);
		if (!( this->comparadorClave->es_menor(this->clave, registroIterado, registro))) {
            break;
        }
    }
	return posicion_insercion;
}

unsigned int IndiceBSharp::buscar_posicion_insercion_interna(const Registro::puntero& registro, BloqueInternoBSharp::iterador_componentes primer_registro,
	BloqueInternoBSharp::iterador_componentes ultimo_registro) throw() {
	unsigned int posicion_insercion = 0;
	for (BloqueInternoBSharp::iterador_componentes actual = primer_registro; actual != ultimo_registro; ++actual, ++posicion_insercion) {
        	Registro::puntero registroIterado = static_cast<Registro::puntero>(*actual);
	        if ((this->comparadorClave->es_menor(this->clave, registroIterado, registro)) ||
			(this->comparadorClave->es_igual(this->clave, registroIterado, registro))) {
        	} else {
                	break;
	        }
    	}
	return posicion_insercion;
}

int IndiceBSharp::buscar_rama(const BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro) throw() {
	BloqueInternoBSharp::iterador_componentes_constante actualComponente = bloqueInterno->primer_componente();
	BloqueInternoBSharp::iterador_componentes_constante finComponente = bloqueInterno->ultimo_componente();
	unsigned int posicion_rama = 0;

	while (actualComponente != finComponente) {
		if (this->comparadorClave->es_menor(this->clave, registro, Registro::puntero(*actualComponente))) {
			break;
		}
		++actualComponente;
		++posicion_rama;
	}

	return bloqueInterno->obtener_rama(posicion_rama);
}

Registro::puntero IndiceBSharp::extraer_clave(const Registro::puntero& registro) throw() {
	Registro::puntero registroClave = new RegistroLongitudVariable(this->clave);

	Clave::iterador_campos actualCampo = this->clave->primer_campo();
	Clave::iterador_campos finCampo = this->clave->ultimo_campo();

	while (actualCampo != finCampo) {
		std::string nombreCampo = *actualCampo;
		registroClave->agregar_campo(nombreCampo, registro->obtener_campo(nombreCampo));
		++actualCampo;
	}
	return registroClave;
}

bool IndiceBSharp::remover_bloque_externo(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro) throw() {
	BloqueExternoBSharp::iterador_componentes actualComponente = bloqueExterno->primer_componente();
	BloqueExternoBSharp::iterador_componentes finComponente = bloqueExterno->ultimo_componente();

	while (actualComponente != finComponente) {
		Registro::puntero registroIterado = *actualComponente;
		if (this->comparadorClave->es_igual(this->clave, registroIterado, registro)) {
			bloqueExterno->remover_componente(actualComponente);
			break;
		}
		++actualComponente;
	}

	// Actualizo espacio en disco
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueExterno->obtener_numero_bloque(), bloqueExterno->obtener_longitud_ocupada());
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueExterno->obtener_numero_bloque(), bloqueExterno, this->archivoIndice);

	return bloqueExterno->esta_semi_vacio();
}

bool IndiceBSharp::remover_bloque_interno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave,
	ResultadoBalanceo& resultadoBalanceo) throw() {
	// Considero que no hay subflujo al remover en el bloque interno
	bool hay_subflujo = false;
	// Busco la rama por la cual borrar
	int rama_borrar = this->buscar_rama(bloqueInterno, registroClave);
	// Leo el bloque por el cual borrar
	BloqueBSharp::puntero bloqueRamaBorrar = this->estrategiaAlmacenamiento->leer_bloque(rama_borrar, this->archivoIndice);

	if (bloqueRamaBorrar != NULL) {
		// Considero que no hay subflujo al remover en el bloque hijo
		bool hay_subflujo_hijo = false;
		if (bloqueRamaBorrar->es_hoja()) {
			BloqueExternoBSharp::puntero bloqueExternoBorrar(bloqueRamaBorrar);
			// Remuevo en el bloque externo hijo
                        hay_subflujo_hijo = this->remover_bloque_externo(bloqueExternoBorrar, registroClave);
		} else {
			BloqueInternoBSharp::puntero bloqueInternoBorrar(bloqueRamaBorrar);
                        // Remuevo en el bloque interno hijo
                        hay_subflujo_hijo = this->remover_bloque_interno(bloqueInternoBorrar, registroClave, resultadoBalanceo);
                }

		if (hay_subflujo_hijo) {
			BloqueBSharp::puntero bloqueHermanoIzquierdo = this->buscar_hermano_izquierdo(bloqueInterno, bloqueRamaBorrar);
			BloqueBSharp::puntero bloqueHermanoDerecho = this->buscar_hermano_derecho(bloqueInterno, bloqueRamaBorrar);
			// Estamos en el caso del bloque mas a la derecha
			if (bloqueRamaBorrar->obtener_numero_bloque() == (unsigned int) *bloqueInterno->ultima_rama() &&
				(bloqueRamaBorrar->obtener_longitud_datos() == 0)) {
					this->borrar_bloque(bloqueRamaBorrar);
					this->actualizar_borrado(bloqueInterno, false);
			} else if (bloqueRamaBorrar->obtener_numero_bloque() == (unsigned int) *bloqueInterno->primer_rama() &&
				(bloqueRamaBorrar->obtener_longitud_datos() == 0)) {
					this->borrar_bloque(bloqueRamaBorrar);
					this->actualizar_borrado(bloqueInterno, true);
			} else {
				if (bloqueHermanoIzquierdo != NULL) {
					if (!this->puede_fusionar_bloques(bloqueHermanoIzquierdo, bloqueRamaBorrar)) {
						this->balancear_bloques(bloqueHermanoIzquierdo, bloqueRamaBorrar, resultadoBalanceo);
						this->actualizar_balanceo(bloqueInterno, resultadoBalanceo);
					} else {
						this->fusionar_bloques(bloqueHermanoIzquierdo, bloqueRamaBorrar);
						this->actualizar_fusion(bloqueInterno, bloqueRamaBorrar->obtener_numero_bloque());
					}
				} else if (bloqueHermanoDerecho != NULL) {
					if (!this->puede_fusionar_bloques(bloqueHermanoDerecho, bloqueRamaBorrar)) {
						this->balancear_bloques(bloqueRamaBorrar, bloqueHermanoDerecho, resultadoBalanceo);
						this->actualizar_balanceo(bloqueInterno, resultadoBalanceo);
					} else {
						this->fusionar_bloques(bloqueRamaBorrar, bloqueHermanoDerecho);
						this->actualizar_fusion(bloqueInterno, bloqueHermanoDerecho->obtener_numero_bloque());
					}
				}
			}
			hay_subflujo = bloqueInterno->esta_semi_vacio();
		}
	}
	return hay_subflujo;
}

void IndiceBSharp::borrar_bloque(BloqueBSharp::puntero& bloqueBorrar) throw() {
	// Escribe espacio libre para el bloque
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueBorrar->obtener_numero_bloque(),0);
}

void IndiceBSharp::actualizar_borrado(BloqueInternoBSharp::puntero& bloquePadre, bool izquierdo) throw() {
	if (izquierdo) {
		bloquePadre->remover_rama(bloquePadre->primer_rama());
		bloquePadre->remover_componente(bloquePadre->primer_componente());
	} else {
		bloquePadre->remover_ultima_rama();
		bloquePadre->remover_ultimo_componente();
	}
	// Escribo bloque padre en disco...
        this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloquePadre->obtener_numero_bloque(), bloquePadre->obtener_longitud_ocupada());
        this->estrategiaAlmacenamiento->escribir_bloque(bloquePadre->obtener_numero_bloque(), bloquePadre, this->archivoIndice);
}

void IndiceBSharp::balancear_bloques(BloqueBSharp::puntero& primerBloque, BloqueBSharp::puntero& segundoBloque,
	ResultadoBalanceo& resultadoBalanceo) throw() {
	// Defino contenedores para los registros del primer bloque, segundo bloque y totales
	BloqueBSharp::contenedor_componentes registros_primer_bloque;
	BloqueBSharp::contenedor_componentes registros_segundo_bloque;
	BloqueBSharp::contenedor_componentes registros_totales;

	primerBloque->transferir_componentes(registros_primer_bloque);
	segundoBloque->transferir_componentes(registros_segundo_bloque);

	registros_totales.insert(registros_totales.end(), registros_primer_bloque.begin(), registros_primer_bloque.end());
	registros_totales.insert(registros_totales.end(), registros_segundo_bloque.begin(), registros_segundo_bloque.end());

	// Obtengo iterador al elemento medio de la secuencia de registros
	BloqueBSharp::iterador_componentes componente_medio = registros_totales.begin() + (registros_totales.size() / 2);

	resultadoBalanceo.establecer_registro_clave_media(this->extraer_clave(*componente_medio));
    resultadoBalanceo.establecer_bloque_hermano_derecho(segundoBloque->obtener_numero_bloque());

	BloqueBSharp::iterador_componentes actual = registros_totales.begin();
	for (actual = registros_totales.begin(); actual != componente_medio; ++actual) {
		primerBloque->agregar_componente(*actual);
	}

	for (actual = componente_medio; actual != registros_totales.end(); ++actual) {
		segundoBloque->agregar_componente(*actual);
	}

	// Si es nodo interno balanceo las ramas
	if (!primerBloque->es_hoja() && !segundoBloque->es_hoja()) {
		BloqueInternoBSharp::puntero primerBloqueInterno = static_cast<BloqueInternoBSharp::puntero>(primerBloque);
		BloqueInternoBSharp::puntero segundoBloqueInterno = static_cast<BloqueInternoBSharp::puntero>(segundoBloque);

		BloqueInternoBSharp::contenedor_ramas ramas_primer_bloque;
		BloqueInternoBSharp::contenedor_ramas ramas_segundo_bloque;
		BloqueInternoBSharp::contenedor_ramas ramas_totales;

		primerBloqueInterno->transferir_ramas(ramas_primer_bloque);
		segundoBloqueInterno->transferir_ramas(ramas_segundo_bloque);

		ramas_totales.insert(ramas_totales.end(), ramas_primer_bloque.begin(), ramas_primer_bloque.end());
		ramas_totales.insert(ramas_totales.end(), ramas_segundo_bloque.begin(), ramas_segundo_bloque.end());

		// Obtiene rama media...
		unsigned int cantidad_ramas_izquierda = (primerBloqueInterno->cantidad_componentes() + 1);
		unsigned int cantidad_ramas_derecha = ramas_totales.size() - cantidad_ramas_izquierda;

		BloqueInternoBSharp::iterador_ramas actual = ramas_totales.begin();
		unsigned int contador = 0;
		while (contador < cantidad_ramas_izquierda && actual != ramas_totales.end()) {
                	primerBloqueInterno->agregar_rama(*actual);
			++actual;
			++contador;
		}

		contador = 0;
		while (contador < cantidad_ramas_derecha && actual != ramas_totales.end()) {
			segundoBloqueInterno->agregar_rama(*actual);
			++actual;
			++contador;
		}
	}

	// Escribo espacio libre de primer bloque
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(primerBloque->obtener_numero_bloque(), primerBloque->obtener_longitud_ocupada());
	// Escribo espacio libre de segundo bloque
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(segundoBloque->obtener_numero_bloque(), segundoBloque->obtener_longitud_ocupada());

	// Escribo primer bloque
	this->estrategiaAlmacenamiento->escribir_bloque(primerBloque->obtener_numero_bloque(), primerBloque, this->archivoIndice);
	this->estrategiaAlmacenamiento->escribir_bloque(segundoBloque->obtener_numero_bloque(), segundoBloque, this->archivoIndice);
}

bool IndiceBSharp::puede_fusionar_bloques(BloqueBSharp::puntero& primerBloque, BloqueBSharp::puntero& segundoBloque) throw() {
	return primerBloque->esta_semi_vacio() && segundoBloque->esta_semi_vacio();
}

void IndiceBSharp::fusionar_bloques(BloqueBSharp::puntero& primerBloque, BloqueBSharp::puntero& segundoBloque) throw() {
	BloqueBSharp::iterador_componentes actualComponente = segundoBloque->primer_componente();
	BloqueBSharp::iterador_componentes finComponente = segundoBloque->ultimo_componente();

	while (actualComponente != finComponente) {
		primerBloque->agregar_componente(*actualComponente);
		++actualComponente;
	}

	if (!primerBloque->es_hoja() && !segundoBloque->es_hoja()) {
		BloqueInternoBSharp::puntero primerBloqueInterno = static_cast<BloqueInternoBSharp::puntero>(primerBloque);
		BloqueInternoBSharp::puntero segundoBloqueInterno = static_cast<BloqueInternoBSharp::puntero>(segundoBloque);

		BloqueInternoBSharp::iterador_ramas actualRama = segundoBloqueInterno->primer_rama();
		BloqueInternoBSharp::iterador_ramas finRama = segundoBloqueInterno->ultima_rama();

		while (actualRama != finRama) {
			primerBloqueInterno->agregar_rama(*actualRama);
			++actualRama;
		}
	}

	// Actualizo numero de bloque siguiente
	primerBloque->establecer_bloque_siguiente(segundoBloque->obtener_bloque_siguiente());

	// Marco segundo bloque como borrado
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(segundoBloque->obtener_numero_bloque(), 0);
	// Escribo longitud ocupada de primer bloque
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(primerBloque->obtener_numero_bloque(), primerBloque->obtener_longitud_ocupada());
	// Escribo primer bloque
	this->estrategiaAlmacenamiento->escribir_bloque(primerBloque->obtener_numero_bloque(), primerBloque, this->archivoIndice);
}

BloqueBSharp::puntero IndiceBSharp::buscar_hermano_izquierdo(BloqueInternoBSharp::puntero& bloquePadre, BloqueBSharp::puntero& bloqueHijo) throw() {
	BloqueInternoBSharp::iterador_ramas actualRama = bloquePadre->primer_rama();
	BloqueInternoBSharp::iterador_ramas finRama = bloquePadre->ultima_rama();
	bool encontrado = false;
	int posicion_rama_hija = 0;

	while (actualRama != finRama && !encontrado) {
		if (*actualRama == bloqueHijo->obtener_numero_bloque()) {
			encontrado = true;
		} else {
			++posicion_rama_hija;
			++actualRama;
		}
	}
	//Es la primera de las ramas, es decir el primer hijo, no tiene hermano izquierdo, devuelvo NULL
	if (posicion_rama_hija == 0) {
		return NULL;
	} else {
		return this->estrategiaAlmacenamiento->leer_bloque(bloquePadre->obtener_rama(posicion_rama_hija - 1), this->archivoIndice);
	}
}

BloqueBSharp::puntero IndiceBSharp::buscar_hermano_derecho(BloqueInternoBSharp::puntero& bloquePadre, BloqueBSharp::puntero& bloqueHijo) throw() {
	// Si el bloque siguiente no es invalido, tiene hermano derecho, lo devuelvo
	if (bloqueHijo->obtener_bloque_siguiente() != BloqueBSharp::ID_BLOQUE_INVALIDO) {
		return this->estrategiaAlmacenamiento->leer_bloque(bloqueHijo->obtener_bloque_siguiente(), this->archivoIndice);
	} else {
		return NULL;
	}
}

void IndiceBSharp::actualizar_balanceo(BloqueInternoBSharp::puntero& bloquePadre, ResultadoBalanceo& resultadoBalanceo) throw() {
        BloqueInternoBSharp::iterador_ramas actualRama = bloquePadre->primer_rama();
        BloqueInternoBSharp::iterador_ramas finRama = bloquePadre->ultima_rama();
        int posicion_rama_actualizar = 0;
        while (actualRama != finRama) {
                if (*actualRama == resultadoBalanceo.obtener_bloque_hermano_derecho()) {
                        break;
                }
                ++posicion_rama_actualizar;
                ++actualRama;
        }
	bloquePadre->establecer_componente(posicion_rama_actualizar-1, resultadoBalanceo.obtener_registro_clave_media());
	// Escribo bloque padre en disco...
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloquePadre->obtener_numero_bloque(), bloquePadre->obtener_longitud_ocupada());
	this->estrategiaAlmacenamiento->escribir_bloque(bloquePadre->obtener_numero_bloque(), bloquePadre, this->archivoIndice);
}

void IndiceBSharp::actualizar_fusion(BloqueInternoBSharp::puntero& bloquePadre, int numero_bloque_eliminado) throw() {
	BloqueInternoBSharp::iterador_ramas actualRama = bloquePadre->primer_rama();
	BloqueInternoBSharp::iterador_ramas finRama = bloquePadre->ultima_rama();
	int posicion_rama_eliminar = 0;
	while (actualRama != finRama) {
		if (*actualRama == numero_bloque_eliminado) {
			bloquePadre->remover_rama(actualRama);
			break;
		}
		++posicion_rama_eliminar;
		++actualRama;
	}
	BloqueInternoBSharp::iterador_componentes actualClave = bloquePadre->primer_componente();
	for (int contador_claves = 0; contador_claves <posicion_rama_eliminar - 1; ++contador_claves) {
		++actualClave;
	}
	bloquePadre->remover_componente(actualClave);
	// Escribo bloque padre en disco...
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloquePadre->obtener_numero_bloque(), bloquePadre->obtener_longitud_ocupada());
	this->estrategiaAlmacenamiento->escribir_bloque(bloquePadre->obtener_numero_bloque(), bloquePadre, this->archivoIndice);
}

Registro::puntero IndiceBSharp::buscar_bloque_externo(const BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro) throw() {
	Registro::puntero registroEncontrado;
	bool encontrado = false;

	if (bloqueExterno != NULL) {
		BloqueExternoBSharp::iterador_componentes_constante actualComponente = bloqueExterno->primer_componente();
		BloqueExternoBSharp::iterador_componentes_constante finComponente = bloqueExterno->ultimo_componente();

		while (actualComponente != finComponente && !encontrado) {
			Registro::puntero registroIterado = *actualComponente;
			if (this->comparadorClave->es_igual(this->clave, registroIterado, registro)) {
				registroEncontrado = registroIterado;
				encontrado = true;
			}
			++actualComponente;
		}
	}
	return registroEncontrado;
}

Registro::puntero IndiceBSharp::buscar_bloque_interno(const BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro) throw() {
	Registro::puntero registroEncontrado;
	if (bloqueInterno != NULL) {
		int rama_buscar = this->buscar_rama(bloqueInterno, registro);
		BloqueBSharp::puntero bloqueLeido = this->estrategiaAlmacenamiento->leer_bloque(rama_buscar, this->archivoIndice);
		if (bloqueLeido != NULL) {
			if (bloqueLeido->es_hoja()) {
				BloqueExternoBSharp::puntero bloqueExternoLeido = static_cast<BloqueExternoBSharp::puntero>(bloqueLeido);
				registroEncontrado = this->buscar_bloque_externo(bloqueExternoLeido, registro);
			} else {
				BloqueInternoBSharp::puntero bloqueInternoLeido = static_cast<BloqueInternoBSharp::puntero>(bloqueLeido);
				registroEncontrado = this->buscar_bloque_interno(bloqueInternoLeido, registro);
			}
		}
	}
	return registroEncontrado;
}

void IndiceBSharp::imprimir_recursivo(const BloqueBSharp::puntero& bloqueActual, std::ostream& streamSalida, unsigned int nivel) throw() {
	if (bloqueActual != NULL) {
		streamSalida << std::string(nivel * 4, '-');
		streamSalida << "NUMERO BLOQUE: " << bloqueActual->obtener_numero_bloque() << " ";
		streamSalida << "NIVEL: " << bloqueActual->obtener_nivel() << " ";
		streamSalida << "COMPONENTES BLOQUE: "<<std::endl;;
		Bloque::iterador_componentes_constante actualComponente = bloqueActual->primer_componente();
		Bloque::iterador_componentes_constante finComponente = bloqueActual->ultimo_componente();
		while (actualComponente != finComponente) {
			Registro::puntero registro = (Registro::puntero) *actualComponente;
			this->imprimir_registro(registro, streamSalida);
			++actualComponente;
		}
		streamSalida << "--CON SIGUIENTE: " << bloqueActual->obtener_bloque_siguiente();
		if (bloqueActual->es_hoja()) {
			streamSalida << "--EN BLOQUE HOJA--";
			streamSalida << std::endl;
			streamSalida << std::endl;
			streamSalida << std::endl;
                } else {
                        streamSalida << "--EN BLOQUE INTERNO--";
                        const BloqueInternoBSharp::puntero& bloqueInterno = static_cast<BloqueInternoBSharp::puntero>(bloqueActual);
                        BloqueInternoBSharp::iterador_ramas_constante actualRama = bloqueInterno->primer_rama();
                        BloqueInternoBSharp::iterador_ramas_constante finRama = bloqueInterno->ultima_rama();
			std::cout << "CON RAMAS(";
                        while (actualRama != finRama) {
                                streamSalida << " " << *actualRama;
                                ++actualRama;
                        }
                        streamSalida << " ) ";
			streamSalida << std::endl;
                        streamSalida << std::endl;
                        streamSalida << std::endl;

			actualRama = bloqueInterno->primer_rama();
			finRama = bloqueInterno->ultima_rama();
			while (actualRama != finRama) {
				BloqueBSharp::puntero bloqueHijo = this->estrategiaAlmacenamiento->leer_bloque(*actualRama, this->archivoIndice);
				if (bloqueHijo != NULL) {
					this->imprimir_recursivo(bloqueHijo, streamSalida, nivel + 1);
				}
				++actualRama;
			}
                }
	}
}

void IndiceBSharp::imprimir_registro(const Registro::puntero& registro, std::ostream& streamSalida) throw() {
	Registro::iterador_campos_constante actualCampo = registro->primer_campo();
	Registro::iterador_campos_constante finCampo = registro->ultimo_campo();
	streamSalida << "( ";
	while (actualCampo != finCampo) {
		std::cout << actualCampo->first << ": ";
		Campo::puntero campo = actualCampo->second;
		switch (campo->obtener_tipo_campo()) {
			case TIPO_CAMPO_BOOLEANO:
				streamSalida << (*(bool*) campo->obtener_valor()) << " ";
				break;
			case TIPO_CAMPO_CADENA:
                                streamSalida << (*(std::string*) campo->obtener_valor()) << " ";
                                break;
			case TIPO_CAMPO_DOBLE:
                                streamSalida << (*(double*) campo->obtener_valor()) << " ";
                                break;
			case TIPO_CAMPO_ENTERO:
                                streamSalida << (*(int*) campo->obtener_valor()) << " ";
                                break;
			case TIPO_CAMPO_FLOTANTE:
                                streamSalida << (*(float*) campo->obtener_valor()) << " ";
                                break;
			case TIPO_CAMPO_LARGO:
                                streamSalida << (*(long*) campo->obtener_valor()) << " ";
                                break;
		}
		++actualCampo;
	}
	streamSalida << " )";
}
