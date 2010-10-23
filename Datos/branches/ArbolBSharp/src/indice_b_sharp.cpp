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
		//ACA EL HERMANO VA EN 0 PORQUE LA RAIZ NO TIENE HERMANOS
		Registro::puntero aux = NULL;
		respuesta = this->insertar_bloque_interno(bloqueInterno, registro, resultadoInsercion, 0, aux);
	}

	if (respuesta == HAY_SOBREFLUJO) {
		if(this->bloqueRaiz->es_hoja())
			this->manejarDivisionRaizHoja(resultadoInsercion, registro);
		else
			this->manejarDivisionRaizInterna(resultadoInsercion);
	}
}

void IndiceBSharp::borrar_registro(Registro::puntero registro) throw() {
	ResultadoBalanceo resultadoBalanceo;
	ResultadoInsercion resultadoInsercion;
	int respuesta = ELIMINACION_CORRECTA;
	if (this->bloqueRaiz->es_hoja()) {
		BloqueExternoBSharp::puntero bloqueExterno = static_cast<BloqueExternoBSharp::puntero>(this->bloqueRaiz);
		respuesta = this->remover_bloque_externo(bloqueExterno, registro, resultadoInsercion, 0, 0);
	} else {
		BloqueInternoBSharp::puntero bloqueInterno = static_cast<BloqueInternoBSharp::puntero>(this->bloqueRaiz);
		respuesta = this->remover_bloque_interno(bloqueInterno, registro, resultadoBalanceo,resultadoInsercion, 0, 0);
	}

	if (respuesta == HAY_BALANCEO) {
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
	this->bloqueRaiz = new BloqueExternoBSharp(2*this->longitud_bloque, 0);
	// Ecscribe bloque raiz
	this->escribir_bloque_raiz();
}

void IndiceBSharp::leer_bloque_raiz() throw() {
	this->bloqueRaiz = this->estrategiaAlmacenamiento->leer_bloque_raiz(0, this->archivoIndice);
	if (bloqueRaiz == NULL) {
		this->crear_bloque_raiz();
	}
}

void IndiceBSharp::escribir_bloque_raiz() throw() {
	bool exitoso = this->estrategiaAlmacenamiento->escribir_bloque_raiz(0, this->bloqueRaiz, this->archivoIndice);
	if (!exitoso) {
		this->estrategiaEspacioLibre->buscar_espacio_libre();
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(0, this->bloqueRaiz->obtener_longitud_ocupada());
		std::cout<<"PORQUE ESTA ACA"<<std::endl;
//		this->estrategiaAlmacenamiento->agregar_bloque(this->bloqueRaiz, this->archivoIndice);
	}
}

void IndiceBSharp::manejarDivisionRaizHoja(ResultadoInsercion& resultado, const Registro::puntero& registro) throw() {
	unsigned int cont=0;
	unsigned int numero_bloque_libre;

	//Creo bloque izquierdo
	numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
	BloqueExternoBSharp::puntero nuevoBloqueIzq = new BloqueExternoBSharp(this->longitud_bloque, numero_bloque_libre);
	std::cout<<"Bloque izquierdo en pos: "<<numero_bloque_libre<<std::endl;

	//Creo bloque centro
	numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
	BloqueExternoBSharp::puntero nuevoBloqueCen = new BloqueExternoBSharp(this->longitud_bloque, numero_bloque_libre+1);
	std::cout<<"Bloque central en pos: "<<numero_bloque_libre+1<<std::endl;

	//Creo bloque derecho
	numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
	BloqueExternoBSharp::puntero nuevoBloqueDer = new BloqueExternoBSharp(this->longitud_bloque, numero_bloque_libre+2);
	std::cout<<"Bloque der en pos: "<<numero_bloque_libre+2<<std::endl;


	// Crea contenedor de componentes para insertar ordenado el registro...
	BloqueExternoBSharp::contenedor_componentes lista_registros;

	// Transfiere todos los regsitros del bloque raiz a la lista de registros para insertar ordenado el regitro...
	this->bloqueRaiz->transferir_componentes(lista_registros);

	// Busca posicion de insercion para el registro...
	unsigned int posicion_insercion = buscar_posicion_insercion_externa(registro, lista_registros.begin(), lista_registros.end());

	// Inserta ordenado el registro
	lista_registros.insert(lista_registros.begin() + posicion_insercion, registro);


	unsigned int peso_promedio = this->calcularPromedio(lista_registros.begin(), lista_registros.end());
	nuevoBloqueIzq->setPesoPromedio(peso_promedio);
	nuevoBloqueCen->setPesoPromedio(peso_promedio);
	nuevoBloqueDer->setPesoPromedio(peso_promedio);


	// Inserta elementos en bloque izquierdo
	BloqueExternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
	while (nuevoBloqueIzq->hay_subflujo((peso_promedio*lista_registros.size())/3)){
		nuevoBloqueIzq->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
		cont++;
	}

	// Establece primer elemento a insertar en la raiz
	resultado.establecer_registro_clave_izq(this->extraer_clave(*componenteListaFinal));

	// Inserta elementos en bloque central
	while (nuevoBloqueCen->hay_subflujo((peso_promedio*lista_registros.size())/3)){
		nuevoBloqueCen->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
		cont++;
	}

	// Establece segundo elemento a insertar en la raiz
	resultado.establecer_registro_clave_der(this->extraer_clave(*componenteListaFinal));

	// Inserta elementos en bloque derecho
	while (componenteListaFinal != lista_registros.end()){
		if (nuevoBloqueDer->puede_agregar_componente(*componenteListaFinal))
			nuevoBloqueDer->agregar_componente(*componenteListaFinal);
		else
			break;
		componenteListaFinal++;
		cont++;
	}

	if(cont!=lista_registros.size()){
		std::cout<<"###########################################################"<<std::endl;
		std::cout<<"############# DANGER SE PERDIO UN registro    ##############"<<std::endl;
		std::cout<<"###########################################################"<<std::endl;

		std::cout<<" CANTIDAD DE REGISTROS INSERTADOS "<<cont<<std::endl;
		std::cout<<" CANTIDAD DE REGISTROS "<<lista_registros.size()<<std::endl;
	}

	// Enlaza a los bloques
	nuevoBloqueIzq->establecer_bloque_siguiente(nuevoBloqueCen->obtener_numero_bloque());
	nuevoBloqueCen->establecer_bloque_siguiente(nuevoBloqueDer->obtener_numero_bloque());

	// Crea una nueva raiz
	BloqueInternoBSharp::puntero nuevoRaiz = new BloqueInternoBSharp(2*this->longitud_bloque, 0, this->bloqueRaiz->obtener_nivel() + 1);

	nuevoRaiz->agregar_rama(nuevoBloqueIzq->obtener_numero_bloque());
	nuevoRaiz->agregar_rama(nuevoBloqueCen->obtener_numero_bloque());
	nuevoRaiz->agregar_rama(nuevoBloqueDer->obtener_numero_bloque());

	nuevoRaiz->agregar_componente(resultado.obtener_registro_clave_izq());
	nuevoRaiz->agregar_componente(resultado.obtener_registro_clave_der());

	// Escribe el bloque raiz
	this->bloqueRaiz = nuevoRaiz;
	this->escribir_bloque_raiz();

	// Actualiza espacios ocupados
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueIzq->obtener_numero_bloque(), nuevoBloqueIzq->obtener_longitud_ocupada());
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueCen->obtener_numero_bloque(), nuevoBloqueCen->obtener_longitud_ocupada());
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueDer->obtener_numero_bloque(), nuevoBloqueDer->obtener_longitud_ocupada());
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(this->bloqueRaiz->obtener_numero_bloque(), this->bloqueRaiz->obtener_longitud_ocupada());

	// Escribe bloques en disco
	this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueIzq->obtener_numero_bloque(), nuevoBloqueIzq, this->archivoIndice);
	this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueCen->obtener_numero_bloque(), nuevoBloqueCen, this->archivoIndice);
	this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueDer->obtener_numero_bloque(), nuevoBloqueDer, this->archivoIndice);
	this->estrategiaAlmacenamiento->escribir_bloque_raiz(this->bloqueRaiz->obtener_numero_bloque(), this->bloqueRaiz, this->archivoIndice);

}



