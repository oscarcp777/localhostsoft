/*
 * IndexConfig.cpp
 *
 *  Created on: 25/09/2010
 *      Author: richy
 */

#include "IndexConfig.h"

IndexConfig::IndexConfig() {
	// TODO Auto-generated constructor stub
	this->condition =0;
	this->value="";
	this->typeSecundaryIndex ="";

}

IndexConfig::~IndexConfig() {
	// TODO Auto-generated destructor stub
}
int IndexConfig::getBlockSize() const
{
	return blockSize;
}

string IndexConfig::getFileName() const
{
	return fileName;
}
string IndexConfig::getFilterName() const
{
	return filterName;
}

string IndexConfig::getTypeIndex() const
{
	return typeIndex;
}

string IndexConfig::getTypeSecundaryIndex() const
{
	return typeSecundaryIndex;
}

string IndexConfig::getUserName() const
{
	return userName;
}

void IndexConfig::setBlockSize(int blockSize)
{
	this->blockSize = blockSize;
}

void IndexConfig::setFileName(string fileName)
{
	this->fileName = fileName;
}
void IndexConfig::setFilterName(string filterName)
{
	this->filterName = filterName;
}

void IndexConfig::setTypeIndex(string typeIndex)
{
	this->typeIndex = typeIndex;
}

void IndexConfig::setTypeSecundaryIndex(string typeSecundaryIndex)
{
	this->typeSecundaryIndex = typeSecundaryIndex;
}

void IndexConfig::setUserName(string userName)
{
	this->userName = userName;
}
int IndexConfig::getCondition() const
{
    return condition;
}

string IndexConfig::getValue() const
{
    return value;
}

void IndexConfig::setCondition(int condition)
{
    this->condition = condition;
}

void IndexConfig::setValue(string value)
{
    this->value = value;
}
void IndexConfig::print(){
	cout<<"File Name: " << this->getFileName() << endl ;
	cout<<"User Name: " << this->getUserName() << endl ;
	cout<<"Filter Name: " << this->getFilterName()<< endl;
	cout<<"Type Index: " << this->getTypeIndex()<< endl;
	cout<<"Type Secondary: " << this->getTypeSecundaryIndex()<< endl;
	cout<<"Condition: " << this->getCondition()<< endl;
	cout<<"Value: " << this->getValue() << endl;
}

