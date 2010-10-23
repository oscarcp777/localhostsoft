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
#include "../src.datos.models/RegInvertedIndex.h"
#include "../src.datos.models/RegPrimary.h"
#include "../src.datos.models/Mail.h"
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
	 Registry* insertInvertedIndexBlockNew(RegInvertedIndex* registry,ContainerInsertDataBlock* container);
	 Registry* insertIucBlockNew(RegClassification* registry,ContainerInsertDataBlock* container);
	 Registry* insertInfoPerDoc(RegInvertedIndex* registryNew,RegInvertedIndex* registryFind,ContainerInsertDataBlock* container);
	 Registry* insertMailInBlockData(RegPrimary* registryNew,RegPrimary* registryFind,ContainerInsertDataBlock* container);
	 Registry* insertIucInBlockData(RegClassification* registryNew,RegClassification* registryFind,ContainerInsertDataBlock* container);
	 void loadListRegistry(list<KeyInteger*> &listRegistry, list<Registry*>::iterator itBegin,list<Registry*>::iterator itEnd);
	 void loadListInfoPerDocBlockData(RegInvertedIndex* regIndex,unsigned  int numBlock,ContainerInsertDataBlock* container);
	 void loadListInfoPerDoc(list<InfoPerDoc*> &listRegistry, list<Registry*>::iterator itBegin,list<Registry*>::iterator itEnd);
private:
	 Mail*  validedSizeMail(Mail* mail,ContainerInsertDataBlock* container);
};

#endif /* BLOCKDATAMANAGER_H_ */
