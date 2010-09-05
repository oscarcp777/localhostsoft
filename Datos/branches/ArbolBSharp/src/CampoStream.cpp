#include "CampoStream.hpp"
#include <string.h>

CampoStream::CampoStream()
{
    buffer.str("");
	int aux =0;
	buffer.write((char*)&aux,sizeof(int));
}

CampoStream::~CampoStream() throw()
{
}

void CampoStream::reset(void)
{
	buffer.str("");
	int aux =0;
    buffer.write((char*)&aux,sizeof(int));
}

/*Retorna el tamaño en bytes del stream almacenado.*/
unsigned CampoStream::size(void){
	string aux = buffer.str();
	return aux.length();
}

/*Retorna el stream de bytes almacenados.*/
const char* CampoStream::str(void){
	buffer.seekp(0,ios::beg);
	int tam = (buffer.str()).length();
	buffer.write((char*)&tam,sizeof(int));
	buffer.seekp(0,ios::end);
	std::string str1 = buffer.str();
	return str1.c_str();
}

/*Retorna el stream de bytes almacenados.*/
string CampoStream::str_string(void){
	buffer.seekp(0,ios::beg);
	int tam = (buffer.str()).length();
	buffer.write((char*)&tam,sizeof(int));
	buffer.seekp(0,ios::end);
	return buffer.str();
}

/*Carga el stream con el bloque indicado o parametro.*/
void CampoStream::str(string& bloque, unsigned size){
	buffer.str("");
	buffer.write((char*)bloque.c_str(),sizeof(char)*size);
}

/*Carga el stream con el bloque indicado o parametro.*/
void CampoStream::str(char* bloque, unsigned size){
	buffer.str("");
	buffer.write(bloque,sizeof(char)*size);
}

/*Inserta un entero en la siguiente posicion del stream.*/
void CampoStream::insert(const void* valor, TipoCampo tipo)
{
    bool bolean;
    switch(tipo)
    {
        case TIPO_CAMPO_BOOLEANO:
            bolean = (bool) valor;
            buffer.write((char*)&(bolean),sizeof(bool));
            break;

        case TIPO_CAMPO_ENTERO:
            buffer.write((char*)&valor,sizeof(int));
            break;

        case TIPO_CAMPO_DOBLE:
            buffer.write((char*)&valor,sizeof(double));
            break;

        case TIPO_CAMPO_FLOTANTE:
            buffer.write((char*)&valor,sizeof(float));
            break;

        case TIPO_CAMPO_LARGO:
            buffer.write((char*)&valor,sizeof(long));
            break;

        case TIPO_CAMPO_CADENA:
            break;

        default:
            break;
    }
}

/*Inserta un entero en la siguiente posicion del stream.*/
void CampoStream::insert(int numero){
	buffer.write((char*)&numero,sizeof(int));
}

void CampoStream::insert(string cadena)
{
    buffer.write((char*)cadena.c_str(), sizeof(char)*cadena.length());
}

void CampoStream::insert(string cadena, int longitud)
{
    buffer.write((char*)&longitud,sizeof(int));
    buffer.write((char*)cadena.c_str(), sizeof(char)*longitud);
}

/*Obtiene un entero en la siguiente posicion del stream.*/
bool CampoStream::get(int& numero){
	buffer.read((char*)&numero,sizeof(int));
	if (buffer.fail())
		return false;
	return true;
}

/*Obtiene un entero en la siguiente posicion del stream.*/
bool CampoStream::get(float& numero){
	buffer.read((char*)&numero,sizeof(float));
	if (buffer.fail())
		return false;
	return true;
}
/*Obtiene un entero en la siguiente posicion del stream.*/
bool CampoStream::get(long& numero){
	buffer.read((char*)&numero,sizeof(long));
	if (buffer.fail())
		return false;
	return true;
}
/*Obtiene un entero en la siguiente posicion del stream.*/
bool CampoStream::get(double& numero){
	buffer.read((char*)&numero,sizeof(double));
	if (buffer.fail())
		return false;
	return true;
}

/*Obtiene un string en la siguiente posicio del stream.*/
bool CampoStream::get(string& cadena, int longitud){
	char* aux = new char[longitud+1];
	buffer.read((char*)aux,sizeof(char)*longitud);
	aux[longitud] = '\0';
	cadena = aux;
	delete[] aux;
	if (buffer.fail())
		return false;
	return true;
}

/*Obtiene un string en la siguiente posicio del stream.*/
bool CampoStream::get(char** cadena, int longitud){
	char* aux = new char[longitud+1];
	buffer.read((char*)aux,sizeof(char)*longitud);
	aux[longitud] = '\0';
	memcpy(*cadena, aux, longitud+1);
	delete[] aux;
	if (buffer.fail())
		return false;
	return true;
}

/*Obtiene un booleano en la siguiente posicio del stream.*/
bool CampoStream::get(bool& bandera){
	buffer.read((char*)&bandera,sizeof(bool));
	if (buffer.fail())
		return false;
	return true;
}

/*Desplaza al puntero del stream a la posicion indicada.*/
bool CampoStream::seek(unsigned pos){
	buffer.seekp(pos,ios::beg);
	buffer.seekg(pos,ios::beg);
	if (buffer.fail())
		return false;
	return true;
}

/*Vacia el stream.*/
void CampoStream::erase(void){
	buffer.str("");
}
