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

	if (operation == "-a"){
		inputFile1 = argv[2];
		inputFile2 = argv[3];
		outputFile = argv[4];
		im.load(inputFile1);
		im2.load(inputFile2);
		im+im2;

	}else if (operation == "-s"){
		inputFile1 = argv[2];
		inputFile2 = argv[3];
		outputFile = argv[4];
		im.load(inputFile1);
		im2.load(inputFile2);
		//im3 = im-im2;

	}else if (operation == "-i"){
		inputFile1 = argv[2];
		outputFile = argv[3];
		im.load(inputFile1);
		//im3 = !im;

	}else if (operation == "-l"){
		inputFile1 = argv[2];
		inputFile2 = argv[3];
		outputFile = argv[4];
		im.load(inputFile1);
		im2.load(inputFile2);
		//im3 = im/im2;
		
	}else if (operation == "-t"){
		inputFile1 = argv[2];
		threshold = atoi(argv[3]);
		outputFile = argv[4];
		im.load(inputFile1);
		//im3 = im*threshold;
		
	}
	im.save(outputFile);
	return 0;
}
