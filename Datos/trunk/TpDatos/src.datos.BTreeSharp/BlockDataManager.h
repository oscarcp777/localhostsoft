/*
 * BlockDataManager.h
 *
 *  Created on: 30/09/2010
 *      Author: oscar
 */

#ifndef BLOCKDATAMANAGER_H_
#define BLOCKDATAMANAGER_H_
#include "../src.datos.models/Block.h"
#include "ContainerInsertDataBlock.h"
#include "../src.datos.models/Registry.h"
#include "../src.datos.models/RegClassification.h"
#include "../src.datos.models/RegPrimary.h"
class BlockDataManager {
public:
	BlockDataManager();
	virtual ~BlockDataManager();
	 /**
	  *  Escribe un bloque de datos externo al arbol con los valores determinados por el container
	  */
	 void writeBlockData(Block* block ,unsigned int numBlock,ContainerInsertDataBlock* container);
	 /**
	  *  Lee un bloque de datos externo al arbol con los valores determinados por el container
	  */
	 void loadListIucBlockData(RegClassification* regClas,unsigned  int numBlock,ContainerInsertDataBlock* container);
	 Block* readBlockData(unsigned int numBlock,ContainerInsertDataBlock* container);
	 Registry* insertMailBlockNew(RegPrimary* registry,ContainerInsertDataBlock* container);
	 Registry* insertIucBlockNew(RegClassification* registry,ContainerInsertDataBlock* container);
	 Registry* insertMailInBlockData(RegPrimary* registryNew,RegPrimary* registryFind,ContainerInsertDataBlock* container);
	 Registry* insertIucInBlockData(RegClassification* registryNew,RegClassification* registryFind,ContainerInsertDataBlock* container);
	 void      loadListRegistry(list<KeyInteger*> &listRegistry, list<Registry*>::iterator itBegin,list<Registry*>::iterator itEnd);
};

#endif /* BLOCKDATAMANAGER_H_ */
