/*
 * KeyClassifIndex.h
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#ifndef KEYCLASSIFINDEX_H_
#define KEYCLASSIFINDEX_H_

#include "Registry.h"

class KeyClassifIndex: public Registry {
public:
	KeyClassifIndex();
	virtual ~KeyClassifIndex();
	Registry* clone();
};

#endif /* KEYCLASSIFINDEX_H_ */
