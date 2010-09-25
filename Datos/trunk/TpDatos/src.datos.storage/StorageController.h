/*
 * StorageController.h
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#ifndef STORAGECONTROLLER_H_
#define STORAGECONTROLLER_H_
#include "../src.datos.BTreeSharp/IndexBSharp.h"

class StorageController {
public:
	StorageController();
	virtual ~StorageController();
	IndexBSharp* generatePrimaryIndex(char* userName, char* password);
	void addMail(char* message);
	Mail* generateMail(char* message);
private:
	IndexBSharp* primaryIndex;
	int numberOfIuc;
};


#endif /* STORAGECONTROLLER_H_ */