void IndiceBSharp::manejarDivisionRaizInterna(ResultadoInsercion& resultado) throw() {
	unsigned int cont=0;
	unsigned int numero_bloque_libre;
	BloqueInternoBSharp::puntero bloque_Raiz = static_cast<BloqueInternoBSharp::puntero>(this->bloqueRaiz);

	//Creo bloque izquierdo
	numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
	BloqueInternoBSharp::puntero nuevoBloqueIzq = new BloqueInternoBSharp(this->longitud_bloque, numero_bloque_libre, bloque_Raiz->obtener_nivel());
	std::cout<<"Bloque izquierdo en pos: "<<numero_bloque_libre<<std::endl;

	//Creo bloque centro
	numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
	BloqueInternoBSharp::puntero nuevoBloqueCen = new BloqueInternoBSharp(this->longitud_bloque, numero_bloque_libre+1, bloque_Raiz->obtener_nivel());
	std::cout<<"Bloque central en pos: "<<numero_bloque_libre+1<<std::endl;

	//Creo bloque derecho
	numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
	BloqueInternoBSharp::puntero nuevoBloqueDer = new BloqueInternoBSharp(this->longitud_bloque, numero_bloque_libre+2, bloque_Raiz->obtener_nivel());
	std::cout<<"Bloque der en pos: "<<numero_bloque_libre+2<<std::endl;


	// Crea contenedor de componentes para insertar ordenado el registro...
	BloqueInternoBSharp::contenedor_componentes lista_registros;

	// Crea contenedor de ramas para insertar la rama nueva...
	BloqueInternoBSharp::contenedor_ramas lista_ramas;


	// Transfiere todos los regsitros del bloque raiz a la lista de registros para insertar ordenado el regitro...
	bloque_Raiz->transferir_componentes(lista_registros);

	bloque_Raiz->transferir_ramas(lista_ramas);

	unsigned int posicion_insercion;
	// Busca posicion de insercion para el registro der...
	posicion_insercion = buscar_posicion_insercion_interna(resultado.obtener_registro_clave_der(), lista_registros.begin(), lista_registros.end());

	// Inserta ordenado el registro izq
	lista_registros.insert(lista_registros.begin() + posicion_insercion, resultado.obtener_registro_clave_der());

	// Inserta la rama
	lista_ramas.insert(lista_ramas.begin() + posicion_insercion + 1, resultado.obtener_bloque_derecho());

		std::cout<<"LISTA ENTERA RAMAS: "<< std::endl;
		BloqueInternoBSharp::iterador_rama ramaActual = lista_ramas.begin();
		while (ramaActual != lista_ramas.end()){
			std::cout<<"RAMA: "<<*ramaActual<<" - ";
			ramaActual++;
		}
		std::cout<<"FIN LISTA ENTERA RAMAS: "<< std::endl;

	// Calcula peso promedio
	//BloqueBSharp::pesoPromedio = this->calcularPromedio(lista_registros.begin(), lista_registros.end());

	unsigned int peso_promedio = this->calcularPromedio(lista_registros.begin(), lista_registros.end());
	nuevoBloqueIzq->setPesoPromedio(peso_promedio);
	nuevoBloqueCen->setPesoPromedio(peso_promedio);
	nuevoBloqueDer->setPesoPromedio(peso_promedio);

	// Inserta elementos en bloque izquierdo
	BloqueInternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
	BloqueInternoBSharp::iterador_rama ramaListaFinal = lista_ramas.begin();
	nuevoBloqueIzq->agregar_rama(*ramaListaFinal);
	std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
	ramaListaFinal++;
	while (nuevoBloqueIzq->hay_subflujo((peso_promedio*lista_registros.size())/3)){
		Registro::puntero registroAux = static_cast<Registro::puntero>(*componenteListaFinal);
		imprimir_registro(registroAux,std::cout);
		std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
		nuevoBloqueIzq->agregar_rama(*ramaListaFinal);
		nuevoBloqueIzq->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
		ramaListaFinal++;
		cont++;
	}

	std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
	nuevoBloqueCen->agregar_rama(*ramaListaFinal);
	ramaListaFinal++;

	// Establece primer elemento a insertar en la raiz
	resultado.establecer_registro_clave_izq(this->extraer_clave(*componenteListaFinal));
	componenteListaFinal++;
	cont++;

	// Inserta elementos en bloque central
	while (nuevoBloqueCen->hay_subflujo((peso_promedio*lista_registros.size())/3)){
		Registro::puntero registroAux = static_cast<Registro::puntero>(*componenteListaFinal);
		imprimir_registro(registroAux,std::cout);
		std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
		nuevoBloqueCen->agregar_rama(*ramaListaFinal);
		nuevoBloqueCen->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
		ramaListaFinal++;
		cont++;
	}

	std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
	nuevoBloqueDer->agregar_rama(*ramaListaFinal);
	ramaListaFinal++;

	// Establece segundo elemento a insertar en la raiz
	resultado.establecer_registro_clave_der(this->extraer_clave(*componenteListaFinal));
	componenteListaFinal++;
	cont++;

	// Inserta elementos en bloque derecho
	while (componenteListaFinal != lista_registros.end()){
		if (nuevoBloqueDer->puede_agregar_componente(*componenteListaFinal)){
			Registro::puntero registroAux = static_cast<Registro::puntero>(*componenteListaFinal);
			imprimir_registro(registroAux,std::cout);
			std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
			nuevoBloqueDer->agregar_rama(*ramaListaFinal);
			nuevoBloqueDer->agregar_componente(*componenteListaFinal);
		}else
			break;
		componenteListaFinal++;
		ramaListaFinal++;
		cont++;
	}

	if(cont!=lista_registros.size()){
		std::cout<<"###########################################################"<<std::endl;
		std::cout<<"############# DANGER SE PERDIO UN registro    ##############"<<std::endl;
		std::cout<<"###########################################################"<<std::endl;

		std::cout<<" CANTIDAD DE REGISTROS INSERTADOS "<<cont<<std::endl;
		std::cout<<" CANTIDAD DE REGISTROS "<<lista_registros.size()<<std::endl;
	}

	// Crea una nueva raiz
	BloqueInternoBSharp::puntero nuevoRaiz = new BloqueInternoBSharp(2*this->longitud_bloque, 0, this->bloqueRaiz->obtener_nivel() + 1);

	nuevoRaiz->agregar_rama(nuevoBloqueIzq->obtener_numero_bloque());
	nuevoRaiz->agregar_rama(nuevoBloqueCen->obtener_numero_bloque());
	nuevoRaiz->agregar_rama(nuevoBloqueDer->obtener_numero_bloque());

	nuevoRaiz->agregar_componente(resultado.obtener_registro_clave_izq());
	nuevoRaiz->agregar_componente(resultado.obtener_registro_clave_der());

	// Escribe el bloque raiz
	this->bloqueRaiz = nuevoRaiz;
	this->escribir_bloque_raiz();

	// Actualiza espacios ocupados
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueIzq->obtener_numero_bloque(), nuevoBloqueIzq->obtener_longitud_ocupada());
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueCen->obtener_numero_bloque(), nuevoBloqueCen->obtener_longitud_ocupada());
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueDer->obtener_numero_bloque(), nuevoBloqueDer->obtener_longitud_ocupada());
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(this->bloqueRaiz->obtener_numero_bloque(), this->bloqueRaiz->obtener_longitud_ocupada());

	// Escribe bloques en disco
	this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueIzq->obtener_numero_bloque(), nuevoBloqueIzq, this->archivoIndice);
	this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueCen->obtener_numero_bloque(), nuevoBloqueCen, this->archivoIndice);
	this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueDer->obtener_numero_bloque(), nuevoBloqueDer, this->archivoIndice);
	this->estrategiaAlmacenamiento->escribir_bloque_raiz(this->bloqueRaiz->obtener_numero_bloque(), this->bloqueRaiz, this->archivoIndice);

}

