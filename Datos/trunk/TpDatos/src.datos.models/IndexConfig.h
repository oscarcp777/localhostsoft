/*
 * IndexConfig.h
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#ifndef INDEXCONFIG_H_
#define INDEXCONFIG_H_
#include <string>

using namespace std;
class IndexConfig {
public:
	IndexConfig();
	virtual ~IndexConfig();
    int getBlockSize() const;
    string getFileName() const;
    string getTypeIndex() const;
    string getTypeSecundaryIndex() const;
    string getUserName() const;
    void setBlockSize(int blockSize);
    void setFileName(string fileName);
    void setTypeIndex(string typeIndex);
    void setTypeSecundaryIndex(string typeSecundaryIndex);
    void setUserName(string userName);
    int getCondition() const;
    string getValue() const;
    void setCondition(int condition);
    void setValue(string value);

private:
	string fileName;
	string userName;
	int blockSize;
	string typeIndex;
	string typeSecundaryIndex;
	int condition;
	string value;
};

#endif /* INDEXCONFIG_H_ */
