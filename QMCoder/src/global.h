/*
 * global.h
 *
 *  Created on: Feb 15, 2014
 *      Author: jigar
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_


#include <vector>
#include "Table/Qmtable.h"

//Forward declaring the class
class Qmtable;
extern int FileSizeinBytes;

extern char *memblock;

extern std::vector <Qmtable*> qmcodetable;


#endif /* GLOBAL_H_ */