void IndiceBSharp::manejar_subflujo_raiz() throw() {
	if (!bloqueRaiz->es_hoja()) {
		BloqueInternoBSharp::puntero bloqueRaizInterno = static_cast<BloqueInternoBSharp::puntero>(this->bloqueRaiz);
		if (bloqueRaizInterno->cantidad_componentes() == 1){
			unsigned int cont=0;
			BloqueExternoBSharp::puntero nuevaRaiz = new BloqueExternoBSharp(2*this->longitud_bloque, 0);

			BloqueInternoBSharp::iterador_rama actualRama = bloqueRaizInterno->primer_rama();
			BloqueExternoBSharp::puntero bloquePrimerHijo = this->estrategiaAlmacenamiento->leer_bloque(*actualRama, this->archivoIndice);
			BloqueExternoBSharp::puntero bloqueSegundoHijo = this->estrategiaAlmacenamiento->leer_bloque(*(++actualRama), this->archivoIndice);

			BloqueExternoBSharp::contenedor_componentes registrosBloqueIzquierdo;
			BloqueExternoBSharp::contenedor_componentes registrosBloqueDerecho;

			bloquePrimerHijo->transferir_componentes(registrosBloqueIzquierdo);
			bloqueSegundoHijo->transferir_componentes(registrosBloqueDerecho);

			// Crea contenedor de componentes para insertar ordenado el registro...
			BloqueInternoBSharp::contenedor_componentes lista_registros;

			this->juntarListasComponentes(lista_registros,registrosBloqueIzquierdo,registrosBloqueDerecho);

			BloqueExternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
			while (componenteListaFinal != lista_registros.end()){
					if (nuevaRaiz->puede_agregar_componente(*componenteListaFinal))
						nuevaRaiz->agregar_componente(*componenteListaFinal);
					else
						break;
					componenteListaFinal++;
					cont++;
			}

			if(cont!=lista_registros.size()){
				std::cout<<"###########################################################"<<std::endl;
				std::cout<<"############# DANGER SE PERDIO UN registro    ##############"<<std::endl;
				std::cout<<"###########################################################"<<std::endl;

				std::cout<<" CANTIDAD DE REGISTROS INSERTADOS "<<cont<<std::endl;
				std::cout<<" CANTIDAD DE REGISTROS "<<lista_registros.size()<<std::endl;
			}

			this->bloqueRaiz = nuevaRaiz;

			this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloquePrimerHijo->obtener_numero_bloque(), 0);
			this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueSegundoHijo->obtener_numero_bloque(), 0);
			this->estrategiaEspacioLibre->escribir_espacio_ocupado(this->bloqueRaiz->obtener_numero_bloque(), this->bloqueRaiz->obtener_longitud_ocupada());

			this->estrategiaAlmacenamiento->escribir_bloque_raiz(this->bloqueRaiz->obtener_numero_bloque(), this->bloqueRaiz, this->archivoIndice);
		}


	}
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
void IndiceBSharp::juntarListaRamas(BloqueInternoBSharp::contenedor_ramas& lista_ramas,BloqueInternoBSharp::contenedor_ramas& ramasBloqueIzquierdo,
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

bool IndiceBSharp::removerBloqueExternoLleno(BloqueExternoBSharp::puntero& bloqueActual,
								BloqueExternoBSharp::puntero& bloquePrimerHermano, BloqueExternoBSharp::puntero& bloqueSegundoHermano,
								ResultadoInsercion& resultado){

	unsigned int cont=0;

	if (bloquePrimerHermano == NULL || bloqueSegundoHermano == NULL)
			return false;


	// Crea contenedor de componentes para almacenar los registros de los bloques
	BloqueExternoBSharp::contenedor_componentes lista_registros;

	//Registro menor del bloque actual
	Registro::puntero registroActual = static_cast<Registro::puntero>(*(bloqueActual->primer_componente()));

	//Registro menor bloque primer hermano
	Registro::puntero registroPrimerHermano = static_cast<Registro::puntero>(*(bloquePrimerHermano->primer_componente()));

	//Registro menor bloque segundo hermano
	Registro::puntero registroSegundoHermano = static_cast<Registro::puntero>(*(bloqueSegundoHermano->primer_componente()));

	BloqueExternoBSharp::puntero bloqueIzquierdo;
	BloqueExternoBSharp::puntero bloqueCentro;
	BloqueExternoBSharp::puntero bloqueDerecho;
	BloqueExternoBSharp::contenedor_componentes registrosBloqueIzquierdo;
	BloqueExternoBSharp::contenedor_componentes registrosBloqueCentro;
	BloqueExternoBSharp::contenedor_componentes registrosBloqueDerecho;

	//Diferencio orden bloques
	if (this->comparadorClave->es_menor(this->clave, registroActual, registroPrimerHermano))
		if (this->comparadorClave->es_menor(this->clave, registroActual, registroSegundoHermano)){
			bloqueIzquierdo = bloqueActual;
			if (this->comparadorClave->es_menor(this->clave, registroPrimerHermano, registroSegundoHermano)){
				bloqueCentro = bloquePrimerHermano;
				bloqueDerecho = bloqueSegundoHermano;
			}else{
				bloqueCentro = bloqueSegundoHermano;
				bloqueDerecho = bloquePrimerHermano;
			}
		}else{
			bloqueIzquierdo = bloqueSegundoHermano;
			bloqueCentro = bloqueActual;
			bloqueDerecho = bloquePrimerHermano;
		}
	else
		if (this->comparadorClave->es_menor(this->clave, registroActual, registroSegundoHermano)){
			bloqueIzquierdo = bloquePrimerHermano;
			bloqueCentro = bloqueActual;
			bloqueDerecho = bloqueSegundoHermano;
		}else{
			bloqueDerecho = bloqueActual;
			if (this->comparadorClave->es_menor(this->clave, registroPrimerHermano, registroSegundoHermano)){
				bloqueIzquierdo = bloquePrimerHermano;
				bloqueCentro = bloqueSegundoHermano;
			}else{
				bloqueIzquierdo = bloqueSegundoHermano;
				bloqueCentro = bloquePrimerHermano;
			}
		}

	bloqueIzquierdo->transferir_componentes(registrosBloqueIzquierdo);
	bloqueCentro->transferir_componentes(registrosBloqueCentro);
	bloqueDerecho->transferir_componentes(registrosBloqueDerecho);

	BloqueExternoBSharp::contenedor_componentes lista_registros_aux;
	this->juntarListasComponentes(lista_registros_aux,registrosBloqueIzquierdo,registrosBloqueCentro);

	this->juntarListasComponentes(lista_registros,lista_registros_aux,registrosBloqueDerecho);

	// Llena bloque izquierdo
	BloqueExternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
	while (bloqueIzquierdo->puede_agregar_componente(*componenteListaFinal)){
		bloqueIzquierdo->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
		cont++;
	}

	// Llena bloque centro
	resultado.establecer_registro_clave_media(this->extraer_clave(*componenteListaFinal));
	while (componenteListaFinal != lista_registros.end()){
			if (bloqueCentro->puede_agregar_componente(*componenteListaFinal))
				bloqueCentro->agregar_componente(*componenteListaFinal);
			else
				break;
			componenteListaFinal++;
			cont++;
	}

	if (componenteListaFinal != lista_registros.end()){
		std::cout<<"No se puede fusionar bloques"<<std::endl;
		bloqueIzquierdo->vaciar_componentes();
		BloqueExternoBSharp::iterador_componentes componenteListaBloque = registrosBloqueIzquierdo.begin();
		while (componenteListaBloque != registrosBloqueIzquierdo.end()){
			bloqueIzquierdo->agregar_componente(*componenteListaBloque);
			componenteListaBloque++;
		}
		bloqueCentro->vaciar_componentes();
		componenteListaBloque = registrosBloqueCentro.begin();
		while (componenteListaBloque != registrosBloqueCentro.end()){
			bloqueCentro->agregar_componente(*componenteListaBloque);
			componenteListaBloque++;
		}
		bloqueDerecho->vaciar_componentes();
		componenteListaBloque = registrosBloqueDerecho.begin();
		while (componenteListaBloque != registrosBloqueDerecho.end()){
			bloqueDerecho->agregar_componente(*componenteListaBloque);
			componenteListaBloque++;
		}
		registrosBloqueIzquierdo.clear();
		registrosBloqueCentro.clear();
		registrosBloqueDerecho.clear();
		return false;
	}
	else{
		std::cout<<"BLOQUE BORRADO: "<<bloqueDerecho->obtener_numero_bloque()<<std::endl;
		// Enlaza a los bloques
		bloqueCentro->establecer_bloque_siguiente(bloqueDerecho->obtener_bloque_siguiente());
		resultado.establecer_bloque_derecho(bloqueDerecho->obtener_numero_bloque());
		// Marco segundo bloque como borrado
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueDerecho->obtener_numero_bloque(), 0);
		// Escribo longitud ocupada de primer bloque
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueCentro->obtener_numero_bloque(), bloqueCentro->obtener_longitud_ocupada());
		// Escribo longitud ocupada de primer bloque
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo->obtener_longitud_ocupada());
		// Escribo primer bloque
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo, this->archivoIndice);
		// Escribo primer bloque
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueCentro->obtener_numero_bloque(), bloqueCentro, this->archivoIndice);

		return true;
	}
}
bool IndiceBSharp::removerBloqueInternoLleno(BloqueInternoBSharp::puntero& bloqueActual,
												BloqueInternoBSharp::puntero& bloquePrimerHermano, BloqueInternoBSharp::puntero& bloqueSegundoHermano,
												ResultadoInsercion& resultado){

	unsigned int cont=0;

	if (bloquePrimerHermano == NULL || bloqueSegundoHermano == NULL)
				return false;

	// Crea contenedor de componentes para almacenar los registros de los bloques
	BloqueInternoBSharp::contenedor_componentes lista_registros;

	//Registro menor del bloque actual
	Registro::puntero registroActual = static_cast<Registro::puntero>(*(bloqueActual->primer_componente()));

	//Registro menor bloque primer hermano
	Registro::puntero registroPrimerHermano = static_cast<Registro::puntero>(*(bloquePrimerHermano->primer_componente()));

	//Registro menor bloque segundo hermano
	Registro::puntero registroSegundoHermano = static_cast<Registro::puntero>(*(bloqueSegundoHermano->primer_componente()));

	BloqueInternoBSharp::puntero bloqueIzquierdo;
	BloqueInternoBSharp::puntero bloqueCentro;
	BloqueInternoBSharp::puntero bloqueDerecho;
	BloqueInternoBSharp::contenedor_componentes registrosBloqueIzquierdo;
	BloqueInternoBSharp::contenedor_componentes registrosBloqueCentro;
	BloqueInternoBSharp::contenedor_componentes registrosBloqueDerecho;

	// Crea contenedor de ramas para insertar la rama nueva...
	BloqueInternoBSharp::contenedor_ramas lista_ramas;

	BloqueInternoBSharp::contenedor_ramas ramasBloqueIzquierdo;
	BloqueInternoBSharp::contenedor_ramas ramasBloqueCentro;
	BloqueInternoBSharp::contenedor_ramas ramasBloqueDerecho;

	//Diferencio orden bloques
	if (this->comparadorClave->es_menor(this->clave, registroActual, registroPrimerHermano))
		if (this->comparadorClave->es_menor(this->clave, registroActual, registroSegundoHermano)){
			bloqueIzquierdo = bloqueActual;
			if (this->comparadorClave->es_menor(this->clave, registroPrimerHermano, registroSegundoHermano)){
				bloqueCentro = bloquePrimerHermano;
				bloqueDerecho = bloqueSegundoHermano;
			}else{
				bloqueCentro = bloqueSegundoHermano;
				bloqueDerecho = bloquePrimerHermano;
			}
		}else{
			bloqueIzquierdo = bloqueSegundoHermano;
			bloqueCentro = bloqueActual;
			bloqueDerecho = bloquePrimerHermano;
		}

	else
		if (this->comparadorClave->es_menor(this->clave, registroActual, registroSegundoHermano)){
			bloqueIzquierdo = bloquePrimerHermano;
			bloqueCentro = bloqueActual;
			bloqueDerecho = bloqueSegundoHermano;
		}else{
			bloqueDerecho = bloqueActual;
			if (this->comparadorClave->es_menor(this->clave, registroPrimerHermano, registroSegundoHermano)){
				bloqueIzquierdo = bloquePrimerHermano;
				bloqueCentro = bloqueSegundoHermano;
			}else{
				bloqueIzquierdo = bloqueSegundoHermano;
				bloqueCentro = bloquePrimerHermano;
			}
		}

	bloqueIzquierdo->transferir_componentes(registrosBloqueIzquierdo);
	bloqueCentro->transferir_componentes(registrosBloqueCentro);
	bloqueDerecho->transferir_componentes(registrosBloqueDerecho);

	BloqueInternoBSharp::contenedor_componentes lista_registros_aux;
	this->juntarListasComponentes(lista_registros_aux,registrosBloqueIzquierdo,registrosBloqueCentro);

	this->juntarListasComponentes(lista_registros,lista_registros_aux,registrosBloqueDerecho);

	bloqueIzquierdo->transferir_ramas(ramasBloqueIzquierdo);
	bloqueCentro->transferir_ramas(ramasBloqueCentro);
	bloqueDerecho->transferir_ramas(ramasBloqueDerecho);

	BloqueInternoBSharp::contenedor_ramas lista_ramas_aux;
	this->juntarListaRamas(lista_ramas_aux,ramasBloqueIzquierdo,ramasBloqueDerecho);

	this->juntarListaRamas(lista_ramas,lista_ramas_aux,ramasBloqueDerecho);


	// Llena bloque izquierdo
	BloqueInternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
	BloqueInternoBSharp::iterador_rama ramaListaFinal = lista_ramas.begin();

	bloqueIzquierdo->agregar_rama(*ramaListaFinal);
	ramaListaFinal++;

	while (bloqueIzquierdo->puede_agregar_componente(*componenteListaFinal)){
		bloqueIzquierdo->agregar_componente(*componenteListaFinal);
		bloqueIzquierdo->agregar_rama(*ramaListaFinal);
		componenteListaFinal++;
		ramaListaFinal++;
		cont++;
	}

	bloqueCentro->agregar_rama(*ramaListaFinal);
		ramaListaFinal++;
		// Establece el elemento medio a subir en el resultado de insercion
		Registro::puntero copia = resultado.obtener_registro_clave_media();
		resultado.establecer_registro_clave_media(this->extraer_clave(*componenteListaFinal));
		componenteListaFinal++;
		cont++;

	// Llena bloque centro
	while (bloqueCentro->puede_agregar_componente(*componenteListaFinal)){
		bloqueCentro->agregar_componente(*componenteListaFinal);
		bloqueCentro->agregar_rama(*ramaListaFinal);
		componenteListaFinal++;
		ramaListaFinal++;
		cont++;
	}

	if(cont!=lista_registros.size()){
		std::cout<<"###########################################################"<<std::endl;
		std::cout<<"############# DANGER SE PERDIO UN registro    ##############"<<std::endl;
		std::cout<<"###########################################################"<<std::endl;

		std::cout<<" CANTIDAD DE REGISTROS INSERTADOS "<<cont<<std::endl;
		std::cout<<" CANTIDAD DE REGISTROS "<<lista_registros.size()<<std::endl;
	}


	if (componenteListaFinal != lista_registros.end()){
		std::cout<<"No se puede fusionar bloques"<<std::endl;
		bloqueIzquierdo->vaciar_componentes();
		BloqueInternoBSharp::iterador_componentes componenteListaBloque = registrosBloqueIzquierdo.begin();
		while (componenteListaBloque != registrosBloqueIzquierdo.end()){
			bloqueIzquierdo->agregar_componente(*componenteListaBloque);
			componenteListaBloque++;
		}
		bloqueCentro->vaciar_componentes();
		componenteListaBloque = registrosBloqueCentro.begin();
		while (componenteListaBloque != registrosBloqueCentro.end()){
			bloqueCentro->agregar_componente(*componenteListaBloque);
			componenteListaBloque++;
		}
		registrosBloqueIzquierdo.clear();
		registrosBloqueCentro.clear();
		registrosBloqueDerecho.clear();

		bloqueIzquierdo->vaciar_ramas();
		BloqueInternoBSharp::iterador_rama ramaListaBloque = ramasBloqueIzquierdo.begin();
		while (ramaListaBloque != ramasBloqueIzquierdo.end()){
			bloqueIzquierdo->agregar_rama(*ramaListaBloque);
			ramaListaBloque++;
		}
		bloqueCentro->vaciar_ramas();
		ramaListaBloque = ramasBloqueCentro.begin();
		while (ramaListaBloque != ramasBloqueCentro.end()){
			bloqueCentro->agregar_rama(*ramaListaBloque);
			ramaListaBloque++;
		}
		ramasBloqueIzquierdo.clear();
		ramasBloqueDerecho.clear();
		ramasBloqueCentro.clear();

		resultado.establecer_registro_clave_media(copia);

		return false;
	}////////////////////////////////////////////////////////////////7me quede aca antes del sushi
	else{
		// Enlaza a los bloques
		bloqueCentro->establecer_bloque_siguiente(bloqueDerecho->obtener_numero_bloque());

		// Marco segundo bloque como borrado
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueDerecho->obtener_numero_bloque(), 0);
		// Escribo longitud ocupada de primer bloque
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueCentro->obtener_numero_bloque(), bloqueCentro->obtener_longitud_ocupada());
		// Escribo longitud ocupada de primer bloque
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo->obtener_longitud_ocupada());
		// Escribo primer bloque
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo, this->archivoIndice);
		// Escribo primer bloque
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueCentro->obtener_numero_bloque(), bloqueCentro, this->archivoIndice);
		return true;
	}
}
bool IndiceBSharp::balancearBloquesExternosAlRemover(BloqueExternoBSharp::puntero& bloqueActual,
								BloqueExternoBSharp::puntero& bloquePrimerHermano, BloqueExternoBSharp::puntero& bloqueSegundoHermano,
								ResultadoInsercion& resultado){
	unsigned int cont=0;

	// Crea contenedor de componentes para almacenar los registros de los bloques
	BloqueExternoBSharp::contenedor_componentes lista_registros;

	//Registro menor del bloque actual
	Registro::puntero registroActual = static_cast<Registro::puntero>(*(bloqueActual->primer_componente()));

	//Registro menor bloque primer hermano
	Registro::puntero registroPrimerHermano = static_cast<Registro::puntero>(*(bloquePrimerHermano->primer_componente()));

	//Registro menor bloque segundo hermano
	Registro::puntero registroSegundoHermano = static_cast<Registro::puntero>(*(bloqueSegundoHermano->primer_componente()));

	BloqueExternoBSharp::puntero bloqueIzquierdo;
	BloqueExternoBSharp::puntero bloqueCentro;
	BloqueExternoBSharp::puntero bloqueDerecho;
	BloqueExternoBSharp::contenedor_componentes registrosBloqueIzquierdo;
	BloqueExternoBSharp::contenedor_componentes registrosBloqueCentro;
	BloqueExternoBSharp::contenedor_componentes registrosBloqueDerecho;

	//Diferencio orden bloques
	if (this->comparadorClave->es_menor(this->clave, registroActual, registroPrimerHermano))
		if (this->comparadorClave->es_menor(this->clave, registroActual, registroSegundoHermano)){
			bloqueIzquierdo = bloqueActual;
			if (this->comparadorClave->es_menor(this->clave, registroPrimerHermano, registroSegundoHermano)){
				bloqueCentro = bloquePrimerHermano;
				bloqueDerecho = bloqueSegundoHermano;
			}else{
				bloqueCentro = bloqueSegundoHermano;
				bloqueDerecho = bloquePrimerHermano;
			}
		}else{
			bloqueIzquierdo = bloqueSegundoHermano;
			bloqueCentro = bloqueActual;
			bloqueDerecho = bloquePrimerHermano;
		}
	else
		if (this->comparadorClave->es_menor(this->clave, registroActual, registroSegundoHermano)){
			bloqueIzquierdo = bloquePrimerHermano;
			bloqueCentro = bloqueActual;
			bloqueDerecho = bloqueSegundoHermano;
		}else{
			bloqueDerecho = bloqueActual;
			if (this->comparadorClave->es_menor(this->clave, registroPrimerHermano, registroSegundoHermano)){
				bloqueIzquierdo = bloquePrimerHermano;
				bloqueCentro = bloqueSegundoHermano;
			}else{
				bloqueIzquierdo = bloqueSegundoHermano;
				bloqueCentro = bloquePrimerHermano;
			}
		}

	bloqueIzquierdo->transferir_componentes(registrosBloqueIzquierdo);
	bloqueCentro->transferir_componentes(registrosBloqueCentro);
	bloqueDerecho->transferir_componentes(registrosBloqueDerecho);

	BloqueExternoBSharp::contenedor_componentes lista_registros_aux;
	this->juntarListasComponentes(lista_registros_aux,registrosBloqueIzquierdo,registrosBloqueCentro);

	this->juntarListasComponentes(lista_registros,lista_registros_aux,registrosBloqueDerecho);


	unsigned int peso_promedio = this->calcularPromedio(lista_registros.begin(), lista_registros.end());
	bloqueIzquierdo->setPesoPromedio(peso_promedio);
	bloqueCentro->setPesoPromedio(peso_promedio);
	bloqueDerecho->setPesoPromedio(peso_promedio);
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
	while (bloqueIzquierdo->hay_subflujo((peso_promedio*lista_registros.size())/3)){
		bloqueIzquierdo->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
		cont++;
	}

	// Establece el elemento izq a subir en el resultado
	resultado.establecer_registro_clave_izq(this->extraer_clave(*componenteListaFinal));
	while (bloqueCentro->hay_subflujo((peso_promedio*lista_registros.size())/3)){
			bloqueCentro->agregar_componente(*componenteListaFinal);
			componenteListaFinal++;
			cont++;
	}
	// Establece el elemento izq a subir en el resultado
	resultado.establecer_registro_clave_der(this->extraer_clave(*componenteListaFinal));
	while (componenteListaFinal != lista_registros.end()){
		if (bloqueDerecho->puede_agregar_componente(*componenteListaFinal))
			bloqueDerecho->agregar_componente(*componenteListaFinal);
		else
			break;
		componenteListaFinal++;
		cont++;
	}

	if(cont!=lista_registros.size()){
		std::cout<<"###########################################################"<<std::endl;
		std::cout<<"############# DANGER SE PERDIO UN registro    ##############"<<std::endl;
		std::cout<<"###########################################################"<<std::endl;

		std::cout<<" CANTIDAD DE REGISTROS INSERTADOS "<<cont<<std::endl;
		std::cout<<" CANTIDAD DE REGISTROS "<<lista_registros.size()<<std::endl;
	}

	std::cout<<"Si se puede hacer balanceo externo"<<std::endl;
	// Escribe bloque izquierdo
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo, this->archivoIndice);
	// Escribe bloque centro
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueCentro->obtener_numero_bloque(), bloqueCentro, this->archivoIndice);
	// Escribe bloque derecho
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueDerecho->obtener_numero_bloque(), bloqueDerecho, this->archivoIndice);

	return true;

}

