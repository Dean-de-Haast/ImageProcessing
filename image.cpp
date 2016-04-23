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
	Image::~Image() {
		data = NULL;
		height = 0;
		width = 0;
	}


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

		//Skip the line ith 255 on it.
		getline(file,str);
		
		//Reading in the data..
		//Creating a new unsigned char array pointer.
		unique_ptr<unsigned char []> temp(new unsigned char [height*width]);
		
		//Adds each piece of binary data to the array.

		//****************************************MIGHT HAVE TO CHANGE THIS TO USING AN INTERATOR_ CURRENTLY USING A LIBRARY.
		for (int i = 0; i < width*height; i++){
        	file.read((char *) temp.get(), height*width);
		}

        data = std::move(temp);

        //Printing out the input.
  //       for (int i = 0; i < width*height; i++){
  //       	cout<<data.get()[i]<<endl;
		// }

		file.close();	

		//cout<<"THE HEIGHT IS: "<<height<<"THE WIDTH IS "<<width;
	}

	void Image::save(string fileName){

		ofstream outFile(fileName);

		if(!outFile){
			cerr << "File open failed!";
		}
		outFile<<"P5"<<endl;
		outFile<<"# This is a comment"<<endl;
		outFile<< height<<" "<<width<<endl;
		outFile<<"255"<<endl;

		//****************************************MIGHT HAVE TO CHANGE THIS TO USING AN INTERATOR_ CURRENTLY USING A LIBRARY.
    	outFile.write((char *) data.get(), height*width);
	}

	// Image& Image::add(Image& image){
	// 	return this+image;
	// }

	//Overiding the  + operator to allow the addition of images.
	Image& Image::operator+(const Image& image){
		//Check whether the width of both images are the same.
		//Use the iterator instead of this.
		if(height ==image.height && width == image.width){
            for (int i = 0; i < width*height; i++){
            	int currentTemp = (int)((data.get())[i]);
            	int imageTemp = (int)(image.data.get()[i]);
                int tempAddition = currentTemp + imageTemp;

                if (tempAddition <255){
                	data.get()[i] = u_char(tempAddition);
                }else{
                	data.get()[i] =u_char(255);
                } 
            }
        }
        return *this;
    }

    //Overiding the  + operator to allow the addition of images.
	Image& Image::operator-(const Image& image){
		//Check whether the width of both images are the same.
		//Use the iterator instead of this.
		if(height ==image.height && width == image.width){
            for (int i = 0; i < width*height; i++){
            	int currentTemp = (int)((data.get())[i]);
            	int imageTemp = (int)(image.data.get()[i]);
                int tempAddition = currentTemp - imageTemp;

                if (tempAddition > 0){
                	data.get()[i] = u_char(tempAddition);
                }else{
                	data.get()[i] =u_char(0);
                } 
            }
        }
        return *this;
    }

    Image& Image::operator!(){
    	int temp;
        for (int i = 0; i < width*height; i++){
        	temp = (int)(data.get()[i]);
        	data.get()[i]= u_char(255 - temp);
        } 
        return *this;
    }
    
    //***************************************************
    Image& Image::operator/(const Image& image){

        if(width == image.width && height==image.height){
	        for (int i = 0; i < image.width*image.height; i++){

	        	if(((int)(image.data.get()[i]))!=255){
	        		image.data.get()[i] = u_char(0);		
	        	}   	
	        }
        } 
        return *this;
    }
    //*************************************************
    Image& Image::operator*(int f){
        for (int i = 0; i < width*height; i++){

            if((int)((data.get())[i]) > f){
            	data.get()[i] = u_char(255);
            }else{
            	data.get()[i] = 0;	
            } 
        }
        return *this;
    }
