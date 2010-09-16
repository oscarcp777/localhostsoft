#include "archivo.hpp"
#include "EstrategiaRecursoEscrituraDiferida.hpp"
#include "indice_secuencial.hpp"
#include "EstrategiaAlmacenamientoBloques.hpp"
#define LLENO -900

EstrategiaRecursoEscrituraDiferida::EstrategiaRecursoEscrituraDiferida()
{
    this->posicion_en_almacenamiento = -1;
    this->posicion_en_buffer = 0;
    this->xreg_ultimo = 0;
    this->total_en_buffer = 15;
    this->esquema = new EsquemaBloque(10000);
}

EstrategiaRecursoEscrituraDiferida::~EstrategiaRecursoEscrituraDiferida() throw()
{
}

int EstrategiaRecursoEscrituraDiferida::agregar_en_buffer(int ppos )
{
    if (this->posicion_en_buffer < this->total_en_buffer)
    {
        this->actualmente_en_buffer[this->posicion_en_buffer].pos_disco = ppos;
        this->actualmente_en_buffer[this->posicion_en_buffer].endisco = false;
        this->posicion_en_buffer++;
        return this->posicion_en_buffer-1;
    }
    else
    {
        return LLENO;
    }
}


int EstrategiaRecursoEscrituraDiferida::si_esta_en_buffer( int pos )
{
   for(int i=0; i < this->posicion_en_buffer; i++)
   {
        if (this->actualmente_en_buffer[i].pos_disco == pos)
            return i;
   }
    return -1;
}

int EstrategiaRecursoEscrituraDiferida::si_esta_en_buffer_ademas( int pos, int ultima_pos_encontrada )
{
   for( int i = ultima_pos_encontrada + 1; i < this->posicion_en_buffer; i++)
   {
        if (this->actualmente_en_buffer[i].pos_disco == pos)
            return i;
   }
    return -1;
}