bool IndiceBSharp::balancearBloquesInternosAlRemover(BloqueInternoBSharp::puntero& bloqueActual,
		BloqueInternoBSharp::puntero& bloquePrimerHermano, BloqueInternoBSharp::puntero& bloqueSegundoHermano,
								ResultadoInsercion& resultado){
	unsigned int cont=0;
	if (bloquePrimerHermano == NULL || bloqueSegundoHermano == NULL)
		return false;

	// Crea contenedor de componentes para almacenar los registros de los bloques
	BloqueInternoBSharp::contenedor_componentes lista_registros;

	//Registro menor del bloque actual
	Registro::puntero registroActual = static_cast<Registro::puntero>(*(bloqueActual->primer_componente()));

	//Registro menor bloque primer hermano
	Registro::puntero registroPrimerHermano = static_cast<Registro::puntero>(*(bloquePrimerHermano->primer_componente()));

	//Registro menor bloque segundo hermano
	Registro::puntero registroSegundoHermano = static_cast<Registro::puntero>(*(bloqueSegundoHermano->primer_componente()));

	BloqueInternoBSharp::puntero bloqueIzquierdo;
	BloqueInternoBSharp::puntero bloqueCentro;
	BloqueInternoBSharp::puntero bloqueDerecho;
	BloqueInternoBSharp::contenedor_componentes registrosBloqueIzquierdo;
	BloqueInternoBSharp::contenedor_componentes registrosBloqueCentro;
	BloqueInternoBSharp::contenedor_componentes registrosBloqueDerecho;

	// Crea contenedor de ramas para insertar la rama nueva...
	BloqueInternoBSharp::contenedor_ramas lista_ramas;

	BloqueInternoBSharp::contenedor_ramas ramasBloqueIzquierdo;
	BloqueInternoBSharp::contenedor_ramas ramasBloqueCentro;
	BloqueInternoBSharp::contenedor_ramas ramasBloqueDerecho;

	//Diferencio orden bloques
	if (this->comparadorClave->es_menor(this->clave, registroActual, registroPrimerHermano))
		if (this->comparadorClave->es_menor(this->clave, registroActual, registroSegundoHermano)){
			bloqueIzquierdo = bloqueActual;
			if (this->comparadorClave->es_menor(this->clave, registroPrimerHermano, registroSegundoHermano)){
				bloqueCentro = bloquePrimerHermano;
				bloqueDerecho = bloqueSegundoHermano;
			}else{
				bloqueCentro = bloqueSegundoHermano;
				bloqueDerecho = bloquePrimerHermano;
			}
		}else{
			bloqueIzquierdo = bloqueSegundoHermano;
			bloqueCentro = bloqueActual;
			bloqueDerecho = bloquePrimerHermano;
		}
	else
		if (this->comparadorClave->es_menor(this->clave, registroActual, registroSegundoHermano)){
			bloqueIzquierdo = bloquePrimerHermano;
			bloqueCentro = bloqueActual;
			bloqueDerecho = bloqueSegundoHermano;
		}else{
			bloqueDerecho = bloqueActual;
			if (this->comparadorClave->es_menor(this->clave, registroPrimerHermano, registroSegundoHermano)){
				bloqueIzquierdo = bloquePrimerHermano;
				bloqueCentro = bloqueSegundoHermano;
			}else{
				bloqueIzquierdo = bloqueSegundoHermano;
				bloqueCentro = bloquePrimerHermano;
			}
		}

	bloqueIzquierdo->transferir_componentes(registrosBloqueIzquierdo);
	bloqueCentro->transferir_componentes(registrosBloqueCentro);
	bloqueDerecho->transferir_componentes(registrosBloqueDerecho);

	bloqueIzquierdo->transferir_ramas(ramasBloqueIzquierdo);
	bloqueCentro->transferir_ramas(ramasBloqueCentro);
	bloqueDerecho->transferir_ramas(ramasBloqueDerecho);

	BloqueInternoBSharp::contenedor_componentes lista_registros_aux;
	this->juntarListasComponentes(lista_registros_aux,registrosBloqueIzquierdo,registrosBloqueCentro);

	this->juntarListasComponentes(lista_registros,lista_registros_aux,registrosBloqueDerecho);

	BloqueInternoBSharp::contenedor_ramas lista_ramas_aux;
	this->juntarListaRamas(lista_ramas_aux,ramasBloqueIzquierdo,ramasBloqueDerecho);

	this->juntarListaRamas(lista_ramas,lista_ramas_aux,ramasBloqueDerecho);

	BloqueInternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
	BloqueInternoBSharp::iterador_rama ramaListaFinal = lista_ramas.begin();

	bloqueIzquierdo->agregar_rama(*ramaListaFinal);
	ramaListaFinal++;
	while (bloqueIzquierdo->puede_agregar_componente(*componenteListaFinal)){
		bloqueIzquierdo->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
		bloqueIzquierdo->agregar_rama(*ramaListaFinal);
		componenteListaFinal++;
		cont++;
	}
	bloqueCentro->agregar_rama(*ramaListaFinal);
	ramaListaFinal++;

	// Establece el elemento izq a subir en el resultado
	resultado.establecer_registro_clave_izq(this->extraer_clave(*componenteListaFinal));
	componenteListaFinal++;
	cont++;
	while (bloqueCentro->puede_agregar_componente(*componenteListaFinal)){
			bloqueCentro->agregar_componente(*componenteListaFinal);
			bloqueCentro->agregar_rama(*ramaListaFinal);
			ramaListaFinal++;
			componenteListaFinal++;
			cont++;
	}
	// Establece el elemento izq a subir en el resultado

	resultado.establecer_registro_clave_der(this->extraer_clave(*componenteListaFinal));
	componenteListaFinal++;
	cont++;
	while (componenteListaFinal != lista_registros.end()){
		if (bloqueDerecho->puede_agregar_componente(*componenteListaFinal)){
			bloqueDerecho->agregar_componente(*componenteListaFinal);
			bloqueDerecho->agregar_rama(*ramaListaFinal);
		}
		else
			break;
		componenteListaFinal++;
		ramaListaFinal++;
		cont++;
	}


	if(cont!=lista_registros.size()){
		std::cout<<"###########################################################"<<std::endl;
		std::cout<<"############# DANGER SE PERDIO UN registro    ##############"<<std::endl;
		std::cout<<"###########################################################"<<std::endl;

		std::cout<<" CANTIDAD DE REGISTROS INSERTADOS "<<cont<<std::endl;
		std::cout<<" CANTIDAD DE REGISTROS "<<lista_registros.size()<<std::endl;
	}

	std::cout<<"Si se puede hacer balanceo externo"<<std::endl;
	// Escribe bloque izquierdo
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo, this->archivoIndice);
	// Escribe bloque centro
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueCentro->obtener_numero_bloque(), bloqueCentro, this->archivoIndice);
	// Escribe bloque derecho
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueDerecho->obtener_numero_bloque(), bloqueDerecho, this->archivoIndice);

	return true;

}

