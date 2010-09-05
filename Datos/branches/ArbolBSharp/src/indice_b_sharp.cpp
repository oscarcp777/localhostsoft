#include "indice_b_sharp.hpp"
#include<typeinfo>
IndiceBSharp::IndiceBSharp(const std::string& nombre_archivo, unsigned int longitud_bloque, const Esquema::puntero& esquema, const Clave::puntero& clave,
	const ComparadorClave::puntero& comparadorClave) throw(): EstrategiaIndice(clave) {

	this->longitud_bloque = longitud_bloque;
	this->esquema = esquema;
	this->clave = clave;
	this->comparadorClave = comparadorClave;
	this->archivoIndice = new Archivo(this->longitud_bloque, nombre_archivo + ".idx");
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
		this->manejar_division_raiz(resultadoInsercion);
	}
}

void IndiceBSharp::borrar_registro(Registro::puntero registro) throw() {
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

void IndiceBSharp::manejar_division_raiz(ResultadoInsercion& resultado) throw() {
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

bool IndiceBSharp::insertar_bloque_externo(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro, ResultadoInsercion& resultado) throw() {
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
	bloqueExterno->agregar_componente(registro, iterador_insercion);
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

	// Establece numero de bloque izquierdo en resultado de insercion
	resultado.establecer_bloque_izquierdo(bloqueExterno->obtener_numero_bloque());
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
					resultado.obtener_bloque_izquierdo(),
					resultado.obtener_bloque_derecho());
			} else {
				// Inserto en el bloque interno lleno
				hay_sobreflujo = true;
				this->insertar_bloque_interno_lleno(bloqueInterno, resultado.obtener_registro_clave_media(),
					resultado.obtener_bloque_izquierdo(),
					resultado.obtener_bloque_derecho(), resultado);
			}
		}
	}
	return hay_sobreflujo;
}

void IndiceBSharp::insertar_bloque_interno_no_lleno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave, unsigned int bloque_izquierdo, unsigned int bloque_derecho) throw() {
	unsigned int posicion_insercion = this->buscar_posicion_insercion_interna(registroClave, bloqueInterno->primer_componente(), bloqueInterno->ultimo_componente());

	// Agrego componente
	BloqueInternoBSharp::iterador_componentes iterador_insercion = bloqueInterno->primer_componente() + posicion_insercion;
	bloqueInterno->agregar_componente(registroClave, iterador_insercion);

	// Agrego rama
	BloqueInternoBSharp::iterador_rama iterador_insercion_rama_derecha = bloqueInterno->primer_rama() + posicion_insercion + 1;
	bloqueInterno->agregar_rama(bloque_derecho, iterador_insercion_rama_derecha);

	// Actualizo espacio libre
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueInterno->obtener_numero_bloque(), bloqueInterno->obtener_longitud_ocupada());
	// Escribo bloque
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueInterno->obtener_numero_bloque(), bloqueInterno, this->archivoIndice);
}

void IndiceBSharp::insertar_bloque_interno_lleno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave,
	unsigned int bloque_izquierdo, unsigned int bloque_derecho, ResultadoInsercion& resultado) throw() {
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

	// Obtiene rama media...
	BloqueInternoBSharp::iterador_rama rama_media = lista_ramas.begin() + (lista_ramas.size() / 2) + 1;

	BloqueInternoBSharp::iterador_rama actual = lista_ramas.begin();
	BloqueInternoBSharp::iterador_rama fin = lista_ramas.end();

	while (actual != rama_media) {
		bloqueInterno->agregar_rama(*actual);
		++actual;
	}

	actual = rama_media;
	while (actual != fin) {
		nuevoBloqueInterno->agregar_rama(*actual);
		++actual;
	}

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

	// Actualiza espacio ocupado para el bloque a dividir
        this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueInterno->obtener_numero_bloque(), bloqueInterno->obtener_longitud_ocupada());
        // Escribe bloque a dividir en disco
        this->estrategiaAlmacenamiento->escribir_bloque(bloqueInterno->obtener_numero_bloque(), bloqueInterno, this->archivoIndice);

        // Actualiza espacio ocupado para el bloque nuevo
        this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueInterno->obtener_numero_bloque(), nuevoBloqueInterno->obtener_longitud_ocupada());
        // Escribe bloque nuevo
        this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueInterno->obtener_numero_bloque(), nuevoBloqueInterno, this->archivoIndice);

	// Establezco bloque izquierdo en resultado de insercion
	resultado.establecer_bloque_izquierdo(bloqueInterno->obtener_numero_bloque());
	// Establezco bloque derecho en resultado de insercion
	resultado.establecer_bloque_derecho(nuevoBloqueInterno->obtener_numero_bloque());
}

unsigned int IndiceBSharp::buscar_posicion_insercion_externa(const Registro::puntero& registro, BloqueExternoBSharp::iterador_componentes primer_registro,
	BloqueExternoBSharp::iterador_componentes ultimo_registro) throw() {
	unsigned int posicion_insercion = 0;
	bool menor = true;

	for (BloqueExternoBSharp::iterador_componentes actual = primer_registro; actual != ultimo_registro && menor; ++actual, ++posicion_insercion) {
		Registro::puntero registroIterado = static_cast<Registro::puntero>(*primer_registro);
		if (!this->comparadorClave->es_menor(this->clave, registroIterado, registro)) {
                	menor = false;
        	}
    	}
	return posicion_insercion;
}

unsigned int IndiceBSharp::buscar_posicion_insercion_interna(const Registro::puntero& registro, BloqueInternoBSharp::iterador_componentes primer_registro,
	BloqueInternoBSharp::iterador_componentes ultimo_registro) throw() {
	unsigned int posicion_insercion = 0;
	bool menor_igual = true;
	for (BloqueInternoBSharp::iterador_componentes actual = primer_registro; actual != ultimo_registro && menor_igual; ++actual, ++posicion_insercion) {
        	Registro::puntero registroIterado = static_cast<Registro::puntero>(*primer_registro);
	        if ((this->comparadorClave->es_menor(this->clave, registroIterado, registro)) ||
			(this->comparadorClave->es_igual(this->clave, registroIterado, registro))) {
        	} else {
                	menor_igual = false;
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
		streamSalida << "COMPONENTES BLOQUE: ";
		Bloque::iterador_componentes_constante actualComponente = bloqueActual->primer_componente();
		Bloque::iterador_componentes_constante finComponente = bloqueActual->ultimo_componente();
		while (actualComponente != finComponente) {
			Registro::puntero registro = (Registro::puntero) *actualComponente;
			this->imprimir_registro(registro, streamSalida);
			++actualComponente;
		}
		if (bloqueActual->es_hoja()) {
                        streamSalida << "--EN BLOQUE HOJA--";
                        const BloqueExternoBSharp::puntero& bloqueExterno = static_cast<BloqueExternoBSharp::puntero>(bloqueActual);
                        streamSalida << "CON SIGUIENTE: " << bloqueExterno->obtener_bloque_siguiente() << " ";
			streamSalida << std::endl;
	                streamSalida << std::endl;
        	        streamSalida << std::endl;
                } else {
                        streamSalida << "--EN BLOQUE INTERNO--";
                        const BloqueInternoBSharp::puntero& bloqueInterno = static_cast<BloqueInternoBSharp::puntero>(bloqueActual);
                        BloqueInternoBSharp::iterador_rama_constante actualRama = bloqueInterno->primer_rama();
                        BloqueInternoBSharp::iterador_rama_constante finRama = bloqueInterno->ultima_rama();
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
