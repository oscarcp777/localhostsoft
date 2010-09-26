/*
 * Mail.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef MAIL_H_
#define MAIL_H_

#include "Registry.h"


class Mail: public Registry {

public:
	Mail();
	virtual ~Mail();
	string getDate();
	string getFrom();
	string getMessage();
	string getSubject();
	string getTo();
	unsigned int getSize();
	void setDate(string date);
	void setFrom(string from);
	void setMessage(string message);
	void setSubject(string subject);
	void setTo(string to);
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	bool equals(Registry* comp);
	int print(std::ostream& outStream);
	int getLongBytes();
	Registry* clone();
	int compareTo(Registry* registry);
	Registry* cloneRegKey();
	void parseMail(char* text);
	int getIuc();
	bool containCondition(int condition,string value);
private:
	string from;
	string to;
	string subject;
	string message;
	string date;


};



#endif /* MAIL_H_ */