bool IndiceBSharp::balancearBloquesExternos(const Registro::puntero& registro, BloqueExternoBSharp::puntero& bloqueActual,
								BloqueExternoBSharp::puntero& bloqueHermano, ResultadoInsercion& resultado) throw(){
	//SE BALANCEA POR TAMAÑO
	//SE LLENA EL BLOQUE DE LA IZQUIERDA LO MAS POSIBLE, LUEGO SE INTENTA LLENAR EL DE LA DERECHA
	unsigned int cont=0;
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
		cont++;
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
		cont++;
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
		if(cont!=lista_registros.size()){
			std::cout<<"###########################################################"<<std::endl;
			std::cout<<"############# DANGER SE PERDIO UN registro    ##############"<<std::endl;
			std::cout<<"###########################################################"<<std::endl;

			std::cout<<" CANTIDAD DE REGISTROS INSERTADOS "<<cont<<std::endl;
			std::cout<<" CANTIDAD DE REGISTROS "<<lista_registros.size()<<std::endl;
		}

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
			// Si la rama hermana es nula el sobreflujo se da en la raiz, no inserto, la raiz se encarga
			if (bloqueRamaHermana != NULL){
				// Agrega el registro en el bloque externo lleno
				this->insertar_bloque_externo_lleno(bloqueExterno, bloqueRamaHermana, registro, resultado);
			}
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
	if (bloqueExterno->obtener_numero_bloque() == 0)
		this->estrategiaAlmacenamiento->escribir_bloque_raiz(bloqueExterno->obtener_numero_bloque(), bloqueExterno, this->archivoIndice);
	else
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueExterno->obtener_numero_bloque(), bloqueExterno, this->archivoIndice);
}


