/*
 * Session.cpp
 *
 *  Created on: 04/12/2010
 *      Author: Richard
 */

#include "Session.h"
Session *Session::instance = NULL;
Session::Session() {

}
Session *Session::getInstance()
{
	 if (!Session::instance)
		 Session::instance = new Session();
	 return Session::instance;
}
Session::~Session() {
	//delete this->control;
}
int Session::checkMailAndPass(string mail, string password){
	if ((mail == this->email) && (password == this->pass)){
		return 0;
	}else return 1;
}
void Session::setMail(string mail){
	this->email == mail;
}
void Session::setPass(string password){
	this->pass == password;
}
string Session::getMail(){
	return this->email;
}
string Session::getPass(){
	return this->pass;
}
void Session::setController(){

//		this->control = new Controller(this->email,this->pass);

}
Controller* Session::getController(string mail, string password){
	if (this->checkMailAndPass(mail,password)){
		return this->control;
//	}else{
//		delete this->control;
//				this->control = new Controller(this->email,this->pass);
//}
	}
	return this->control;
}

