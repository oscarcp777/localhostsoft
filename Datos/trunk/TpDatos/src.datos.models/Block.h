/*
 * Block.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <list>
#include <iostream>
#include<algorithm>
#include "Component.h"
#include "../src.datos.storage/Buffer.h"
#include "FactoryOfRegistry.h"
#include "Registry.h"
#include "Key.h"
#include "Mail.h"
using namespace std;

class Block: public Component {
public:
	Block(unsigned int maxLong, unsigned int numBlock, unsigned int level) throw();
	~Block() throw();
	Block();
	int getNumElements();
	int getFreeSize();
	void setSizeFree(int size);
	void addReg(Registry* reg);
	Registry* getReg(Key* key);
	virtual void pack(Buffer* buffer);
	virtual void unPack(Buffer* buffer);
	virtual void packMetadata(Buffer* buffer);
	virtual int unPackMetadata(Buffer* buffer);
	void packListRegistry(Buffer* buffer);
	void unPackListRegistry(Buffer* buffer,int numberElements,int typeElement);
	int print(std::ostream& outStream);
	unsigned int getSize();
    unsigned int getSizeRegistry();
    void transferRegistry(list<Registry*> &listElement) throw();
	/**
	 * Devuelve si hay subflujo o no
	 */
//	virtual bool isUnderflow() const throw() = 0;
    list<Registry*>::iterator iteratorBegin();
    list<Registry*>::iterator iteratorEnd();


	/**
	 * Reemplaza un componente por otro
	 */
	void replaceRegistry(Registry* registryOld,Registry* registryNew) throw();
	/**
	 * Vacia la lista de componentes del bloque
	 */
	void clearListRegistry() throw();

    /* Obtiene el numero de bloque en el arbol B sharp.
     */
    unsigned int getNumBlock() const throw();
    /**
     * Establece el numero de bloque en el arbol B sharp.
     */
    void setNumBlock(unsigned int numBlock) throw();
    /**
     * Obtiene el nivel del bloque en el arbol B sharp.
     */
    unsigned int getLevel() const throw();
    /**
     * Establece el nivel del bloque en el arbol B sharp.
     */
    void setLevel(unsigned int level) throw();
    /**
     * Devuelve si el bloque es hoja o no, si su nivel es 0.
     */
    virtual bool isLeaf() const throw();
    /**
     * Agrega un componente al bloque en el arbol b sharp.
     */
	 void addComponent(Registry* registry) throw() ;
	  /**
	     * Agrega un componente al bloque en el arbol B sharp en la posicion especificada.
	     */
	 void addComponent(Registry* registry,list<Registry*>::iterator it,int pos) throw() ;

    /**
     * Obtiene la longitud en bytes ocupada del bloque.
     * */
    virtual unsigned int getOcupedLong() throw();
    /**
     * Obtiene la longitud maxima en bytes del bloque.
     */
    unsigned int getMaxLong() const throw();
    /**
     * Establece la longitud maxima en bytes del bloque.
     */
    void setMaxLong(unsigned int maxLong) throw();
    /**
     * Obtiene la longitud en bytes  del bloque.
     */
    virtual unsigned int getLongBytes() throw();
    /**
     *ordena la lista de registros
     */
    void sortListRegistry();
    virtual bool posibleToAgregateComponent(Registry* registry) throw();


private:
	list<Registry*> regList;
	unsigned int freeSize;
	unsigned int numBlock;
	unsigned int level;
	unsigned int maxLong;
	FactoryOfRegistry* factory;
};

#endif /* BLOCK_H_ */
