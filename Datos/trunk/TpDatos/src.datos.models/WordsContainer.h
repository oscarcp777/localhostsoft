/*
 * WordsContainer.h
 *
 *  Created on: 16/10/2010
 *      Author: richy
 */

#ifndef WORDSCONTAINER_H_
#define WORDSCONTAINER_H_
#include <vector>
#include <string>
#include "../src.datos.utils/Define.h"
#include "../src.datos.utils/StringUtils.h"

using namespace std;

class WordsContainer {
public:
	WordsContainer(string message);
	WordsContainer(int iuc, string message);
	virtual ~WordsContainer();
	int getIuc();
	void setIuc(int iuc);
	vector<string>::iterator getWordsBegin();
	vector<string>::iterator getWordsEnd();
	void parserMailWords(string message);
	void removeWord(vector<string>::iterator it);
	bool contains(string word);
	void print();

private:
	vector<string> words;
	int iuc;
};

#endif /* WORDSCONTAINER_H_ */
