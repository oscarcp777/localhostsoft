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
	int respuesta = INSERCION_CORRECTA;
	if (this->bloqueRaiz->es_hoja()) {
		BloqueExternoBSharp::puntero bloqueExterno = static_cast<BloqueExternoBSharp::puntero>(this->bloqueRaiz);
		respuesta = this->insertar_bloque_externo(bloqueExterno, registro, resultadoInsercion, 0);
	} else {
		BloqueInternoBSharp::puntero bloqueInterno = static_cast<BloqueInternoBSharp::puntero>(this->bloqueRaiz);
		//ACA EL HERMANO VA EN NULL PORQUE LA RAIZ NO TIENE HERMANOS
		Registro::puntero aux = NULL;
		respuesta = this->insertar_bloque_interno(bloqueInterno, registro, resultadoInsercion, 0, aux);
	}

	if (respuesta == HAY_SOBREFLUJO) {
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
//quiero usar polimorfismo con los bloques internos y externos
void IndiceBSharp::juntarListasComponentes(Bloque::contenedor_componentes& lista_registros,
		Bloque::contenedor_componentes& registrosBloqueIzquierdo,Bloque::contenedor_componentes& registrosBloqueDerecho)throw(){

	//Arma la lista de registros ordenada entre ambos bloques
	Bloque::iterador_componentes componenteListaBloque = registrosBloqueIzquierdo.begin();
	while (componenteListaBloque != registrosBloqueIzquierdo.end()){
		lista_registros.push_back(*componenteListaBloque);
		componenteListaBloque++;
	}
	componenteListaBloque = registrosBloqueDerecho.begin();
	while (componenteListaBloque != registrosBloqueDerecho.end()){
		lista_registros.push_back(*componenteListaBloque);
		componenteListaBloque++;
	}
}
void::IndiceBSharp::juntarListaRamas(BloqueInternoBSharp::contenedor_ramas& lista_ramas,BloqueInternoBSharp::contenedor_ramas& ramasBloqueIzquierdo,
BloqueInternoBSharp::contenedor_ramas& ramasBloqueDerecho)throw(){
	//Arma la lista de ramas ordenada entre ambos bloques
	BloqueInternoBSharp::iterador_rama ramaListaBloque = ramasBloqueIzquierdo.begin();
	while (ramaListaBloque != ramasBloqueIzquierdo.end()){
		lista_ramas.push_back(*ramaListaBloque);
		ramaListaBloque++;
	}
	ramaListaBloque = ramasBloqueDerecho.begin();
	while (ramaListaBloque != ramasBloqueDerecho.end()){
		lista_ramas.push_back(*ramaListaBloque);
		ramaListaBloque++;
	}
}
bool IndiceBSharp::balancearBloquesExternos(const Registro::puntero& registro, BloqueExternoBSharp::puntero& bloqueActual,
								BloqueExternoBSharp::puntero& bloqueHermano, ResultadoInsercion& resultado) throw(){
	//SE BALANCEA POR TAMAÑO
	//SE LLENA EL BLOQUE DE LA IZQUIERDA LO MAS POSIBLE, LUEGO SE INTENTA LLENAR EL DE LA DERECHA

	if (bloqueHermano == NULL)
		return false;

	// Crea contenedor de componentes para insertar ordenado el registro...
	BloqueExternoBSharp::contenedor_componentes lista_registros;

	//Registro menor del bloque actual
	Registro::puntero registroActual = static_cast<Registro::puntero>(*(bloqueActual->primer_componente()));

	//Registro menor bloque hermano
	Registro::puntero registroHermano = static_cast<Registro::puntero>(*(bloqueHermano->primer_componente()));

	BloqueExternoBSharp::puntero bloqueIzquierdo;
	BloqueExternoBSharp::puntero bloqueDerecho;
	BloqueExternoBSharp::contenedor_componentes registrosBloqueIzquierdo;
	BloqueExternoBSharp::contenedor_componentes registrosBloqueDerecho;

	//Diferencio cual es el bloque izquierdo del derecho
	if (this->comparadorClave->es_menor(this->clave, registroActual, registroHermano)) {
		bloqueActual->transferir_componentes(registrosBloqueIzquierdo);
		bloqueHermano->transferir_componentes(registrosBloqueDerecho);
		bloqueIzquierdo = bloqueActual;
		bloqueDerecho = bloqueHermano;
	}else{
		bloqueHermano->transferir_componentes(registrosBloqueIzquierdo);
		bloqueActual->transferir_componentes(registrosBloqueDerecho);
		bloqueIzquierdo = bloqueHermano;
		bloqueDerecho = bloqueActual;
	}
//	//Arma la lista de registros ordenada entre ambos bloques
//	BloqueExternoBSharp::iterador_componentes componenteListaBloque = registrosBloqueIzquierdo.begin();
//	while (componenteListaBloque != registrosBloqueIzquierdo.end()){
//		lista_registros.push_back(*componenteListaBloque);
//		componenteListaBloque++;
//	}
//	componenteListaBloque = registrosBloqueDerecho.begin();
//	while (componenteListaBloque != registrosBloqueDerecho.end()){
//		lista_registros.push_back(*componenteListaBloque);
//		componenteListaBloque++;
//	}
//remplazo por:
	this->juntarListasComponentes(lista_registros,registrosBloqueIzquierdo,registrosBloqueDerecho);


	// Busca posicion de insercion para el registro...
	unsigned int posicion_insercion = buscar_posicion_insercion_externa(registro, lista_registros.begin(), lista_registros.end());

	// Inserta ordenado el registro
	lista_registros.insert(lista_registros.begin() + posicion_insercion, registro);

	//SACAR
//			std::cout<<"LISTA ENTERA: "<< std::endl;
//			BloqueExternoBSharp::iterador_componentes actual3 = lista_registros.begin();
//			while (actual3 != lista_registros.end()){
//				Registro::puntero registroAux = static_cast<Registro::puntero>(*actual3);
//				imprimir_registro(registroAux,std::cout);
//				actual3++;
//			}
//			std::cout<<"FIN LISTA ENTERA: "<< std::endl;



	BloqueExternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
	while (bloqueIzquierdo->puede_agregar_componente(*componenteListaFinal)){
		bloqueIzquierdo->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
	}

	// Establece el elemento medio a subir en el resultado de insercion
	Registro::puntero copia = resultado.obtener_registro_clave_media();
	resultado.establecer_registro_clave_media(this->extraer_clave(*componenteListaFinal));
	while (componenteListaFinal != lista_registros.end()){
		if (bloqueDerecho->puede_agregar_componente(*componenteListaFinal))
			bloqueDerecho->agregar_componente(*componenteListaFinal);
		else
			break;
		componenteListaFinal++;
	}

	if (componenteListaFinal != lista_registros.end()){
		std::cout<<"No se puede hacer balanceo externo"<<std::endl;
		bloqueIzquierdo->vaciar_componentes();
		BloqueExternoBSharp::iterador_componentes componenteListaBloque = registrosBloqueIzquierdo.begin();
		while (componenteListaBloque != registrosBloqueIzquierdo.end()){
			bloqueIzquierdo->agregar_componente(*componenteListaBloque);
			componenteListaBloque++;
		}
		bloqueDerecho->vaciar_componentes();
		componenteListaBloque = registrosBloqueDerecho.begin();
		while (componenteListaBloque != registrosBloqueDerecho.end()){
			bloqueDerecho->agregar_componente(*componenteListaBloque);
			componenteListaBloque++;
		}

		resultado.establecer_registro_clave_media(copia);

		registrosBloqueIzquierdo.clear();
		registrosBloqueDerecho.clear();
		return false;
	}
	else{
		std::cout<<"Si se puede hacer balanceo externo"<<std::endl;
		// Escribe bloque izquierdo
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo, this->archivoIndice);
		// Escribe bloque derecho
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueDerecho->obtener_numero_bloque(), bloqueDerecho, this->archivoIndice);

		return true;
	}


}

