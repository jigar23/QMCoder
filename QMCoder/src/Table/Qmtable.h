/*
 * Qmtable.h
 *
 *  Created on: Feb 15, 2014
 *      Author: jigar
 */

#ifndef QMTABLE_H_
#define QMTABLE_H_
#include "../global.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
class Qmtable {
	int state;
	unsigned int	Qe;
	int	incS;
	int	decS;
public:
	Qmtable();
	virtual ~Qmtable();
	int getDecS() const;
	void setDecS(int decS);
	int getIncS() const;
	void setIncS(int incS);
	unsigned int getQe() const;
	void setQe(unsigned int qe);
	int getState() const;
	void setState(int state);
	void printTable();
	static void loadQMtable(char[]);
};

#endif /* QMTABLE_H_ */
