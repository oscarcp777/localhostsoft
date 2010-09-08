/*
 * LeafNode.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef LEAFNODE_H_
#define LEAFNODE_H_

#include "Node.h"

class LeafNode: public Node {
public:
	LeafNode(int typeElement,unsigned int maxLong, unsigned int numBlock, unsigned int level)throw();
	virtual ~LeafNode()throw();
	virtual bool isLeaf() const throw();
	virtual void addComponent(Component* component) throw();
	virtual void addComponent(Component* component,int pos/*, ComponenteCompuesto::iterador_componentes posicion*/) throw();

	/**
	 * Obtiene el id del bloque externo siguiente del arbol b sharp.
	 */
	int getNextBlock() const throw();
	/**
	 * Establece el id del bloque externo siguiente del arbol b sharp.
	 */
	void setNextBlock(int numero_bloque) throw();
	/**
	 * Obtiene la longitud ocupada en bytes del bloque.
	 */
//TODO MODIFICAR METODO (nombre)
//	virtual unsigned int obtener_longitud_ocupada() const throw();

private:
	int nextNode;

};

#endif /* LEAFNODE_H_ */
