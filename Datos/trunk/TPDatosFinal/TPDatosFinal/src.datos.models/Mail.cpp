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
		if(campo.compare("\nSubject: ")==0||campo.compare("Subject: ")==0){
			posInitial = aux.find(caracter.c_str(),0);
			if(posInitial >= 0){
				aux= aux.substr(0,posInitial);
			}
		}
	}

	return aux;
}
string Mail::parserMesssage(string textMail,string campo,string end){
	int posInitial = 0;
	int posFinal = 0;
	posInitial = textMail.find(campo.c_str(),0);
	posInitial+= campo.size();
	posFinal = textMail.find(end.c_str(),posInitial);
	if(posInitial >= 0 && posFinal>=0 ){
		return textMail.substr(posInitial+1,posFinal-(posInitial+1));

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
		cout<<"*******************************************************************"<<endl;
		cout<<text<<endl;
		cout<<"*******************************************************************"<<endl;
		this->setDate(this->parserCampo(textMail,endLine+date));
		this->setTo(this->parserCampo(textMail,endLine+to));
		this->setFrom(this->parserCampo(textMail,endLine+from));
		this->setSubject(this->parserCampo(textMail,endLine+subject));
		this->setMessage(this->parserMesssage(textMail,message,end));
	}
	else{
		end = "¡¡END MAIL!!";
		textMail+=end;
		this->setDate(this->parserCampo(textMail,date));
		this->setTo(this->parserCampo(textMail,to));
		this->setFrom(this->parserCampo(textMail,from));
		this->setSubject(this->parserCampo(textMail,subject));
		this->setMessage(this->parserMesssage(textMail,message,end));
	}
}

string Mail::toString(){
		return ("FROM: "+ from +"\n"+"TO: " +to+"\n"+"DATE: "+date+"\n"+subject+"subject"+"\n"+"MESSAGE"+message+"\n");
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
