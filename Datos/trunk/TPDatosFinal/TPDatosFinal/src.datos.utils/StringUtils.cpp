
#include "StringUtils.h"
#include "Define.h"
#include <cstdlib>
#include<sstream>
#include <time.h>
#include <QtGui>

 StringUtils::StringUtils(){
}
 string StringUtils::replaceCharacterASCII(string originalText){
	 //Acentos áéíóó y otros Ñ ñ ü
	 //Acentos =E1=E9=ED=F3=F3 y otros =D1 =F1 =FC
	 string
	 newText=StringUtils::replaceAll(originalText,"=E1",3,"a");
	 newText=StringUtils::replaceAll(newText,"=E9",3,"e");
	 newText=StringUtils::replaceAll(newText,"=ED",3,"i");
	 newText=StringUtils::replaceAll(newText,"=F3",3,"o");
	 newText=StringUtils::replaceAll(newText,"=FA",3,"u");
	 newText=StringUtils::replaceAll(newText,"=D1",3,"Ñ");
	 newText=StringUtils::replaceAll(newText,"=F1",3,"ñ");
	 newText=StringUtils::replaceAll(newText,"=A1",3,"¡");
	 newText=StringUtils::replaceAll(newText,"=2C",3,":");
	 newText=StringUtils::replaceAll(newText,"=\n",2,"");
	 newText=StringUtils::replaceAll(newText,"=",1,"");
	 return newText;
}
string StringUtils::getPassword(int cant) {
    string ramdom = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string passwordAux,password;

    for(int i=0; i<cant; i++) {
    	passwordAux+=ramdom.at(rand()%((int)ramdom.size()));
    }
    int cantChar=rand()%cant;
    if(cantChar<3)
    	cantChar=3;
    for(int i=0; i<cantChar; i++) {
        	password+=passwordAux.at(i);
        }
    return password;

}

 bool compare(int i,int j) { return (i<j); }

 string StringUtils::replaceIntChar(string text,int charactersIntToreplace, string newCharacter){
	for(unsigned int i = 0; i < text.size(); i++){
			if(int(text.at(i)) == charactersIntToreplace)
				text.replace(i, 1, newCharacter );

	    }
	    return text;
 }

 string StringUtils::replaceAll(string text,string charOld,int cantCharacterToReplace,string charNew){
	 string string1=text;
	   int position = string1.find(charOld);
	    while ( position != -1/*string::npos*/ ){
	       string1.replace( position, cantCharacterToReplace, charNew );
	       position = string1.find(charOld, position + 1 );
	    }
	    return string1;
 }
 void StringUtils::sortVector(vector<int> &vector){
	 sort(vector.begin(), vector.end(), compare);
 }
 std::string StringUtils::convertirAString( int numero){
       std::stringstream flujo;
       flujo<< numero;
        return flujo.str();
  }
 std::string  StringUtils::getValorTag(std::string nombretag,vector<string>& tokens){
 	vector<string>::iterator the_iterator;
 	string valorTag="sinValor";
 	string valor ;
 	the_iterator = tokens.begin();
 	while( the_iterator != tokens.end() ) {
 		valor = *the_iterator;
 		valor =trimPalabra(valor);
 		int posicionCaracterIgual = valor.find_first_of("=");
 		valor= valor.substr(0,posicionCaracterIgual);
 		if(valor.compare(nombretag)==0){
 			++the_iterator;
 			valorTag=*the_iterator;
 			return valorTag;
 		}
 		++the_iterator;


 	}
 	return valorTag;
 }

