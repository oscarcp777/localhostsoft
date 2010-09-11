/*
 * Dir.cpp
 *
 *  Created on: 04/09/2010
 *      Author: Facundo
 */

#include "Dir.h"

Dir::Dir() {
	// TODO Auto-generated constructor stub

}

Dir::~Dir() {
	// TODO Auto-generated destructor stub
}
bool Dir::equals(Registry* comp){
	return false;
}
void Dir::pack(Buffer* buffer){

}
void Dir::unPack(Buffer* buffer){

}
int Dir::getLongBytes(){
	return 0;
}

int  Dir::print(std::ostream& outStream){
      return 1;
}

int Dir::getSize(){
	return 1;
}
Registry* Dir::clone(){
	return new Dir();
}
