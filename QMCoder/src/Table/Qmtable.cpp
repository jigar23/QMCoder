/*
 * Qmtable.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: jigar
 */

#include "Qmtable.h"

//Declare the global qmcodetable
std::vector<Qmtable*> qmcodetable;


Qmtable::Qmtable() {
	state = 0;
	Qe = 0;
	incS = 0;
	decS = 0;

}

int Qmtable::getDecS() const {
	return decS;
}

void Qmtable::setDecS(int decS) {
	this->decS = decS;
}

int Qmtable::getIncS() const {
	return incS;
}

void Qmtable::setIncS(int incS) {
	this->incS = incS;
}

unsigned int Qmtable::getQe() const {
	return Qe;
}

void Qmtable::setQe(unsigned int qe) {
	Qe = qe;
}

int Qmtable::getState() const {
	return state;
}

void Qmtable::setState(int state) {
	this->state = state;
}

Qmtable::~Qmtable() {
	// TODO Auto-generated destructor stub
}


/**
 * This function loads the QM table from the
 * path specified.
 * REMEMBER: the integer Qe row has been discarded from the file.
 * So delete that row inputting the file.
 */
void Qmtable::loadQMtable(char filePath[]){
		//read the file
		ifstream infile(filePath);
		//create a buffer to store values
		char buff[80];
		//Get single line
		while(infile.getline(buff,80)){
			Qmtable *qt = new Qmtable;
			char * pEnd;
			int li1, li3, li4;
			unsigned int li2;
			//strtol converts the char[] into signed long int
			li1 = strtol (buff,&pEnd,10);
			li2 = strtol (pEnd,&pEnd,0);
			li3 = strtol (pEnd,&pEnd,10);
			li4 = strtol (pEnd,NULL,10);

			qt->setState(li1);
			qt->setQe(li2);
			qt->setIncS(li3);
			qt->setDecS(li4);
			//cout << li1 << " " << li2 << " " << li3 << " " << li4 <<  endl;
			qmcodetable.push_back(qt);
		}

//		Qmtable *temp;
//		temp->printTable();
}

/**
 * Display the contents of the table.
 */
void Qmtable::printTable(){
	for(int i = 0; i < qmcodetable.size(); i++){
		std::cout << qmcodetable[i]->getState() << " " << qmcodetable[i]->getQe()
				<< " " << qmcodetable[i]->getIncS() << " " << qmcodetable[i]->getDecS() << std::endl;
	}
}

