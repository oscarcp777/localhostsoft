/*
 * IndexBSharp.cpp
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#include "IndexBSharp.h"
bool comparatorRegistry( Registry* reg1, Registry* reg2) {
	return (reg1->compareTo(reg2)==-1);
}
IndexBSharp::IndexBSharp(const std::string& nameFile,unsigned int sizeBlock,int typeElement){
	this->sizeBlock=sizeBlock;
	this->typeElement=typeElement;
	this->binaryFile= new BinaryFile();
	if(!this->binaryFile->isCreated(nameFile))
		this->binaryFile->create(nameFile);
	else
		this->binaryFile->open(nameFile);
	this->buffer= new Buffer(sizeBlock);
	this->freeBlockController = new FreeBlockController(nameFile+"free");
	this->readBlockRoot();
}

IndexBSharp::~IndexBSharp() {
	this->binaryFile->close();
	delete this->freeBlockController;
	delete this->binaryFile;
}

void IndexBSharp::addRegistry(Registry* registry) throw(){
	if(this->searchRegistry(registry) == NULL){
		ContainerInsertion* containerInsertion=new ContainerInsertion();
		bool isOverflow = false;
		if (this->rootNode->isLeaf()){
			LeafNode* leafNode = static_cast<LeafNode*>(this->rootNode);
			isOverflow = this->insertLeafNode(leafNode, registry, containerInsertion);
		} else {
			InternalNode* internalNode  = static_cast<InternalNode*>(this->rootNode);
			isOverflow = this->insertInternalNode(internalNode, registry, containerInsertion);
		}

		if (isOverflow) {
			this->splitRoot(containerInsertion);
		}
		delete containerInsertion;
	}
}

void IndexBSharp::deleteRegistry(Registry* registry) throw(){

}
Registry* IndexBSharp::searchRegistry(Registry* registry) throw(){
	if (this->rootNode->isLeaf()){
		LeafNode* leafNode = static_cast<LeafNode*>(this->rootNode);
		return this->searchLeafNode(leafNode, registry);
	} else {
		InternalNode* internalNode  = static_cast<InternalNode*>(this->rootNode);
		return this->searchInternalNode(internalNode, registry);
	}
}
void IndexBSharp::print(std::ostream& streamSalida) throw(){
	this->printRecursive(this->rootNode,streamSalida,0);
}
void IndexBSharp::createBlockRoot() throw(){
	// Instancia un nuevo bloque raiz
	this->rootNode = new LeafNode(this->typeElement,this->sizeBlock, 0,0);
	// Ecscribe bloque raiz
	this->writeBlockRoot();
}
void IndexBSharp::readBlockRoot() throw(){
	this->rootNode= this->readNode(0);
	if (this->rootNode== NULL) {
		this->createBlockRoot();
	}
}
void IndexBSharp::writeBlockRoot() throw(){
     this->writeBlock(this->rootNode,0);
}
void IndexBSharp::writeBlock(Node* node,int numBlock) throw(){
	this->buffer->clear();
	node->pack(this->buffer);
//	int var2=node->getOcupedLong()/4;
//	if(node->getNumBlock()==9){
//		buffer->init();
//	for (int var = 0;var<= var2 ; ++var) {
//       int num;
//       buffer->unPackField(&num,sizeof(num));
//       cout<<" | "<<num;
//	}
//	cout<<"fin del bloque "<<endl;
//}
	this->binaryFile->write(this->buffer->getData(),this->buffer->getMaxBytes(),numBlock*this->sizeBlock);
}
Node* IndexBSharp::readNode(unsigned int numBlock) throw() {
	this->buffer->clear();
	if(this->binaryFile->read(buffer->getData(),this->sizeBlock,this->sizeBlock*numBlock)){
		Node* node = readNodeBytes(buffer);
//		buffer->init();
//		int var2=this->sizeBlock/4;
//		if(node->getNumBlock()==9){
//			for (int var = 0;var<= var2; ++var) {
//			       int num;
//			       buffer->unPackField(&num,sizeof(num));
//			       cout<<" | "<<num;
//				}
//				cout<<"fin del bloque "<<endl;
//			}
		return node;
	}else {
		return NULL;
	}
}
Node* IndexBSharp::readNodeBytes(Buffer* buffer) throw(){
	unsigned int levelNode;
	if (buffer->getData() != NULL) {
		buffer->unPackField(&levelNode, sizeof(levelNode));
		buffer->init();
		if (levelNode == 0) {
			return readLeafNodeBytes(buffer);
		} else {
			return readInternalNodeBytes(buffer);
		}
	}
	return NULL;
}
Node* IndexBSharp::readInternalNodeBytes(Buffer* buffer) throw(){
	InternalNode* internalNode= new InternalNode(this->sizeBlock,this->typeElement);
	internalNode->unPack(buffer);
	return internalNode;
}
Node* IndexBSharp::readLeafNodeBytes(Buffer* buffer) throw(){
	LeafNode* leafNode= new LeafNode(this->typeElement,this->sizeBlock);
	leafNode->unPack(buffer);
	return leafNode;
}

void IndexBSharp::splitRoot(ContainerInsertion* container) throw(){
	// Busca espacio libre para la nueva raiz
	unsigned int positionFree = this->freeBlockController->searchSizeBusy();
	// Establece el nuevo numero de bloque de la raiz
	this->rootNode->setNumBlock(positionFree);
	// Escribe el espacio ocupado de la raiz
	this->freeBlockController->writeSizeBusy(positionFree, this->rootNode->getOcupedLong());
	// Escribe el bloque raiz en una nueva posicion
	this->writeBlock(this->rootNode);
	// Crea una nueva raiz
	InternalNode* newRoot = new InternalNode(this->typeElement,this->sizeBlock,0, this->rootNode->getLevel() + 1);
	newRoot->addBranch(positionFree);
	newRoot->addBranch(container->getRightBlock());
	newRoot->addComponent(container->getRegMidleKey());
	// Escribe el bloque raiz
	this->rootNode = newRoot;
	this->writeBlockRoot();
}
bool IndexBSharp::insertLeafNode(LeafNode* leafNode,Registry* registry,ContainerInsertion* container) throw(){
	// Consideramos que no hay sobreflujo
	bool isOverflow = false;
	// Verifica que el bloque externo puede agregar el registro
	if (leafNode->posibleToAgregateComponent(registry)) {
		// Agrega el registro en el bloque externo no lleno
		this->insertLeafNodeNotFull(leafNode,registry);
	} else {
		// Hubo sobreflujo
		isOverflow = true;
		// Agrega el registro en el bloque externo lleno
		this->insertLeafNodeFull(leafNode,registry,container);
	}
	// Devuelve si hubo sobreflujo o no
	return isOverflow;
}
void IndexBSharp::insertLeafNodeNotFull(LeafNode* leafNode,Registry* registry) throw(){

	// Inserta el registro en el bloque externo
	leafNode->addReg(registry);
	leafNode->sortListRegistry();
	// Actualiza espacio ocupado para el bloque
	this->freeBlockController->writeSizeBusy(leafNode->getNumBlock(), leafNode->getOcupedLong());
	// Escribe bloque en disco
	this->writeBlock(leafNode, leafNode->getNumBlock());

}
void IndexBSharp::advanceListPointer(list<Registry*>::iterator& iterator,unsigned int countAdvance){
      for (unsigned int var = 0; var < countAdvance; var++) {
    	  iterator++;
	}
}
void IndexBSharp::advanceVectorPointer(vector<int>::iterator& iterator,unsigned int countAdvance){
      for (unsigned int var = 0; var < countAdvance; var++) {
    	  iterator++;
	}
}
//todo hasta aca
void IndexBSharp::insertLeafNodeFull(LeafNode* leafNode,Registry* registry,ContainerInsertion* container) throw(){

	// Busco numero de bloque libre
	unsigned int numBlockFree = this->freeBlockController->searchSizeBusy();
	// Creo nuevo bloque externo para dividir bloque..
	LeafNode* newLeafNode = new LeafNode(this->typeElement,this->sizeBlock, numBlockFree,0);

	// Crea contenedor de componentes para insertar ordenado el registro...
	listRegistry.clear();
	list<Registry*>::iterator iterator=listRegistry.begin();
	// Transfiere todos los regsitros del bloque externo a la lista de registros para insertar ordenado el regitro...
	leafNode->transferRegistry(listRegistry);
	listRegistry.push_back(registry);
	listRegistry.sort(comparatorRegistry);

	// Obtiene elemento medio...
	list<Registry*>::iterator iteratorPosMedium=listRegistry.begin();
	this->advanceListPointer(iteratorPosMedium,(listRegistry.size() / 2));

	// Establece el elemento medio a subir en el resultado de insercion
	container->setRegMidleKey(this->extractKey(*iteratorPosMedium));
	// Inserta elementos a la izquierda del medio en bloque a dividir
	for (list<Registry*>::iterator current = listRegistry.begin(); current != iteratorPosMedium; ++current) {
		Registry* registry=*current;
		leafNode->addComponent(registry);
	}
	// Inserta elementos a la derecha del medio en bloque nuevo
	for (list<Registry*>::iterator current = iteratorPosMedium; current != listRegistry.end(); ++current) {
		Registry* registry=*current;
		newLeafNode->addComponent(registry);
	}

	// Enlaza a los bloques
	newLeafNode->setNextBlock(leafNode->getNextBlock());
	leafNode->setNextBlock(newLeafNode->getNumBlock());

	// Actualiza espacio ocupado para el bloque a dividir
	this->freeBlockController->writeSizeBusy(leafNode->getNumBlock(), leafNode->getOcupedLong());
	// Escribe bloque a dividir en disco
	this->writeBlock(leafNode, leafNode->getNumBlock());

	// Actualiza espacio ocupado para el bloque nuevo
	this->freeBlockController->writeSizeBusy(newLeafNode->getNumBlock(), newLeafNode->getOcupedLong());
	// Escribe bloque nuevo
	this->writeBlock(newLeafNode, newLeafNode->getNumBlock());


	// Establece numero de bloque derecho en resultado de insercion
	container->setRightBlock(newLeafNode->getNumBlock());
}
bool IndexBSharp::insertInternalNode(InternalNode* internalNode,Registry* registryKey,ContainerInsertion* container) throw(){
	// Considero que no hay sobreflujo al insertar en el bloque interno
	bool isOverflow = false;
	// Busco la rama por la cual insertar
	int branchInsert = this->searchBranch(internalNode, registryKey);
	// Leo el bloque por el cual insertar
	Node* nodeInsert= this->readNode(branchInsert);
	// Si el bloque existe
	if (nodeInsert != NULL) {
		// Considero que no hay sobreflujo al insertar en el bloque hijo
		bool isOverflowChild = false;
		if (nodeInsert->isLeaf()) {
			LeafNode* leafNodeInsert =static_cast<LeafNode*>(nodeInsert);
			// Inserto en el bloque externo hijo
			isOverflowChild = this->insertLeafNode(leafNodeInsert, registryKey, container);
		} else {
			InternalNode* internalNodeInsert =static_cast<InternalNode*>(nodeInsert);
			// Inserto en el bloque interno hijo
			isOverflowChild = this->insertInternalNode(internalNodeInsert, registryKey, container);
		}

		// Verifico si hubo sobrelujo al insertar en el bloque hijo
		if (isOverflowChild) {
			// Verifico si puedo agregar en el bloque interno
			if (internalNode->posibleToAgregateComponent(container->getRegMidleKey())) {
				// Inserto en el bloque interno no lleno
				this->insertInternalNodeNotFull(internalNode, container->getRegMidleKey(),container->getRightBlock());
			} else {
				// Inserto en el bloque interno lleno
				isOverflow = true;
				this->insertInternalNodeFull(internalNode, container->getRegMidleKey(),container->getRightBlock(),container);
			}
		}
	}
	return isOverflow;
}
void IndexBSharp::insertInternalNodeNotFull(InternalNode* internalNode,Registry* registryKey,unsigned int rightBlock) throw(){
	unsigned int insertPosition = this->searchPositionInsertInternalNode(registryKey, internalNode->iteratorBegin(), internalNode->iteratorEnd());

	   internalNode->addReg(registryKey);
		internalNode->sortListRegistry();
	// Agrego rama
	vector<int>::iterator iterator=internalNode->firstBranch();
	 for (unsigned int var = 0; var < insertPosition + 1; var++) {
	    	  iterator++;
		}
	internalNode->addBranch(iterator,rightBlock);
	// Actualizo espacio libre
	this->freeBlockController->writeSizeBusy(internalNode->getNumBlock(), internalNode->getOcupedLong());
	// Escribo bloque
	this->writeBlock(internalNode, internalNode->getNumBlock());
}
void IndexBSharp::insertInternalNodeFull(InternalNode* internalNode,Registry* registry,unsigned int rightBlock,ContainerInsertion* container) throw(){
	// Busco numero de bloque libre
	unsigned int numBlockFree = this->freeBlockController->searchSizeBusy();
	// Creo nuevo bloque interno para dividir
	InternalNode* newInternalNode = new InternalNode(this->typeElement,this->sizeBlock, numBlockFree, internalNode->getLevel());

	// Crea contenedor de registros para insertar ordenado el registro...
	listRegistry.clear();
	// Crea contenedor de ramas para insertar la rama nueva...
	branchList.clear();

	// Transfiere todos los regsitros del bloque interno a la lista de registros para insertar ordenado el regitro...
	internalNode->transferRegistry(listRegistry);
	// Transfiere todas las ramas del bloque interno a la lista de ramas para insertar la rama...
	internalNode->transferBranchs(branchList);
	// Busca posicion de insercion para el registro...
	unsigned int insertPos = searchPositionInsertInternalNode(registry, listRegistry.begin(), listRegistry.end());
	for (std::list<Registry*>::iterator actual = listRegistry.begin(); actual != listRegistry.end(); ++actual) {
				Registry* reg=*actual;
			}
	listRegistry.push_back(registry);
	listRegistry.sort(comparatorRegistry);
	for (std::list<Registry*>::iterator actual = listRegistry.begin(); actual != listRegistry.end(); ++actual) {
			Registry* reg=*actual;
		}
	//adelanto el puntero
	std::vector<int>::iterator itListBranchs = branchList.begin();
	this->advanceVectorPointer(itListBranchs ,insertPos + 1);
	// Inserta la rama
	branchList.insert(itListBranchs, rightBlock);

	// Obtiene elemento medio...
	list<Registry*>::iterator iteratorPosMedium=listRegistry.begin();
	this->advanceListPointer(iteratorPosMedium,(listRegistry.size() / 2));

	// Establece el elemento medio a subir en el resultado de insercion
	Registry* registryMedium=*iteratorPosMedium;
	container->setRegMidleKey(registryMedium->clone());

	// Inserta elementos a la izquierda del medio en bloque a dividir

	for (std::list<Registry*>::iterator actual = listRegistry.begin(); actual != iteratorPosMedium; ++actual) {
		Registry* reg=*actual;
		internalNode->addReg(reg);
	}

	// Inserta elementos a la derecha del medio en bloque nuevo
	iteratorPosMedium++;
	for (std::list<Registry*>::iterator actual = iteratorPosMedium; actual != listRegistry.end(); ++actual) {
		newInternalNode->addReg(*actual);
	}


	unsigned int counterLeftBranches = (internalNode->getNumElements() + 1);
	unsigned int counterRightBranches = branchList.size() - counterLeftBranches;

	std::vector<int>::iterator actual = branchList.begin();
	unsigned int counter = 0;
	while (counter < counterLeftBranches && actual != branchList.end()) {
		internalNode->addBranch(*actual);
		++actual;
	        ++counter;
	}

	counter = 0;
	while (counter < counterRightBranches && actual != branchList.end()) {
		newInternalNode->addBranch(*actual);
		++actual;
	        ++counter;
	}

	newInternalNode->setNextBlock(internalNode->getNextBlock());
	internalNode->setNextBlock(newInternalNode->getNumBlock());
	// Actualiza espacio ocupado para el bloque a dividir
	this->freeBlockController->writeSizeBusy(internalNode->getNumBlock(), internalNode->getOcupedLong());
	// Escribe bloque a dividir en disco
	this->writeBlock(internalNode, internalNode->getNumBlock());

	// Actualiza espacio ocupado para el bloque nuevo
	this->freeBlockController->writeSizeBusy(newInternalNode->getNumBlock(), newInternalNode->getOcupedLong());

	// Escribe bloque nuevo
	this->writeBlock(newInternalNode, newInternalNode->getNumBlock());


	// Establezco bloque derecho en resultado de insercion
	container->setRightBlock(newInternalNode->getNumBlock());

}
unsigned int IndexBSharp::searchPositionInsertLeafNode(Registry* registry, list<Registry*>::iterator iteratorBegin, list<Registry*>::iterator iteratorEnd) throw(){
	unsigned int insertPos = 0;
	for (list<Registry*>::iterator actual= iteratorBegin; actual != iteratorEnd ; ++actual, ++insertPos) {
		Registry* reg = *actual;
		if (!(reg->compareTo(registry) < 0)) {
			break;
		}
	}
	return insertPos;
}
unsigned int IndexBSharp::searchPositionInsertInternalNode(Registry* registry, list<Registry*>::iterator iteratorBegin, list<Registry*>::iterator iteratorEnd) throw(){
	unsigned int insertPos = 0;
	for (list<Registry*>::iterator actual= iteratorBegin; actual != iteratorEnd ; ++actual, ++insertPos) {
		Registry* reg = *actual;
		if ((reg->compareTo(registry) < 0)||(reg->compareTo(registry)==0)) {

		}else {
			break;
		}
	}
	return insertPos;
}
int IndexBSharp::searchBranch(InternalNode* internalNode,Registry* registry) throw(){

	std::list<Registry*>::const_iterator actualComponent = internalNode->iteratorBegin();
	std::list<Registry*>::const_iterator endComponent = internalNode->iteratorEnd();
	unsigned int branchPos = 0;
	while (actualComponent != endComponent) {
		Registry* actual=*actualComponent;
		if (registry->compareTo(actual) < 0) {
			break;
		}
		++actualComponent;
		++branchPos;
	}
	return internalNode->getBranch(branchPos);

}
Registry* IndexBSharp::extractKey(Registry* registry) throw(){
	return registry->cloneRegKey();
}
Registry* IndexBSharp::searchLeafNode(LeafNode* leafNode,Registry* registry) throw(){
	Registry* findRegistry = NULL;
	bool find = false;

	if (leafNode != NULL) {
		std::list<Registry*>::const_iterator actualComponent = leafNode->iteratorBegin();
		std::list<Registry*>::const_iterator endComponent = leafNode->iteratorEnd();

		while (actualComponent != endComponent && !find) {
			Registry* iterRegistry = *actualComponent;
			if (iterRegistry->compareTo(registry)==0) {
				findRegistry = iterRegistry;
				find = true;
			}
			++actualComponent;
		}
	}
	return findRegistry;
}
Registry*  IndexBSharp::searchInternalNode(InternalNode* internalNode,Registry* registry) throw(){

	Registry* findRegistry = NULL;
	if (internalNode != NULL) {
		int searchBranch = this->searchBranch(internalNode,registry);
		Node* readNode = this->readNode(searchBranch);
		if (readNode != NULL) {
			if (readNode->isLeaf()) {
				LeafNode* leafNodeRead = (LeafNode*)readNode;
				findRegistry = this->searchLeafNode(leafNodeRead, registry);
			} else {
				InternalNode* internalNodeRead = (InternalNode*)readNode;
				findRegistry = this->searchInternalNode(internalNodeRead, registry);
			}
		}
	}
	return findRegistry;

}
void IndexBSharp::printRecursive(Node* currentNode, std::ostream& outStream, unsigned int level) throw(){


	if (currentNode != NULL) {
		outStream << std::string(level * 4, '-');
		outStream << "NUMERO BLOQUE: " << currentNode->getNumBlock() << " ";
		outStream << "NIVEL: " << currentNode->getLevel() << " ";
		outStream << "COMPONENTES BLOQUE: "<<endl;
		list<Registry*>::iterator actualComp  = currentNode->iteratorBegin();
		list<Registry*>::iterator endComp = currentNode->iteratorEnd();
		while (actualComp != endComp) {
			Registry* reg =  *actualComp;
			this->printRegistry(reg, outStream);
			++actualComp;
		}
		if (currentNode->isLeaf()) {
			outStream << "--EN BLOQUE HOJA--";
			LeafNode* leafNode =  (LeafNode*)currentNode;
			outStream << "CON SIGUIENTE: " << leafNode->getNextBlock()<< " ";
			outStream << std::endl;
			outStream << std::endl;
			outStream << std::endl;
		} else {
			outStream << "--EN BLOQUE INTERNO--";
			InternalNode* internalNode = (InternalNode*)currentNode;
			std::vector<int>::const_iterator actualBranch = internalNode->firstBranch();
			std::vector<int>::const_iterator endBranch = internalNode->lastBranch();
			std::cout << "CON RAMAS(";
			while (actualBranch != endBranch) {
				outStream << " " << *actualBranch;
				++actualBranch;
			}
			outStream << " ) ";
			outStream << std::endl;
			outStream << std::endl;
			outStream << std::endl;

			actualBranch = internalNode->firstBranch();
			endBranch = internalNode->lastBranch();
			while (actualBranch != endBranch) {
				Node* childNode  = this->readNode(*actualBranch);
				if (childNode != NULL) {
					this->printRecursive(childNode, outStream, level + 1);
				}
				++actualBranch;
			}
		}
	}


}
void IndexBSharp::printRegistry(Registry* registry, std::ostream& outStream) throw(){
	registry->print(outStream);
}
