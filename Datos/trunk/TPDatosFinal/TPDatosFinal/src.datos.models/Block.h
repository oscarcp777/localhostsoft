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
#include "../src.datos.storage/Buffer.h"
#include "../src.datos.utils/Define.h"
#include "FactoryOfRegistry.h"
#include "Registry.h"
#include "Key.h"
#include "Mail.h"
using namespace std;

class Block {
public:
	Block(unsigned int maxLong, unsigned int numBlock, unsigned int level) throw();
	Block(unsigned int sizeBlock,int typeElement,bool indexed);
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
    list<Registry*>::iterator iteratorBegin();
    list<Registry*>::iterator iteratorEnd();
    void replaceRegistry(Registry *registryOld, Registry *registryNew) throw ();
    void clearListRegistry() throw ();
    unsigned int getNumBlock() const throw ();
    void setNumBlock(unsigned int numBlock) throw ();
    unsigned int getLevel() const throw ();
    void setLevel(unsigned int level) throw ();
    virtual bool isLeaf() const throw ();
    void addComponent(Registry *registry) throw ();
    virtual unsigned int getOcupedLong() throw ();
    unsigned int getMaxLong() const throw ();
    void setMaxLong(unsigned int maxLong) throw ();
    virtual unsigned int getLongBytes() throw ();
    void sortListRegistry();
    virtual bool posibleToAgregateComponent(Registry *registry) throw ();
    unsigned int getAverageWeight() const;
    void setAverageWeight(unsigned int averageWeight);
	int getTypeElement();
	void setTypeElement(int typeElement);
    int getNextBlock() const;
    void setNextBlock(int numero_bloque);
    bool getIndexed() const;
    void setIndexed(bool indexed);
    void removeReg(list<Registry*>::iterator it);
    void removeReg(Registry* registry);
protected:
    /**
     * 
     * metodo que dice cual es el tipo de clave que usa el registro
     */
	int getTipeKey(int typeElement);
    list<Registry*> regList;
	int nextNode;
	int typeElement;
protected:
	 bool indexed;
	 FactoryOfRegistry* factory;
private:

    unsigned int freeSize;
    unsigned int numBlock;
    unsigned int level;
    unsigned int maxLong;
    unsigned int averageWeight;
};

#endif /* BLOCK_H_ */