int IndiceBSharp::insertar_bloque_externo(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro,
					ResultadoInsercion& resultado, unsigned int bloque_hermano) throw() {
	// Consideramos que no hay sobreflujo
	int respuesta = INSERCION_CORRECTA;

	// Verifica que el bloque externo puede agregar el registro
	if (bloqueExterno->puede_agregar_componente(registro)) {
		// Agrega el registro en el bloque externo no lleno
		this->insertar_bloque_externo_no_lleno(bloqueExterno, registro);
	} else {
		// LEO BLOQUE DE LA DIR DEL HERMANO
		BloqueExternoBSharp::puntero bloqueRamaHermana;
		if (bloque_hermano != 0)
			bloqueRamaHermana = this->estrategiaAlmacenamiento->leer_bloque(bloque_hermano, this->archivoIndice);
		else
			bloqueRamaHermana = NULL;

		// BALANCEO
		if (this->balancearBloquesExternos(registro,bloqueExterno,bloqueRamaHermana,resultado)){
			// Hubo balanceo
			respuesta = HAY_BALANCEO;
		}else{
			// Hubo sobreflujo
			respuesta = HAY_SOBREFLUJO;
			// Agrega el registro en el bloque externo lleno
			this->insertar_bloque_externo_lleno(bloqueExterno, registro, resultado);
		}
	}
	return respuesta;
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

	//DONI-FAQ    BALANCEAR POR TAMAÑO NO BUSCAR ELEMENTO MEDIO DE LA LISTA
	//SE LLENA EL BLOQUE DE LA DERECHA HASTA SUPERAR LOS 2/3, LUEGO SE CARGA EL
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
/////////////////////////////////
void IndiceBSharp::insertar_bloque_externo_lleno2(BloqueExternoBSharp::puntero& bloqueExterno,BloqueExternoBSharp::puntero& bloqueHermano, const Registro::puntero& registro,
				ResultadoInsercion& resultado) throw(){
	// Busco numero de bloque libre
		unsigned int numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
		// Creo nuevo bloque externo para dividir bloque..
		BloqueExternoBSharp::puntero nuevoBloqueExterno = new BloqueExternoBSharp(this->longitud_bloque, numero_bloque_libre);

		// Crea contenedor de componentes para insertar ordenado el registro...
		BloqueExternoBSharp::contenedor_componentes lista_registros;

		// Transfiere todos los regsitros del bloque externo a la lista de registros para insertar ordenado el regitro...
		bloqueExterno->transferir_componentes(lista_registros);

		BloqueExternoBSharp::puntero bloqueIzquierdo;
		BloqueExternoBSharp::puntero bloqueDerecho;
		BloqueExternoBSharp::contenedor_componentes registrosBloqueIzquierdo;
		BloqueExternoBSharp::contenedor_componentes registrosBloqueDerecho;

		//Registro menor del bloque actual
		Registro::puntero registroActual = static_cast<Registro::puntero>(*(bloqueExterno->primer_componente()));
		//Registro menor bloque hermano
		Registro::puntero registroHermano = static_cast<Registro::puntero>(*(bloqueHermano->primer_componente()));

		//Diferencio cual es el bloque izquierdo del derecho
		if (this->comparadorClave->es_menor(this->clave, registroActual, registroHermano)) {
			bloqueExterno->transferir_componentes(registrosBloqueIzquierdo);
			bloqueHermano->transferir_componentes(registrosBloqueDerecho);
			bloqueIzquierdo = bloqueExterno;
			bloqueDerecho = bloqueHermano;
		}else{
			bloqueHermano->transferir_componentes(registrosBloqueIzquierdo);
			bloqueExterno->transferir_componentes(registrosBloqueDerecho);
			bloqueIzquierdo = bloqueHermano;
			bloqueDerecho = bloqueExterno;
		}

		this->juntarListasComponentes(lista_registros,registrosBloqueIzquierdo,registrosBloqueDerecho);
		// Busca posicion de insercion para el registro...
		unsigned int posicion_insercion = buscar_posicion_insercion_externa(registro, lista_registros.begin(), lista_registros.end());

		// Inserta ordenado el registro
		lista_registros.insert(lista_registros.begin() + posicion_insercion, registro);

		//DONI-FAQ    BALANCEAR POR TAMAÑO NO BUSCAR ELEMENTO MEDIO DE LA LISTA
		//SE LLENA EL BLOQUE DE LA DERECHA HASTA SUPERAR LOS 2/3, LUEGO SE CARGA EL
		// Obtiene elemento medio...
		////////BloqueExternoBSharp::iterador_componentes posicion_medio = lista_registros.begin() + (lista_registros.size() / 2);

		// Establece el elemento medio a subir en el resultado de insercion
		///////resultado.establecer_registro_clave_media(this->extraer_clave(*posicion_medio));

		// Inserta elementos a la izquierda del medio en bloque a dividir
		BloqueExternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
		while (bloqueIzquierdo->puede_agregar_componente(*componenteListaFinal)){
			bloqueIzquierdo->agregar_componente(*componenteListaFinal);
			componenteListaFinal++;
		}

		// Establece el elemento medio a subir en el resultado de insercion
		resultado.establecer_registro_clave_izq(this->extraer_clave(*componenteListaFinal));////MODIFICAR ESTABLECER CALVE IZQ
		while (bloqueDerecho->puede_agregar_componente(*componenteListaFinal)){
			bloqueDerecho->agregar_componente(*componenteListaFinal);
			componenteListaFinal++;
		}
		resultado.establecer_registro_clave_der(this->extraer_clave(*componenteListaFinal));////MODIFICAR ESTABLECER CALVE DER
		while (componenteListaFinal != lista_registros.end()){
			if (nuevoBloqueExterno->puede_agregar_componente(*componenteListaFinal))
				nuevoBloqueExterno->agregar_componente(*componenteListaFinal);
			else
				break;
			componenteListaFinal++;
		}

		// Enlaza a los bloques
		nuevoBloqueExterno->establecer_bloque_siguiente(bloqueDerecho->obtener_bloque_siguiente());
		bloqueDerecho->establecer_bloque_siguiente(nuevoBloqueExterno->obtener_numero_bloque());

		// Actualiza espacio ocupado para el bloque a dividir
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo->obtener_longitud_ocupada());
		// Escribe bloque a dividir en disco
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo, this->archivoIndice);
		// Actualiza espacio ocupado para el bloque a dividir
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueDerecho->obtener_numero_bloque(), bloqueDerecho->obtener_longitud_ocupada());
		// Escribe bloque a dividir en disco
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueDerecho->obtener_numero_bloque(), bloqueDerecho, this->archivoIndice);
		// Actualiza espacio ocupado para el bloque nuevo
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueExterno->obtener_numero_bloque(), nuevoBloqueExterno->obtener_longitud_ocupada());
		// Escribe bloque nuevo
		this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueExterno->obtener_numero_bloque(), nuevoBloqueExterno, this->archivoIndice);

		// Establece numero de bloque izquierdo en resultado de insercion
		resultado.establecer_bloque_izquierdo(bloqueIzquierdo->obtener_numero_bloque());
		// Establece numero de bloque medio en resultado de insercion
		resultado.establecer_bloque_medio(bloqueDerecho->obtener_numero_bloque());
		// Establece numero de bloque derecho en resultado de insercion
		resultado.establecer_bloque_derecho(nuevoBloqueExterno->obtener_numero_bloque());
}
///////////////////////////////////
bool IndiceBSharp::balancearBloquesInternos(BloqueInternoBSharp::puntero& bloqueInterno, BloqueInternoBSharp::puntero& bloqueHermano, ResultadoInsercion& resultado, Registro::puntero& registroPadre) throw(){

	//SE BALANCEA POR TAMAÑO
	//SE LLENA EL BLOQUE DE LA IZQUIERDA LO MAS POSIBLE, LUEGO SE INTENTA LLENAR EL DE LA DERECHA

	if (bloqueHermano == NULL)
		return false;


	const Registro::puntero& registroClave = resultado.obtener_registro_clave_media();
	unsigned int bloque_izquierdo = resultado.obtener_bloque_izquierdo();
	unsigned int bloque_derecho = resultado.obtener_bloque_derecho();

	// Crea contenedor de componentes para insertar ordenado el registro...
	BloqueInternoBSharp::contenedor_componentes lista_registros;
	// Crea contenedor de ramas para insertar la rama nueva...
	BloqueInternoBSharp::contenedor_ramas lista_ramas;


	//Registro menor del bloque actual
	Registro::puntero registroActual = static_cast<Registro::puntero>(*(bloqueInterno->primer_componente()));

	//Registro menor bloque hermano
	Registro::puntero registroHermano = static_cast<Registro::puntero>(*(bloqueHermano->primer_componente()));


	BloqueInternoBSharp::puntero bloqueIzquierdo;
	BloqueInternoBSharp::puntero bloqueDerecho;
	BloqueInternoBSharp::contenedor_componentes registrosBloqueIzquierdo;
	BloqueInternoBSharp::contenedor_componentes registrosBloqueDerecho;
	BloqueInternoBSharp::contenedor_ramas ramasBloqueIzquierdo;
	BloqueInternoBSharp::contenedor_ramas ramasBloqueDerecho;

	//Diferencio cual es el bloque izquierdo del derecho
	if (this->comparadorClave->es_menor(this->clave, registroActual, registroHermano)) {
		bloqueInterno->transferir_componentes(registrosBloqueIzquierdo);
		bloqueHermano->transferir_componentes(registrosBloqueDerecho);
		bloqueInterno->transferir_ramas(ramasBloqueIzquierdo);
		bloqueInterno->transferir_ramas(ramasBloqueDerecho);
		bloqueIzquierdo = bloqueInterno;
		bloqueDerecho = bloqueHermano;
	}else{
		bloqueHermano->transferir_componentes(registrosBloqueIzquierdo);
		bloqueInterno->transferir_componentes(registrosBloqueDerecho);
		bloqueHermano->transferir_ramas(ramasBloqueIzquierdo);
		bloqueInterno->transferir_ramas(ramasBloqueDerecho);
		bloqueIzquierdo = bloqueHermano;
		bloqueDerecho = bloqueInterno;
	}

//	//Arma la lista de registros ordenada entre ambos bloques
//	BloqueInternoBSharp::iterador_componentes componenteListaBloque = registrosBloqueIzquierdo.begin();
//	while (componenteListaBloque != registrosBloqueIzquierdo.end()){
//		lista_registros.push_back(*componenteListaBloque);
//		componenteListaBloque++;
//	}
//	componenteListaBloque = registrosBloqueDerecho.begin();
//	while (componenteListaBloque != registrosBloqueDerecho.end()){
//		lista_registros.push_back(*componenteListaBloque);
//		componenteListaBloque++;
//	}
////reemplazo por:

	this->juntarListasComponentes(lista_registros,registrosBloqueIzquierdo,registrosBloqueDerecho);

//	//Arma la lista de ramas ordenada entre ambos bloques
//	BloqueInternoBSharp::iterador_rama ramaListaBloque = ramasBloqueIzquierdo.begin();
//	while (ramaListaBloque != ramasBloqueIzquierdo.end()){
//		lista_ramas.push_back(*ramaListaBloque);
//		ramaListaBloque++;
//	}
//	ramaListaBloque = ramasBloqueDerecho.begin();
//	while (ramaListaBloque != ramasBloqueDerecho.end()){
//		lista_ramas.push_back(*ramaListaBloque);
//		ramaListaBloque++;
//	}
	this->juntarListaRamas(lista_ramas,ramasBloqueIzquierdo,ramasBloqueDerecho);
	// Busca posicion de insercion para el registro padre...
	unsigned int posicion_insercion = buscar_posicion_insercion_interna(registroPadre, lista_registros.begin(), lista_registros.end());

	// Inserta ordenado el registro padre
	lista_registros.insert(lista_registros.begin() + posicion_insercion, registroPadre);

	// Busca posicion de insercion para el registro padre...
	posicion_insercion = buscar_posicion_insercion_interna(registroClave, lista_registros.begin(), lista_registros.end());

	// Inserta ordenado el registro padre
	lista_registros.insert(lista_registros.begin() + posicion_insercion, registroClave);

	// Inserta la rama
	lista_ramas.insert(lista_ramas.begin() + posicion_insercion + 1, bloque_derecho);



	//SACAR
//	std::cout<<"LISTA ENTERA COMPONENTES: "<< std::endl;
//	BloqueInternoBSharp::iterador_componentes componenteActual = lista_registros.begin();
//	while (componenteActual != lista_registros.end()){
//		Registro::puntero registroAux = static_cast<Registro::puntero>(*componenteActual);
//		imprimir_registro(registroAux,std::cout);
//		componenteActual++;
//	}
//	std::cout<<"FIN LISTA ENTERA COMPONENTES: "<< std::endl;
//
//	std::cout<<"LISTA ENTERA RAMAS: "<< std::endl;
//	BloqueInternoBSharp::iterador_rama ramaActual = lista_ramas.begin();
//	while (ramaActual != lista_ramas.end()){
//		std::cout<<"RAMA: "<<*ramaActual<<" - ";
//		ramaActual++;
//	}
//	std::cout<<"FIN LISTA ENTERA RAMAS: "<< std::endl;


	BloqueInternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
	BloqueInternoBSharp::iterador_rama ramaListaFinal = lista_ramas.begin();
	bloqueIzquierdo->agregar_rama(*ramaListaFinal);
	ramaListaFinal++;
	while (bloqueIzquierdo->puede_agregar_componente(*componenteListaFinal)){
		Registro::puntero registroAux = static_cast<Registro::puntero>(*componenteListaFinal);
		imprimir_registro(registroAux,std::cout);
		std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
		bloqueIzquierdo->agregar_rama(*ramaListaFinal);
		bloqueIzquierdo->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
		ramaListaFinal++;
	}
	std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
	bloqueDerecho->agregar_rama(*ramaListaFinal);
	ramaListaFinal++;
	// Establece el elemento medio a subir en el resultado de insercion
	Registro::puntero copia = resultado.obtener_registro_clave_media();
	resultado.establecer_registro_clave_media(this->extraer_clave(*componenteListaFinal));
	componenteListaFinal++;
	while (componenteListaFinal != lista_registros.end()){
		if (bloqueDerecho->puede_agregar_componente(*componenteListaFinal)){
			Registro::puntero registroAux = static_cast<Registro::puntero>(*componenteListaFinal);
					imprimir_registro(registroAux,std::cout);
					std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
			bloqueDerecho->agregar_rama(*ramaListaFinal);
			bloqueDerecho->agregar_componente(*componenteListaFinal);
		}
		else
			break;
		componenteListaFinal++;
		ramaListaFinal++;
	}

	if (componenteListaFinal != lista_registros.end()){
			std::cout<<"No se puede hacer balanceo interno"<<std::endl;
			bloqueIzquierdo->vaciar_componentes();
			BloqueInternoBSharp::iterador_componentes componenteListaBloque = registrosBloqueIzquierdo.begin();
			while (componenteListaBloque != registrosBloqueIzquierdo.end()){
				bloqueIzquierdo->agregar_componente(*componenteListaBloque);
				componenteListaBloque++;
			}
			bloqueDerecho->vaciar_componentes();
			componenteListaBloque = registrosBloqueDerecho.begin();
			while (componenteListaBloque != registrosBloqueDerecho.end()){
				bloqueDerecho->agregar_componente(*componenteListaBloque);
				componenteListaBloque++;
			}
			registrosBloqueIzquierdo.clear();
			registrosBloqueDerecho.clear();

			//SACAR
//			std::cout<<"LISTA COMPONENTES BLOQUE IZQ: "<< std::endl;
//			std::cout << "NUMERO BLOQUE: " << bloqueIzquierdo->obtener_numero_bloque() << " ";
//			std::cout << "NIVEL: " << bloqueIzquierdo->obtener_nivel() << " ";
//			std::cout << "COMPONENTES BLOQUE: ";
//			Bloque::iterador_componentes_constante act = bloqueIzquierdo->primer_componente();
//			Bloque::iterador_componentes_constante fin = bloqueIzquierdo->ultimo_componente();
//			while (act != fin) {
//				Registro::puntero registro = (Registro::puntero) *act;
//				this->imprimir_registro(registro, std::cout);
//				++act;
//					}
//			std::cout<<" FIN LISTA COMPONENTES BLOQUE IZQ "<< std::endl;
//
//			std::cout<<"LISTA COMPONENTES BLOQUE DER: "<< std::endl;
//			std::cout << "NUMERO BLOQUE: " << bloqueDerecho->obtener_numero_bloque() << " ";
//			std::cout << "NIVEL: " << bloqueDerecho->obtener_nivel() << " ";
//			std::cout << "COMPONENTES BLOQUE: ";
//			act = bloqueDerecho->primer_componente();
//			fin = bloqueDerecho->ultimo_componente();
//			while (act != fin) {
//				Registro::puntero registro = (Registro::puntero) *act;
//				this->imprimir_registro(registro, std::cout);
//				++act;
//			}
//			std::cout<<" FIN LISTA COMPONENTES BLOQUE DER "<< std::endl;

			bloqueIzquierdo->vaciar_ramas();
			BloqueInternoBSharp::iterador_rama ramaListaBloque = ramasBloqueIzquierdo.begin();
			while (ramaListaBloque != ramasBloqueIzquierdo.end()){
				bloqueIzquierdo->agregar_rama(*ramaListaBloque);
				ramaListaBloque++;
			}
			bloqueDerecho->vaciar_ramas();
			ramaListaBloque = ramasBloqueDerecho.begin();
			while (ramaListaBloque != ramasBloqueDerecho.end()){
				bloqueDerecho->agregar_rama(*ramaListaBloque);
				ramaListaBloque++;
			}
			ramasBloqueIzquierdo.clear();
			ramasBloqueDerecho.clear();

			resultado.establecer_registro_clave_media(copia);

			//SACAR
//			std::cout<<"LISTA RAMAS IZQ: "<< std::endl;
//			BloqueInternoBSharp::iterador_rama_constante actualRama = bloqueIzquierdo->primer_rama();
//			BloqueInternoBSharp::iterador_rama_constante finRama = bloqueIzquierdo->ultima_rama();
//			std::cout << "RAMAS(";
//			while (actualRama != finRama) {
//				std::cout << " " << *actualRama;
//			    ++actualRama;
//			}
//			std::cout << ")";
//			std::cout << std::endl;
//			std::cout<<"FIN LISTA RAMAS IZQ: "<< std::endl;
//
//			std::cout<<"LISTA RAMAS DER: "<< std::endl;
//			actualRama = bloqueDerecho->primer_rama();
//			finRama = bloqueDerecho->ultima_rama();
//			std::cout << "RAMAS(";
//			while (actualRama != finRama) {
//				std::cout << " " << *actualRama;
//				++actualRama;
//			}
//			std::cout << ")";
//			std::cout << std::endl;
//			std::cout<<"FIN LISTA RAMAS DER: "<< std::endl;

			return false;
		}
		else{
			std::cout<<"Si se puede hacer balanceo interno"<<std::endl;
			// Escribe bloque izquierdo
			this->estrategiaAlmacenamiento->escribir_bloque(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo, this->archivoIndice);
			// Escribe bloque derecho
			this->estrategiaAlmacenamiento->escribir_bloque(bloqueDerecho->obtener_numero_bloque(), bloqueDerecho, this->archivoIndice);

			return true;
		}

	return false;

}

