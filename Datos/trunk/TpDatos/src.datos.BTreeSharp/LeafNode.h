/*
 * LeafNode.h
 *
 *  Created on: 04/09/2010
 *      Author: Facurndo
 */

#ifndef LEAFNODE_H_
#define LEAFNODE_H_

#include "Node.h"
#include "ContainerInsertDataBlock.h"

class LeafNode: public Node {
public:
	LeafNode(int typeElement,unsigned int maxLong);
	LeafNode(int typeElement,unsigned int maxLong, unsigned int numBlock, unsigned int level)throw();
	virtual ~LeafNode()throw();
	virtual bool isLeaf() const throw();
	void pack(Buffer* buffer);
	void unPack(Buffer* buffer);
	void packMetadata(Buffer* buffer);
	int unPackMetadata(Buffer* buffer);

	/**
	 * Obtiene la longitud ocupada en bytes del bloque.
	 */
	 unsigned int getOcupedLong() throw();
	/**
	 * Devuelve si hay subflujo o no
	 */
	bool isUnderflow()throw();
  /**
   * inserta el mail el bloque de datos
   * y devuelve el registro para insertarlo en el arbol si es necesario
   */
	Registry* insertBlockData(Registry* registry,ContainerInsertDataBlock* container);
	 bool posibleToAgregateComponent(Registry* registry)throw();

private:
	 void writeBlockData(Block* block ,unsigned int numBlock,ContainerInsertDataBlock* container);
	 Block* readBlockData(unsigned int numBlock,ContainerInsertDataBlock* container);
	 Registry* insertBlockMails(Registry* registry,ContainerInsertDataBlock* container);
	 Registry* insertBlockRegClassification(Registry* registry,ContainerInsertDataBlock* container);
	 Registry* insertMailBlockNew(Registry* registry,ContainerInsertDataBlock* container);

};

#endif /* LEAFNODE_H_ */
