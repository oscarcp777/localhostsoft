/*
 * IteratorBSharp.h
 *
 *  Created on: 25/09/2010
 *      Author: San
 */

#ifndef ITERATORBSHARP_H_
#define ITERATORBSHARP_H_
#include "LeafNode.h"
#include "../src.datos.models/Registry.h"
#include "../src.datos.models/Block.h"
#include "../src.datos.models/RegPrimary.h"

class IteratorBSharp {
public:
	IteratorBSharp(unsigned int firstNode, int typeElement, BinaryFile* binaryFile, int sizeBlock, ContainerInsertDataBlock* containerInsertDataBlock);
	virtual ~IteratorBSharp();

	bool hasNext() throw();
	Registry* next() throw();

private:
	/**
	 * Tipo arbol (primario, sec. sel., sec.clas)
	 */
	int typeElement;
	/**
	 * Archivo arbol
	 */
	BinaryFile* binaryFile;
	/**
	 * Tamanio bloque
	 */
	int sizeBlock;
	/**
	 * Flag primer iteracion
	 */
	bool firstIteration;
	/**
	 * Archivo datos mails
	 */
	ContainerInsertDataBlock* containerInsertDataBlock;

	/**
	 * Nodo actual
	 */
	LeafNode* currentNode;

	/**
	 * Puntero a registro clave actual
	 */
	list<Registry*>::iterator currentRegistry;
	/**
	 * Bloque datos (solo arboles primarios)
	 */
	Block* dataBlock;
	/**
	 * Puntero a registro dato actual
	 */
	list<Registry*>::iterator currentDataRegistry;



	LeafNode* readNode(unsigned int pos) throw() ;
	LeafNode* readNodeBytes(Buffer* buffer, int sizeBlock) throw();
	LeafNode* readLeafNodeBytes(Buffer* buffer, int sizeBlock) throw();

	Block* readBlockData(unsigned int numBlock) throw();
};

#endif /* ITERATORBSHARP_H_ */

