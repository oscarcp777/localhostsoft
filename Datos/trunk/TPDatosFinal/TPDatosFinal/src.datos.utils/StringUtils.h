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
	 static string chanceAccents(string str);
	 static string getPassword(int cant);
    static std::string getValorTag(std::string nombretag,vector<string>& tokens);
    static string trim(std::string cadena);
    static string trimPorTag(std::string cadena);
	static std::string trimPalabra(std::string cadena);
	static std::string actualizarCadena(string cadena,char char_reemplazable);
	static string removeCharacter(std::string cadena);
	static void Tokenize(const string& str, vector<string>& tokens, const string& delimiters );
	static void TokenizeAndTrimAndUpper(const string& str, vector<string>& tokens, const string& delimiters);
	static int contadorTag(std::string cadena);
	static  std::string convertirAString( int numero);
	static std::string toUpper(std::string word);
	static void sortVector(vector<int> &vector);
    static int countRead;
    static int countWrite;
    static string replaceCharacterASCII(string originalText);
    static string replaceAll(string text,string charOld,int cantCharacterToReplace,string charNew);
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
	static string convertConditionIntToString(int condition);
	static int convertConditionStringToInt(string cond);
};
#endif