int IndiceBSharp::insertar_bloque_interno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave,
						ResultadoInsercion& resultado, unsigned int bloque_hermano, Registro::puntero& registroPadre) throw() {
	// Considero que no hay sobreflujo al insertar en el bloque interno
	int respuesta = INSERCION_CORRECTA;
	// Busco la rama por la cual insertar
	int rama_insertar = this->buscar_rama(bloqueInterno, registroClave);
	std::cout<<"Rama: "<< rama_insertar<<std::endl;
	//OBTENER RAMA HERMANA PARA ENVIAR A LOS INSERTAR DE MAS ABAJO, ES LA RAMA DERECHA POR DEFECTO, SINO LA IZQ
	int rama_hermana = this->buscar_rama_hermana(bloqueInterno, registroClave);
	std::cout<<"Rama Hermana: "<< rama_hermana<<std::endl;


	//Obtengo elemento actual del bloque por el cual bajo a la rama siguiente
	BloqueInternoBSharp::iterador_componentes_constante actualComponente = bloqueInterno->primer_componente();
	BloqueInternoBSharp::iterador_componentes_constante finComponente = bloqueInterno->ultimo_componente();
	--finComponente;
	while (actualComponente != finComponente) {
		if (this->comparadorClave->es_menor(this->clave, registroClave, Registro::puntero(*actualComponente))) {
			break;
		}
		actualComponente++;
	}

	// Leo el bloque por el cual insertar
	BloqueBSharp::puntero bloqueRamaInsertar = this->estrategiaAlmacenamiento->leer_bloque(rama_insertar, this->archivoIndice);
	// Si el bloque existe
	if (bloqueRamaInsertar != NULL) {
		// Considero que no hay sobreflujo al insertar en el bloque hijo
		int respuestaHijo = INSERCION_CORRECTA;
		if (bloqueRamaInsertar->es_hoja()) {
			//MANDAR TAMBIEN POR PARAMETRO EL NUMERO DE BLOQUE QUE CONSEGUI
			BloqueExternoBSharp::puntero bloqueExternoInsertar(bloqueRamaInsertar);
			// Inserto en el bloque externo hijo
			respuestaHijo = this->insertar_bloque_externo(bloqueExternoInsertar, registroClave, resultado, rama_hermana);
		} else {
			BloqueInternoBSharp::puntero bloqueInternoInsertar(bloqueRamaInsertar);
			Registro::puntero registroPadreHijo = (Registro::puntero) *actualComponente;
			// Inserto en el bloque interno hijo
			respuestaHijo = this->insertar_bloque_interno(bloqueInternoInsertar, registroClave, resultado, rama_hermana, registroPadreHijo);
		}

		//Se actualiza la clave cuando hay balanceo en el hijo
		if (respuestaHijo == HAY_BALANCEO){
			// Agrego componente
			Registro::puntero registroAReemplazar = (Registro::puntero) *actualComponente;
			std::cout << "Registro a reemplazar: ";
			this->imprimir_registro(registroAReemplazar, std::cout);
			std::cout<< std::endl;
			std::cout << "Registro a subir: ";
			this->imprimir_registro(resultado.obtener_registro_clave_media(), std::cout);
			std::cout<< std::endl;
			bloqueInterno->reemplazar_componente(registroAReemplazar, resultado.obtener_registro_clave_media());

//SACAR
//			//Imprimir componentes bloque
//			std::cout << "NUMERO BLOQUE: " << bloqueInterno->obtener_numero_bloque() << " ";
//			std::cout << "NIVEL: " << bloqueInterno->obtener_nivel() << " ";
//			std::cout << "COMPONENTES BLOQUE: ";
//			actualComponente = bloqueInterno->primer_componente();
//			while (actualComponente != finComponente) {
//				Registro::puntero registro = (Registro::puntero) *actualComponente;
//				this->imprimir_registro(registro, std::cout);
//				++actualComponente;
//			}
			// Escribo bloque
			this->estrategiaAlmacenamiento->escribir_bloque(bloqueInterno->obtener_numero_bloque(), bloqueInterno, this->archivoIndice);
		}

		// Verifico si hubo sobrelujo al insertar en el bloque hijo
		if (respuestaHijo == HAY_SOBREFLUJO) {
			// Verifico si puedo agregar en el bloque interno
			if (bloqueInterno->puede_agregar_componente(resultado.obtener_registro_clave_media())) {
				// Inserto en el bloque interno no lleno
				//ESTE RESULTADO VA A TENER DOS CLAVES, LA 1 Y LA DOS, DESAPARECE CLAVE MEDIA
				//Y TAMBIEN TRES BLOQUES (IZQ, CENTRAL, DERECHO)
				this->insertar_bloque_interno_no_lleno(bloqueInterno, resultado.obtener_registro_clave_media(),
					resultado.obtener_bloque_izquierdo(),
					resultado.obtener_bloque_derecho());
			} else {

				// LEO BLOQUE DE LA DIR DEL HERMANO
				BloqueInternoBSharp::puntero bloqueRamaHermana;
				if (bloque_hermano != 0)
					bloqueRamaHermana = this->estrategiaAlmacenamiento->leer_bloque(bloque_hermano, this->archivoIndice);
				else
					bloqueRamaHermana = NULL;



				// BALANCEO
				if (registroPadre != NULL){
					std::cout << "Registro Padre: ";
					imprimir_registro(registroPadre,std::cout);
					std::cout<< std::endl;
				}
				if (this->balancearBloquesInternos(bloqueInterno, bloqueRamaHermana, resultado, registroPadre)){
					// Hubo balanceo
					respuesta = HAY_BALANCEO;
				}else{
					// Inserto en el bloque interno lleno
					respuesta = HAY_SOBREFLUJO;

					this->insertar_bloque_interno_lleno(bloqueInterno, resultado.obtener_registro_clave_media(),
							resultado.obtener_bloque_izquierdo(),
							resultado.obtener_bloque_derecho(), resultado);
				}
			}
		}
	}
	return respuesta;
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

	for (BloqueExternoBSharp::iterador_componentes actual = primer_registro; actual != ultimo_registro && menor; actual++, posicion_insercion++) {
		Registro::puntero registroIterado = static_cast<Registro::puntero>(*actual);
		if (!this->comparadorClave->es_menor(this->clave, registroIterado, registro)) {
                	menor = false;
                	break;
        	}
    	}
	return posicion_insercion;
}

