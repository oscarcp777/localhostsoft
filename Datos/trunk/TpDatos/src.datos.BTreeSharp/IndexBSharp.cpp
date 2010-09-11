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
		this->insertLeafNodeFull(leafNode,registry);
	}
	// Devuelve si hubo sobreflujo o no
	return isOverflow;
}
void IndexBSharp::insertLeafNodeNotFull(LeafNode* leafNode,Registry* registry) throw(){
	// Busca posicion de insercion
	unsigned int posicion_insercion = this->searchPositionInsertLeafNode(registry, this->rootNode->iterator());
	// Obtiene iterador al elemento donde insertar.
	BloqueExternoBSharp::iterador_componentes iterador_insercion = bloqueExterno->primer_componente() + posicion_insercion;
	// Inserta el registro en el bloque externo
	bloqueExterno->agregar_componente(registro, iterador_insercion);
	// Actualiza espacio ocupado para el bloque
	this->estrategiaEspacioLibre->escribir_espacio_ocupado(bloqueExterno->obtener_numero_bloque(), bloqueExterno->obtener_longitud_ocupada());
	// Escribe bloque en disco
	this->estrategiaAlmacenamiento->escribir_bloque(bloqueExterno->obtener_numero_bloque(), bloqueExterno, this->archivoIndice);

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
unsigned int IndexBSharp::searchPositionInsertLeafNode(Registry* registry, list<Registry*>::iterator) throw(){
	return 1;
}
unsigned int IndexBSharp::searchPositionInsertInternalNode(Registry* registry, list<Registry*>::iterator) throw(){
	return 1;
}
int IndexBSharp::searchBranch(InternalNode* internalNode,Registry* registry) throw(){
	return 1;
}
Registry* IndexBSharp::extractKey(Registry* registry) throw(){
	return NULL;
}
Registry* IndexBSharp::searchLeafNode(LeafNode* leafNode,Registry* registry) throw(){
	return NULL;
}
Registry*  IndexBSharp::searchInternalNode(InternalNode* internalNode,Registry* registry) throw(){
	return NULL;
}
void IndexBSharp::printRecursive(Node* currentNode, std::ostream& streamSalida, unsigned int level) throw(){

}
void IndexBSharp::printRegistry(Registry* registry, std::ostream& streamSalida) throw(){

}
