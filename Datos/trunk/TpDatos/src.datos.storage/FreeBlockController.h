/*
 * FreeBlockList.h
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#ifndef FREEBLOCKCONTROLLER_H_
#define FREEBLOCKCONTROLLER_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "BinaryFile.h"

using namespace std;

class FreeBlockController {
public:

	        /**
			 * Constructor de la clase FreeBlockController.
			 */
	        FreeBlockController(const std::string& fileName) throw();
			/**
			 * Destructor virtual de la clase FreeBlockController.
			 */
			virtual ~FreeBlockController() throw();
			/**
			 * Escribe la cantidad de espacio ocupado / libre para un numero de elemento dentro de un bloque dado.
			 */
			void writeSizeBusy(unsigned int position, unsigned int sizeBusy) throw();
			/**
			 * Lee la cantidad de espacio ocupado / libre para un numero de elemento dentro de un almacenamiento dado.
			 */
			unsigned int readSizeBusy(unsigned int position) throw();
			/**
			 * Busca el numero de elemento dentro de un almacenamiento dado con espacio libre.
			 */
			unsigned int searchSizeBusy() throw();
		protected:
			/**
			 * Verifica si el espacio ocupado / libre para un numero de elemento dentro de un almacenamiento dado se considera  no lleno.
			 */
			 bool isSizeBusy(unsigned int sizeBusy) throw();
		private:
			/**
			 * Almacena el archivo de espacios ocupados / libres.
			 */
			 BinaryFile* binaryFile;

private:

};

#endif /* FREEBLOCKCONTROLLER_H_ */