unsigned int IndiceBSharp::buscar_posicion_insercion_interna(const Registro::puntero& registro, BloqueInternoBSharp::iterador_componentes primer_registro,
	BloqueInternoBSharp::iterador_componentes ultimo_registro) throw() {
	unsigned int posicion_insercion = 0;
	bool menor_igual = true;
	for (BloqueInternoBSharp::iterador_componentes actual = primer_registro; actual != ultimo_registro && menor_igual; ++actual, ++posicion_insercion) {
        	Registro::puntero registroIterado = static_cast<Registro::puntero>(*actual);
	        if ((this->comparadorClave->es_menor(this->clave, registroIterado, registro)) ||
			(this->comparadorClave->es_igual(this->clave, registroIterado, registro))) {
        	} else {
                	menor_igual = false;
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

int IndiceBSharp::buscar_rama_hermana(const BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro) throw() {
	BloqueInternoBSharp::iterador_componentes_constante actualComponente = bloqueInterno->primer_componente();
	BloqueInternoBSharp::iterador_componentes_constante finComponente = bloqueInterno->ultimo_componente();
	unsigned int rama_hermana = 0;
	unsigned int posicion_rama = 0;

	while (actualComponente != finComponente) {
			if (this->comparadorClave->es_menor(this->clave, registro, Registro::puntero(*actualComponente))) {
				break;
			}
			++actualComponente;
			++posicion_rama;
	}

	if (actualComponente == finComponente) {
		rama_hermana = posicion_rama - 1;
	}
	else{
		rama_hermana = posicion_rama + 1;
	}

	return bloqueInterno->obtener_rama(rama_hermana);
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
		streamSalida << "--ESPACIO OCUPADO-- " << bloqueActual->obtener_longitud_ocupada();
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
			std::cout << "RAMAS(";
                        while (actualRama != finRama) {
                                streamSalida << " " << *actualRama;
                                ++actualRama;
                        }
                        streamSalida << ")";
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
	streamSalida << "(";
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
	streamSalida << ") ";
}
