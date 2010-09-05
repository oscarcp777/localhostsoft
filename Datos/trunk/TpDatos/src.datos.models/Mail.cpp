/*
 * Mail.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Mail.h"
#include "Key.h"
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
int Mail::getSize(){
	return from.length()+to.length()+subject.length()+message.length()+date.length()
		+NUM_FIELDS_MAILS*sizeof(int)+this->getKey()->getSize();
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
    this->setKey(new Key());
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
int Mail::print(){
	this->getKey()->print();
	cout << "from: "<<from<< endl;
	cout << "to: "<<to<< endl;
	cout << "subject: "<<subject<< endl;
	cout << "message: "<<message<< endl;
	cout << "date: "<<date<< endl;
	return 1;
}
