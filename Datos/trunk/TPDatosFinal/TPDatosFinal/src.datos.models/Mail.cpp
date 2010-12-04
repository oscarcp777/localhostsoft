/*
 * Mail.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Mail.h"
#include "KeyInteger.h"
#include "../src.datos.utils/StringUtils.h"
#include "../src.datos.utils/Define.h"
#include <list>
using namespace std;
Mail::Mail() {
	// TODO Auto-generated constructor stub

}

Mail::~Mail() {
	// TODO Auto-generated destructor stub

}

string Mail::getDate()
{
	return date;
}

string Mail::getFrom()
{
	return from;
}

string Mail::getMessage()
{
	return message;
}

string Mail::getSubject()
{
	return subject;
}

string Mail::getTo()
{
	return to;
}

void Mail::setDate(string date)
{
	this->date = date;
}

void Mail::setFrom(string from)
{
	this->from = from;
}

void Mail::setMessage(string message)
{
	this->message = message;
}

void Mail::setSubject(string subject)
{
	this->subject = subject;
}

void Mail::setTo(string to)
{
	this->to = to;
}
unsigned int Mail::getSize(){
	return from.length()+to.length()+subject.length()+message.length()+date.length()
		+NUM_FIELDS_MAILS*sizeof(int)+this->getKey()->getSize();
}
int Mail::getLongBytes(){
	return getSize();
}
bool Mail::equals(Registry* comp){
	comp->getKey();
	return false;
}
void Mail::pack(Buffer* buffer){

	int totalSize = this->getSize();
	int size;
	buffer->packField(&(totalSize), sizeof(totalSize));
	this->getKey()->pack(buffer);

	size = from.length();
	buffer->packField(&size, sizeof(size));
	buffer->packField(from.c_str(),size);

	size = to.length();
	buffer->packField(&size, sizeof(size));
	buffer->packField(to.c_str(),size);

	size = subject.length();
	buffer->packField(&size, sizeof(size));
	buffer->packField(subject.c_str(),size);

	size = message.length();
	buffer->packField(&size, sizeof(size));
	buffer->packField(message.c_str(),size);

	size = date.length();
	buffer->packField(&size, sizeof(size));
	buffer->packField(date.c_str(),size);
}
void Mail::unPack(Buffer* buffer){
	int totalSize;
	int size;
	this->setKey(new KeyInteger(0));
    buffer->unPackField(&totalSize,sizeof(totalSize));
    this->getKey()->unPack(buffer);

	buffer->unPackField(&size,sizeof(size));
	buffer->unPackFieldString(from,size);

	buffer->unPackField(&size,sizeof(size));
	buffer->unPackFieldString(to,size);

	buffer->unPackField(&size,sizeof(size));
	buffer->unPackFieldString(subject,size);

	buffer->unPackField(&size,sizeof(size));
	buffer->unPackFieldString(message,size);

	buffer->unPackField(&size,sizeof(size));
	buffer->unPackFieldString(date,size);



}
int Mail::print(std::ostream& outStream){
	//this->getKey()->print();
	outStream << "****************************************************"<< endl;
	outStream << "**from: "<<from<< endl;
	outStream << "**to: "<<to<< endl;
	outStream << "**subject: "<<subject<< endl;
	outStream << "**date: "<<date<< endl;
	outStream << "**message: "<<message<< endl;
	outStream << "**IUC: "<<((KeyInteger*)(this->getKey()))->getValue()<< endl;
	outStream << "****************************************************"<< endl;

	return 1;
}
Registry* Mail::clone(){
	Mail* cloneMail = new Mail();
	cloneMail->setDate(this->getDate());
	cloneMail->setFrom(this->getFrom());
	cloneMail->setMessage(this->getMessage());
	cloneMail->setSubject(this->getSubject());
	cloneMail->setTo(this->getTo());
	cloneMail->setKey((Key*)this->getKey()->clone());
	return cloneMail;
}
int Mail::compareTo(Registry* registry){
	registry->getKey();
	return 0; //TODO implementar
}
Registry* Mail::cloneRegKey(){
   return NULL;
}
string Mail::parserCampo(string textMail,string campo ){
	int posInitial = 0;
	int posFinal = 0;
	string endLine = "\n";
	string beginMail = "<";
	string endMail = ">";
	string caracter = " =?";
	string aux="";
	string separator="";
	posInitial = textMail.find(campo.c_str(),0);
	posFinal = textMail.find(endLine.c_str(),posInitial+campo.size());
	if(posInitial >= 0 && posFinal>=0 ){
		aux= textMail.substr(posInitial+campo.size(),posFinal-(posInitial+campo.size()+1));
		if(campo.compare("\nFrom: ")==0||campo.compare("From: ")==0){
			//busco si el mail tiene <> porque si es un contacto figura como "nombreContacto <contacto@gmail.com>
			posInitial = aux.find(beginMail.c_str(),0);
			if(posInitial >= 0){
				posFinal = aux.find(endMail.c_str(),posInitial);
				aux= aux.substr(posInitial+1,posFinal-(posInitial+1));
			}
		}
		else if(campo.compare("\nSubject: ")==0||campo.compare("Subject: ")==0){
			posInitial = aux.find(caracter.c_str(),0);
			if(posInitial >= 0){
				aux= aux.substr(0,posInitial);
			}
		}
		else if(campo.compare("\nTo: ")==0||campo.compare("To: ")==0){
			//busco si el mail tiene <> porque si es un contacto figura como "nombreContacto <contacto@gmail.com>
			posInitial = aux.find(beginMail.c_str(),0);
			if(posInitial >= 0){
				posFinal = aux.find(endMail.c_str(),posInitial);
				aux= aux.substr(posInitial+1,posFinal-(posInitial+1));
			}
		}
	}

	return aux;
}
string Mail::parserMesssage(string textMail,string end){
	int posInitial = -1;
	int posFinal = -1;
	int posContent = -1;
	int posHTML = -1;
	int posAux = -1;
	int posCharset = -1;

	string endLine = "\n";
	string textPlain = "Content-Type: text/plain;";
	string charset = "charset";
	string charset1 = "ISO-8859-1";
	string charset2 = "iso-8859-1";
	string charset3 = "Windows-1252";
	string charset4 = "us-ascii";
	list<string> charsetList;
	charsetList.push_back(charset1);
	charsetList.push_back(charset2);
	charsetList.push_back(charset3);
	charsetList.push_back(charset4);
	list<string>::iterator itCharset;

	string contentHTML = "Content-Type: text/html;";
	string contentTransferEncoding = "Content-Transfer-Encoding:";
	string content1 = "quoted-printable";
	string content2 = "8bit";
	list<string> contentList;
	contentList.push_back(content1);
	contentList.push_back(content2);
	list<string>::iterator itContent;

	//puede venir MIME-Version: 1.0 TODO
	bool correct = false;

	posInitial = textMail.find(textPlain.c_str(),0); // busco Content-Type: text/plain;
	if(posInitial > 0){//si lo encuentra
		posInitial+= textPlain.size();
		posInitial = textMail.find(charset.c_str(),posInitial); // busco charset
		posInitial += charset.size();
		for(itCharset = charsetList.begin(); itCharset != charsetList.end(); itCharset++){
			//cout<<"BUSCO: "<<(*itCharset).c_str()<<endl;
			posCharset = textMail.find((*itCharset).c_str(),posInitial); // busco tipo de charset
					if(posCharset > 0){
						//cout<<"ENCONTRO: "<<*itCharset<<endl;
						posInitial = posCharset + (*itCharset).size();
						correct = true;
						break;
					}
		}

	}
	else if (posInitial < 0){
		correct = false;
	}

	if(correct){//si encontro el Content-Type: text/plain; charset=ISO-8859-1 o Content-Type: text/plain; charset=iso-8859-1 o el q sea
		correct = false;
		posContent = textMail.find(contentTransferEncoding.c_str(),posInitial); //busco Content-Transfer-Encoding:
		posHTML = textMail.find(contentHTML.c_str(),posInitial);//busco Content-Type: text/html;

		if(posContent > 0){//si existe Content-Transfer-Encoding:
			if(posHTML>0){//si existe Content-Type: text/html;
				if(posContent < posHTML){ //si Content-Transfer-Encoding: quoted-printable ESTA ANTES QUE Content-Type: text/html;
					posInitial = posContent + contentTransferEncoding.size();
					for(itContent = contentList.begin(); itContent != contentList.end(); itContent++){
						posAux = textMail.find((*itContent).c_str(),posInitial); // busco los content (quoted-printable, 8bits, etc)
						if(posAux > 0){
							//cout<<"ENCONTRO: "<<*itContent<<endl;
							posInitial = posAux + (*itContent).size();
							correct = true;
							break;
						}
					}
				}
				else if(posContent > posHTML){
					correct = true;
				}
			}
			else if(posHTML<0) {//si no existe Content-Type: text/html; o posContent no es menor q posHTML
				posInitial = posContent + contentTransferEncoding.size();
				for(itContent = contentList.begin(); itContent != contentList.end(); itContent++){
					posAux = textMail.find((*itContent).c_str(),posInitial); // busco los content (quoted-printable, 8bits, etc)
					if(posAux > 0){
						//cout<<"ENCONTRO: "<<*itContent<<endl;
						posInitial= posAux + (*itContent).size();
						correct = true;
						break;
					}
				}

			}

		}
		else if(posContent < 0){ //si no existe Content-Transfer-Encoding:
			correct = true;
		}
	}
	else if(!correct){
	}



	if(correct){
		posAux = textMail.find(endLine.c_str(),posInitial);// busco el fin de linea
		if(posAux > 0)
			posInitial = posAux + endLine.size();

		posFinal = textMail.find(end.c_str(),posInitial);
		if(posFinal < 0 )// si no encuentra el \n-- es porque era el unico tag
			posFinal = textMail.size();// entonces el mensaje es hasta el final del archivo
		return textMail.substr(posInitial,posFinal-(posInitial+1));
	}


	return "";
}

void Mail::parseMail(char* text){
	string textMail = text;
	string date = "Date: ";
	string to = "To: ";
	string from = "From: ";
	string subject = "Subject: ";
	string message = "Content-Type: text/plain;";
	string endLine = "\n";
	string end = "\n--";

	if(CONNECT == 1){
//		cout<<"*******************************************************************"<<endl;
//		cout<<text<<endl;
//		cout<<"*******************************************************************"<<endl;
		this->setDate(this->parserCampo(textMail,endLine+date));
		this->setTo(this->parserCampo(textMail,endLine+to));
		this->setFrom(this->parserCampo(textMail,endLine+from));
		this->setSubject(this->parserCampo(textMail,endLine+subject));
		string messageNew=StringUtils::replaceCharacterASCII(this->parserMesssage(textMail,end));
		this->setMessage(messageNew);
	}
	else{
		end = "¡¡END MAIL!!";
		textMail+=end;
		this->setDate(this->parserCampo(textMail,date));
		this->setTo(this->parserCampo(textMail,to));
		this->setFrom(this->parserCampo(textMail,from));
		this->setSubject(this->parserCampo(textMail,subject));
		this->setMessage(this->parserMesssage(textMail,end));
	}
}

string Mail::toString(){
		return ("FROM: "+ from +"\n"+"TO: " +to+"\n"+"DATE: "+date+"\n"+"SUBJECT: "+subject+"\n"+"MESSAGE"+"\n"+message+"\n");
}
int Mail::getIuc(){
	return ((KeyInteger*)this->getKey())->getValue();
}
bool Mail::containCondition(int condition,string value){
	switch(condition){
	case FROM:
		if(this->getFrom().compare(value.c_str()) == 0)
			return true;

	case TO:
		if(this->getTo().compare(value.c_str()) == 0)
			return true;

	case SUBJECT:
		if(this->getSubject().compare(value.c_str()) == 0)
			return true;

	case DATE:

		if(this->getDate().compare(value.c_str()) == 0)
			return true;

	default:
		return false;
		}

		return false;
}


string Mail::getCondition(int condition){
	switch(condition){
	case FROM:
		return this->getFrom();

	case TO:
		return this->getTo();

	case SUBJECT:
		return this->getSubject();

	case DATE:
		return this->getDate();

	default:
		return NULL;
		}

		return NULL;
}
