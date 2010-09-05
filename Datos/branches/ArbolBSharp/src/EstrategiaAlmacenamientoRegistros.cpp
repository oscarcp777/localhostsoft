#include "EstrategiaAlmacenamientoRegistros.hpp"
#include<iostream>

EstrategiaAlmacenamientoRegistros::EstrategiaAlmacenamientoRegistros()
{
}

EstrategiaAlmacenamientoRegistros::~EstrategiaAlmacenamientoRegistros() throw()
{
}

bool EstrategiaAlmacenamientoRegistros::Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    Registro::puntero registro = componente;
    CampoStream* buffer = new CampoStream();
    char* bytes = new char[almacenamiento->obtener_longitud_en_bytes()];

    //recorro la lista de campos
    for(Registro::iterador_campos it = registro->primer_campo(); it != registro->ultimo_campo(); it++)
    {
        Campo::puntero campo = it->second;

        switch(campo->obtener_tipo_campo())
        {
            case TIPO_CAMPO_BOOLEANO:
            {
                bool flag = *(bool*)campo->obtener_valor();
                buffer->insert((void*)flag, campo->obtener_tipo_campo());
                break;
            }
            case TIPO_CAMPO_CADENA:
            {
                //si el campo es tipo cadena, almaceno antes la longitud de la cadena
                string valor = *(std::string*)campo->obtener_valor();
                int valorLongitud = valor.length();
                buffer->insert((void *)valorLongitud, TIPO_CAMPO_ENTERO);
                buffer->insert((string)valor);
                break;
            }
            case TIPO_CAMPO_DOBLE:
            {
                //el casteo de doble a void no se si esta bien, despues agrego prueba para este campo
                double doble = *(double*)campo->obtener_valor();
                buffer->insert((void *)&doble, campo->obtener_tipo_campo());
                break;
            }
            case TIPO_CAMPO_ENTERO:
            {
                int entero = *(int*)campo->obtener_valor();
                buffer->insert((void *)entero, campo->obtener_tipo_campo());
                break;
            }
            case TIPO_CAMPO_FLOTANTE:
            {
                //el casteo de float a void no se si esta bien, despues agrego prueba para este campo
                float flotante = *(float*)campo->obtener_valor();
                buffer->insert((void*)&flotante, campo->obtener_tipo_campo());
                break;
            }
            case TIPO_CAMPO_LARGO:
            {
                long largo = *(long*)campo->obtener_valor();
                buffer->insert((void *)largo, campo->obtener_tipo_campo());
                break;
            }
            default:
                break;
        }
    }
    string puntero = buffer->str_string();
    memcpy(bytes, puntero.c_str(), buffer->size());

    //almaceno
    bool exitoso = almacenamiento->escribir(bytes, posicion);

    delete[] bytes;
    delete buffer;

    return exitoso;
}

Componente::puntero EstrategiaAlmacenamientoRegistros::Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave)
{
    Esquema::puntero esquema = almacenamiento->GetEsquema();
    RegistroLongitudVariable::puntero registro = new RegistroLongitudVariable(clave);
    CampoStream* buffer = new CampoStream();
    char * bytes;
    bytes = (char *) malloc( almacenamiento->obtener_longitud_en_bytes() );

    //leo desde el almacenamiento en la posicion pedida
    if(almacenamiento->leer(bytes, posicion))
    {
        buffer->str(bytes, almacenamiento->obtener_longitud_en_bytes());

        //CONNIEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE                      ACA TENES QUE BUSCAR EL LARGO TOTAL
        int tamanio_total = 0;
        buffer->get( tamanio_total );

        //recorro el esquema para ver que tipo de dato tengo q crear y asignarle un nombre al campo
        for(Esquema::iterador_campos it = esquema->primer_campo(); it != esquema->ultimo_campo(); it++)
        {
            //segun el tipo de campo...
            switch(it->second)
            {
                case TIPO_CAMPO_BOOLEANO:
                {
                    bool valor;
                    buffer->get(valor);
                    CampoBooleano::puntero campo = new CampoBooleano(valor);
                    registro->agregar_campo(it->first, campo);
                    break;
                }
                case TIPO_CAMPO_CADENA:
                {
                    //si es cadena, leo primero la longitud y luego la cadena
                    string cadena;
                    int tamanio = 0;
                    buffer->get(tamanio);
                    buffer->get(cadena, tamanio);
                    CampoCadena::puntero campo = new CampoCadena(cadena);
                    registro->agregar_campo(it->first, campo);
                    break;
                }
                case TIPO_CAMPO_DOBLE:
                {
                    double doble;
                    buffer->get(doble);
                    CampoDoble::puntero campo = new CampoDoble(doble);
                    registro->agregar_campo(it->first, campo);
                    break;
                }
                case TIPO_CAMPO_ENTERO:
                {
                    int entero;
                    buffer->get(entero);
                    CampoEntero::puntero campo = new CampoEntero(entero);
                    registro->agregar_campo(it->first, campo);
                    break;
                }
                case TIPO_CAMPO_FLOTANTE:
                {
                    float flotante;
                    buffer->get(flotante);
                    CampoFlotante::puntero campo = new CampoFlotante(flotante);
                    registro->agregar_campo(it->first, campo);
                    break;
                }
                case TIPO_CAMPO_LARGO:
                {
                    long largo;
                    buffer->get(largo);
                    CampoLargo::puntero campo = new CampoLargo(largo);
                    registro->agregar_campo(it->first, campo);
                    break;
                }
                default:
                    break;
            }
        }
    }

    delete buffer;
    free (bytes);

    return registro;
}

int EstrategiaAlmacenamientoRegistros::AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    //agrega al final a componente y devuelve la posicion final
    return 0;
}
