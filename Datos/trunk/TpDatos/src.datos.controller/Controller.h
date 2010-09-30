/*
 * Controller.h
 *
 *  Created on: 24/09/2010
 *      Author: Facundo
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <fstream>
#include "../src.datos.storage/TextFile.h"
#include "../src.datos.models/IndexConfig.h"
#include "../src.datos.BTreeSharp/IndexBSharp.h"
#include "../src.datos.utils/StringUtils.h"
#include "../src.datos.consultations/Search.h"
#include "../src.datos.storage/StorageController.h"
#include "../src.datos.models/IndexController.h"
#include "../src.datos.classification/Classification.h"

#include <vector>
#include <stdlib.h>




class Controller {
private:
	TextFile* programFile;
	std::string strEmail;
	std::string strPass;
	std::string strSearch;
	Search* search;
	list<IndexConfig*> indexes;
	list<int> listOfIucs;
	list<Mail*> listOfMails;
	IndexBSharp* primaryTree;
	void loadIndexNames();
	void loadInfoIndex(std::string linea, IndexConfig* index);

public:
	Controller();
	virtual ~Controller();
	Search* getSearch();
	void setSearch(Search* search);
	void addSecondIndex(IndexConfig* indexConfig);
	int loadSecondIndex(IndexConfig* indexConfig);
	void addIndexToFile(IndexConfig* index);
	int searchMails(std::string strSearch);
	void convertStringToListOfInt(Search* search,std::string str);
	Search* parseStrSearch(std::string strSearch);
	void addEmail(std::string email);
	void addPass(std::string pass);
	void printIndexNames();
	int createPrimaryIndex();
	list<int>::iterator iteratorBeginListOfIucs();
	list<int>::iterator iteratorEndListOfIucs();

};

#endif /* CONTROLLER_H_ */