string StringUtils::actualizarCadena(string cadena,char char_reemplazable){
	 //nueva cadena donde se reemplazaran los valores no deseados por los que quiero que contenga la cadena
	 std::string nueva_cadena;

	 int cant_veces = 0;
	 int inc = 0;

	 //tipo ostringstream que se utiliza para ingresar un string, char, int para despues poder pasarselo a la nueva_cadena
	 //sirve mas que nada para que no tome como un ascii al asignarle a nueva_cadena un valor entero.
	 std::ostringstream ostr;
    int length=(int)cadena.length();
	 while(inc<=length){

		 //Se obtiene el valor de cada posicion de cadena y se compara en la misma con el caracter que se desea reemplazar
		 //En caso de que el caracter a reemplazar coincida con el de la posicion inc en la cadena, a nueva_cadena le
		 //asigno el caracter_reemplazable mas un entero que diferencia al resto de los caracteres.
		 //Ej: x="2" x="3" x="4" se reemplazara por x1="2" x2="3" x3="4" copiando esto en nueva_cadena.
		 if(cadena[inc]==char_reemplazable&&(cadena[inc+1]==' '||cadena[inc+1]=='=')){
		     cant_veces++;
			 ostr.str("");
			 ostr << cant_veces;
			 nueva_cadena+=char_reemplazable;
			 nueva_cadena+=ostr.str();
		 }else

		  nueva_cadena+=cadena[inc];
		  inc++;
	}

	 return nueva_cadena;

 }
int StringUtils::contadorTag(std::string cadena){
 string::iterator It = cadena.begin();
 string cadenaSinEspacios;
 int cont=0;

    while ( It != cadena.end() )
    {


		if(*It == '<'||*It == '>'){
			cont++;
				It++;
		}
		else{
			It++;
		}


    }


	return cont;
}
string StringUtils::trimPorTag(std::string cadena){
 string::iterator It = cadena.begin();
 string cadenaSinEspacios;
 bool isTag=false;
    while ( It != cadena.end() )
    {


		if(*It == '<'||isTag||*It == '>'){
				isTag=true;
		if(*It == '>'){isTag=false;}
	        	cadenaSinEspacios+=*It;
				It++;
		}
		else{
			It++;
		}


    }


	return cadenaSinEspacios;
}
string StringUtils::removeCharacter(std::string cadena){
	char point = '.';
	char coma = ',';
	char comilla = '"';
	char par1 = '(';
	char par2 = ')';
	char puntoComa = ';';
	char dosPuntos = ':';
	vector<char> vec;
	vector<char>::iterator it = vec.begin();
	vec.push_back(point);
	vec.push_back(coma);
	vec.push_back(comilla);
	vec.push_back(par1);
	vec.push_back(par2);
	vec.push_back(puntoComa);
	vec.push_back(dosPuntos);

	int i;
	for(it = vec.begin(); it != vec.end(); it++){
		 i = cadena.find((*it),0);
		while(i > 0){
			cadena.erase(i,1);
			i = cadena.find((*it),i);

		}

	}

	return cadena;
}

bool StringUtils::isDirtycharacter(std::string cadena, vector<string> vec){
	vector<string>::iterator it = vec.begin();
	bool dirty = false;

//	cout<<"caracter a comparar: "<<cadena<<endl;
	for(it = vec.begin(); it != vec.end(); it++){
		if((cadena.at(0) == (*it).at(0)) || (cadena.size() == 0)){
			dirty = true;
			break;
		}

	}

//	cout<<"dirty: "<<dirty<<endl;
	return dirty;
}
string StringUtils::trim(std::string cadena){
 string::iterator It = cadena.begin();
 string cadenaSinEspacios;
string caracter;

	while ( It != cadena.end() ){

		caracter = *It;

		if(caracter.compare(" ") == 0){
			//si el caracter es un espacio leo el siguiente
			It++;
			caracter = *It;
			if((caracter.compare(" ") == 0)){
				//si es otro espacio, itero hasta que sea distinto de espacio
	        	//cadenaSinEspacios+=*It;
				while((caracter.compare(" ") == 0)){
				It++;
				caracter = *It;
				}
				cadenaSinEspacios+=*It;
				It++;

			}
			else{
				//si lei un  espacio y el siguiente no es espacio vuelvo al primer espacio
				It--;
				//si no era otro espacio copio el caracter
				cadenaSinEspacios+=*It;
				It++;
				}

		}
		else{
			//si no es un espacio
			cadenaSinEspacios+=*It;
			It++;
		}

    }

	//cout<<"cadena q sale: "<<cadenaSinEspacios<<endl;
	return cadenaSinEspacios;
}

