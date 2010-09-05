/*
 * Registry.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Registry.h"
#include "Key.h"
Registry::Registry() {
	// TODO Auto-generated constructor stub

}

Registry::~Registry() {
	delete this->key;
}
Key* Registry::getKey(){
	return this->key;
}
void Registry::setKey(Key* key){
  this->key=key;
}
