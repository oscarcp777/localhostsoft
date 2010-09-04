/*
 * Mail.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Mail.h"

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
	return from.length()+to.length()+subject.length()+message.length()+date.length();
}
bool Mail::equals(Component* comp){
	return false;
}
void Mail::pack(Buffer* buffer){

	int totalSize = this->getSize();
	int size;
	buffer->packField(&(totalSize), sizeof(totalSize));
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
	buffer->unPackField(&totalSize,sizeof(totalSize));
	buffer->unPackField(&size,sizeof(size));
	buffer->unPackField((char*)from.c_str(),sizeof(char)*size);

	buffer->unPackField(&size,sizeof(size));
	buffer->unPackField((char*)to.c_str(),sizeof(char)*size);

	buffer->unPackField(&size,sizeof(size));
	buffer->unPackField((char*)subject.c_str(),sizeof(char)*size);

	buffer->unPackField(&size,sizeof(size));
	buffer->unPackField((char*)message.c_str(),sizeof(char)*size);

	buffer->unPackField(&size,sizeof(size));
	buffer->unPackField((char*)date.c_str(),sizeof(char)*size);



}