void StringUtils::Tokenize(const string& str, vector<string>& tokens, const string& delimiters ){
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
    	// Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}
std::string StringUtils::toUpper(std::string word){
	unsigned int i = 0;
	std::string caracter;
	while(i< word.size()){
		caracter = word.at(i);
		if(isalpha(*caracter.c_str())){
			if(islower(*caracter.c_str())){
				caracter = toupper(word.at(i));
				word[i] = *caracter.c_str();
				}
		}
		else{
			if(caracter.compare("á")==0)
				caracter = 'A';
			else if (caracter.compare("é")==0)
				caracter = 'E';

			else if (caracter.compare("í")==0)
				caracter = 'I';

			else if (caracter.compare("ó")==0)
				caracter = 'O';

			else if (caracter.compare("ú")==0)
				caracter = 'U';

			word[i] = *caracter.c_str();
			}
		i++;
		}

	return word;
}
void StringUtils::TokenizeAndTrimAndUpper(const string& str, vector<string>& tokens, const string& delimiters ){
	string point = ".";
		string coma = ",";
		string comilla = "\"";
		string par1 = "(";
		string par2 = ")";
		string puntoComa = ";";
		string dosPuntos = ":";
		string menor = "<";
		string mayor = ">";
		string pipe = "|";
		string admir1 = "!";
		string admir2 = "¡";
		string guionMedio = "-";
		string barra = "/";
		string ampersand = "&";
		string numeral = "#";
		string mas = "+";
		string arroba = "@";
		string asterisco = "*";
		string llave1 = "{";
		string llave2 = "}";
		string int1 = "?";
		string int2 = "¿";
		string com = "`";
		string cor1 = "[";
		string cor2 = "]";
		string comi = "'";
		string nuflo = "~";
		string guionBajo = "_";
		vector<string> vec;
		vec.push_back(point);
		vec.push_back(coma);
		vec.push_back(comilla);
		vec.push_back(par1);
		vec.push_back(par2);
		vec.push_back(puntoComa);
		vec.push_back(dosPuntos);
		vec.push_back(menor);
		vec.push_back(mayor);
		vec.push_back(pipe);
		vec.push_back(admir1);
		vec.push_back(admir2);
		vec.push_back(guionMedio);
		vec.push_back(barra);
		vec.push_back(ampersand);
		vec.push_back(numeral);
		vec.push_back(mas);
		vec.push_back(arroba);
		vec.push_back(asterisco);
		vec.push_back(llave1);
		vec.push_back(llave2);
		vec.push_back(int1);
		vec.push_back(int2);
		vec.push_back(com);
		vec.push_back(cor1);
		vec.push_back(cor2);
		vec.push_back(comi);
		vec.push_back(nuflo);
		vec.push_back(guionBajo);


//	cout<<"*********************EN TokenizeAndTrimAndUpper*******************************"<<endl;
//		cout<<"CADENA Q ENTRA"<<endl;
//		cout<<str<<endl;
//		cout<<"FIN CADENA"<<endl;
	// char "\n" en int 10
	//char "\r" en int 13
	//char "\t" en int 9
	QString message=  QString(str.c_str());
	QByteArray array=   message.toAscii();
	string strModifide=array.data();
	  strModifide = replaceIntChar(strModifide,10," ");
	strModifide = replaceIntChar(strModifide ,13," ");
	strModifide = replaceIntChar(strModifide ,9," ");

//	cout<<"BORRANDO CARACTERES, CADENA"<<endl;
//	cout<<strModifide<<endl;
//	cout<<"FIN CADENA"<<endl;

	// Skip delimiters at beginning.
    string::size_type lastPos = strModifide.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = strModifide.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
    	string var = strModifide.substr(lastPos, pos - lastPos);
    	// Found a token, add it to the vector.

       var = trim(var);
       var = removeCharacter(var);
     //  cout<<"VAR: "<<var<<endl;
       if(!StringUtils::isDirtycharacter(var,vec))
    	   tokens.push_back(toUpper(var));
        // Skip delimiters.  Note the "not_of"
        lastPos = strModifide.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = strModifide.find_first_of(delimiters, lastPos);
    }
}
std::string StringUtils::trimPalabra(std::string cadena){
 string::iterator It = cadena.begin();
 string cadenaSinEspacios;

    while ( It != cadena.end() )
    {
 		if(*It != ' '){
			cadenaSinEspacios+=*It;
				It++;
		}
		else{
			It++;
		}
  }
    return cadenaSinEspacios;
}

