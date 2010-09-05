#include<stdio.h>
#include<cstring>
#include<sstream>
#include<iostream>
#include "campo.hpp"
#include "campo_entero.hpp"
#include "campo_booleano.hpp"
#include "campo_doble.hpp"
#include "campo_flotante.hpp"
#include "campo_largo.hpp"
#include "campo_cadena.hpp"
#include "esquema.hpp"
#include "clave.hpp"
#include "archivo.hpp"
#include "buffer.hpp"
#include "registro.hpp"
#include "RegistroLongitudFija.hpp"
#include "EstrategiaEspacioLibreBloque.hpp"
#include "EstrategiaAlmacenamientoRegistros.hpp"
#include "EstrategiaAlmacenamientoBSharp.hpp"
#include "EstrategiaAlmacenamientoTexto.hpp"
#include "estrategia_indice.hpp"
#include "indice_b_sharp.hpp"
#include "indice_hash.hpp"
#include "estrategia_indice.hpp"
#include "EsquemaBloque.hpp"
#include "EstrategiaAlmacenamientoBloques.hpp"
#include "contador_referencias.hpp"
#include "puntero_intrusivo.hpp"
#include <cstdlib>
#include <ctime> 

#include "RecursoDeAlmacenamiento.hpp"
#include "EstrategiaRecurso.hpp"
#include "EstrategiaRecursoEscrituraDirecta.hpp"

class PruebaPuntero: public ContadorReferencias {
	public:
		void hacerAlgo() const throw() {
			std::cout << "Hace algo" << std::endl;
		}
};

class PruebaPunteroDerivada: public PruebaPuntero {
};

