/*
 * FabricaDeRegistros.cpp
 *
 *  Created on: 05/09/2010
 *      Author: richy
 */

#include "FabricaDeRegistros.h"

FabricaDeRegistros::FabricaDeRegistros() {
	// TODO Auto-generated constructor stub

}

FabricaDeRegistros::~FabricaDeRegistros() {
	// TODO Auto-generated destructor stub
}

Registry* crearRegistro(int type){

	switch(type){

	//case TYPE_REG_SELECTION : return new Reg

	case TYPE_MAIL: return new Mail();
					break;

	case TYPE_KEY: return new Key();
					break;

	case TYPE_DIRECTION: return new Dir();

	default: return NULL;
	}
}
