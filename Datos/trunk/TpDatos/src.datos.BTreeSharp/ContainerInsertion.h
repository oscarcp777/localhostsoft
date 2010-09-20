/*
 * ContainerInsertion.h
 *
 *  Created on: 05/09/2010
 *      Author: oscar
 */

#ifndef CONTAINERINSERTION_H_
#define CONTAINERINSERTION_H_

#include "../src.datos.models/Registry.h"
class ContainerInsertion {
public:
	ContainerInsertion();
	virtual ~ContainerInsertion();

	/**
	 * Establece el regsitro con la clve de dato media luego de una division de bloques.
	 */
	void setRegMidleKey(Registry* reg) throw();
	/**
	 * Obtiene el registro con la clave de dato media luego de una division de bloques.
	 */
	Registry* getRegMidleKey() throw();
	/**
	 * Establece el numero de bloque izquierdo luego de una division de bloques.
	 */
	void setLeftBlock(unsigned int numBlock) throw();
	/**
	 * Obtiene el numero de bloque izquierdo luego de una division de bloques.
	 */
	unsigned int getLeftBlock() const throw();
	/**
	 * Establece el numero de bloque derecho luego de una division de bloques.
	 */
	void setRightBlock(unsigned int numBlock) throw();
	/**
	 * Obtiene el numero de bloque derecho luego de una division de bloques.
	 */
	unsigned int getRightBlock() const throw();
	/**
	 * Obtiene el numero de bloque medio luego de una division de bloques de 2 a 3.
	 * @return unsigned int - El numero de bloque medio luego de una division de bloques de 2 a 3.
	 */
	unsigned int getMediumBlock() const;
	/**
	 * Establece el numero de bloque medio luego de una division de bloques de 2 a 3.
	 * @param numero_bloque - El numero de bloque medio luego de una division de bloques de 2 a 3.
	 */
	void setMediumBlock(unsigned int mediumBlock);
    Registry* getLeftRegKey();
    Registry* getRightRegKey();
    void setLeftRegKey(Registry* leftRegKey);
    void setRightRegKey(Registry* rightRegKey);
private:
	/**
	 * Almacena el registro con la clave de dato media luego de una division de bloques.
	 */
	Registry* midleRegKey;
	/**
	 * Almacena el registro con la clave de dato izquierda luego de una division de bloques para el split de 2 a 3.
	 */
	Registry* rightRegKey;
	/**
	 * Almacena el registro con la clave de dato derecha luego de una division de bloques para el split de 2 a 3.
	 */
	Registry* leftRegKey;
	/**
	 * Almacena el numero de bloque izquierdo luego de una division de bloques.
	 */
	unsigned int leftBlock;
	/**
	 * Almacena el numero de bloque derecho luego de una division de bloques.
	 */
	unsigned int rigthBlock;

	/**
	 * Almacena el numero de bloque medio luego de una division de bloques de 2 a 3.
	 */
	unsigned int mediumBlock;

};


#endif /* CONTAINERINSERTION_H_ */
