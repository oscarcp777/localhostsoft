/*
 * Registry.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Registry.h"
#include "Key.h"
Registry::Registry() {
	this->key = NULL;
}

Registry::~Registry() {
	if(this->key!=NULL)
		delete this->key;

	this->key=NULL;
}
Key* Registry::getKey(){
	return this->key;
}
void Registry::setKey(Key* key){
  this->key=key;
}

ContainerInsertDataBlock *Registry::getContainer() const
{
    return container;
}

void Registry::setContainer(ContainerInsertDataBlock *container)
{
    this->container = container;
}



