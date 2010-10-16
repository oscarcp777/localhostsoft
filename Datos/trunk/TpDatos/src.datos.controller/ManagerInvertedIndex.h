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

class ManagerInvertedIndex {
public:
	ManagerInvertedIndex();
	virtual ~ManagerInvertedIndex();
	void loadMessageWords(Mail* mail);
	void removeStopWords();
private:
	WordsContainer* stopWords;
	WordsContainer* currentWords;
};

#endif /* MANAGERINVERTEDINDEX_H_ */
