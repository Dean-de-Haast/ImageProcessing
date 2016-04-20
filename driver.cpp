//Assignment 3 - Driver file
//20 April, 2016
//Dean de Haast


#include "Image.h"
#include <memory>

using namespace std;
using namespace DHSDEA001;



 int main (int argc, char *argv[]){
 	string operation = argv[1];
	string inputFile1;
	string inputFile2;
	string outputFile = argv[4];

	Image im;

	if (operation == "-a"){
		inputFile1 = argv[2];
		inputFile2 = argv[3];
		//im.addOperation();

	}else if (operation == "-s"){
		inputFile1 = argv[2];
		inputFile2 = argv[3];
		//im.subtractOperation();

	}else if (operation == "-i"){
		inputFile1 = argv[2];
		//im.invertOperation();

	}else if (operation == "-l"){
		inputFile1 = argv[2];
		inputFile2 = argv[3];
		//im.maskOperation();
		
	}else if (operation == "-t"){
		inputFile1 = argv[2];
		//im.thresholdOperation();
		
	}
	return 0;
 }