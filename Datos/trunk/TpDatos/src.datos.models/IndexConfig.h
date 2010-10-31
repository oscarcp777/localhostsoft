/*
 * IndexConfig.h
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#ifndef INDEXCONFIG_H_
#define INDEXCONFIG_H_
#include <string>
#include <iostream>
using namespace std;
class IndexConfig {
public:
	IndexConfig();
	virtual ~IndexConfig();
    int getBlockSize() const;
    string getFilterName() const;
    string getFileName() const;
    string getTypeIndex() const;
    string getTypeSecundaryIndex() const;
    string getUserName() const;
    void setBlockSize(int blockSize);
    void setFileName(string fileName);
    void setFilterName(string filterName);
    void setTypeIndex(string typeIndex);
    void setTypeSecundaryIndex(string typeSecundaryIndex);
    void setUserName(string userName);
    int getCondition() const;
    string getValue() const;
    void setCondition(int condition);
    void setValue(string value);
    void print();
    void setLastIuc(int lastIuc);
    int getLastIuc();
    void setLoaded(bool loaded);
    bool isLoaded();

private:
    bool loaded;
    int lastIuc;
    string filterName;
	string fileName;
	string userName;
	int blockSize;
	string typeIndex;
	string typeSecundaryIndex;
	int condition;
	string value;
};

#endif /* INDEXCONFIG_H_ */