/*
 *
 */
string StringUtils::convertIntToString(int numero){

	string retorno;
	int temp;
	int tempCountFiles = numero;

	while((tempCountFiles/ 10) != 0){
		temp = tempCountFiles % 10;
		tempCountFiles = tempCountFiles/10;
		temp =temp + 48;
		retorno = (char)temp + retorno;
	}

	tempCountFiles = tempCountFiles + 48;
	retorno = (char)tempCountFiles + retorno ;
	return retorno;
}

string StringUtils::joinStringCmdLine(int argc, char* const argv[]){

	string retorno = "";
	for(int i=2;i<argc;i++){

		if(i == (argc-1)){
			retorno = retorno + argv[i];
		}else{
			retorno = retorno + argv[i] + " ";
		}
	}
	return retorno;
}

string StringUtils::convertConditionIntToString(int condition){
	string cond;


	switch(condition){
	case FROM:
				cond = "From";
				break;

	case TO:
		        cond = "To";
				break;

	case SUBJECT:
				cond ="Subject";
				break;
	case DATE:
				cond = "Date";
				break;
	default:
				cond = "";
				break;
	}
	return cond;
}
string StringUtils::chanceAccents(string str){
	  int isa=str.find("á");
	  int ise=str.find("é");
	  int isi=str.find("í");
	  int iso=str.find("ó");
	  int isu=str.find("ú");
	  int isA=str.find("Á");
	  int isE=str.find("É");
	  int isI=str.find("Í");
	  int isO=str.find("Ó");
	  int isU=str.find("Ú");
	  if(isa!=-1||ise!=-1||isi!=-1||iso!=-1||isu!=-1||isA!=-1||isE!=-1||isI!=-1||isO!=-1||isU!=-1){
		  if(isa!=-1)
	      str.replace(str.begin()+isa,str.begin()+isa+2,"A");
		  if(ise!=-1)
	      str.replace(str.begin()+ise,str.begin()+ise+2,"E");
		  if(isi!=-1)
	      str.replace(str.begin()+isi,str.begin()+isi+2,"I");
		  if(iso!=-1)
	      str.replace(str.begin()+iso,str.begin()+iso+2,"O");
		  if(isu!=-1)
	      str.replace(str.begin()+isu,str.begin()+isu+2,"U");
		  if(isA!=-1)
	      str.replace(str.begin()+isA,str.begin()+isA+2,"A");
		  if(isE!=-1)
	      str.replace(str.begin()+isE,str.begin()+isE+2,"E");
		  if(isI!=-1)
	      str.replace(str.begin()+isI,str.begin()+isI+2,"I");
		  if(isO!=-1)
	      str.replace(str.begin()+isO,str.begin()+isO+2,"O");
		  if(isU!=-1)
	      str.replace(str.begin()+isU,str.begin()+isU+2,"U");
	  }
	  return str;
}
int StringUtils::convertConditionStringToInt(string cond){

	if(cond.compare((char*)"From")==0)
		return FROM;

	else if(cond.compare((char*)"To")==0)
		return TO;

	else if(cond.compare((char*)"Subject")==0)
			return SUBJECT;

	else if(cond.compare((char*)"Date")==0)
			return DATE;

	return 0;
}
