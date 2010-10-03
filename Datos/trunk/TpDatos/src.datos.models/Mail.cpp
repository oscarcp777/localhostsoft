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
	return 0; //TODO implementar
}
Registry* Mail::cloneRegKey(){
   return NULL;
}
void Mail::parseMail(char* text){
	int posInitial = 0;
	int posFinal = 0;
	string aux;
	string textMail = text;
	string date = "\nDate: ";
	string to = "\nTo: ";
	string from = "\nFrom: ";
	string subject = "\nSubject: ";
	string message = "Content-Type: text/plain";
	string messageId = "Message-Id:";
	string endLine = "\n";
	string delim = "--";
	string end = "=";
	string beginMail = "<";
	string endMail = ">";
	string space = " ";
	string caracter = " =?";

	if(CONNECT == 1){
//		cout<<"*******************************************************************"<<endl;
//		cout<<text<<endl;
//		cout<<"*******************************************************************"<<endl;

		posInitial = textMail.find(date.c_str(),0);
		posFinal = textMail.find(endLine.c_str(),posInitial+date.size());

		if(posInitial >= 0 && posFinal>=0 ){
			aux = textMail.substr(posInitial+date.size(),posFinal-(posInitial+date.size()+1));
			//cout<<"*************"<<aux<<"***********"<<endl;
			this->setDate(aux);
		}

		posInitial = textMail.find(to.c_str(),0);
		posFinal = textMail.find(endLine.c_str(),posInitial+to.size());

		if(posInitial >= 0 && posFinal>=0 ){
			aux = textMail.substr(posInitial+to.size(),posFinal-(posInitial+to.size()+1));
			//cout<<"*************"<<aux<<"***********"<<endl;
			this->setTo(aux);
		}

		posInitial = textMail.find(from.c_str(),0);
		posFinal = textMail.find(endLine.c_str(),posInitial+from.size());
		if(posInitial >= 0 && posFinal>=0 ){
			aux = textMail.substr(posInitial+from.size(),posFinal-(posInitial+from.size()+1));
			//busco si el mail tiene <> porque si es un contacto figura como "nombreContacto <contacto@gmail.com>
			posInitial = aux.find(beginMail.c_str(),0);

			if(posInitial >= 0){
				posFinal = aux.find(endMail.c_str(),posInitial);
				aux= aux.substr(posInitial+1,posFinal-(posInitial+1));
			}
			//cout<<"*************"<<aux<<"***********"<<endl;
			this->setFrom(aux);
		}

		posInitial = textMail.find(subject.c_str(),0);
		posFinal = textMail.find(endLine.c_str(),posInitial+subject.size());
		if(posInitial >= 0 && posFinal>=0 ){
			aux = textMail.substr(posInitial+subject.size(),posFinal-(posInitial+subject.size()+1));

			posInitial = aux.find(caracter.c_str(),0);
			if(posInitial >= 0){
				aux= aux.substr(0,posInitial);
			}

			//cout<<"*************"<<aux<<"***********"<<endl;
			this->setSubject(aux);
		}
		posInitial = textMail.find(message.c_str(),posFinal);
		posInitial = textMail.find(endLine.c_str(),posInitial);
		if(posInitial >= 0 && posFinal>=0 ){
			posFinal = textMail.find(end.c_str(),posInitial);
			aux = textMail.substr(posInitial+1,posFinal-(posInitial+1));
			this->setMessage(aux);
		}
	}
	else{

				date = "Date: ";
				to = "To: ";
				from = "From: ";
				subject = "Subject: ";
				message = "Content-Type: text/plain";
				messageId = "Message-Id:";
				endLine = "\n";
				delim = "--";
				end = "¡¡END MAIL!!";
				beginMail = "<";
				endMail = ">";
				space = " ";
				caracter = " =?";
//
//				cout<<"*******************************************************************"<<endl;
//				cout<<text<<endl;
//				cout<<"*******************************************************************"<<endl;


				posInitial = textMail.find(date.c_str(),0);
				posFinal = textMail.find(endLine.c_str(),posInitial+date.size());

				if(posInitial >= 0 && posFinal>=0 ){
					aux = textMail.substr(posInitial+date.size(),posFinal-(posInitial+date.size()+1));
					//cout<<"*************"<<aux<<"***********"<<endl;
					this->setDate(aux);
				}

				posInitial = textMail.find(to.c_str(),0);
				posFinal = textMail.find(endLine.c_str(),posInitial+to.size());

				if(posInitial >= 0 && posFinal>=0 ){
					aux = textMail.substr(posInitial+to.size(),posFinal-(posInitial+to.size()));
					//cout<<"*************"<<aux<<"***********"<<endl;
					this->setTo(aux);
				}

				posInitial = textMail.find(from.c_str(),0);
				posFinal = textMail.find(endLine.c_str(),posInitial+from.size());
				if(posInitial >= 0 && posFinal>=0 ){
					aux = textMail.substr(posInitial+from.size(),posFinal-(posInitial+from.size()));
					//busco si el mail tiene <> porque si es un contacto figura como "nombreContacto <contacto@gmail.com>
					posInitial = aux.find(beginMail.c_str(),0);

					if(posInitial >= 0){
						posFinal = aux.find(endMail.c_str(),posInitial);
						aux= aux.substr(posInitial+1,posFinal-(posInitial+1));
					}
					//cout<<"*************"<<aux<<"***********"<<endl;
					this->setFrom(aux);
				}

				posInitial = textMail.find(subject.c_str(),0);
				posFinal = textMail.find(endLine.c_str(),posInitial+subject.size());
				if(posInitial >= 0 && posFinal>=0 ){
					aux = textMail.substr(posInitial+subject.size(),posFinal-(posInitial+subject.size()+1));

					posInitial = aux.find(caracter.c_str(),0);
					if(posInitial >= 0){
						aux= aux.substr(0,posInitial);
					}

					//cout<<"*************"<<aux<<"***********"<<endl;
					this->setSubject(aux);
				}
				posInitial = textMail.find(message.c_str(),posFinal);
				posInitial = textMail.find(endLine.c_str(),posInitial);
				if(posInitial >= 0 && posFinal>=0 ){
					posFinal = textMail.find(end.c_str(),posInitial);
					aux = textMail.substr(posInitial+1,posFinal-(posInitial+1));
					this->setMessage(aux);
				}
	}
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
