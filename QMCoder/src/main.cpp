//============================================================================
// Name        : QMCoder.cpp
// Author      : Jigar Gada
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "FileIO/fileIO.h"
#include <vector>
#include "Table/Qmtable.h"
#include "global.h"

void initialize();
void changeQe(int val);
void checkChangeQ_e();
void renormalize();
void printFileSize(char[],char[],int, int);
using namespace std;
char *memblock;

namespace QM{
	unsigned int A;
	unsigned short int C;
	int currentState;
	unsigned int Q_e;
	bool carry;
	bool MPS;
	bool LPS;
	int scrapBits;
}


//int main(){
//	char opFile[] = "resources/HWProb.dat";
//	char *outputFile = opFile;
//	writePrepare(outputFile);
//	WriteBit(1);
//	WriteBit(1);
//	WriteBit(0);
//	WriteBit(0);
//	WriteBit(0);
//	WriteBit(1);
//	WriteBit(0);
//	WriteBit(0);
//	WriteBit(1);
//	WriteBit(0);
//
//	checkStatusOfLastBit();
//	closeFile();
//}

int main() {

	//User Interaction to enter filename
		cout << "-----------------------------" << endl;
		cout << "Enter the *full* file Path with name: " << endl;
		char filename[512];
		cin.getline(filename,512);

//	char filename[] = "resources/binary.dat";

	//load the QM table in the global vector qmcodetable
	char tablefile[] = "QM_state_transition_table.txt";
	Qmtable::loadQMtable(tablefile);

	char opFile[] = "QMEncoded.dat";
	char *outputFile = opFile;
	writePrepare(outputFile);

	//read the contents of the file and store it in memblock
	memblock = readFileByBytes(filename);
	int originalFileSize = FileSizeinBytes;
	//initialize the QM coder
	initialize();
	cout << "Started Encoding..." << endl;
	//read the bits from the file till end of file
	while (!checkEOF()) {
		if (ReadBit() == QM::MPS) {
//			cout << "0";
			QM::A = QM::A - QM::Q_e;
			if(QM::A < 0x8000){
				if(QM::A < QM::Q_e){
					if((QM::C + QM::A) > 0xFFFF) QM::carry = true;
					QM::C += QM::A;
					QM::A = QM::Q_e;
				}
				changeQe(1);
				renormalize();
			}
		}
		else{
//			cout << "1";
			QM::A = QM::A - QM::Q_e;
			if(QM::A >= QM::Q_e){
				if((QM::C + QM::A) > 0xFFFF) QM::carry = true;
					QM::C += QM::A;
					QM::A = QM::Q_e;
			}
			changeQe(0);
			renormalize();
		}
	}

	cout << "Done Encoding.!! :)" << endl;
	cout << "Encoded data stored in *QMEncoded.dat*" << endl;

	checkStatusOfLastBit();
	closeFile();

	int encodedFileSize = getFileSize("QMEncoded.dat");
	printFileSize(filename,outputFile,encodedFileSize,originalFileSize);
	return 0;
}


void initialize(){
	QM::A = 0x10000;
	QM::C = 0x0000;
	QM::currentState = 10;
	QM::Q_e = qmcodetable[QM::currentState]->getQe();
	QM::carry = false;
	QM::MPS = 0;
	QM::LPS = 1;
	QM::scrapBits = 0;
}

/**
 * @param
 * 1. int val
 * val = 1 if MPS
 * val = 0 for LPS
 */
void changeQe(int val){
	//MPS received, increment the state
	if(val == 1){
		int temp = qmcodetable[QM::currentState]->getIncS();
		QM::currentState += temp;
	}
	//LPS received, decrement the state
	else{
		int temp = qmcodetable[QM::currentState]->getDecS();
		QM::currentState -= temp;
		//Swap the MSB and LSB
		if(qmcodetable[QM::currentState]->getDecS() == -1){
			temp = QM::LPS;
			QM::LPS = QM::MPS;
			QM::MPS = temp;
		}

	}
	QM::Q_e = qmcodetable[QM::currentState]->getQe();
}

/**
 * For this function detail, Refer the algorithm.
 */
void renormalize(){

	if(QM::carry){
		WriteBit(1);
		QM::scrapBits++;
		cout << "Carry generated" << endl;
		QM::carry = false;
	}
	//output until the value of A >= 0x8000
	while(QM::A < 0x8000){
		QM::A = QM::A << 1;
		//check if MSB is 0
		if((QM::C & (0x8000)) == 0) {
			//cout << 0;
			WriteBit(0);
			QM::scrapBits++;
		}
		else {
			//cout << 1;
			WriteBit(1);
			QM::scrapBits++;
		}
		cout << hex << QM::C << endl;
		QM::C = QM::C << 1;
	}
}

/**
 * This function just checks whether q_e is changing
 * properly or not.
 */
void checkChangeQ_e(){
	cout << "current state: " << std::dec << QM::currentState << endl;
	cout << "current Qe: " << std::hex << QM::Q_e << endl;
	changeQe(0);
	cout << "next state: " << std::dec << QM::currentState << endl;
	cout << "next Qe: " << std::hex << QM::Q_e << endl;
}

void printFileSize(char inputFileName[], char outputFileName[], int encodedFileSize, int originalFileSize){
	cout << endl;
	cout << "**********************************" << endl << endl;
	cout << "Input File Name      : " <<inputFileName << endl;
	cout << "Output File Name     : " << outputFileName << endl;
	cout << "Original File size   : " << originalFileSize << " bytes" << endl;
	cout << "Compressed File size : " << encodedFileSize << " bytes" << endl;
	cout << "Compression Ratio    : " << (float)encodedFileSize/originalFileSize*100 << "%" << endl << endl;
	cout << "**********************************" << endl;
}


