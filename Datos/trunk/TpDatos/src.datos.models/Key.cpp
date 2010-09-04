/*
 * Key.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Key.h"

Key::Key() {
	// TODO Auto-generated constructor stub

}

Key::~Key() {
	// TODO Auto-generated destructor stub
}
int Key::getValue(){
	return this->value;
}

bool Key::equals(Component* comp){
	Key* key= (Key*)comp;
	if(this->value == key->getValue())
		return true;

	else
		return false;

}
