/*
 * InternalNode.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef INTERNALNODE_H_
#define INTERNALNODE_H_

#include "Node.h"
#include <iostream>
#include <vector>
#include <algorithm>


class InternalNode: public Node {
public:
	InternalNode();
	InternalNode(unsigned int maxLong, unsigned int numBlock, unsigned int level)throw();
	virtual ~InternalNode()throw();
	bool isLeaf() const throw();
	void addComponent(Component* component) throw();
	void addComponent(Component* component,list<Registry*>::iterator ,int pos) throw();
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	void packMetadata(Buffer* buffer);
	int unPackMetadata(Buffer* buffer);
	/**
	 * Agrega una rama al bloque interno b sharp.
	 */
	void addBranch(int branch) throw();
	void addBranch(std::vector<int>::iterator pos,unsigned int branch) throw();
	/**
	 * Remueve una rama del bloque interno b sharp.
	 */
	void removeBranch(int branch) throw();
	/**
	 * Transfiere todas las ramas del indice b sharp al contenedor de ramas.
	 */
	void transferBranchs(std::vector<int>& branchList) throw();
	/**
	 * Verifica si contiene una rama dentro del bloque interno b sharp.
	 */
	bool containsBranch(int branch) throw();
	/**
	 * Obtiene la rama del bloque interno b sharp dada por posicion.
	 */
	int getBranch(unsigned int index) const throw();
	/**
	 * Obtiene la cantidad de ramas del bloque interno b sharp.
	 */
	unsigned int numberOfBranchs() const throw();
	/**
	 * Obtiene un iterador a la primer rama del bloque interno b sharp.
	 */
	std::vector<int>::iterator firstBranch() throw();
	/**
	 * Obtiene un iterador a la primer rama del bloque interno b sharp.
	 */
	std::vector<int>::const_iterator  firstBranch() const throw();
	/**
	 * Obtiene un iterador a la ultima rama del bloque interno b sharp.
	 */
	std::vector<int>::iterator lastBranch() throw();
	/**
	 * Obtiene un iterador a la ultima rama del bloque interno b sharp.
	 */
	std::vector<int>::const_iterator  lastBranch() const throw();
	/**
	 * Decide si puede agregar un componente.
	 */
//	virtual bool addComponent(Component* componen) const throw();
	/**
	 * Obtiene la longitud ocupada del bloque.
	 */
//TODO	virtual unsigned int obtener_longitud_ocupada() const throw();

private:
	std::vector<int> branchList;

};

#endif /* INTERNALNODE_H_ */
