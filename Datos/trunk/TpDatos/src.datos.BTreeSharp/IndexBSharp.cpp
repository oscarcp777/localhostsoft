/*
 * IndexBSharp.cpp
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#include "IndexBSharp.h"

IndexBSharp::IndexBSharp(const std::string& nameFile,unsigned int sizeBlock,int typeElement){
	this->sizeBlock=sizeBlock;
	this->typeElement=typeElement;
	this->binaryFile= new BinaryFile();
	this->binaryFile->create(nameFile);
	this->buffer= new Buffer(sizeBlock);
	this->readBlockRoot();
}

IndexBSharp::~IndexBSharp() {
	this->binaryFile->close();
	delete this->binaryFile;
}

void IndexBSharp::addRegistry(Registry* registry) throw(){
	ContainerInsertion* containerInsertion=NULL;
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
void IndexBSharp::writeBlock(Node* node,int position) throw(){
	this->buffer->clear();
	node->pack(this->buffer);
	this->binaryFile->write(this->buffer->getData(),this->buffer->getMaxBytes(),position);
}
Node* IndexBSharp::readNode(unsigned int pos) throw() {
	this->buffer->clear();
	if(this->binaryFile->read(buffer->getData(), pos)){
		Node* node = readNodeBytes(buffer);
		return node;
	}else {
		return NULL;
	}
}
Node* IndexBSharp::readNodeBytes(Buffer* buffer) throw(){
	unsigned int levelNode;
	if (buffer->getData() != NULL) {
		buffer->unPackField(&levelNode, sizeof(levelNode));
		if (levelNode == 0) {
			return readLeafNodeBytes(buffer);
		} else {
			return readInternalNodeBytes(buffer);
		}
	}
	return NULL;
}
Node* IndexBSharp::readInternalNodeBytes(Buffer* buffer) throw(){
	InternalNode* internalNode= new InternalNode();
	internalNode->unPack(buffer);
	return internalNode;
}
Node* IndexBSharp::readLeafNodeBytes(Buffer* buffer) throw(){
	LeafNode* leafNode= new LeafNode();
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
	InternalNode* newRoot = new InternalNode(this->sizeBlock,0, this->rootNode->getLevel() + 1);
	newRoot->addBranch(positionFree);
//	newRoot->addBranch(container->obtener_bloque_derecho);
//	newRoot->addComponent(container.obtener_registro_clave_media());
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
	// Busca posicion de insercion
//	unsigned int posicion_insercion = this->searchPositionInsertLeafNode(registry, this->rootNode->iterator());
	// Obtiene iterador al elemento donde insertar.
//	BloqueExternoBSharp::iterador_componentes iterador_insercion = bloqueExterno->primer_componente() + posicion_insercion;
	// Inserta el registro en el bloque externo
//	bloqueExterno->agregar_componente(registro, iterador_insercion);
	// Actualiza espacio ocupado para el bloque
//	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueExterno->obtener_numero_bloque(), bloqueExterno->obtener_longitud_ocupada());
	// Escribe bloque en disco
//	this->estrategiaAlmacenamiento->escribir_bloque(bloqueExterno->obtener_numero_bloque(), bloqueExterno, this->archivoIndice);

}
void IndexBSharp::insertLeafNodeFull(LeafNode* leafNode,Registry* registry,ContainerInsertion* container) throw(){

}
bool IndexBSharp::insertInternalNode(InternalNode* internalNode,Registry* registry,ContainerInsertion* container) throw(){
	return true;
}
void IndexBSharp::insertInternalNodeNotFull(InternalNode* internalNode,Registry* registry,unsigned int rightBlock, unsigned int leftBlock) throw(){

}
void IndexBSharp::insertInternalNodeFull(InternalNode* internalNode,Registry* registry,unsigned int rightBlock, unsigned int leftBlock,ContainerInsertion* container) throw(){

}
unsigned int IndexBSharp::searchPositionInsertLeafNode(Registry* registry, list<Registry*>::iterator iteratorBegin, list<Registry*>::iterator iteratorEnd) throw(){
		unsigned int insertPos = 0;
		bool less = true;
		list<Registry*>::iterator itReg;
		for (itReg= iteratorBegin; itReg != iteratorEnd && less; ++itReg, ++insertPos) {
			Registry* reg = *itReg;
			if (reg->getKey()->compareTo(registry) >= 0) {
						less = false;
	                	break;
	        	}
	    	}
		return insertPos;
}
unsigned int IndexBSharp::searchPositionInsertInternalNode(Registry* registry, list<Registry*>::iterator iteratorBegin, list<Registry*>::iterator iteratorEnd) throw(){
	unsigned int insertPos = 0;
		bool lessOrEquals = true;
		list<Registry*>::iterator itReg;
		for (itReg= iteratorBegin; itReg != iteratorEnd && lessOrEquals; ++itReg, ++insertPos) {
	        	Registry* reg = *itReg;
		        if (reg->getKey()->compareTo(registry) < 0 || reg->getKey()->compareTo(registry) == 0) {
	        	}
		        else {
						lessOrEquals = false;
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
		if (registry->getKey()->compareTo(*actualComponent) < 0) {
			break;
		}
		++actualComponent;
		++branchPos;
	}

	return internalNode->getBranch(branchPos);

}
Registry* IndexBSharp::extractKey(Registry* registry) throw(){
	Registry* cloneRegistry = registry->clone();
	return cloneRegistry;
}
Registry* IndexBSharp::searchLeafNode(LeafNode* leafNode,Registry* registry) throw(){
	Registry* findRegistry;
		bool find = false;

		if (leafNode != NULL) {
			std::list<Registry*>::const_iterator actualComponent = leafNode->iteratorBegin();
			std::list<Registry*>::const_iterator endComponent = leafNode->iteratorEnd();

			while (actualComponent != endComponent && !find) {
				Registry* iterRegistry = *actualComponent;
				if (iterRegistry->getKey()->equals(registry->getKey())) {
					findRegistry = iterRegistry;
					find = true;
				}
				++actualComponent;
			}
		}
		return findRegistry;
}
Registry*  IndexBSharp::searchInternalNode(InternalNode* internalNode,Registry* registry) throw(){

	Registry* findRegistry;
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
			outStream << "COMPONENTES BLOQUE: ";
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
