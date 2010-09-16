#include "EstrategiaAlmacenamientoBloques.hpp"
#include "archivo.hpp"
#include <iostream>

EstrategiaAlmacenamientoBloques::EstrategiaAlmacenamientoBloques(ComparadorClave::puntero comparadorClave)
{
    this->comparadorClave = comparadorClave;
    this->esquemaBloque = NULL;
}

EstrategiaAlmacenamientoBloques::~EstrategiaAlmacenamientoBloques() throw()
{
}

int EstrategiaAlmacenamientoBloques::TamanioAOcupar( Componente::puntero componente )
{
    Registro::puntero registro = componente;
    CampoStream* buffer = new CampoStream();

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
                buffer->insert(&doble, campo->obtener_tipo_campo());
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
                buffer->insert(&flotante, campo->obtener_tipo_campo());
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
    string almacenados;
    almacenados.append(buffer->str_string());

    return  almacenados.length();

}

bool EstrategiaAlmacenamientoBloques::Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    Archivo::puntero archivo = almacenamiento;
    if(archivo != NULL)
    {
        archivo->cerrar();
        archivo->abrirModoBinario();
    }
    Registro::puntero registro = componente;
    CampoStream* buffer = new CampoStream();

    this->esquemaBloque = almacenamiento->GetEsquemaBloque();
    int espacioOcupado = esquemaBloque->GetEspacioOcupado(posicion);
    //int espacioOcupado = almacenamiento->GetEspacioBloque( posicion );

    int longitudRegistro = registro->GetLongitudBytes();

    if(espacioOcupado + longitudRegistro > almacenamiento->obtener_longitud_en_bytes())
        return false;

    //bloque en donde se almacenara el registro
    char* bytesBloque = new char[almacenamiento->obtener_longitud_en_bytes()];
    char* bytes = new char[almacenamiento->obtener_longitud_en_bytes()];
    string almacenados;

    //traigo el bloque y guardo los bytes
    if(espacioOcupado > 0 && almacenamiento->leer(bytesBloque, posicion))
    {
        stringstream ss;
        ss.write(bytesBloque, espacioOcupado);
        almacenados.append(ss.str());
    }

    //gurado cada campo en el buffer
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
                buffer->insert(&doble, campo->obtener_tipo_campo());
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
                buffer->insert(&flotante, campo->obtener_tipo_campo());
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

    //agrego los campos del registro a almacenar con los datos que ya habia almacenados
    almacenados.append(buffer->str_string());
    memcpy(bytes, almacenados.c_str(), almacenados.length());

    //guardo
    bool exitoso = almacenamiento->escribir(bytes, posicion);

    ///si pudo guardarse, actualizo el espacio usado por el bloque
    if(exitoso)
        this->esquemaBloque->SetEspacioOcupado(posicion, almacenados.length());
    if(archivo != NULL) archivo->cerrar();

    return exitoso;
}

