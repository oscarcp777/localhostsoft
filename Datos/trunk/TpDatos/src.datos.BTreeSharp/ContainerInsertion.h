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
	const Registry* getRegMidleKey() const throw();
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
private:
	/**
	 * Almacena el registro con la clave de dato media luego de una division de bloques.
	 */
	Registry* midleRegKey;
	/**
	 * Almacena el numero de bloque izquierdo luego de una division de bloques.
	 */
	unsigned int leftBlock;
	/**
	 * Almacena el numero de bloque derecho luego de una division de bloques.
	 */
	unsigned int rigthBlock;



};


#endif /* CONTAINERINSERTION_H_ */
