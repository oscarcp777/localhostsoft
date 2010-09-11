/*
 * FabricaDeRegistros.h
 *
 *  Created on: 05/09/2010
 *      Author: richy
 */

#ifndef FABRICADEREGISTROS_H_
#define FABRICADEREGISTROS_H_
#include "Registry.h"
#include "Mail.h"
#include "KeyClassifIndex.h"
#include "KeySelectIndex.h"
#include "Key.h"
#include "Dir.h"
#include "../src.datos.utils/Define.h"



class FabricaDeRegistros {
public:
	FabricaDeRegistros();
	virtual ~FabricaDeRegistros();
	Registry* crearRegistro(int type);
};

#endif /* FABRICADEREGISTROS_H_ */
