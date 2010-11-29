/*
 * gmail-poptest.h
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#ifndef GMAILPOPTEST_H_
#define GMAILPOPTEST_H_
#include "StorageController.h"
#include "../src.datos.storage/TextFile.h"
#include "../src.datos.utils/Define.h"

int connection(char* username,char* password, StorageController* storageController);
int connectionOK(char* username,char* password);
#endif /* GMAILPOPTEST_H_ */
