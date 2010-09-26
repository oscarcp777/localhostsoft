/*
 * Mail.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Mail.h"
#include "KeyInteger.h"
#include "../src.datos.utils/StringUtils.h"
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
		+NUM_FIELDS_MAILS*sizeof(int)/*+this->getKey()->getSize()*/;
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
	string date = "Date:";
	string to = "To:";
	string from = "From:";
	string subject = "Subject:";
	string message = "Content-Type: text/plain";
	string messageId = "Message-Id:";
	string endLine = "\n";
	string delim = "--";
	string end = "=";


	posInitial = textMail.find(date.c_str(),0);
	posFinal = textMail.find(endLine.c_str(),posInitial);
	aux = textMail.substr(posInitial+date.size(),posFinal-(posInitial+date.size()));
	this->setDate(StringUtils::trim(aux));

	posInitial = textMail.find(to.c_str(),0);
	posFinal = textMail.find(endLine.c_str(),posInitial);
	aux = textMail.substr(posInitial+to.size(),posFinal-(posInitial+to.size()));
	this->setTo(StringUtils::trim(aux));

	posInitial = textMail.find(from.c_str(),0);
	posFinal = textMail.find(endLine.c_str(),posInitial);
	aux = textMail.substr(posInitial+from.size(),posFinal-(posInitial+from.size()));
	string aux2 = "";
	aux2 = StringUtils::trim(aux);
	cout<<"*************"<<aux2<<"***********"<<endl;
	this->setFrom(aux2);

	posInitial = textMail.find(subject.c_str(),0);
	posFinal = textMail.find(endLine.c_str(),posInitial);
	aux = textMail.substr(posInitial+subject.size(),posFinal-(posInitial+subject.size()));
	this->setSubject(aux);

	posInitial = textMail.find(message.c_str(),posFinal);
	posInitial = textMail.find(endLine.c_str(),posInitial);
	posFinal = textMail.find(end.c_str(),posInitial);
	aux = textMail.substr(posInitial+1,posFinal-posInitial);
	this->setMessage(aux);

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
