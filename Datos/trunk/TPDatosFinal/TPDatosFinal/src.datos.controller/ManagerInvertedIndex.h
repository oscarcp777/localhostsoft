/*
 * ManagerInvertedIndex.h
 *
 *  Created on: 16/10/2010
 *      Author: richy
 */

#ifndef MANAGERINVERTEDINDEX_H_
#define MANAGERINVERTEDINDEX_H_
#include "../src.datos.models/WordsContainer.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.storage/TextFile.h"
#include "../src.datos.models/Mail.h"
#include "../src.datos.models/RegInvertedIndex.h"
#include "../src.datos.BTreeSharp/IndexBSharp.h"
#include <map>

class ManagerInvertedIndex {
public:
	ManagerInvertedIndex();
	virtual ~ManagerInvertedIndex();
	void loadMessageWords(Mail* mail, IndexBSharp* indexBSharp);
	void loadDirtyWords();
	void removeStopWords();
	void removeDirtyWords();
	void printMap(std::ostream& outStream);
	map<string,RegInvertedIndex*>::iterator getIteratorBegin();
	map<string,RegInvertedIndex*>::iterator getIteratorEnd();
	void writeOrUpdateInvertedIndex(IndexBSharp* indexBSharp);
	void removeStopWordsFromVector(vector<string>* words);
	string validateSize(string word);

private:
	WordsContainer* stopWords;
	WordsContainer* dirtyWords;
	WordsContainer* currentWords;
	map<string,RegInvertedIndex*> regMap;

};

#endif /* MANAGERINVERTEDINDEX_H_ */
