/*
 * StorageController.h
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#ifndef STORAGECONTROLLER_H_
#define STORAGECONTROLLER_H_
#include "../src.datos.BTreeSharp/IndexBSharp.h"
#include "../src.datos.models/IndexConfig.h"

class StorageController {
public:
	StorageController();
	virtual ~StorageController();
	IndexBSharp* generatePrimaryIndex(char* userName, char* password,IndexConfig* configIndex);
	void addMail(char* message);
	Mail* generateMail(char* message);
private:
	IndexBSharp* primaryIndex;
	int numberOfIuc;
};


#endif /* STORAGECONTROLLER_H_ */
