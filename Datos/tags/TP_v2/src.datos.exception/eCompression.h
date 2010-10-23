/*
 * eCompression.h
 *
 *  Created on: 22/10/2010
 *      Author: oscar
 */

#ifndef ECOMPRESSION_H_
#define ECOMPRESSION_H_

#include <string>
#include <exception>

using std::exception;

class eCompression: public exception{

protected:
        std::string message;
public:
	eCompression(const std::string& amessage): exception(), message(amessage){
	    }
	virtual ~eCompression()throw(){

	}

	 const char* what() const throw()
	        {
	            return message.c_str();
	        }
};

#endif /* ECOMPRESSION_H_ */
