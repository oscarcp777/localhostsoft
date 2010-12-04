/*
 * Session.h
 *
 *  Created on: 04/12/2010
 *      Author: Richard
 */

#ifndef SESSION_H_
#define SESSION_H_
#include <iostream>
#include "Controller.h"
#include "gmail-poptest.h"

using namespace std;
class Session {
private:
	string email;
	string pass;
	Controller* control;
	Session();
public:
	void setMail(string mail);
	void setPass(string pass);
	string getMail();
	string getPass();
	void setController();
	Controller* getController(string mail, string password);
	int checkMailAndPass(string mail, string password);
	virtual ~Session();
	/**
	 * Singleton, metodo devuelve instancia unica de la clase
	 */
	static Session *getInstance();
	/**
	 * Instancia singleton de la clase
	 */
	static Session *instance;
};

#endif /* SESSION_H_ */