void IndiceBSharp::insertar_bloque_externo_lleno(BloqueExternoBSharp::puntero& bloqueExterno,BloqueExternoBSharp::puntero& bloqueHermano, const Registro::puntero& registro,
				ResultadoInsercion& resultado) throw(){
	 	unsigned int cont=0;
	 	// Busco numero de bloque libre
		unsigned int numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
		// Creo nuevo bloque externo para dividir bloque..
		BloqueExternoBSharp::puntero nuevoBloqueExterno = new BloqueExternoBSharp(this->longitud_bloque, numero_bloque_libre);

		// Crea contenedor de componentes para insertar ordenado el registro...
		BloqueExternoBSharp::contenedor_componentes lista_registros;

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


		unsigned int peso_promedio = this->calcularPromedio(lista_registros.begin(), lista_registros.end());
		bloqueIzquierdo->setPesoPromedio(peso_promedio);
		bloqueDerecho->setPesoPromedio(peso_promedio);
		nuevoBloqueExterno->setPesoPromedio(peso_promedio);


		// Inserta elementos a la izquierda del medio en bloque a dividir
		BloqueExternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
		while (bloqueIzquierdo->hay_subflujo((peso_promedio*lista_registros.size())/3)){
			bloqueIzquierdo->agregar_componente(*componenteListaFinal);
			componenteListaFinal++;
			cont++;
		}

		// Establece el elemento medio a subir en el resultado de insercion
		resultado.establecer_registro_clave_izq(this->extraer_clave(*componenteListaFinal));////MODIFICAR ESTABLECER CALVE IZQ
		while (bloqueDerecho->hay_subflujo((peso_promedio*lista_registros.size())/3)){
			bloqueDerecho->agregar_componente(*componenteListaFinal);
			componenteListaFinal++;
			cont++;
		}
		resultado.establecer_registro_clave_der(this->extraer_clave(*componenteListaFinal));////MODIFICAR ESTABLECER CALVE DER
		while (componenteListaFinal != lista_registros.end()){
			if (nuevoBloqueExterno->puede_agregar_componente(*componenteListaFinal))
				nuevoBloqueExterno->agregar_componente(*componenteListaFinal);
			else
				break;
			componenteListaFinal++;
			cont++;
		}
		if(cont!=lista_registros.size()){
				std::cout<<"###########################################################"<<std::endl;
				std::cout<<"############# DANGER SE PERDIO UN registro    ##############"<<std::endl;
				std::cout<<"###########################################################"<<std::endl;

				std::cout<<" CANTIDAD DE REGISTROS INSERTADOS "<<cont<<std::endl;
				std::cout<<" CANTIDAD DE REGISTROS "<<lista_registros.size()<<std::endl;
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

bool IndiceBSharp::balancearBloquesInternos(BloqueInternoBSharp::puntero& bloqueInterno, BloqueInternoBSharp::puntero& bloqueHermano, ResultadoInsercion& resultado, Registro::puntero& registroPadre) throw(){

	//SE BALANCEA POR TAMAÑO
	//SE LLENA EL BLOQUE DE LA IZQUIERDA LO MAS POSIBLE, LUEGO SE INTENTA LLENAR EL DE LA DERECHA
	unsigned int cont=0;
	if (bloqueHermano == NULL)
		return false;


	const Registro::puntero& registroClave = resultado.obtener_registro_clave_der();
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
		bloqueHermano->transferir_ramas(ramasBloqueDerecho);
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


	this->juntarListasComponentes(lista_registros,registrosBloqueIzquierdo,registrosBloqueDerecho);

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


	BloqueInternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
	BloqueInternoBSharp::iterador_rama ramaListaFinal = lista_ramas.begin();
	bloqueIzquierdo->agregar_rama(*ramaListaFinal);
	std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
	ramaListaFinal++;
	while (bloqueIzquierdo->puede_agregar_componente(*componenteListaFinal)){
		Registro::puntero registroAux = static_cast<Registro::puntero>(*componenteListaFinal);
		imprimir_registro(registroAux,std::cout);
		std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
		bloqueIzquierdo->agregar_rama(*ramaListaFinal);
		bloqueIzquierdo->agregar_componente(*componenteListaFinal);
		componenteListaFinal++;
		ramaListaFinal++;
		cont++;
	}
	std::cout<<"  RAMA: "<<*ramaListaFinal<<" - "<<std::endl;
	bloqueDerecho->agregar_rama(*ramaListaFinal);
	ramaListaFinal++;
	// Establece el elemento medio a subir en el resultado de insercion
	Registro::puntero copia = resultado.obtener_registro_clave_media();
	resultado.establecer_registro_clave_media(this->extraer_clave(*componenteListaFinal));
	componenteListaFinal++;
	cont++;
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
		cont++;
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

			return false;
		}
		else{

			if(cont!=lista_registros.size()){
				std::cout<<"###########################################################"<<std::endl;
				std::cout<<"############# DANGER SE PERDIO UN registro    ##############"<<std::endl;
				std::cout<<"###########################################################"<<std::endl;

				std::cout<<" CANTIDAD DE REGISTROS INSERTADOS "<<cont<<std::endl;
				std::cout<<" CANTIDAD DE REGISTROS "<<lista_registros.size()<<std::endl;
			}

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
			Registro::puntero registroAReemplazar = (Registro::puntero) *actualComponente;
			std::cout << "Registro a reemplazar: ";
			this->imprimir_registro(registroAReemplazar, std::cout);
			std::cout<< std::endl;
			std::cout << "Registro a subir: ";
			this->imprimir_registro(resultado.obtener_registro_clave_izq(), std::cout);
			std::cout<< std::endl;
			bloqueInterno->reemplazar_componente(registroAReemplazar, resultado.obtener_registro_clave_izq());

			if (bloqueInterno->puede_agregar_componente(resultado.obtener_registro_clave_der())) {
				// Inserto en el bloque interno no lleno
							std::cout << "Registro nuevo a subir: ";
				this->imprimir_registro(resultado.obtener_registro_clave_der(), std::cout);
				std::cout<< std::endl;


				this->insertar_bloque_interno_no_lleno(bloqueInterno, resultado.obtener_registro_clave_der(),
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

					// Si la rama hermana es nula el sobreflujo se da en la raiz, no inserto, la raiz se encarga
					if (bloqueRamaHermana != NULL){
						this->insertar_bloque_interno_lleno(bloqueInterno,bloqueRamaHermana, resultado.obtener_registro_clave_der(), resultado, registroPadre);


					}
				}
			}
		}
	}
	return respuesta;
}

void IndiceBSharp::insertar_bloque_interno_no_lleno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave, unsigned int bloque_derecho) throw() {
	unsigned int posicion_insercion = this->buscar_posicion_insercion_interna(registroClave, bloqueInterno->primer_componente(), bloqueInterno->ultimo_componente());

	// Agrego componente
	BloqueInternoBSharp::iterador_componentes iterador_insercion = bloqueInterno->primer_componente() + posicion_insercion;
	bloqueInterno->agregar_componente(registroClave, iterador_insercion);

	// Agrego rama
	BloqueInternoBSharp::iterador_rama iterador_insercion_rama_derecha = bloqueInterno->primer_rama() + posicion_insercion + 1;
	bloqueInterno->agregar_rama(bloque_derecho, iterador_insercion_rama_derecha);

	// Actualizo espacio libre
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueInterno->obtener_numero_bloque(), bloqueInterno->obtener_longitud_ocupada());

	if (bloqueInterno->obtener_numero_bloque() == 0)
			this->estrategiaAlmacenamiento->escribir_bloque_raiz(bloqueInterno->obtener_numero_bloque(), bloqueInterno, this->archivoIndice);
		else
			this->estrategiaAlmacenamiento->escribir_bloque(bloqueInterno->obtener_numero_bloque(), bloqueInterno, this->archivoIndice);
}




