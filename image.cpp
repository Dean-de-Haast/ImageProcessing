//Assignment 3 - image file
//20 April, 2016
//Dean de Haast


#include "image.h"

using namespace DHSDEA001;
using namespace std;

	//constructor(s)
	Image::Image() {
		width = 0;
		height = 0;
	}

	//copy constructor
	Image::Image(const Image& image) {
		height = image.height;
		width = image.width;
	}

	//move constructor
	Image::Image(Image&& image) {
		
	}

	//destructor
	Image::~Image() {}

	//method headers and definitions
	void Image::load(string fileName) {
		//Reading in from the file:
		string str;

		ifstream file(fileName);
		if(!file){
			cerr << "File open failed!";
		}
		//Get rid of the first line.
		getline(file,str);
		//Get the next line, the first of the comment lines.
		getline(file,str);
		while(str[0] == '#'){
			getline(file,str);
		}
		
		stringstream parts(str);
			
		parts >> height >> width >> ws;	
		file.close();	

		cout<<"THE HEIGHT IS: "<<height<<"THE WIDTH IS "<<width;
	}

	void Image:: save(string fileName){
		
		ofstream outFile(fileName);

		if(!outFile){
			cerr << "File open failed!";
		}
		outFile<< height<<" "<<width<<endl;
		outFile.write((char *) data.get(), height*width);
	}
