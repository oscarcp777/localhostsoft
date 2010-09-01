/*
 * TextFile.h
 *
 *  Created on: 25/03/2010
 *      Author: oscar
 */

#ifndef TEXTFILE_H_
#define TEXTFILE_H_

#include "File.h"

class TextFile: public File {
public:
	TextFile();
	virtual ~TextFile();

	/**
	 *deprecado
	 */
	void create(string fileName);
	/**
	 * Abre el archivo ubicado en el path pasado (debe incluir nombre completo) en modo lectura/escritura.
	 * Deja el cursor al comienzo del mismo.
	 * En caso de no existir el archivo, lo crea.
	 * Si no puede realizar la operación, arroja una excepción
	 */
	void open(string fileName);

};

#endif /* TEXTFILE_H_ */
