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
#include "../src.datos.models/RegPrimary.h"
#include "../src.datos.models/RegClassification.h"
#include "../src.datos.models/BlockDataManager.h"

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
	bool isUnderflow(unsigned int sizeMinumum)throw();
  /**
   * inserta el mail el bloque de datos
   * y devuelve el registro para insertarlo en el arbol si es necesario
   */
	Registry* insertBlockData(Registry* registry,ContainerInsertDataBlock* container);
	 bool posibleToAgregateComponent(Registry* registry)throw();
	 unsigned int getMetadata();
	 Registry* searchRegistryBlockData(Registry* registry,ContainerInsertDataBlock* container);
	 void printMails(std::ostream& outStream,Registry* reg,ContainerInsertDataBlock* container);
private:
      BlockDataManager*  blockDataManager;
	 // Los metodos siguientes fueron agregados al BSharp para darle la funcionalidad de un secuence set
	 // segun se necesite


	 /**
	  *  Inserta un Mail en un bloque de datos, el bloque puede ser uno existe o uno nuevo
	  */
	 Registry* insertBlockMails(Registry* registry,ContainerInsertDataBlock* container);
	 /**
	  *  Inserta un Iuc en un bloque de datos, el bloque puede ser uno existe o uno nuevo
	  */
	 Registry* insertBlockRegClassification(Registry* registry,ContainerInsertDataBlock* container);
	 Registry* insertMailBlockNew(Registry* registry,ContainerInsertDataBlock* container);
	 Registry* insertIucBlockNew(Registry* registry,ContainerInsertDataBlock* container);
	 Registry* searchBlockMails(Registry* registry,ContainerInsertDataBlock* container);
	 Registry* searchBlockRegClassification(Registry* registry,ContainerInsertDataBlock* container);

};

#endif /* LEAFNODE_H_ */
