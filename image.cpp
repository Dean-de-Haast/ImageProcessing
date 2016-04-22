//Assignment 3 - image file
//20 April, 2016
//Dean de Haast


#include "image.h"

using namespace DHSDEA001;
using namespace std;

	//constructor
	Image::Image() {
		width = 0;
		height = 0;
	}

	//copy constructor
	Image::Image(const Image& i){
        width = i.width;
        height = i.height;
        unique_ptr<unsigned char []> temp (new unsigned char[i.width*i.height]);
        //Call the inbuilt move method.
        data = std::move(temp);

        //Change the data for each entry, ie like a for loop but with iterators.
    }

	//move constructor
	Image::Image(Image&& i) {
		width = i.width;
        height = i.height;
        data = std::move(i.data);
        i.width = 0;
        i.height = 0;
		
	}

	//destructor
	Image::~Image() {}


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
		//Check whether the next lines are comment lines, if so skip them.
		while(str[0] == '#'){
			getline(file,str);
		}
		//Create a stringStream
		stringstream parts(str);
		//Read in all of the bytes into  the char array.	
		parts >> height >> width >> ws;	
		
		file.close();	

		cout<<"THE HEIGHT IS: "<<height<<"THE WIDTH IS "<<width;
	}

	void Image::save(string fileName){

		ofstream outFile(fileName);

		if(!outFile){
			cerr << "File open failed!";
		}
		outFile<< height<<" "<<width<<endl;
		outFile.write((char *) data.get(), height*width);
	}

	//Overiding the  + operator to allow the addition of images.
	Image& Image::operator+(const Image& image){
		//Check whether the width of both images are the same.
		//Use the iterator instead of this.
            for (int i = 0; i < width*height; i++){
            	int currentTemp = (int)((data.get())[i]);
            	int imageTemp = (int)(image.data.get()[i]);
                int tempAddition = currentTemp + imageTemp;

                if (temp <255){
                	data.get()[i] = u_char(temp);
                }else{
                	data.get()[i] =u_char(255);
                } 
            }
        return *this;
    }
