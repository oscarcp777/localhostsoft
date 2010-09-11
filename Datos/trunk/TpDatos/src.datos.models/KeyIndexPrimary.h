/*
 * KeyIndexPrimary.h
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#ifndef KEYINDEXPRIMARY_H_
#define KEYINDEXPRIMARY_H_
#include "Key.h"

class KeyIndexPrimary :public Key{
public:
	KeyIndexPrimary(int value);
	virtual ~KeyIndexPrimary();
private:
	int value;
};

#endif /* KEYINDEXPRIMARY_H_ */
