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
	this->blocksFile = new BinaryFile();

	if(this->blocksFile->isCreated(fileName)){
		this->blocksFile->open(fileName);

	}
	else{
		this->blocksFile->create(fileName);
		this->numBlocks = 0;
		this->currentBlock = 0;
		this->freeSizeBlocksMap.insert(pair<int,int>(this->currentBlock,this->freeSizeCurrentBlock));

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
		this->blocksFile->write(this->buffer->getData(),this->blockSize,(this->currentBlock)*this->blockSize);
		//actualizo el espacio libre del bloque actual en el mapa
		updateFreeSizeBlockMap(this->currentBlock,this->freeSizeCurrentBlock);
		//busco en que bloque entra el nuevo mail y si no entra en ninguno creo uno nuevo. Luego Inserto
		searchBlockWithSpaceAndInsert(mail);
	}
}
void MailBlockManager::updateFreeSizeBlockMap(int block, int sizeFree){
	//borro del mapa el free space viejo del bloque actual y lo actualizo
	this->freeSizeBlocksMap.erase(block);
	this->freeSizeBlocksMap.insert(pair<int,int>(block,sizeFree));
}
void MailBlockManager::searchBlockWithSpaceAndInsert(Mail* mail){
	map<int,int>::iterator it;
	this->currentBlock = -1;
	//itero el mapa y buscando si entra en el espacio libre de los bloques existentes
	 for ( it=this->freeSizeBlocksMap.begin() ; it != this->freeSizeBlocksMap.end(); it++ ){
	   if((*it).second >= mail->getSize()){
		 this->currentBlock = (*it).first;
		 this->freeSizeCurrentBlock = (*it).second - mail->getSize();
		 //cuando encontre el bloque donde entra el mail, levanto todos los mails para despues poder agregar el nuevo
		 this->loadMailsInBlock(this->currentBlock);
		 break;
	   }
	 }

	if( this->currentBlock == -1){ //si no hay espacio, incremento la cantidad de bloques y el num de bloque nuevo se lo asigno al bloque actual
		this->numBlocks++;
		this->currentBlock = this->numBlocks;
		this->freeSizeCurrentBlock = this->blockSize - mail->getSize();
	}
	this->mailList.push_back(mail); //agrego el nuevo mail a la lista

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
	//antes de cerrar el archivo escribo el buffer por si hay cambios
	this->loadMailListToBuffer();
	this->blocksFile->write(this->buffer->getData(),this->blockSize,(this->currentBlock)*this->blockSize);
	this->blocksFile->close();
}

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
