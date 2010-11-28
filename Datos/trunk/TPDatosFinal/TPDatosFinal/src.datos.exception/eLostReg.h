/*
 * eLostReg.h
 *
 *  Created on: 26/10/2010
 *      Author: Richard
 */

#ifndef ELOSTREG_H_
#define ELOSTREG_H_

class eLostReg: public exception{
    protected:
        std::string message;

    public:
        eLostReg(const std::string& amessage): exception(), message(amessage)
        {
        }

        ~eLostReg()throw()
        {
        }

        const char* what() const throw()
        {
            return message.c_str();
        }
};

#endif /* ELOSTREG_H_ */
