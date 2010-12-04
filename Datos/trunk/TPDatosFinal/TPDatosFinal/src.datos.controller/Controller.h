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
#include "StorageController.h"
#include "IndexController.h"
#include "../src.datos.classification/Classification.h"
#include "../src.datos.cryptography/Hill.h"
#include <vector>
#include <stdlib.h>



class QTextEdit;
class Controller {
private:
	std::string fileNameAccount;
	std::string message;
	TextFile* programFile;
	std::string strEmail;
	std::string strPass;
	std::string strSearch;
	Search* search;
	list<IndexConfig*> indexes;
	list<int> listOfIucs;
	list<Mail*> listOfMails;
	IndexBSharp* primaryTree;
	bool mailAndPass;
	QTextEdit *bigEditor;
	void loadIndexNames();
	void loadInfoIndex(std::string linea, IndexConfig* index);
	Controller(std::string userMail,std::string password);

public:
	void setEditorText(QTextEdit* bigEditor);
	int checkMailData();
	virtual ~Controller();
	Search* getSearch();
	bool getMailAndPass();
	std::string getListOfIndexes();
	void setSearch(Search* search);
	void addSecondIndex(IndexConfig* indexConfig);
	int loadSecondIndex(IndexConfig* indexConfig);
	void addIndexToFile(IndexConfig* index);
	std::string getMails(std::string strListOfIucs);
	int searchMails(std::string strSearch);
	void convertStringToListOfInt(Search* search,std::string str);
	Search* parseStrSearch(std::string strSearch);
	void createIndexes(std::string strSearch);
	IndexConfig* createIndexConfig2(std::string str);
	void addEmail(std::string email);
	std::string getEmail();
	void addPass(std::string pass);
	void printIndexNames();
	void updateIndexes(Mail* mail);
	void updateIndexesDelete(Mail* mail);
	int createPrimaryIndex();
	IndexConfig* getIndex(std::string index);
	list<int>::iterator iteratorBeginListOfIucs();
	list<int>::iterator iteratorEndListOfIucs();
	list<Mail*>::iterator iteratorBeginListOfMails();
	list<IndexConfig*>::iterator iteratorBeginListOfIndexes();
	list<IndexConfig*>::iterator iteratorEndListOfIndexes();
	list<Mail*>::iterator iteratorEndListOfMails();
	list<int> getListOfIUCS();
	list<Mail*> getListOfMails();
	bool searchIndex(std::string index);
	bool searchPrimaryIndex(IndexConfig* indexConfig);
	IndexConfig* loadIndexConfig(std::string index);
	int strSearchValidation(std::string strSearch,std::string &strError);
	void clearListsIucs();
	void deleteIucs(std::string strIucs);
	void deleteIuc(int iuc);
	void overWriteFile();
	list<int>* getListOfIucs();
	void calculateIntersection(unsigned int numSearchs, list<int>* listIucs);
    static Controller *getInstance(string mail, string pass);
    std::string getMessage() const;
    void setMessage(std::string message);
    static Controller *instance;

};

#endif /* CONTROLLER_H_ */
