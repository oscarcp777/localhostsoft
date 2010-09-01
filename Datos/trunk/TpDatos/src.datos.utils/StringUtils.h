#ifndef __STRINGUTILS_H__
#define __STRINGUTILS_H__

#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
class StringUtils{

public:
	 StringUtils();
	/**
	* Este metodo quita los espacios en blanco entre los tag
	* de una cadena de caracteres
	*
	*/
    static std::string getValorTag(std::string nombretag,vector<string>& tokens);
    static string trim(std::string cadena);
    static string trimPorTag(std::string cadena);
	static std::string trimPalabra(std::string cadena);
	static std::string actualizarCadena(string cadena,char char_reemplazable);
	static void Tokenize(const string& str, vector<string>& tokens, const string& delimiters );
	static int contadorTag(std::string cadena);
	static  std::string convertirAString( int numero);
	static void sortVector(vector<int> &vector);
    static int countRead;
    static int countWrite;
	/*
	 * Metodos de la nueva version.
	 *
	 */
	/*
	 * Funcion que convierte un numero entero al mismo
	 * numero en una cadena de caracteres.
	 */
	static string convertIntToString(int numero);

	static string joinStringCmdLine(int argc, char* const argv[]);
};
#endif
