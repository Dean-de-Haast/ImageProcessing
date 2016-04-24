//Assignment 3 - Driver file
//20 April, 2016
//Dean de Haast


#include "image.h"
#include <memory>


using namespace std;
using namespace DHSDEA001;



 int main (int argc, char *argv[]){

	string operation = argv[1];
	string inputFile1;
	string inputFile2;
	string outputFile;
	int threshold;

	Image im,im2;
	//Depending on what operation the user choses depends on what arguments are placed in different places.

	//addition
	if (operation == "-a"){
		inputFile1 = argv[2];
		inputFile2 = argv[3];
		outputFile = argv[4];
		im.load(inputFile1);
		im2.load(inputFile2);
		im+im2;

	//Subtraction
	}else if (operation == "-s"){
		inputFile1 = argv[2];
		inputFile2 = argv[3];
		outputFile = argv[4];
		im.load(inputFile1);
		im2.load(inputFile2);
		im-im2;

	//Inverse
	}else if (operation == "-i"){
		inputFile1 = argv[2];
		outputFile = argv[3];
		im.load(inputFile1);
		!im;

	//Mask
	}else if (operation == "-l"){
		inputFile1 = argv[2];
		inputFile2 = argv[3];
		outputFile = argv[4];
		im.load(inputFile1);
		im2.load(inputFile2);
		im/im2;
		
	//Threshold
	}else if (operation == "-t"){
		inputFile1 = argv[2];
		threshold = atoi(argv[3]);
		outputFile = argv[4];
		im.load(inputFile1);
		im*threshold;
		
	}
	//Save the image.
	im.save(outputFile);
	return 0;
}