class ComparadorClaveDummy: public ComparadorClave {
	bool es_menor(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() {
		Campo::puntero idRegistro1 = registro1->obtener_campo("id");
		Campo::puntero idRegistro2 = registro2->obtener_campo("id");

		return *idRegistro1 < *idRegistro2;
	}

	bool es_mayor(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() {
		Campo::puntero idRegistro1 = registro1->obtener_campo("id");
		Campo::puntero idRegistro2 = registro2->obtener_campo("id");

		return *idRegistro1 > *idRegistro2;
	}

	bool es_igual(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() {
		Campo::puntero idRegistro1 = registro1->obtener_campo("id");
		Campo::puntero idRegistro2 = registro2->obtener_campo("id");

		return *idRegistro1 == *idRegistro2;
	}
};

class ComparadorClaveId: public ComparadorClave {
	bool es_menor(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() {
		Campo::puntero idRegistro1 = registro1->obtener_campo("id");
		Campo::puntero idRegistro2 = registro2->obtener_campo("id");

		return *idRegistro1 < *idRegistro2;
	}

	bool es_mayor(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() {
		Campo::puntero idRegistro1 = registro1->obtener_campo("id");
		Campo::puntero idRegistro2 = registro2->obtener_campo("id");

		return *idRegistro1 > *idRegistro2;
	}

	bool es_igual(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() {
		int id1 = *(int*)registro1->obtener_campo("id")->obtener_valor();
		int id2 = *(int*)registro2->obtener_campo("id")->obtener_valor();

		return id1 == id2;
	}
};

class ComparadorClaveApellido: public ComparadorClave {
	bool es_menor(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() {
		Campo::puntero apellidoRegistro1 = registro1->obtener_campo("id");
		Campo::puntero apellidoRegistro2 = registro2->obtener_campo("id");
		return *apellidoRegistro1 < *apellidoRegistro2;
	}
	bool es_mayor(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() {
                Campo::puntero apellidoRegistro1 = registro1->obtener_campo("id");
                Campo::puntero apellidoRegistro2 = registro2->obtener_campo("id");
                std::cout << "llego a obtener el valor..." << std::endl;
                return *apellidoRegistro1 > *apellidoRegistro2;
        }
	bool es_igual(Clave::puntero clave, Registro::puntero registro1, Registro::puntero registro2) const throw() {
                Campo::puntero apellidoRegistro1 = registro1->obtener_campo("id");
                Campo::puntero apellidoRegistro2 = registro2->obtener_campo("id");
                return *apellidoRegistro1 == *apellidoRegistro2;
        }
};

void mostrarRegistroEnPantalla(Registro::puntero registro)
{
    for(Registro::iterador_campos it = registro->primer_campo(); it != registro->ultimo_campo(); it++)
    {
        Campo::puntero campo = it->second;
        switch(campo->obtener_tipo_campo())
        {
            case TIPO_CAMPO_BOOLEANO:
            {
                bool flag = *(bool*)campo->obtener_valor();
                if(flag)
                    std::cout << "true" << '\t';
                else
                    std::cout << "false" << '\t';
                break;
            }
            case TIPO_CAMPO_CADENA:
            {
                string valor = *(std::string*)campo->obtener_valor();
                std::cout<< valor << '\t';
                break;
            }
            case TIPO_CAMPO_DOBLE:
            {
                double doble = *(double *)(campo->obtener_valor());
                std::cout<< doble << '\t';
                break;
            }
            case TIPO_CAMPO_ENTERO:
            {
                int entero = *(int*)campo->obtener_valor();
                std::cout<< entero << '\t';
                break;
            }
            case TIPO_CAMPO_FLOTANTE:
            {
                float flotante = *(float*)campo->obtener_valor();
                std::cout<< flotante << '\t';
                break;
            }
            case TIPO_CAMPO_LARGO:
            {
                long largo = *(long*)campo->obtener_valor();
                std::cout<< largo << '\t';
                break;
            }
            default:
                break;
        }
    }
    std::cout<<endl;
}

void probarPunteroIntrusivo() {
	PunteroIntrusivo<PruebaPuntero> p1(new PruebaPuntero);
	PunteroIntrusivo<PruebaPuntero> p2(new PruebaPunteroDerivada);
	PunteroIntrusivo<PruebaPuntero> p3;
	PunteroIntrusivo<PruebaPuntero> p4;
	const PunteroIntrusivo<PruebaPuntero>& p5 = p1;
	p3 = new PruebaPuntero();
	p3 = new PruebaPunteroDerivada();

	p4 = p1;
	p4 = p2;
	p1  < p2;
	p1 > p2;
	p1 == p2;
	p1 == p3;
	p1->hacerAlgo();
	p5->hacerAlgo();

}

void probarIndiceBSharpImprimir() {
	Esquema::puntero esquema = new Esquema();
	Clave::puntero clavePrimaria = new Clave();
	ComparadorClave::puntero comparadorClave = new ComparadorClaveDummy();
	esquema->agregar_campo("id", TIPO_CAMPO_ENTERO);
	esquema->agregar_campo("nombre", TIPO_CAMPO_CADENA);
	esquema->agregar_campo("apellido", TIPO_CAMPO_CADENA);
	esquema->agregar_campo("lalala", TIPO_CAMPO_CADENA);

	clavePrimaria->agregar_campo("id");

	IndiceBSharp::puntero indice = new IndiceBSharp("prueba-indice-imprimir", 128, esquema, clavePrimaria, comparadorClave);
	srand((unsigned) time(0));
	int cantidad_insertar = 3; //rand() % RAND_MAX;

	for (int counter = 0; counter < cantidad_insertar; ++counter) {
		RegistroLongitudVariable::puntero registro = new RegistroLongitudVariable(clavePrimaria);
		std::stringstream stream;
		std::stringstream streamApellido;
		std::stringstream streamLalala;
		int id_agregar = rand() % RAND_MAX;
		stream << "PABLO " << id_agregar; 
		streamApellido << "VIVA " << id_agregar;
		streamLalala << "LALALA " << id_agregar;

		registro->agregar_campo("id", new CampoEntero(counter));
		registro->agregar_campo("nombre", new CampoCadena(stream.str()));
		registro->agregar_campo("apellido", new CampoCadena(streamApellido.str()));
		registro->agregar_campo("lalala", new CampoCadena(streamLalala.str()));

		indice->agregar_registro(registro);
		std::cout << "REGISTRO AGREGADO id: " << id_agregar << std::endl << std::endl;
		std::cout << *(std::string*) registro->obtener_campo("nombre")->obtener_valor() << std::endl;
        std::cout << *(std::string*) registro->obtener_campo("apellido")->obtener_valor() << std::endl;
		std::cout << *(std::string*) registro->obtener_campo("lalala")->obtener_valor() << std::endl;
		std::cout << std::endl << std::endl;

	}
	indice->imprimir(std::cout);

	int cantidad_busquedas = 4; //rand() % RAND_MAX;
	for (int counter = 0; counter < cantidad_busquedas; ++counter) {
		int id_random = rand() % RAND_MAX;
		std::cout << "Random number: " << id_random << std::endl;
		Registro::puntero registroBuscar = new RegistroLongitudVariable(clavePrimaria);
		registroBuscar->agregar_campo("id", new CampoEntero(counter));

		Registro::puntero registroEncontrado = NULL;
		registroEncontrado = indice->buscar_registro(registroBuscar);

		if (registroEncontrado != NULL) {
			std::cout << "se encontro registro con campos:" << std::endl;
			std::cout << "Id encontrado: " << *(int*) registroEncontrado->obtener_campo("id")->obtener_valor() << std::endl;
			std::cout << *(std::string*) registroEncontrado->obtener_campo("nombre")->obtener_valor() << std::endl;
			std::cout << *(std::string*) registroEncontrado->obtener_campo("apellido")->obtener_valor() << std::endl;
		} else {
			std::cout << "no se encontro registro" << std::endl;
		}
	}
}

void probarIndiceBSharp() {
	std::cout << "-------PRUEBA DE INDICE X ARBOL B SHARP---------" << std::endl;
	Esquema::puntero esquema = new Esquema();
	Clave::puntero clavePrimaria = new Clave();
	ComparadorClave::puntero comparadorClave = new ComparadorClaveApellido();

	esquema->agregar_campo("id", TIPO_CAMPO_ENTERO);
	esquema->agregar_campo("nombre", TIPO_CAMPO_CADENA);
	esquema->agregar_campo("edad", TIPO_CAMPO_ENTERO);
	clavePrimaria->agregar_campo("id");

	IndiceBSharp::puntero indice = new IndiceBSharp("personas", 100, esquema, clavePrimaria, comparadorClave);

	for (int counter = 0; counter < 5; ++counter) {
		std::string nombre;
		int id;
		int edad;
		std::cout << "----INGRESE REGISTRO----" << std::endl;
		std::cout << "Ingrese id (Clave primaria): ";
		std::cin >> id;
		std::cout << "Ingrese nombre: ";
		std::cin >> nombre;
		std::cout << "Ingrese edad: ";
		std::cin >> edad;
		std::cout << "Ingrese edad: ";
		RegistroLongitudVariable::puntero registro = new RegistroLongitudVariable(clavePrimaria);
		registro->agregar_campo("id", new CampoEntero(id));
		registro->agregar_campo("nombre", new CampoCadena(nombre));
		registro->agregar_campo("edad", new CampoEntero(edad));
		indice->agregar_registro(registro);
		indice->imprimir(std::cout);
    }

	std::string opcion;
	std::ofstream salidaDebugIndice("debugIndice.log");
	indice->imprimir(salidaDebugIndice);
	salidaDebugIndice.close();
	do {
		std::cout << "--------PRUEBA DE BUSQUEDA-----" << std::endl;
		int id;
		std::cout << "Ingrese id a buscar: ";
		std::cin >> id;
		std::cout << "Se va a buscar el id: " << id << std::endl;
		RegistroLongitudVariable::puntero registro = new RegistroLongitudVariable(clavePrimaria);
		registro->agregar_campo("id", new CampoEntero(id));

		Registro::puntero registroLeido = indice->buscar_registro(registro);

		if (registroLeido != NULL) {
			std::cout << "Registro encontrado..." << std::endl;
			std::cout << "id: " << (*(int*)  registroLeido->obtener_campo("id")->obtener_valor()) << std::endl;
			std::cout << "Nombre: " << (*(std::string*) registroLeido->obtener_campo("nombre")->obtener_valor()) << std::endl;
			std::cout << "Edad: " << (*(int*) registroLeido->obtener_campo("edad")->obtener_valor()) << std::endl;
		} else {
			std::cout << "No se pudo encontrar registro con ese id..." << std::endl;
		}
		std::cout << "Desea buscar nuevamente? (SI / NO) " << std::endl;
		std::cin >> opcion;
	} while (opcion == "SI");

}


void prueba_hash_almacenamiento( void )
{
    ComparadorClave::puntero comparadorClave = new ComparadorClaveDummy();
    char nombre_archivo[1024];
    char linea[104];
    char opcion[1024];
    char cuit[16], nombrecompleto[100], nrodocumento[16], fechanacimiento[16];

    printf( "****  PRUEBA DE ALMACENAMIENTO Y BUSQUEDA POR INDICE HASH EXTENSIBLE  ****\n" );
    printf( "En esta prueba se leera el archivo datos.txt que contiene datos de personas de una base de datos real.\n" );
    printf( "El formato de los registros sera CUIT-NOMBRE_COMPLETO-NRO_DOCUMENTO-FECHA_NACIMIENTO.\n" );
    printf( "EN ESTA PRUEBA SE SUPONE REGISTROS DE LONGITUD MAXIMA FIJA.\n" );

    Clave::puntero clavePrimaria = new Clave();
	clavePrimaria->agregar_campo("cuit");

	Esquema::puntero esquema = new Esquema();
	esquema->agregar_campo("cuit",            TIPO_CAMPO_CADENA);
    esquema->agregar_campo("nrodocumento",    TIPO_CAMPO_ENTERO);
	esquema->agregar_campo("nombrecompleto",  TIPO_CAMPO_CADENA);
	esquema->agregar_campo("fechanacimiento", TIPO_CAMPO_CADENA);

    std::list<Clave::puntero> listaClaves;
    listaClaves.push_back(clavePrimaria);
    EstrategiaAlmacenamientoRegistros* est = new EstrategiaAlmacenamientoRegistros();

    printf ( "Primero escriba el nombre del archivo donde desea se guarden estos registros:\n" );
    scanf( "%s\0", nombre_archivo );
    //printf ( "Escoja el tamanio de bloque (DEBE SER MAYOR A 100 bytes) :\n" );
    //scanf( opcion );

    Archivo::puntero archivo = new Archivo(128, nombre_archivo, esquema, listaClaves);
    archivo->abrirModoBinario();

    Esquema::puntero esquema_indice = new Esquema();
    esquema->agregar_campo("cuit", TIPO_CAMPO_CADENA);
	esquema->agregar_campo("posicionAlmacenamiento", TIPO_CAMPO_ENTERO);

    //printf ( "Escoja el tamanio de bloque en el HASH (DEBE SER MAYOR A 100 bytes) :\n" );
    //scanf( opcion );

    EstrategiaIndice::puntero indice = new IndiceHash(esquema_indice, clavePrimaria, comparadorClave, 128, nombre_archivo);

    printf ( "Indexacion:\n\t1)POR CUIT\n" );

    /*Leyendo del archivo*/
    int posicion = 0;
    FILE * f = fopen( "datos.txt", "r" );
    while ( !feof(f) )
    {
        fgets( linea, 104, f );
        char *a, *b;
        a = linea;

        b = cuit;
        while ( *a!='\t' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        b = nombrecompleto;
        while ( *a!='\t' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        b = nrodocumento;
        while ( *a!='\t' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        b = fechanacimiento;
        while ( *a!='\n' && *a!='\r' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        Registro::puntero r = new RegistroLongitudFija(clavePrimaria,128);

        r->agregar_campo("cuit",           new CampoCadena( cuit ));
        r->agregar_campo("nombrecompleto", new CampoCadena(nombrecompleto));
        r->agregar_campo("fechanacimiento",new CampoCadena(fechanacimiento));
        r->agregar_campo("nrodocumento",   new CampoEntero(atoi(nrodocumento)));

        if(est->Escribir(posicion, r,archivo))
            std::cout<<"Registro guardado"<<std::endl;

        Registro::puntero r_indice = new RegistroLongitudVariable(clavePrimaria);
        r_indice->agregar_campo("cuit", new CampoCadena( cuit ));
        r_indice->agregar_campo("posicionAlmacenamiento", new CampoEntero(posicion));

        indice->agregar_registro( r_indice );

        posicion++;

    }
    fclose( f );
    /*Leyendo del archivo*/

    /*Borrar del HASH*/
    Registro::puntero registro_b = new RegistroLongitudVariable(clavePrimaria);
    printf ( "Ingrese el cuit que desea borrar:\n" );
    scanf( "%s\0", opcion );
    registro_b->agregar_campo("cuit",new CampoCadena( opcion ) );
    indice->borrar_registro( registro_b );
    /*Borrar del HASH*/
    //delete( registro_b );
    /*Buscar en HASH*/
    while (strcmp(opcion, "EXIT")!=0)
    {
        registro_b = new RegistroLongitudVariable(clavePrimaria);
        printf ( "Ingrese el cuit que esta buscando:\n" );
        scanf( "%s\0", opcion );
        registro_b->agregar_campo("cuit",new CampoCadena( opcion ));
        Registro::puntero registro_resultado;
        registro_resultado = indice->buscar_registro( registro_b );
        if (registro_resultado == NULL)
        {
            printf("No se ha encontrado el registro\n");
            return;
        }
        int pos =*((int*) registro_resultado->obtener_campo("posicionAlmacenamiento")->obtener_valor());

        RegistroLongitudVariable::puntero regLevantado = (RegistroLongitudVariable::puntero)est->Leer(pos, archivo, clavePrimaria);

        for(RegistroLongitudFija::iterador_campos it = regLevantado->primer_campo(); it != regLevantado->ultimo_campo(); it++)
        {
            Campo::puntero campo = it->second;
            switch(campo->obtener_tipo_campo())
            {
                case TIPO_CAMPO_BOOLEANO:
                {
                    bool flag = (bool)campo->obtener_valor();
                    if(flag)
                        std::cout << "true" << '\t';
                    else
                        std::cout << "false" << '\t';
                    break;
                }
                case TIPO_CAMPO_CADENA:
                {
                    string valor = *(std::string*)campo->obtener_valor();
                    std::cout<< valor << '\t';
                    break;
                }
                case TIPO_CAMPO_DOBLE:
                {
                    double doble = *(double *)(campo->obtener_valor());
                    std::cout<< doble << '\t';
                    break;
                }
                case TIPO_CAMPO_ENTERO:
                {
                    int entero = *(int*)campo->obtener_valor();
                    std::cout<< entero << '\t';
                    break;
                }
                case TIPO_CAMPO_FLOTANTE:
                {
                    float flotante = *(float*)campo->obtener_valor();
                    std::cout<< flotante << '\t';
                    break;
                }
                case TIPO_CAMPO_LARGO:
                {
                    long largo = (long)campo->obtener_valor();
                    std::cout<< largo << '\t';
                    break;
                }
                default:
                    break;
            }
        }
        std::cout<<endl;

    }
}

void probarAlmacenamientoRegistroEnArchivo()
{
    std::cout<<"PRUEBA ESTRATEGIA ALMACENAMIENTO REGISTRO EN ARCHIVO"<<std::endl;

    Clave::puntero clave = new Clave();
    std::list<Clave::puntero> listaClaves;
    Esquema::puntero esquema = new Esquema();
    Campo::puntero campoDni = new CampoEntero(89);
    Campo::puntero campoNombre = new CampoCadena("connie");
    RegistroLongitudVariable::puntero reg = new RegistroLongitudVariable(clave);
    EstrategiaAlmacenamientoRegistros::puntero est = new EstrategiaAlmacenamientoRegistros();

    listaClaves.push_back(clave);
    esquema->agregar_campo("dni", TIPO_CAMPO_ENTERO);
    esquema->agregar_campo("nombre", TIPO_CAMPO_CADENA);

    Archivo::puntero archivo = new Archivo(1024, "test_ear.dat", esquema, listaClaves);

    reg->agregar_campo("dni", campoDni);
    reg->agregar_campo("nombre", campoNombre);

    archivo->abrirModoBinario();
    if(est->Escribir(0,reg,archivo))
        std::cout<<"Registro guardado"<<std::endl;
    archivo->cerrar();

    archivo->abrirModoBinario();
    RegistroLongitudVariable::puntero regLevantado = est->Leer(0, archivo, clave);
    if(regLevantado!=0)
        std::cout<<"Registro leido"<<std::endl;
    archivo->cerrar();

    for(RegistroLongitudFija::iterador_campos it = regLevantado->primer_campo(); it != regLevantado->ultimo_campo(); it++)
    {
        Campo::puntero campo = it->second;
        switch(campo->obtener_tipo_campo())
        {
            case TIPO_CAMPO_BOOLEANO:
            {
                bool flag = (bool)campo->obtener_valor();
                if(flag)
                    std::cout << "true" << '\t';
                else
                    std::cout << "false" << '\t';
                break;
            }
            case TIPO_CAMPO_CADENA:
            {
                string valor = *(std::string*)campo->obtener_valor();
                std::cout<< valor << '\t';
                break;
            }
            case TIPO_CAMPO_DOBLE:
            {
                double doble = *(double *)(campo->obtener_valor());
                std::cout<< doble << '\t';
                break;
            }
            case TIPO_CAMPO_ENTERO:
            {
                int entero = *(int*)campo->obtener_valor();
                std::cout<< entero << '\t';
                break;
            }
            case TIPO_CAMPO_FLOTANTE:
            {
                float flotante = *(float*)campo->obtener_valor();
                std::cout<< flotante << '\t';
                break;
            }
            case TIPO_CAMPO_LARGO:
            {
                long largo = (long)campo->obtener_valor();
                std::cout<< largo << '\t';
                break;
            }
            default:
                break;
        }
    }
    std::cout<<endl;

    std::cout<<"--------------------------------------------------"<<std::endl;
}

void probarAlmacenamientoRegistroEnBuffer()
{
    std::cout<<"PRUEBA ESTRATEGIA ALMACENAMIENTO REGISTRO EN BUFFER"<<std::endl;

    Clave::puntero clave = new Clave();
    std::list<Clave::puntero> listaClaves;
    Esquema::puntero esquema = new Esquema();
    Campo::puntero campoDni = new CampoEntero(123);
    Campo::puntero campoNombre = new CampoCadena("connie");
    RegistroLongitudVariable::puntero reg = new RegistroLongitudVariable(clave);
    EstrategiaAlmacenamientoRegistros::puntero est = new EstrategiaAlmacenamientoRegistros();

    listaClaves.push_back(clave);
    esquema->agregar_campo("dni", TIPO_CAMPO_ENTERO);
    esquema->agregar_campo("nombre", TIPO_CAMPO_CADENA);

    Buffer::puntero buffer = new Buffer(1024, esquema, listaClaves);

    reg->agregar_campo("dni", campoDni);
    reg->agregar_campo("nombre", campoNombre);

    if(est->Escribir(0,reg,buffer))
        std::cout<<"Registro guardado"<<std::endl;

    RegistroLongitudVariable::puntero regLevantado = est->Leer(0, buffer, clave);
    if(regLevantado!=0)
        std::cout<<"Registro leido"<<std::endl;

    for(RegistroLongitudFija::iterador_campos it = regLevantado->primer_campo(); it != regLevantado->ultimo_campo(); it++)
    {
        Campo::puntero campo = it->second;
        switch(campo->obtener_tipo_campo())
        {
            case TIPO_CAMPO_BOOLEANO:
            {
                bool flag = (bool)campo->obtener_valor();
                if(flag)
                    std::cout << "true" << '\t';
                else
                    std::cout << "false" << '\t';
                break;
            }
            case TIPO_CAMPO_CADENA:
            {
                string valor = *(std::string*)campo->obtener_valor();
                std::cout<< valor << '\t';
                break;
            }
            case TIPO_CAMPO_DOBLE:
            {
                double doble = *(double *)(campo->obtener_valor());
                std::cout<< doble << '\t';
                break;
            }
            case TIPO_CAMPO_ENTERO:
            {
                int entero = *(int*)campo->obtener_valor();
                std::cout<< entero << '\t';
                break;
            }
            case TIPO_CAMPO_FLOTANTE:
            {
                float flotante = *(float*)campo->obtener_valor();
                std::cout<< flotante << '\t';
                break;
            }
            case TIPO_CAMPO_LARGO:
            {
                long largo = (long)campo->obtener_valor();
                std::cout<< largo << '\t';
                break;
            }
            default:
                break;
        }
    }
    std::cout<<endl;

    std::cout<<"--------------------------------------------------"<<std::endl;
}

void probarAlmacenamientoTextoEnArchivo()
{
    std::cout<<"PRUEBA ESTRATEGIA ALMACENAMIENTO TEXTO EN ARCHIVO"<<std::endl;

    Clave::puntero clave = new Clave();
    std::list<Clave::puntero> listaClaves;
    Esquema::puntero esquema = new Esquema();
    Campo::puntero campoConTexto = new CampoCadena("Este es un texto de prueba para almacenar en archivo");
    Campo::puntero campoConTexto2 = new CampoCadena("Otro texto mas para almacenar en archivo");
    RegistroLongitudVariable::puntero reg = new RegistroLongitudVariable(clave);
    EstrategiaAlmacenamientoTexto::puntero est = new EstrategiaAlmacenamientoTexto();

    listaClaves.push_back(clave);
    reg->agregar_campo("texto", campoConTexto);
    reg->agregar_campo("texto2", campoConTexto2);
    esquema->agregar_campo("texto", TIPO_CAMPO_CADENA);
    esquema->agregar_campo("texto2", TIPO_CAMPO_CADENA);

    Archivo::puntero archivo = new Archivo(1024, "test_eat.txt", esquema, listaClaves);

    archivo->abrirModoTexto();
    if(est->Escribir(0,reg,archivo))
        std::cout<<"Registro guardado"<<std::endl;
    archivo->cerrar();

    archivo->abrirModoTexto();
    RegistroLongitudVariable::puntero regLevantado = est->Leer(0, archivo, clave);
    if(regLevantado!=0)
        std::cout<<"Registro leido"<<std::endl;
    archivo->cerrar();

    for(RegistroLongitudVariable::iterador_campos it = regLevantado->primer_campo(); it != regLevantado->ultimo_campo(); it++)
    {
        Campo::puntero campo = it->second;
        string valor = *(std::string*)campo->obtener_valor();
        std::cout<< valor << "\t" << endl;
    }

    std::cout<<"--------------------------------------------------"<<std::endl;
}

void probarAlmacenamientoTextoEnBuffer()
{
    std::cout<<"PRUEBA ESTRATEGIA ALMACENAMIENTO TEXTO EN BUFFER"<<std::endl;

    Clave::puntero clave = new Clave();
    std::list<Clave::puntero> listaClaves;
    Esquema::puntero esquema = new Esquema();
    Campo::puntero campoConTexto = new CampoCadena("Este es un texto de prueba para almacenar en buffer");
    Campo::puntero campoConTexto2 = new CampoCadena("Otro texto mas para almacenar en buffer");
    RegistroLongitudVariable::puntero reg = new RegistroLongitudVariable(clave);
    EstrategiaAlmacenamientoTexto::puntero est = new EstrategiaAlmacenamientoTexto();

    listaClaves.push_back(clave);
    reg->agregar_campo("texto", campoConTexto);
    reg->agregar_campo("texto2", campoConTexto2);
    esquema->agregar_campo("texto", TIPO_CAMPO_CADENA);
    esquema->agregar_campo("texto2", TIPO_CAMPO_CADENA);

    Buffer::puntero buffer = new Buffer(1024, esquema, listaClaves);

    if(est->Escribir(0,reg,buffer))
        std::cout<<"Registro guardado"<<std::endl;

    RegistroLongitudVariable::puntero regLevantado = est->Leer(0, buffer, clave);
    if(regLevantado != NULL)
        std::cout<<"Registro leido"<<std::endl;

    for(RegistroLongitudVariable::iterador_campos it = regLevantado->primer_campo(); it != regLevantado->ultimo_campo(); it++)
    {
        Campo::puntero campo = it->second;
        string valor = *(std::string*)campo->obtener_valor();
        std::cout<< valor << "\t" << endl;
    }

    std::cout<<"--------------------------------------------------"<<std::endl;
}

void probarAlmacenamientoBloquesEnBuffer()
{
    std::cout<<"PRUEBA ESTRATEGIA ALMACENAMIENTO BLOQUES EN BUFFER"<<std::endl;

    //esquemas y claves
    EsquemaBloque::puntero esquemaBloques = new EsquemaBloque(5);
    Esquema::puntero esquema = new Esquema();
    std::list<Clave::puntero> listaClaves;
    Clave::puntero clave = new Clave();
    ComparadorClave::puntero comparador = new ComparadorClaveId();

    //campos
    Campo::puntero campodni = new CampoEntero(123456);
    Campo::puntero campoNombre = new CampoCadena("Alberto Gomez");
    Campo::puntero campoSueldo = new CampoFlotante(2400.78);
    Campo::puntero campoEstaCasado = new CampoBooleano(false);
    Campo::puntero campoCedula = new CampoLargo(1234567890);
    Campo::puntero campoBienes = new CampoDoble(10637.9534);

    //agrego campos a esquema
    esquema->agregar_campo("id", campodni->obtener_tipo_campo());
    esquema->agregar_campo("nombre", campoNombre->obtener_tipo_campo());
    esquema->agregar_campo("sueldo", campoSueldo->obtener_tipo_campo());
    esquema->agregar_campo("casado", campoEstaCasado->obtener_tipo_campo());
    esquema->agregar_campo("cedula", campoCedula->obtener_tipo_campo());
    esquema->agregar_campo("bienes", campoBienes->obtener_tipo_campo());
    clave->agregar_campo("id");
    listaClaves.push_back(clave);

    //registro
    RegistroLongitudVariable* reg = new RegistroLongitudVariable(clave);
    reg->agregar_campo("id", campodni);
    reg->agregar_campo("nombre", campoNombre);
    reg->agregar_campo("sueldo", campoSueldo);
    reg->agregar_campo("casado", campoEstaCasado);
    reg->agregar_campo("cedula", campoCedula);
    reg->agregar_campo("bienes", campoBienes);

    //creo buffer y estrategia
    Buffer::puntero buffer = new Buffer(1024, esquemaBloques, esquema, listaClaves);
    EstrategiaAlmacenamientoBloques* est = new EstrategiaAlmacenamientoBloques(comparador);

    if(est->Escribir(0, reg, buffer))
        std::cout<< "Registro guardado"<<endl;
    else
        std::cout<< "El registro no se pudo guardar"<<endl;

    RegistroLongitudVariable::puntero registroLeido = new RegistroLongitudVariable(clave);
    RegistroLongitudVariable::puntero registroAux = new RegistroLongitudVariable(clave);
    registroAux->agregar_campo("id", campodni);

    est->SetRegistroConDatosClave(registroAux);

    registroLeido = est->Leer(0, buffer, clave);
    if(registroLeido != 0)
    {
        std::cout << "Registro leido" << endl;
        mostrarRegistroEnPantalla(registroLeido);
    }
    else
        std::cout << "No pudo leerse el registro" << endl;

    std::cout<<"--------------------------------------------------"<<std::endl;
}

void probarAlmacenamientoBloquesEnArchivo()
{
    std::cout<<"PRUEBA ESTRATEGIA ALMACENAMIENTO BLOQUES EN ARCHIVO"<<std::endl;

    //esquemas y claves
    EsquemaBloque::puntero esquemaBloques = new EsquemaBloque(5);
    Esquema::puntero esquema = new Esquema();
    std::list<Clave::puntero> listaClaves;
    Clave::puntero clave = new Clave();
    ComparadorClave::puntero comparador = new ComparadorClaveId();

    //campos
    Campo::puntero campodni = new CampoEntero(123456);
    Campo::puntero campoNombre = new CampoCadena("Alberto Gomez");
    Campo::puntero campoSueldo = new CampoFlotante(2400.78);
    Campo::puntero campoEstaCasado = new CampoBooleano(false);
    Campo::puntero campoCedula = new CampoLargo(1234567890);
    Campo::puntero campoBienes = new CampoDoble(10637.9534);

    //campos2
    Campo::puntero campodni2 = new CampoEntero(654321);
    Campo::puntero campoNombre2 = new CampoCadena("Sandalio Zapatero");
    Campo::puntero campoSueldo2 = new CampoFlotante(5400.78);
    Campo::puntero campoEstaCasado2 = new CampoBooleano(true);
    Campo::puntero campoCedula2 = new CampoLargo(987654321);
    Campo::puntero campoBienes2 = new CampoDoble(20637.9534);

    //agrego campos a esquema
    esquema->agregar_campo("id", campodni->obtener_tipo_campo());
    esquema->agregar_campo("nombre", campoNombre->obtener_tipo_campo());
    esquema->agregar_campo("sueldo", campoSueldo->obtener_tipo_campo());
    esquema->agregar_campo("casado", campoEstaCasado->obtener_tipo_campo());
    esquema->agregar_campo("cedula", campoCedula->obtener_tipo_campo());
    esquema->agregar_campo("bienes", campoBienes->obtener_tipo_campo());
    clave->agregar_campo("id");
    listaClaves.push_back(clave);

    //registro
    RegistroLongitudVariable* reg = new RegistroLongitudVariable(clave);
    reg->agregar_campo("id", campodni);
    reg->agregar_campo("nombre", campoNombre);
    reg->agregar_campo("sueldo", campoSueldo);
    reg->agregar_campo("casado", campoEstaCasado);
    reg->agregar_campo("cedula", campoCedula);
    reg->agregar_campo("bienes", campoBienes);

    //registro2
    RegistroLongitudVariable* reg2 = new RegistroLongitudVariable(clave);
    reg2->agregar_campo("id", campodni2);
    reg2->agregar_campo("nombre", campoNombre2);
    reg2->agregar_campo("sueldo", campoSueldo2);
    reg2->agregar_campo("casado", campoEstaCasado2);
    reg2->agregar_campo("cedula", campoCedula2);
    reg2->agregar_campo("bienes", campoBienes2);

    //creo archivo y estrategia
    Archivo::puntero archivo = new Archivo(1024, "test_eab.dat", esquema, esquemaBloques, listaClaves);
    EstrategiaAlmacenamientoBloques* est = new EstrategiaAlmacenamientoBloques(comparador);

    archivo->abrirModoBinario();
    if(est->Escribir(0, reg, archivo))
    {
        archivo->ActualizarEsquemaBloque(est->GetEsquemaBloque());
        std::cout<< "Registro guardado"<<endl;
    }
    else
        std::cout<< "El registro no se pudo guardar"<<endl;
    if(est->Escribir(1, reg2, archivo))
    {
        archivo->ActualizarEsquemaBloque(est->GetEsquemaBloque());
        std::cout<< "Registro2 guardado"<<endl;
    }
    else
        std::cout<< "El registro2 no se pudo guardar"<<endl;
    archivo->cerrar();

    RegistroLongitudVariable::puntero registroLeido = new RegistroLongitudVariable(clave);
    RegistroLongitudVariable::puntero registroLeido2 = new RegistroLongitudVariable(clave);
    RegistroLongitudVariable::puntero registroAux = new RegistroLongitudVariable(clave);
    RegistroLongitudVariable::puntero registroAux2 = new RegistroLongitudVariable(clave);
    registroAux->agregar_campo("id", campodni);
    registroAux2->agregar_campo("id", campodni2);

    archivo->abrirModoBinario();

    /**IMPORTANTE SETEAR ESTE DATO PARA PODER LEER EL REGISTRO QUE QUEREMOS**/
    est->SetRegistroConDatosClave(registroAux);
    registroLeido = est->Leer(0, archivo, clave);
    /**IMPORTANTE SETEAR ESTE DATO PARA PODER LEER EL REGISTRO QUE QUEREMOS**/
    est->SetRegistroConDatosClave(registroAux2);
    registroLeido2 = est->Leer(1, archivo, clave);

    archivo->cerrar();

    if(registroLeido != 0)
    {
        std::cout << "Registro leido" << endl;
        mostrarRegistroEnPantalla(registroLeido);
    }
    else
        std::cout << "No pudo leerse el registro" << endl;

    if(registroLeido2 != 0)
    {
        std::cout << "Registro2 leido" << endl;
        mostrarRegistroEnPantalla(registroLeido2);
    }
    else
        std::cout << "No pudo leerse el registro2" << endl;

    std::cout<<"--------------------------------------------------"<<std::endl;
}

void probarAlmacenamientoBloquesEnBufferSinPosicion()
{
    std::cout<<"PRUEBA ESTRATEGIA ALMACENAMIENTO BLOQUES EN BUFFER SIN POSICION"<<std::endl;

    //esquemas y claves
    EsquemaBloque::puntero esquemaBloques = new EsquemaBloque(5);
    Esquema::puntero esquema = new Esquema();
    std::list<Clave::puntero> listaClaves;
    Clave::puntero clave = new Clave();
    ComparadorClave::puntero comparador = new ComparadorClaveId();

    //campos
    Campo::puntero campodni = new CampoEntero(123456);
    Campo::puntero campoNombre = new CampoCadena("Alberto Gomez");
    Campo::puntero campoSueldo = new CampoFlotante(2400.78);
    Campo::puntero campoEstaCasado = new CampoBooleano(false);
    Campo::puntero campoCedula = new CampoLargo(1234567890);
    Campo::puntero campoBienes = new CampoDoble(10637.9534);

    //campos2
    Campo::puntero campodni2 = new CampoEntero(654321);
    Campo::puntero campoNombre2 = new CampoCadena("Sandalio Zapatero");
    Campo::puntero campoSueldo2 = new CampoFlotante(5400.78);
    Campo::puntero campoEstaCasado2 = new CampoBooleano(true);
    Campo::puntero campoCedula2 = new CampoLargo(987654321);
    Campo::puntero campoBienes2 = new CampoDoble(20637.9534);

    //agrego campos a esquema
    esquema->agregar_campo("id", campodni->obtener_tipo_campo());
    esquema->agregar_campo("nombre", campoNombre->obtener_tipo_campo());
    esquema->agregar_campo("sueldo", campoSueldo->obtener_tipo_campo());
    esquema->agregar_campo("casado", campoEstaCasado->obtener_tipo_campo());
    esquema->agregar_campo("cedula", campoCedula->obtener_tipo_campo());
    esquema->agregar_campo("bienes", campoBienes->obtener_tipo_campo());
    clave->agregar_campo("id");
    listaClaves.push_back(clave);

    //registro
    RegistroLongitudVariable* reg = new RegistroLongitudVariable(clave);
    reg->agregar_campo("id", campodni);
    reg->agregar_campo("nombre", campoNombre);
    reg->agregar_campo("sueldo", campoSueldo);
    reg->agregar_campo("casado", campoEstaCasado);
    reg->agregar_campo("cedula", campoCedula);
    reg->agregar_campo("bienes", campoBienes);

    //registro2
    RegistroLongitudVariable* reg2 = new RegistroLongitudVariable(clave);
    reg2->agregar_campo("id", campodni2);
    reg2->agregar_campo("nombre", campoNombre2);
    reg2->agregar_campo("sueldo", campoSueldo2);
    reg2->agregar_campo("casado", campoEstaCasado2);
    reg2->agregar_campo("cedula", campoCedula2);
    reg2->agregar_campo("bienes", campoBienes2);

    //creo buffer y estrategia
    Buffer::puntero buffer = new Buffer(1024, esquemaBloques, esquema, listaClaves);
    EstrategiaAlmacenamientoBloques* est = new EstrategiaAlmacenamientoBloques(comparador);

    int posicion = est->AgregarAlFinal(reg, buffer);

    if(posicion > -1)
        std::cout<< "Registro guardado"<<endl;
    else
        std::cout<< "El registro no se pudo guardar"<<endl;

    int posicion2 = est->AgregarAlFinal(reg2, buffer);

    if(posicion2 > -1)
        std::cout<< "Registro2 guardado"<<endl;
    else
        std::cout<< "El registro2 no se pudo guardar"<<endl;

    RegistroLongitudVariable::puntero registroLeido = new RegistroLongitudVariable(clave);
    RegistroLongitudVariable::puntero registroLeido2 = new RegistroLongitudVariable(clave);
    RegistroLongitudVariable::puntero registroAux = new RegistroLongitudVariable(clave);
    RegistroLongitudVariable::puntero registroAux2 = new RegistroLongitudVariable(clave);
    registroAux->agregar_campo("id", campodni);
    registroAux2->agregar_campo("id", campodni2);

    /**IMPORTANTE SETEAR ESTE DATO PARA PODER LEER EL REGISTRO QUE QUEREMOS**/
    est->SetRegistroConDatosClave(registroAux);
    registroLeido = est->Leer(posicion, buffer, clave);
    /**IMPORTANTE SETEAR ESTE DATO PARA PODER LEER EL REGISTRO QUE QUEREMOS**/
    est->SetRegistroConDatosClave(registroAux2);
    registroLeido2 = est->Leer(posicion2, buffer, clave);

    if(registroLeido != 0)
    {
        std::cout << "Registro leido" << endl;
        mostrarRegistroEnPantalla(registroLeido);
    }
    else
        std::cout << "No pudo leerse el registro" << endl;
    if(registroLeido2 != 0)
    {
        std::cout << "Registro leido" << endl;
        mostrarRegistroEnPantalla(registroLeido2);
    }
    else
        std::cout << "No pudo leerse el registro" << endl;

    std::cout<<"--------------------------------------------------"<<std::endl;
}

void probarEsquemaBloque()
{
    EsquemaBloque* esquema = new EsquemaBloque(5);

    for(EsquemaBloque::iterador it = esquema->primerCampo(); it != esquema->ultimoCampo(); it++)
    {
        std::cout<< "Bloque " << it->first << '\t' << it->second << endl;
    }

    std::cout<< "Modificando espacio ocupado..." << endl;
    esquema->SetEspacioOcupado(3,999);
    esquema->SetEspacioOcupado(1,3432);
    esquema->SetEspacioOcupado(0,100);

    for(EsquemaBloque::iterador it = esquema->primerCampo(); it != esquema->ultimoCampo(); it++)
    {
        std::cout<< "Bloque " << it->first << '\t' << it->second << endl;
    }

    std::cout<< "Modificando espacio ocupado en bloque incorrecto..." << endl;
    esquema->SetEspacioOcupado(7,100);

    for(EsquemaBloque::iterador it = esquema->primerCampo(); it != esquema->ultimoCampo(); it++)
    {
        std::cout<< "Bloque " << it->first << '\t' << it->second << endl;
    }

    delete esquema;
}

void probarRecursoDeAlmacenamientoenBloques( void )
{
    EsquemaBloque::puntero esquemaBloques = new EsquemaBloque(25000);
    ComparadorClave::puntero comparadorClave = new ComparadorClaveDummy();
    char nombre_archivo[1024];
    char linea[104];
    char opcion[1024];
    char cuit[16], nombrecompleto[100], nrodocumento[16], fechanacimiento[16];

    printf( "****  PRUEBA DE ALMACENAMIENTO Y BUSQUEDA POR INDICE HASH EXTENSIBLE  ****\n" );
    printf( "En esta prueba se leera el archivo datos.txt que contiene datos de personas de una base de datos real.\n" );
    printf( "El formato de los registros sera CUIT-NOMBRE_COMPLETO-NRO_DOCUMENTO-FECHA_NACIMIENTO.\n" );
    printf( "EN ESTA PRUEBA SE SUPONE REGISTROS DE LONGITUD MAXIMA FIJA.\n" );

    Clave::puntero clavePrimaria = new Clave();
	clavePrimaria->agregar_campo("cuit");

    ComparadorClave::puntero comparador = new ComparadorClaveId();

	Esquema::puntero esquema = new Esquema();
	esquema->agregar_campo("cuit",            TIPO_CAMPO_CADENA);
    esquema->agregar_campo("nrodocumento",    TIPO_CAMPO_ENTERO);
	esquema->agregar_campo("nombrecompleto",  TIPO_CAMPO_CADENA);
	esquema->agregar_campo("fechanacimiento", TIPO_CAMPO_CADENA);

    std::list<Clave::puntero> listaClaves;
    listaClaves.push_back(clavePrimaria);
    EstrategiaAlmacenamientoBloques* est = new EstrategiaAlmacenamientoBloques(comparador);

    printf ( "Primero escriba el nombre del archivo donde desea se guarden estos registros:\n" );
    //scanf( "%s\0", nombre_archivo );
    sprintf(nombre_archivo,"prueba");
    //printf ( "Escoja el tamanio de bloque (DEBE SER MAYOR A 100 bytes) :\n" );
    //scanf( opcion );

    Archivo::puntero archivo = new Archivo(1024, "test_eab.dat", esquema, esquemaBloques, listaClaves);
    archivo->abrirModoBinario();
    Esquema::puntero esquema_indice = new Esquema();
    esquema->agregar_campo("cuit", TIPO_CAMPO_CADENA);
	esquema->agregar_campo("posicionAlmacenamiento", TIPO_CAMPO_ENTERO);

    //printf ( "Escoja el tamanio de bloque en el HASH (DEBE SER MAYOR A 100 bytes) :\n" );
    //scanf( opcion );
    printf ( "Indexacion:\n\t1)POR CUIT\n" );
    EstrategiaIndice::puntero indice = new IndiceHash(esquema_indice, clavePrimaria, comparadorClave, 128, nombre_archivo);
    EstrategiaRecurso::puntero directa = new EstrategiaRecursoEscrituraDirecta();
    RecursoDeAlmacenamiento::puntero recurso = new RecursoDeAlmacenamiento(directa, est, indice, archivo, NULL);

    /*Leyendo del archivo*/
    int posicion = 0;
    FILE * f = fopen( "datos.txt", "r" );
    while ( !feof(f) )
    {
        fgets( linea, 104, f );
        char *a, *b;
        a = linea;

        b = cuit;
        while ( *a!='\t' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        b = nombrecompleto;
        while ( *a!='\t' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        b = nrodocumento;
        while ( *a!='\t' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        b = fechanacimiento;
        while ( *a!='\n' && *a!='\r' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        Registro::puntero r = new RegistroLongitudFija(clavePrimaria,128);

        r->agregar_campo("cuit",           new CampoCadena( cuit ));
        r->agregar_campo("nombrecompleto", new CampoCadena(nombrecompleto));
        r->agregar_campo("fechanacimiento",new CampoCadena(fechanacimiento));
        r->agregar_campo("nrodocumento",   new CampoEntero(atoi(nrodocumento)));

        recurso->agregar_registro( r );
        //AGREGO PARA BLOQUES
        archivo->ActualizarEsquemaBloque(est->GetEsquemaBloque());

        posicion++;

    }
    fclose( f );
    /*Leyendo del archivo*/

    /*Buscar*/
    while (strcmp(opcion, "EXIT")!=0)
    {
        Registro::puntero registro_b = new RegistroLongitudVariable(clavePrimaria);
        printf ( "Ingrese el cuit que esta buscando:\n" );
        scanf( "%s\0", opcion );
        registro_b->agregar_campo("cuit",new CampoCadena( opcion ));

        Registro::puntero regLevantado;
        regLevantado = recurso->buscar_registro( registro_b );
        if (regLevantado == NULL)
        {
            printf("No se ha encontrado el registro\n");
            return;
        }

        for(RegistroLongitudFija::iterador_campos it = regLevantado->primer_campo(); it != regLevantado->ultimo_campo(); it++)
        {
            Campo::puntero campo = it->second;
            switch(campo->obtener_tipo_campo())
            {
                case TIPO_CAMPO_BOOLEANO:
                {
                    bool flag = (bool)campo->obtener_valor();
                    if(flag)
                        std::cout << "true" << '\t';
                    else
                        std::cout << "false" << '\t';
                    break;
                }
                case TIPO_CAMPO_CADENA:
                {
                    string valor = *(std::string*)campo->obtener_valor();
                    std::cout<< valor << '\t';
                    break;
                }
                case TIPO_CAMPO_DOBLE:
                {
                    double doble = *(double *)(campo->obtener_valor());
                    std::cout<< doble << '\t';
                    break;
                }
                case TIPO_CAMPO_ENTERO:
                {
                    int entero = *(int*)campo->obtener_valor();
                    std::cout<< entero << '\t';
                    break;
                }
                case TIPO_CAMPO_FLOTANTE:
                {
                    float flotante = *(float*)campo->obtener_valor();
                    std::cout<< flotante << '\t';
                    break;
                }
                case TIPO_CAMPO_LARGO:
                {
                    long largo = (long)campo->obtener_valor();
                    std::cout<< largo << '\t';
                    break;
                }
                default:
                    break;
            }
        }
        std::cout<<endl;
    }
}

void probarRecursoDeAlmacenamiento( void )
{
    ComparadorClave::puntero comparadorClave = new ComparadorClaveDummy();
    char nombre_archivo[1024];
    char linea[104];
    char opcion[1024];
    char cuit[16], nombrecompleto[100], nrodocumento[16], fechanacimiento[16];

    printf( "****  PRUEBA DE ALMACENAMIENTO Y BUSQUEDA POR INDICE HASH EXTENSIBLE  ****\n" );
    printf( "En esta prueba se leera el archivo datos.txt que contiene datos de personas de una base de datos real.\n" );
    printf( "El formato de los registros sera CUIT-NOMBRE_COMPLETO-NRO_DOCUMENTO-FECHA_NACIMIENTO.\n" );
    printf( "EN ESTA PRUEBA SE SUPONE REGISTROS DE LONGITUD MAXIMA FIJA.\n" );

    Clave::puntero clavePrimaria = new Clave();
	clavePrimaria->agregar_campo("cuit");

	Esquema::puntero esquema = new Esquema();
	esquema->agregar_campo("cuit",            TIPO_CAMPO_CADENA);
    esquema->agregar_campo("nrodocumento",    TIPO_CAMPO_ENTERO);
	esquema->agregar_campo("nombrecompleto",  TIPO_CAMPO_CADENA);
	esquema->agregar_campo("fechanacimiento", TIPO_CAMPO_CADENA);

    std::list<Clave::puntero> listaClaves;
    listaClaves.push_back(clavePrimaria);
    EstrategiaAlmacenamientoRegistros* est = new EstrategiaAlmacenamientoRegistros();

    printf ( "Primero escriba el nombre del archivo donde desea se guarden estos registros:\n" );
    //scanf( "%s\0", nombre_archivo );
    sprintf(nombre_archivo,"prueba");
    //printf ( "Escoja el tamanio de bloque (DEBE SER MAYOR A 100 bytes) :\n" );
    //scanf( opcion );

    Archivo::puntero archivo = new Archivo(128, nombre_archivo, esquema, listaClaves);
    archivo->abrirModoBinario();
    Esquema::puntero esquema_indice = new Esquema();
    esquema->agregar_campo("cuit", TIPO_CAMPO_CADENA);
	esquema->agregar_campo("posicionAlmacenamiento", TIPO_CAMPO_ENTERO);

    //printf ( "Escoja el tamanio de bloque en el HASH (DEBE SER MAYOR A 100 bytes) :\n" );
    //scanf( opcion );

    EstrategiaIndice::puntero indice = new IndiceHash(esquema_indice, clavePrimaria, comparadorClave, 128, nombre_archivo);

    printf ( "Indexacion:\n\t1)POR CUIT\n" );

    EstrategiaRecurso::puntero directa = new EstrategiaRecursoEscrituraDirecta();

    RecursoDeAlmacenamiento::puntero recurso = new RecursoDeAlmacenamiento(directa, est, indice, archivo, NULL);

    /*Leyendo del archivo*/
    int posicion = 0;
    FILE * f = fopen( "datos.txt", "r" );
    while ( !feof(f) )
    {
        fgets( linea, 104, f );
        char *a, *b;
        a = linea;

        b = cuit;
        while ( *a!='\t' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        b = nombrecompleto;
        while ( *a!='\t' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        b = nrodocumento;
        while ( *a!='\t' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        b = fechanacimiento;
        while ( *a!='\n' && *a!='\r' && *a!='\0') { *b = *a; b++; a++; } *b='\0';
        a++;

        Registro::puntero r = new RegistroLongitudFija(clavePrimaria,128);

        r->agregar_campo("cuit",           new CampoCadena( cuit ));
        r->agregar_campo("nombrecompleto", new CampoCadena(nombrecompleto));
        r->agregar_campo("fechanacimiento",new CampoCadena(fechanacimiento));
        r->agregar_campo("nrodocumento",   new CampoEntero(atoi(nrodocumento)));

        recurso->agregar_registro( r );

        posicion++;

    }
    fclose( f );
    /*Leyendo del archivo*/

    /*Buscar*/
    while (strcmp(opcion, "EXIT")!=0)
    {
        Registro::puntero registro_b = new RegistroLongitudVariable(clavePrimaria);
        printf ( "Ingrese el cuit que esta buscando:\n" );
        scanf( "%s\0", opcion );
        registro_b->agregar_campo("cuit",new CampoCadena( opcion ));

        Registro::puntero regLevantado;
        regLevantado = recurso->buscar_registro( registro_b );
        if (regLevantado == NULL)
        {
            printf("No se ha encontrado el registro\n");
            return;
        }

        for(RegistroLongitudFija::iterador_campos it = regLevantado->primer_campo(); it != regLevantado->ultimo_campo(); it++)
        {
            Campo::puntero campo = it->second;
            switch(campo->obtener_tipo_campo())
            {
                case TIPO_CAMPO_BOOLEANO:
                {
                    bool flag = (bool)campo->obtener_valor();
                    if(flag)
                        std::cout << "true" << '\t';
                    else
                        std::cout << "false" << '\t';
                    break;
                }
                case TIPO_CAMPO_CADENA:
                {
                    string valor = *(std::string*)campo->obtener_valor();
                    std::cout<< valor << '\t';
                    break;
                }
                case TIPO_CAMPO_DOBLE:
                {
                    double doble = *(double *)(campo->obtener_valor());
                    std::cout<< doble << '\t';
                    break;
                }
                case TIPO_CAMPO_ENTERO:
                {
                    int entero = *(int*)campo->obtener_valor();
                    std::cout<< entero << '\t';
                    break;
                }
                case TIPO_CAMPO_FLOTANTE:
                {
                    float flotante = *(float*)campo->obtener_valor();
                    std::cout<< flotante << '\t';
                    break;
                }
                case TIPO_CAMPO_LARGO:
                {
                    long largo = (long)campo->obtener_valor();
                    std::cout<< largo << '\t';
                    break;
                }
                default:
                    break;
            }
        }
        std::cout<<endl;
    }
}

int main(int argc, char** argv)
{
	/**pruebas indice b#**/
  //  probarIndiceBSharpImprimir();
    probarIndiceBSharp();

    /**pruebas hash**/
	//probarHash();
	//prueba_hash_almacenamiento();

	/**pruebas recurso de almacenamiento**/
	//probarRecursoDeAlmacenamientoenBloques();
    //probarRecursoDeAlmacenamiento();

	/**pruebas estrategias de almacenamiento**/
	//probarAlmacenamientoTextoEnArchivo();
	//probarAlmacenamientoTextoEnBuffer();
	//probarAlmacenamientoRegistroEnArchivo();
	//probarAlmacenamientoRegistroEnBuffer();
	//probarAlmacenamientoBloquesEnBuffer();
	//probarAlmacenamientoBloquesEnArchivo();
	//probarAlmacenamientoBloquesEnBufferSinPosicion();


	/**pruebas soporte**/
	//probarPunteroIntrusivo();
	//probarEsquemaBloque();
    return 0;
}