Componente::puntero EstrategiaAlmacenamientoBloques::Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave)
{
    Archivo::puntero archivo = almacenamiento;
    if(archivo != NULL)
    {
        archivo->cerrar();
        archivo->abrirModoBinario();
    }
    Esquema::puntero esquema = almacenamiento->GetEsquema();
    EsquemaBloque::puntero esquemaBloque = almacenamiento->GetEsquemaBloque();
    char* bytesBloque = new char[almacenamiento->obtener_longitud_en_bytes()];
    RegistroLongitudVariable::puntero registro = new RegistroLongitudVariable(clave);

    int longitudRegistro = 0;
    CampoStream::puntero buffer = new CampoStream();
    bool encontrado = false;
    int espacioOcupado = esquemaBloque->GetEspacioOcupado(posicion);

    if(almacenamiento->leer(bytesBloque, posicion))
    {
        buffer->str(bytesBloque, almacenamiento->obtener_longitud_en_bytes());

        //obtengo tamanio total
        int tamanioTotal = 0;
        int bytesLeidos = 0;

        tamanioTotal = 0;
        buffer->get(tamanioTotal);
        bytesLeidos += sizeof(int);

        while(!encontrado && bytesLeidos < espacioOcupado && tamanioTotal > 0)
        {
            //busco los campos de un registro de acuerdo al esquema del mismo
            for(Esquema::iterador_campos it = esquema->primer_campo(); it != esquema->ultimo_campo(); it++)
            {
                switch(it->second)
                {
                    case TIPO_CAMPO_BOOLEANO:
                        {
                            bool valor;
                            buffer->get(valor);
                            CampoBooleano::puntero campo = new CampoBooleano(valor);
                            registro->agregar_campo(it->first, campo);
                            bytesLeidos += sizeof(bool);
                        }
                        break;

                    case TIPO_CAMPO_ENTERO:
                        {
                            int valor;
                            buffer->get(valor);
                            CampoEntero::puntero campo = new CampoEntero(valor);
                            registro->agregar_campo(it->first, campo);
                            bytesLeidos += sizeof(int);
                        }
                        break;

                    case TIPO_CAMPO_DOBLE:
                        {
                            double valor;
                            buffer->get(valor);
                            CampoDoble::puntero campo = new CampoDoble(valor);
                            registro->agregar_campo(it->first, campo);
                            bytesLeidos += sizeof(double);
                        }
                        break;

                    case TIPO_CAMPO_FLOTANTE:
                        {
                            float valor;
                            buffer->get(valor);
                            CampoFlotante::puntero campo = new CampoFlotante(valor);
                            registro->agregar_campo(it->first, campo);
                            bytesLeidos += sizeof(float);
                        }
                        break;

                    case TIPO_CAMPO_LARGO:
                        {
                            long valor;
                            buffer->get(valor);
                            CampoLargo::puntero campo = new CampoLargo(valor);
                            registro->agregar_campo(it->first, campo);
                            bytesLeidos += sizeof(long);
                        }
                        break;

                    case TIPO_CAMPO_CADENA:
                        {
                            string valor;
                            int longitud;
                            buffer->get(longitud);
                            buffer->get(valor, longitud);
                            CampoCadena::puntero campo = new CampoCadena(valor);
                            registro->agregar_campo(it->first, campo);
                            bytesLeidos += longitud;
                        }
                        break;

                    default:
                        break;
                }
            }

            if ( comparadorClave->es_igual(clave, registro, this->registroAuxiliar) )
                encontrado = true;
            else
                registro->ClearCampos();

            if (!this->por_buffer())
            {
                tamanioTotal = 0;
                buffer->get(tamanioTotal);
                bytesLeidos += sizeof(int);
            }
        }
    }

    delete bytesBloque;
    if(archivo != NULL) archivo->cerrar();

    if (encontrado)
        return registro;
    else
        return 0;
}

int EstrategiaAlmacenamientoBloques::AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    Registro::puntero registro = componente;
    //Esta linea consume mucho tiempo
    this->esquemaBloque = almacenamiento->GetEsquemaBloque();
    int longitudRegistro = registro->GetLongitudBytes();
    int espacioOcupado = 0;
    int posicion = -1;

    for(int i = 0; i < this->esquemaBloque->GetCantidadDeBloques(); i++)
    {
        espacioOcupado = this->esquemaBloque->GetEspacioOcupado(i);
        if(espacioOcupado + longitudRegistro <= almacenamiento->obtener_longitud_en_bytes())
        {
            posicion = i;
            break;
        }
    }

    if(posicion != -1 && this->Escribir(posicion, componente, almacenamiento))
        return posicion;
    return -1;
}

void EstrategiaAlmacenamientoBloques::SetRegistroConDatosClave(Registro::puntero registroAuxiliar)
{
    this->registroAuxiliar = registroAuxiliar;
}

EsquemaBloque::puntero EstrategiaAlmacenamientoBloques::GetEsquemaBloque()
{
    return this->esquemaBloque;
}

ComparadorClave::puntero EstrategiaAlmacenamientoBloques::GetComparador()
{
    return this->comparadorClave;
}

bool EstrategiaAlmacenamientoBloques::Eliminar(int posicion, Almacenamiento::puntero almacenamiento)
{
    this->esquemaBloque = almacenamiento->GetEsquemaBloque();
    this->esquemaBloque->SetEspacioOcupado(posicion, 0);
    char* bytes = new char[almacenamiento->obtener_longitud_en_bytes()];
    bool exitoso = almacenamiento->escribir(bytes, posicion);
    if(exitoso)
        almacenamiento->ActualizarEsquemaBloque(this->esquemaBloque);

    delete bytes;
    return exitoso;
}