bool IndiceBSharp::insertar_bloque_interno_lleno(BloqueInternoBSharp::puntero& bloqueInterno,BloqueInternoBSharp::puntero& bloqueHermano, const Registro::puntero& registroClave,
	 ResultadoInsercion& resultado,Registro::puntero& registroPadre) throw() {
	if (bloqueHermano == NULL)
			return false;
		// Busco numero de bloque libre
		unsigned int numero_bloque_libre = this->estrategiaEspacioLibre->buscar_espacio_libre();
		// Creo nuevo bloque interno para dividir
		BloqueInternoBSharp::puntero nuevoBloqueInterno = new BloqueInternoBSharp(this->longitud_bloque, numero_bloque_libre, bloqueInterno->obtener_nivel());
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
			bloqueHermano->transferir_ramas(ramasBloqueDerecho);
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
		this->juntarListasComponentes(lista_registros,registrosBloqueIzquierdo,registrosBloqueDerecho);
		this->juntarListaRamas(lista_ramas,ramasBloqueIzquierdo,ramasBloqueDerecho);
		// Busca posicion de insercion para el registro padre...
		unsigned int posicion_insercion = buscar_posicion_insercion_interna(registroPadre, lista_registros.begin(), lista_registros.end());
		// Inserta ordenado el registro padre
		lista_registros.insert(lista_registros.begin() + posicion_insercion, registroPadre);
		// Busca posicion de insercion para el registroClave
		posicion_insercion = buscar_posicion_insercion_interna(registroClave, lista_registros.begin(), lista_registros.end());
		// Inserta ordenado el registro clave
		lista_registros.insert(lista_registros.begin() + posicion_insercion, registroClave);

		// Inserta la rama
		lista_ramas.insert(lista_ramas.begin() + posicion_insercion + 1, bloque_derecho);

		unsigned int peso_promedio = this->calcularPromedio(lista_registros.begin(), lista_registros.end());
		bloqueIzquierdo->setPesoPromedio(peso_promedio);
		bloqueDerecho->setPesoPromedio(peso_promedio);
		nuevoBloqueInterno->setPesoPromedio(peso_promedio);


		BloqueInternoBSharp::iterador_componentes componenteListaFinal = lista_registros.begin();
		BloqueInternoBSharp::iterador_rama ramaListaFinal = lista_ramas.begin();
		bloqueIzquierdo->agregar_rama(*ramaListaFinal);
		ramaListaFinal++;
		while (bloqueIzquierdo->hay_subflujo((peso_promedio*lista_registros.size())/3)){
			bloqueIzquierdo->agregar_rama(*ramaListaFinal);
			bloqueIzquierdo->agregar_componente(*componenteListaFinal);
			componenteListaFinal++;
			ramaListaFinal++;
		}
		bloqueDerecho->agregar_rama(*ramaListaFinal);
		ramaListaFinal++;
		// Establece el elemento izquierdo a subir en el resultado de insercion
		resultado.establecer_registro_clave_izq(this->extraer_clave(*componenteListaFinal));

		Registro::puntero registroAux = static_cast<Registro::puntero>(*componenteListaFinal);
		std::cout << "Registro clave izquierda a subir: ";
		imprimir_registro(registroAux,std::cout);
		componenteListaFinal++;

		while (bloqueDerecho->hay_subflujo((peso_promedio*lista_registros.size())/3)){
			bloqueDerecho->agregar_rama(*ramaListaFinal);
			bloqueDerecho->agregar_componente(*componenteListaFinal);
			componenteListaFinal++;
			ramaListaFinal++;
		}
		nuevoBloqueInterno->agregar_rama(*ramaListaFinal);
		ramaListaFinal++;
		// Establece el elemento derecho a subir en el resultado de insercion
		resultado.establecer_registro_clave_der(this->extraer_clave(*componenteListaFinal));

		registroAux = static_cast<Registro::puntero>(*componenteListaFinal);
		std::cout << "Registro clave derecha a subir: ";
		imprimir_registro(registroAux,std::cout);

		componenteListaFinal++;
		while (componenteListaFinal != lista_registros.end()){
			if (nuevoBloqueInterno->puede_agregar_componente(*componenteListaFinal)){
				nuevoBloqueInterno->agregar_rama(*ramaListaFinal);
				nuevoBloqueInterno->agregar_componente(*componenteListaFinal);
			}
			else
				break;
			componenteListaFinal++;
			ramaListaFinal++;
		}


		// Actualiza espacio ocupado para el bloque a dividir
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo->obtener_longitud_ocupada());
		// Escribe bloque a dividir en disco
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueIzquierdo->obtener_numero_bloque(), bloqueIzquierdo, this->archivoIndice);
		// Actualiza espacio ocupado para el bloque a dividir
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueDerecho->obtener_numero_bloque(), bloqueDerecho->obtener_longitud_ocupada());
		// Escribe bloque a dividir en disco
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueDerecho->obtener_numero_bloque(), bloqueDerecho, this->archivoIndice);
		// Actualiza espacio ocupado para el bloque nuevo
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(nuevoBloqueInterno->obtener_numero_bloque(), nuevoBloqueInterno->obtener_longitud_ocupada());
		// Escribe bloque nuevo
		this->estrategiaAlmacenamiento->escribir_bloque(nuevoBloqueInterno->obtener_numero_bloque(), nuevoBloqueInterno, this->archivoIndice);


	// Establezco bloque izquierdo en resultado de insercion
	resultado.establecer_bloque_izquierdo(bloqueIzquierdo->obtener_numero_bloque());
	std::cout << "bloqueIzquierdo: "<< bloqueIzquierdo->obtener_numero_bloque();
	// Establezco bloque derecho en resultado de insercion
	resultado.establecer_bloque_derecho(nuevoBloqueInterno->obtener_numero_bloque());
	std::cout << "bloqueDerecho: "<< nuevoBloqueInterno->obtener_numero_bloque();
	// Establezco bloque medio en resultado de insercion
	resultado.establecer_bloque_medio(bloqueDerecho->obtener_numero_bloque());
	std::cout << "bloqueMedio: "<< bloqueDerecho->obtener_numero_bloque();
	return true;
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


