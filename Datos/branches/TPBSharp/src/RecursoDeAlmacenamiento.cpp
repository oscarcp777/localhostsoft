#include "RecursoDeAlmacenamiento.hpp"

RecursoDeAlmacenamiento::RecursoDeAlmacenamiento(EstrategiaRecurso::puntero estRecur, EstrategiaAlmacenamiento::puntero estAlmac,  EstrategiaAlmacenamiento::puntero estAlmacBuffer, EstrategiaIndice::puntero estIndice, Almacenamiento::puntero parchivo, Almacenamiento::puntero pbuffer)
{
    this->estrategia_almacenamiento = estAlmac;
    this->estrategia_almacenamiento_buffer = estAlmacBuffer;
    this->estrategia_indice = estIndice;
    this->estrategia_recurso = estRecur;
    this->archivo = parchivo;
    this->buffer = pbuffer;
}

RecursoDeAlmacenamiento::~RecursoDeAlmacenamiento() throw()
{
    //dtor
}


Registro::puntero RecursoDeAlmacenamiento::buscar_registro( Registro::puntero registro_consulta, IndiceSecuencial::puntero indice_secuencial )
{
    Registro::puntero registro_encontrado;
    if (this->estrategia_indice!=NULL)
    {
        registro_encontrado = this->estrategia_indice->buscar_registro( registro_consulta );
        if (registro_encontrado==NULL)
            return NULL;
        return this->estrategia_recurso->buscar_registro( registro_encontrado, this->archivo, this->buffer, this->estrategia_almacenamiento, this->estrategia_almacenamiento_buffer , indice_secuencial);
    }else
    {
        registro_encontrado = indice_secuencial->Buscar( (Archivo::puntero)this->archivo, registro_consulta, registro_consulta->obtener_clave_primaria());
        if (registro_encontrado==NULL)
            registro_encontrado = indice_secuencial->Buscar( (Buffer::puntero)this->buffer, registro_consulta, registro_consulta->obtener_clave_primaria());
        return registro_encontrado;
    }
}

bool RecursoDeAlmacenamiento::agregar_registro( Registro::puntero registro , IndiceSecuencial::puntero indice_secuencial )
{
    Registro::puntero req = new RegistroLongitudVariable( registro->obtener_clave_primaria() );
    if (this->estrategia_indice!=NULL)
    {
        Esquema::puntero esq = this->estrategia_indice->obtener_esquema()->clonar();
        Esquema::iterador_campos actual_campo_clave = esq->primer_campo();
        Esquema::iterador_campos fin_campo_clave = esq->ultimo_campo();
        fin_campo_clave--;
        while (actual_campo_clave != fin_campo_clave) {
            Campo::puntero campo = registro->obtener_campo(actual_campo_clave->first);
            switch(campo->obtener_tipo_campo())
            {
                case TIPO_CAMPO_CADENA: {std::string cadena =*((std::string*) campo->obtener_valor());
                                        req->agregar_campo(actual_campo_clave->first, new CampoCadena( cadena ));
                                         break;}
                case TIPO_CAMPO_BOOLEANO: {bool bolean = *((bool*)  campo->obtener_valor());
                                        req->agregar_campo(actual_campo_clave->first, new CampoBooleano( bolean ));
                                        break;}
                case TIPO_CAMPO_ENTERO: {int integer =*((int*)  campo->obtener_valor());
                                        req->agregar_campo(actual_campo_clave->first, new CampoEntero( integer ));
                                        break;}
                case TIPO_CAMPO_DOBLE: {double doble = *((double*)  campo->obtener_valor());
                                        req->agregar_campo(actual_campo_clave->first, new CampoDoble( doble ));
                                        break;}
                case TIPO_CAMPO_FLOTANTE: {float flotante = *((float*) campo->obtener_valor());
                                        req->agregar_campo(actual_campo_clave->first, new CampoFlotante( flotante ));
                                        break;}
                case TIPO_CAMPO_LARGO: {long largo = *((long*)  campo->obtener_valor());
                                        req->agregar_campo(actual_campo_clave->first, new CampoLargo( largo ));
                                        break;}
            }
            ++actual_campo_clave;
        }
    }
    else
        req = indice_secuencial->Buscar( (Archivo::puntero)this->archivo, registro, registro->obtener_clave_primaria());

    if (req==NULL || (this->buscar_registro(req, indice_secuencial))==NULL)
    {
        if(this->estrategia_recurso->agregar_registro( registro, this->archivo, this->buffer, this->estrategia_almacenamiento, this->estrategia_almacenamiento_buffer))
        {
            if (this->estrategia_indice!=NULL)
            {
                Registro::puntero req2 = new RegistroLongitudVariable( registro->obtener_clave_primaria() );
                Esquema::puntero esq = this->estrategia_indice->obtener_esquema()->clonar();
                Esquema::iterador_campos actual_campo_clave = esq->primer_campo();
                Esquema::iterador_campos fin_campo_clave = esq->ultimo_campo();

                while (actual_campo_clave != fin_campo_clave)
                {
                    Campo::puntero campo = registro->obtener_campo(actual_campo_clave->first);
                    switch(campo->obtener_tipo_campo())
                    {
                        case TIPO_CAMPO_CADENA: {std::string cadena =*((std::string*) campo->obtener_valor());
                                                req2->agregar_campo(actual_campo_clave->first, new CampoCadena( cadena ));
                                                 break;}
                        case TIPO_CAMPO_BOOLEANO: {bool bolean = *((bool*)  campo->obtener_valor());
                                                req2->agregar_campo(actual_campo_clave->first, new CampoBooleano( bolean ));
                                                break;}
                        case TIPO_CAMPO_ENTERO: {int integer =*((int*)  campo->obtener_valor());
                                                req2->agregar_campo(actual_campo_clave->first, new CampoEntero( integer ));
                                                break;}
                        case TIPO_CAMPO_DOBLE: {double doble = *((double*)  campo->obtener_valor());
                                                req2->agregar_campo(actual_campo_clave->first, new CampoDoble( doble ));
                                                break;}
                        case TIPO_CAMPO_FLOTANTE: {float flotante = *((float*) campo->obtener_valor());
                                                req2->agregar_campo(actual_campo_clave->first, new CampoFlotante( flotante ));
                                                break;}
                        case TIPO_CAMPO_LARGO: {long largo = *((long*)  campo->obtener_valor());
                                                req2->agregar_campo(actual_campo_clave->first, new CampoLargo( largo ));
                                                break;}
                    }
                    ++actual_campo_clave;
                }
                this->estrategia_indice->agregar_registro( req2 );
            }
            return true;
        }
        else
        {
            printf("REGISTRO NO AGREGADO\t");
            return false;
        }
    }

    printf("EL REGISTRO NO FUE AGREGADO PUES LA CLAVE YA EXISTIA\n");
    return false;
}

bool RecursoDeAlmacenamiento::remover_registro( Registro::puntero registro )
{
    this->estrategia_recurso->borrar_registro( registro, this->archivo, this->buffer, this->estrategia_almacenamiento, this->estrategia_almacenamiento_buffer  );

    if (this->estrategia_indice!=NULL)
        this->estrategia_indice->borrar_registro( registro );

    return true;
}