bool EstrategiaRecursoEscrituraDiferida::agregar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()
{
    bool insertado = false;
    bool res;
    int p;

    TipoAlmacenamiento al = archivo->GetTipoAlmacenamiento();
    int pos_adivinada = 0;

    switch ( al )
    {
        case Registros:{    pos_adivinada = this->xreg_ultimo;
                            this->xreg_ultimo ++;
                            break;
                        }
        case Texto:{        pos_adivinada = this->xreg_ultimo;
                            this->xreg_ultimo ++;
                            break;
                    }
        case Bloques:{      int to = registro->GetLongitudBytes() ;
                            int t = archivo->obtener_longitud_en_bytes();
                            this->xreg_ultimo = 0;
                            int espacio_ocupado =  esquema->GetEspacioOcupado( this->xreg_ultimo);
                            int q = t - espacio_ocupado - to;
                            while ( t > to && q < 0 )
                            {
                                this->xreg_ultimo++;
                                espacio_ocupado =  esquema->GetEspacioOcupado( this->xreg_ultimo);
                                q = t - espacio_ocupado - to;
                            }
                            pos_adivinada = this->xreg_ultimo;
                            esquema->SetEspacioOcupado( this->xreg_ultimo, espacio_ocupado+to+4 );
                            this->xreg_ultimo  = 0;
                            break;
                        }
            case Compresor: { BloqueCompresor::puntero bloque_compresor = new BloqueCompresor(archivo->GetEsquema(), registro->obtener_clave_primaria(), archivo->obtener_longitud_en_bytes());
                             res = true;
                             for(int i = 0; i < this->posicion_en_buffer; i++)
                             {
                                estrategia_almacenamiento_buffer->set_por_buffer( true );
                                Registro::puntero regLevantado = estrategia_almacenamiento_buffer->Leer(i, buffer, registro->obtener_clave_primaria());
                                res = bloque_compresor->puede_agregar_componente( regLevantado );
                                if (res == true)
                                    bloque_compresor->agregar_componente( regLevantado);
                             }
                             res = bloque_compresor->puede_agregar_componente( registro );
                             if (res == true)
                                    bloque_compresor->agregar_componente( registro );
                             if (res == false)
                             {
                                 this->xreg_ultimo++;
                             }else
                             {
                                 this->posicion_en_buffer++;
                                 p = this->posicion_en_buffer - 1;
                             }

                             pos_adivinada = this->xreg_ultimo;

                             //printf("POS ADIVINADA: %d\n", pos_adivinada);
                            }
        default : break;

    }

    if (al!=Compresor)
        p = this->agregar_en_buffer( pos_adivinada );

    if ((p==LLENO) || ( al==Compresor && res==false) )
    {
        printf("\n__ESCRIBO BLOQUE__\n");
        for(int i = 0; i < this->posicion_en_buffer; i++)
        {
            estrategia_almacenamiento_buffer->set_por_buffer( true );
            Registro::puntero regLevantado = estrategia_almacenamiento_buffer->Leer(i, buffer, registro->obtener_clave_primaria());

            Registro::puntero req = new RegistroLongitudVariable( regLevantado->obtener_clave_primaria() );
            {
                Registro::iterador_campos actual_campo_clave = regLevantado->primer_campo();
                Registro::iterador_campos fin_campo_clave = regLevantado->ultimo_campo();
                while (actual_campo_clave != fin_campo_clave) {
                    Campo::puntero campo = regLevantado->obtener_campo(actual_campo_clave->first);
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
            estrategia_almacenamiento->set_por_buffer( false );

            if (al==Compresor)
            {
                estrategia_almacenamiento->Escribir(this->xreg_ultimo-1, req, archivo);
                this->posicion_en_almacenamiento = this->xreg_ultimo- 1;
                //printf("%d\n", this->xreg_ultimo);
            }
            else this->posicion_en_almacenamiento = estrategia_almacenamiento->AgregarAlFinal(req, archivo);

            if (al==Bloques)
                if (this->posicion_en_almacenamiento!=this->actualmente_en_buffer[i].pos_disco)
                {
                    //printf("PROBLEMAAAAAAA");
                    for(int j=0;j<20;j++)
                    {
                        printf( "%d\t%d\n", j, esquema->GetEspacioOcupado( j ));
                    }
                }
            if (al==Bloques)
                ((Archivo::puntero)archivo)->ActualizarEsquemaBloque(((EstrategiaAlmacenamientoBloques::puntero)estrategia_almacenamiento)->GetEsquemaBloque());
            if (this->posicion_en_almacenamiento<0)
                return insertado;
            this->actualmente_en_buffer[i].endisco = true;
        }
        this->posicion_en_buffer = 0;
        p = this->agregar_en_buffer( pos_adivinada );
        if (al == Compresor ) this->xreg_ultimo = pos_adivinada;
    }
    estrategia_almacenamiento_buffer->Escribir(p , registro, buffer);

    insertado = true;
    registro->agregar_campo("posicionAlmacenamiento", new CampoEntero( pos_adivinada ));

    return insertado;


}

bool EstrategiaRecursoEscrituraDiferida::borrar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer   ) throw()
{
    return false;
}

Registro::puntero EstrategiaRecursoEscrituraDiferida::buscar_registro( Registro::puntero registro, Almacenamiento::puntero archivo, Almacenamiento::puntero buffer, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento, EstrategiaAlmacenamiento::puntero estrategia_almacenamiento_buffer , IndiceSecuencial::puntero indice_secuencial  ) throw()
{
    bool encontrado = false;
    int posicion = *((int*) registro->obtener_campo("posicionAlmacenamiento")->obtener_valor());
    printf("INDICE ENCONTRO EN LA POS> %d\n", posicion);
    estrategia_almacenamiento->SetRegistroConDatosClave(registro);
    estrategia_almacenamiento_buffer->SetRegistroConDatosClave(registro);
    Registro::puntero regLevantado;
    /*
    ComparadorClave::puntero cc;
    if (archivo->GetTipoAlmacenamiento()==Bloques)
        cc = ((EstrategiaAlmacenamientoBloques::puntero )estrategia_almacenamiento)->GetComparador();

    if (archivo->GetTipoAlmacenamiento()==Compresor)
        cc = ((EstrategiaAlmacenamientoCompuestoComprimido::puntero)estrategia_almacenamiento)->GetComparador();

   IndiceSecuencial::puntero is = new IndiceSecuencial( cc );
   */
   regLevantado = indice_secuencial->Buscar((Buffer::puntero)buffer, registro, registro->obtener_clave_primaria());
   if ( regLevantado != NULL )
   {
       encontrado = true;
   }

    if (encontrado == false)
    {
        estrategia_almacenamiento->set_por_buffer( false );
        regLevantado = estrategia_almacenamiento->Leer(posicion, archivo, registro->obtener_clave_primaria());
       // estrategia_almacenamiento_buffer->set_por_buffer( true );
       // int p = this->agregar_en_buffer( posicion );
       // estrategia_almacenamiento_buffer->Escribir(p , regLevantado, buffer);
    }

    return regLevantado;
}
