#include "EstrategiaAlmacenamientoTexto.hpp"
#include<iostream>

EstrategiaAlmacenamientoTexto::EstrategiaAlmacenamientoTexto()
{}

EstrategiaAlmacenamientoTexto::~EstrategiaAlmacenamientoTexto() throw()
{}

bool EstrategiaAlmacenamientoTexto::Escribir(int posicion, Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    Registro::puntero registro = componente;
    stringstream s;
    char delimitador = '|';
    int largoRegistro = 0;

	for(Registro::iterador_campos it = registro->primer_campo(); it != registro->ultimo_campo(); it++)
    {
        Campo::puntero campo = it->second;

		switch(campo->obtener_tipo_campo())
        {
            case TIPO_CAMPO_CADENA:
            {
                string cadena = *(std::string*)campo->obtener_valor();
                s << cadena;
                s << delimitador;
                largoRegistro += cadena.length();
                break;
            }
            case TIPO_CAMPO_BOOLEANO:
            {
                bool booleano = *((bool*) campo->obtener_valor());
                if(booleano) s << "1"; else s << "0";
                s << delimitador;
                largoRegistro += 1;
                break;
            }
            case TIPO_CAMPO_ENTERO:
            {
                int integer = *((int*) campo->obtener_valor());
                s << integer;
                s << delimitador;
                stringstream aux;
                aux << integer;
                largoRegistro += aux.str().length();
                break;
            }
            case TIPO_CAMPO_DOBLE:
            {
                double doble = *((double*)  campo->obtener_valor());
                s << doble;
                s << delimitador;
                stringstream aux;
                aux << doble;
                largoRegistro += aux.str().length();
                break;
            }
            case TIPO_CAMPO_FLOTANTE:
            {
                float flotante = *((float*) campo->obtener_valor());
                s << flotante;
                s << delimitador;
                stringstream aux;
                aux << flotante;
                largoRegistro += aux.str().length();
                break;
            }
            case TIPO_CAMPO_LARGO:
            {
                long largo = *((long*) campo->obtener_valor());
                s << largo;
                s << delimitador;
                stringstream aux;
                aux << largo;
                largoRegistro += aux.str().length();
                break;
            }
        }
	}
	if(largoRegistro < almacenamiento->obtener_longitud_en_bytes())
	    for(int j = 0; j < almacenamiento->obtener_longitud_en_bytes(); j++)
	        s << " ";

	bool resultado =  almacenamiento->escribirTexto(s.str().c_str(), posicion);
	string a = s.str();
	return resultado;
}

Componente::puntero EstrategiaAlmacenamientoTexto::Leer(int posicion, Almacenamiento::puntero almacenamiento, Clave::puntero clave)
{
    Esquema::puntero esquema = almacenamiento->GetEsquema();
    Registro::puntero aux = new RegistroLongitudVariable(clave);
    char* bytes = new char[almacenamiento->obtener_longitud_en_bytes()];

    if(almacenamiento->leer(bytes, posicion))
    {
        char dato[5000];
        char linea[5000];
        strcpy(linea , bytes);

        char *a, *b;
        a = linea;
        b = dato;

        for(Esquema::iterador_campos it = esquema->primer_campo(); it != esquema->ultimo_campo(); it++)
        {
            while ( *a!='|' && *a!='\0')
            {
                *b = *a;
                b++;
                a++;
            }
            *b='\0';
            a++;

            switch(it->second)
            {
                case TIPO_CAMPO_CADENA:
                {
                    aux->agregar_campo( it->first, new CampoCadena(dato) );
                    break;
                }
                case TIPO_CAMPO_BOOLEANO:
                {
                    bool boolean = false;
                    if(dato == "1")
                        boolean = true;
                    aux->agregar_campo( it->first, new CampoBooleano(boolean) );
                    break;
                }
                case TIPO_CAMPO_ENTERO:
                {
                    aux->agregar_campo( it->first, new CampoEntero(atoi(dato)) );
                    break;
                }
                case TIPO_CAMPO_DOBLE:
                {
                    aux->agregar_campo(it->first, new CampoDoble( atof(dato)) );
                    break;
                }
                case TIPO_CAMPO_FLOTANTE:
                {
                    aux->agregar_campo( it->first, new CampoFlotante( atof(dato)) );
                    break;
                }
                case TIPO_CAMPO_LARGO:
                {
                    aux->agregar_campo( it->first, new CampoLargo( atol(dato)) );
                    break;
                }
                default: break;
            }
            b = dato;
        }
        delete[] bytes;
        return aux;
    }
    delete[] bytes;
    return 0;
}

int EstrategiaAlmacenamientoTexto::AgregarAlFinal(Componente::puntero componente, Almacenamiento::puntero almacenamiento)
{
    int posicion = almacenamiento->GetEspacioLibre();
    if(posicion != -1 && this->Escribir(posicion, componente, almacenamiento))
        return posicion;
    return -1;
}

bool EstrategiaAlmacenamientoTexto::Eliminar(int posicion, Almacenamiento::puntero almacenamiento)
{
    string blank = "";
    return almacenamiento->escribir(blank.c_str(), posicion);
}
