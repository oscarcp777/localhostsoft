/*
 * MailBlockManager.cpp
 *
 *  Created on: 09/09/2010
 *      Author: richy
 */

#include "MailBlockManager.h"

MailBlockManager::MailBlockManager(string fileName, unsigned int blockSize) {
	this->blockSize = blockSize;
	this->freeSizeCurrentBlock = blockSize;
	this->buffer = new Buffer(blockSize);
	//this->metadataBuffer = new Buffer(blockSize);
	this->blocksFile = new BinaryFile();

	if(this->blocksFile->isCreated(fileName)){
		this->blocksFile->open(fileName);
		//this->readMetadata();
	}
	else{
		this->blocksFile->create(fileName);
		this->numBlocks = 0;
		//this->writeMetadata();//TODO
	}
}

MailBlockManager::~MailBlockManager() {
	delete blocksFile;
	delete buffer;
}

void MailBlockManager::packMail(Mail* mail){
	//si el mail entra en el bloque acutal hago el pack
	if(this->freeSizeCurrentBlock >= mail->getSize()){
		this->mailList.push_back(mail); //mail->pack(this->buffer);
		this->freeSizeCurrentBlock -= mail->getSize();
	}
	else{ //si no entra, cargo en el buffer todos los mails de la lista, escribo en disco el buffer y "creo un nuevo bloque" para hacer el pack
		this->loadMailListToBuffer();
		this->blocksFile->write(this->buffer->getData(),this->blockSize,(this->numBlocks)*this->blockSize);
		this->numBlocks++;
		this->freeSizeCurrentBlock = this->blockSize; //actualizo el tamano libre (vacio)
		this->mailList.push_back(mail); //agrego el nuevo mail a la lista
		this->freeSizeCurrentBlock -= mail->getSize(); //actualizo espacio libre
	}
}
void MailBlockManager::loadMailListToBuffer(){
	//hace pack de todos los mails de la lista en el buffer y limpia la lista
	this->buffer->clear();

	//hago pack del numero de mails en el bloque
	int numberOfMails = this->mailList.size();
	this->buffer->packField(&numberOfMails,sizeof(numberOfMails));

	//hago pack de los mails en el bloque actual (los q estan en la lista)
	std::vector<Mail*>::iterator it;;
	for (it = this->mailList.begin(); it!=this->mailList.end(); it++){
			(*it)->pack(this->buffer);
		}
	//limpio la lista
	this->mailList.clear();
}
void MailBlockManager::close(){
	//antes de cerrar el archivo escribo el buffer por si hay cambios y despues escribo la metadata
	this->loadMailListToBuffer();
	this->blocksFile->write(this->buffer->getData(),this->blockSize,(this->numBlocks)*this->blockSize);
	//this->writeMetadata();
	this->blocksFile->close();
}

//void MailBlockManager::readMetadata(){
//	this->blocksFile->read(this->metadataBuffer->getData(),this->blockSize,0);
//	this->metadataBuffer->unPackField(&this->blockSize,sizeof(this->blockSize));
//	this->metadataBuffer->unPackField(&this->numBlocks,sizeof(this->numBlocks));
//
//}
//void MailBlockManager::writeMetadata(){
//	this->metadataBuffer->clear();
//	this->metadataBuffer->packField(&this->blockSize,sizeof(this->blockSize));
//	this->metadataBuffer->packField(&this->numBlocks,sizeof(this->numBlocks));
//	this->blocksFile->write(this->metadataBuffer->getData(),this->blockSize,0);
//}

std::vector<Mail*> MailBlockManager::loadMailsInBlock(int idBlock){
	Buffer* loadBuffer = new Buffer(this->blockSize);
	int numbersOfMails;
	this->blocksFile->read(loadBuffer->getData(),this->blockSize,idBlock*this->blockSize);
	loadBuffer->unPackField(&numbersOfMails,sizeof(numbersOfMails));
	int i = 0;
	while(i < numbersOfMails){
		Mail* mail = new Mail();
		mail->unPack(loadBuffer);
		mailList.push_back(mail);
		i++;
		}

	delete loadBuffer;
	return mailList;
}
