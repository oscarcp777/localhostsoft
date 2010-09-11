/*
 * RegPrimary.cpp
 *
 *  Created on: 11/09/2010
 *      Author: oscar
 */

#include "RegPrimary.h"

RegPrimary::RegPrimary() {
	// TODO Auto-generated constructor stub

}

RegPrimary::~RegPrimary() {
	// TODO Auto-generated destructor stub
}
Registry* RegPrimary::clone(){
	return NULL;
}
bool RegPrimary::equals(Registry* comp){
 return true;
}
void RegPrimary::pack(Buffer* buffer){

}
void RegPrimary::unPack(Buffer* buffer){

}
int RegPrimary::compareTo(Registry* registry){
  return 1;
}
int RegPrimary::getSize(){
    return 1;
}
int RegPrimary::print(std::ostream& outStream){
 return 1;
}
 int RegPrimary::getLongBytes(){
 return 1;
}
 int RegPrimary::getNumberBlock(){
     return numberBlock;
 }

 void RegPrimary::setNumberBlock(int numberBlock)
 {
     this->numberBlock = numberBlock;
 }