unsigned int IndiceBSharp::calcularPromedio(BloqueBSharp::iterador_componentes actual, BloqueBSharp::iterador_componentes ultimo_registro) throw() {
	unsigned int pesoTotal = 0;
	unsigned int contador = 0;
	while (actual != ultimo_registro){
			Registro::puntero registroAux = static_cast<Registro::puntero>(*actual);
			pesoTotal += registroAux->GetLongitudBytes();
			actual++;
			contador++;
	}
	unsigned int pesoPromedio = pesoTotal/contador;
	return pesoPromedio;
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

void IndiceBSharp::buscar_ramas_hermanas(const BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registro, int *r1, int *r2) throw() {
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
	int rama_hermana_2;
	// Si es el ultimo componente las ramas son las dos anteriores
	if (actualComponente == finComponente) {
		rama_hermana = posicion_rama - 1;
		rama_hermana_2 = posicion_rama - 2;
	}
	else{
		// Si es el primer componente las ramas son las dos posteriores
		if (posicion_rama ==  0){
			rama_hermana = posicion_rama + 1;
			rama_hermana_2 = posicion_rama + 2;
		}else{
			// Si esta en el medio son las ramas anterior y posterior
			rama_hermana = posicion_rama - 1;
			rama_hermana_2 = posicion_rama + 1;
		}
	}

	*r1 = bloqueInterno->obtener_rama(rama_hermana);
	*r2 = bloqueInterno->obtener_rama(rama_hermana_2);
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

int IndiceBSharp::remover_bloque_externo(BloqueExternoBSharp::puntero& bloqueExterno, const Registro::puntero& registro,
		ResultadoInsercion& resultado, unsigned int primerHermano, unsigned int segundoHermano) throw() {

	// Consideramos que no hay subflujo
	int respuesta = ELIMINACION_CORRECTA;

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
	// DONI
	// Pregunto si hay underflow, si hay, intento fusionar y luego balancear
	if (bloqueExterno->haySubflujo()){
		// Leo bloques hermanos
		BloqueExternoBSharp::puntero bloquePrimerHermano, bloqueSegundoHermano;
		if (primerHermano != 0 && segundoHermano != 0){
			bloquePrimerHermano = this->estrategiaAlmacenamiento->leer_bloque(primerHermano, this->archivoIndice);
			bloqueSegundoHermano = this->estrategiaAlmacenamiento->leer_bloque(segundoHermano, this->archivoIndice);
		}else{
			bloquePrimerHermano = NULL;
			bloqueSegundoHermano = NULL;
		}
		// Intento fusionar
		if (this->removerBloqueExternoLleno(bloqueExterno,bloquePrimerHermano,bloqueSegundoHermano, resultado))
			respuesta = HAY_SUBFLUJO;
		else{
			// Si no se puede fusionar se balancea
			if (bloquePrimerHermano != 0 && bloqueSegundoHermano != 0)
				this->balancearBloquesExternosAlRemover(bloqueExterno,bloquePrimerHermano,bloqueSegundoHermano,resultado);
			respuesta = HAY_BALANCEO;
		}
	}

	if (respuesta == ELIMINACION_CORRECTA){
		// Actualizo espacio en disco
		this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueExterno->obtener_numero_bloque(), bloqueExterno->obtener_longitud_ocupada());
		this->estrategiaAlmacenamiento->escribir_bloque(bloqueExterno->obtener_numero_bloque(), bloqueExterno, this->archivoIndice);
	}

	return respuesta;

}

int IndiceBSharp::remover_bloque_interno(BloqueInternoBSharp::puntero& bloqueInterno, const Registro::puntero& registroClave,
		ResultadoBalanceo& resultadoBalanceo, ResultadoInsercion& resultadoInsercion, unsigned int primerHermano, unsigned int segundoHermano) throw() {
	// Considero que no hay subflujo al remover en el bloque interno
	int respuesta = ELIMINACION_CORRECTA;
	// Busco la rama por la cual borrar
	int rama_borrar = this->buscar_rama(bloqueInterno, registroClave);
	int ramaUno,ramaDos;
	this->buscar_ramas_hermanas(bloqueInterno,registroClave,&ramaUno,&ramaDos);
	std::cout<<"Rama Hermana1: "<< ramaUno<<std::endl;
	std::cout<<"Rama Hermana2: "<< ramaDos<<std::endl;
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
	// Leo el bloque por el cual borrar
	BloqueBSharp::puntero bloqueRamaBorrar = this->estrategiaAlmacenamiento->leer_bloque(rama_borrar, this->archivoIndice);

	if (bloqueRamaBorrar != NULL) {
		// Considero que no hay subflujo al remover en el bloque hijo
		int respuestaHijo = ELIMINACION_CORRECTA;
		if (bloqueRamaBorrar->es_hoja()) {
			BloqueExternoBSharp::puntero bloqueExternoBorrar(bloqueRamaBorrar);
			// Remuevo en el bloque externo hijo
			respuestaHijo = this->remover_bloque_externo(bloqueExternoBorrar, registroClave, resultadoInsercion, ramaUno, ramaDos);
		} else {
			BloqueInternoBSharp::puntero bloqueInternoBorrar(bloqueRamaBorrar);
			// Remuevo en el bloque interno hijo
			respuestaHijo = this->remover_bloque_interno(bloqueInternoBorrar, registroClave, resultadoBalanceo,resultadoInsercion, ramaUno, ramaDos);
		}

		if (respuestaHijo == HAY_BALANCEO) {
			Registro::puntero registroMayorAReemplazar;
			Registro::puntero registroMenorAReemplazar;
//			std::cout << "Actual: ";
//						this->imprimir_registro(*(--actualComponente), std::cout);
//						std::cout<< std::endl;
			BloqueInternoBSharp::iterador_rama ultimaRama = bloqueInterno->ultima_rama();
			if (rama_borrar == *(--ultimaRama)){
				registroMayorAReemplazar =  (Registro::puntero) *actualComponente;
				registroMenorAReemplazar =  (Registro::puntero) *(--actualComponente);
			}else{
				registroMenorAReemplazar =  (Registro::puntero) *actualComponente;
				registroMayorAReemplazar =  (Registro::puntero) *(++actualComponente);

			}

			std::cout << "Registro Menor a Reemplazar: ";
			this->imprimir_registro(registroMenorAReemplazar, std::cout);
			std::cout<< std::endl;
			std::cout << "Registro Menor a subir: ";
			this->imprimir_registro(resultadoInsercion.obtener_registro_clave_izq(), std::cout);
			std::cout<< std::endl;
			bloqueInterno->reemplazar_componente(registroMenorAReemplazar, resultadoInsercion.obtener_registro_clave_izq());

			std::cout << "Registro Mayor a Reemplazar: ";
			this->imprimir_registro(registroMayorAReemplazar, std::cout);
			std::cout<< std::endl;
			std::cout << "Registro Mayor a Subir: ";
			this->imprimir_registro(resultadoInsercion.obtener_registro_clave_der(), std::cout);
			std::cout<< std::endl;
			bloqueInterno->reemplazar_componente(registroMayorAReemplazar, resultadoInsercion.obtener_registro_clave_der());
			// Escribo bloque
			this->estrategiaAlmacenamiento->escribir_bloque(bloqueInterno->obtener_numero_bloque(), bloqueInterno, this->archivoIndice);
		}
		// Verifico si hubo sobrelujo al insertar en el bloque hijo
		if (respuestaHijo == HAY_SUBFLUJO) {

			this->actualizar_fusion(bloqueInterno, resultadoInsercion);

			if (bloqueInterno->haySubflujo()){
				// Leo bloques hermanos
				BloqueInternoBSharp::puntero bloquePrimerHermano, bloqueSegundoHermano;
				if (primerHermano != 0 && segundoHermano != 0){
					bloquePrimerHermano = this->estrategiaAlmacenamiento->leer_bloque(primerHermano, this->archivoIndice);
					bloqueSegundoHermano = this->estrategiaAlmacenamiento->leer_bloque(segundoHermano, this->archivoIndice);
				}else{
					bloquePrimerHermano = NULL;
					bloqueSegundoHermano = NULL;
				}
				// Intento fusionar
				if (this->removerBloqueInternoLleno(bloqueInterno,bloquePrimerHermano,bloqueSegundoHermano, resultadoInsercion))
					respuesta = HAY_SUBFLUJO;
				else{
					// Si no se puede fusionar se balancea
					if (primerHermano != 0 && segundoHermano != 0)
						this->balancearBloquesInternosAlRemover(bloqueInterno,bloquePrimerHermano,bloqueSegundoHermano,resultadoInsercion);
					respuesta = HAY_BALANCEO;
					}

				}
		}
	}
	return respuesta;
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

		BloqueInternoBSharp::iterador_rama actual = ramas_totales.begin();
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

		BloqueInternoBSharp::iterador_rama actualRama = segundoBloqueInterno->primer_rama();
		BloqueInternoBSharp::iterador_rama finRama = segundoBloqueInterno->ultima_rama();

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
//	BloqueInternoBSharp::iterador_rama actualRama = bloquePadre->primer_rama();
//	BloqueInternoBSharp::iterador_rama finRama = bloquePadre->ultima_rama();
//	bool encontrado = false;
//	int posicion_rama_hija = 0;
//
//	while (actualRama != finRama && !encontrado) {
//		if (*actualRama == bloqueHijo->obtener_numero_bloque()) {
//			encontrado = true;
//		} else {
//			++posicion_rama_hija;
//			++actualRama;
//		}
//	}
	//Es la primera de las ramas, es decir el primer hijo, no tiene hermano izquierdo, devuelvo NULL
//	if (posicion_rama_hija == 0) {
		return NULL;
//	} else {
//		return this->estrategiaAlmacenamiento->leer_bloque(bloquePadre->obtener_rama(posicion_rama_hija - 1), this->archivoIndice);
//	}
}



BloqueBSharp::puntero IndiceBSharp::buscar_hermano_derecho(BloqueInternoBSharp::puntero& bloquePadre, BloqueBSharp::puntero& bloqueHijo) throw() {
	// Si el bloque siguiente no es invalido, tiene hermano derecho, lo devuelvo
//	if (bloqueHijo->obtener_bloque_siguiente() != BloqueBSharp::ID_BLOQUE_INVALIDO) {
//		return this->estrategiaAlmacenamiento->leer_bloque(bloqueHijo->obtener_bloque_siguiente(), this->archivoIndice);
//	} else {
		return NULL;
//	}
}

void IndiceBSharp::actualizar_balanceo(BloqueInternoBSharp::puntero& bloquePadre, ResultadoBalanceo& resultadoBalanceo) throw() {
        BloqueInternoBSharp::iterador_rama actualRama = bloquePadre->primer_rama();
        BloqueInternoBSharp::iterador_rama finRama = bloquePadre->ultima_rama();
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

void IndiceBSharp::actualizar_fusion(BloqueInternoBSharp::puntero& bloquePadre, ResultadoInsercion& resultadoInsercion) throw() {
	BloqueInternoBSharp::iterador_rama actualRama = bloquePadre->primer_rama();
	BloqueInternoBSharp::iterador_rama finRama = bloquePadre->ultima_rama();
	int posicion_rama_eliminar = 0;
	std::cout<<"RAMA A BORRAR:"<< resultadoInsercion.obtener_bloque_derecho()<<std::endl;
	while (actualRama != finRama) {
		std::cout<<"RAMA ACTUAL: "<<*actualRama<<std::endl;
		if (*actualRama == (int)resultadoInsercion.obtener_bloque_derecho()) {
			bloquePadre->remover_rama(actualRama);
			break;
		}
		++posicion_rama_eliminar;
		++actualRama;
	}
	BloqueInternoBSharp::iterador_componentes actualClave = bloquePadre->primer_componente();
	BloqueInternoBSharp::iterador_componentes claveAnterior = bloquePadre->primer_componente();
	for (int contador_claves = 0; contador_claves <posicion_rama_eliminar - 1; ++contador_claves) {
		claveAnterior = actualClave;
		++actualClave;
	}

	bloquePadre->remover_componente(actualClave);

	Registro::puntero registroAReemplazar =  (Registro::puntero) *claveAnterior;
	std::cout << "Registro a Reemplazar: ";
	this->imprimir_registro(registroAReemplazar, std::cout);
	std::cout<< std::endl;
	std::cout << "Registro a Poner: ";
	this->imprimir_registro(resultadoInsercion.obtener_registro_clave_media(), std::cout);
	std::cout<< std::endl;
	bloquePadre->reemplazar_componente(registroAReemplazar, resultadoInsercion.obtener_registro_clave_media());
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
		streamSalida << "COMPONENTES BLOQUE: ";
		Bloque::iterador_componentes_constante actualComponente = bloqueActual->primer_componente();
		Bloque::iterador_componentes_constante finComponente = bloqueActual->ultimo_componente();
		BloqueInternoBSharp::iterador_rama_constante actualRama;
		if (!bloqueActual->es_hoja()) {
			const BloqueInternoBSharp::puntero& bloque = static_cast<BloqueInternoBSharp::puntero>(bloqueActual);
			actualRama  = bloque->primer_rama();
			streamSalida << " " << *actualRama<< " ";
			actualRama++;
		}

		while (actualComponente != finComponente) {
			Registro::puntero registro = (Registro::puntero) *actualComponente;
			this->imprimir_registro(registro, streamSalida);
			if (!bloqueActual->es_hoja()) {
					streamSalida << " " << *actualRama<< " ";
			}
			++actualComponente;
			actualRama++;
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
