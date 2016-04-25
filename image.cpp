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
		if(this != &i){
	        width = i.width;
	        height = i.height;
	        unique_ptr<unsigned char []> temp (new unsigned char[i.width*i.height]);
	        //Call the inbuilt move method.
	        data = move(temp);

	        //Change the data for each entry, ie like a for loop but with iterators.
	        Image::iterator beg = this->begin(), end = this->end();
			Image::iterator inStart = i.begin(), inEnd = i.end();

			while ( beg != end){
				*beg = *inStart; 
				++beg; 
				++inStart;
			}
		}
    }

	//move constructor
	Image::Image(Image&& i) {
		width = i.width;
        height = i.height;
        data = move(i.data);
        i.width = 0;
        i.height = 0;
        i.data = nullptr;
		
	}

	//destructor
	Image::~Image() {
		height = 0;
		width = 0;
		data = nullptr;
	}

	//Copy assignment operator
	Image& Image::operator=(const Image& other){
		if(this != &other){
	        width = other.width;
	       	height = other.height;

	       	unique_ptr<unsigned char []> temp (new unsigned char[width*height]); 

			data = move(temp);

			Image::iterator beg = this->begin(), end = this->end();
			Image::iterator inStart = other.begin(), inEnd = other.end();

	       // USING ITERATORS
	        while(beg != end){
	        	*beg =*inStart;
	        	++beg;
	        	++inStart;
	        }

	        return *this;
    	}else return *this;
    }
    
    //Assignment move operator
    Image& Image::operator=(Image&& other){
       	Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = other.begin(), inEnd = other.end();

        height = other.height;
        width = other.width;
        data = move(other.data);

        other.width = 0;
        other.height = 0;
        other.data = nullptr;
        return *this;
    }

	//Saving the image to a file.
	void Image::save(string fileName){

		ofstream outFile(fileName);

		if(!outFile){
			cerr << "File open failed!";
		}
		//Saves the file, using the overiden << operator.
		outFile<< *this;

		outFile.close();	
	}


    //Reading in from the file
	void Image::load(string fileName) {
		
		//Checks if file can be opened.
		ifstream file(fileName);
		if(!file){
			cerr << "File open failed!";
		}else{
			//Loads the file, using the overiden >> operator.
			file >> *this;
		}

		file.close();	
	}

	//Overiding the  + operator to allow the addition of images.
	Image Image::operator+(const Image& image)const{

		//Create two temp images.
		Image copyLHS = *this;
		Image copyRHS = image;

		Image::iterator beg = copyLHS.begin(), end = copyLHS.end();
		Image::iterator inStart = copyRHS.begin(), inEnd = copyRHS.end();
		//Check whether the width of both images are the same.
		//Use the iterator instead of this.
		if(height ==image.height && width == image.width){

            while(inStart != inEnd){ 

                int tempAddition = *beg + *inStart;
                //if the value is more than 255 then  set it to 255 else set it to the addition of both images.
                if (tempAddition <255){
                	*inStart = u_char(tempAddition);
                }else{
                	*inStart =u_char(255);
                } 

                ++beg; 
            	++inStart; 
            }
        }

        return copyRHS;
    }

    //Overiding the  - operator to allow the addition of images.
	Image Image::operator-(const Image& image)const{

		//Create two temp images.
		Image copyLHS = *this;
		Image copyRHS = image;

		Image::iterator beg = copyLHS.begin(), end = copyLHS.end();
		Image::iterator inStart = copyRHS.begin(), inEnd = copyRHS.end();
		//Check whether the width of both images are the same.
		
		if(height ==image.height && width == image.width){

			while(inStart != inEnd){ 

                int tempAddition = *beg - *inStart;
                //Subtract the value if the total is bigger than 0 else set it to 0.
                if (tempAddition >0){
                	*inStart = u_char(tempAddition);
                }else{
                	*inStart =u_char(0);
                } 

                ++beg; 
            	++inStart; 
            }
        }
        return copyRHS;
    }

    //Overiding the ! operator.
    Image Image::operator!()const{

    	Image copyLHS = *this;

    	Image::iterator beg = copyLHS.begin(), end = copyLHS.end();

        while(beg != end){
        	*beg= u_char(255 - *beg);
        	++beg; 
        } 
        return copyLHS;
    }
    
    //Overiding the / operator. Takes in a mask as image 2
    Image Image::operator/(const Image& image)const{

    	//Create two temp images.
		Image copyLHS = *this;
		Image copyRHS = image;

    	Image::iterator beg = copyLHS.begin(), end = copyLHS.end();
		Image::iterator inStart = copyRHS.begin(), inEnd = copyRHS.end();

        if(width == image.width && height==image.height){
	        while(beg != end){
	        	//If value mask != 255 then change output image to 0
	        	if(*inStart!=255){ 
	        		*beg = u_char(0);		
	        	}   

	        	++beg; 
            	++inStart; 	
	        }
        } 
        return copyLHS;
    }

    //Overiding the * operator.
    Image Image::operator*(int f)const{

    	//Create two temp images.
		Image copyLHS = *this;

    	Image::iterator beg = copyLHS.begin(), end = copyLHS.end();

        while(beg != end){

            if(*beg > f){
            	*beg = u_char(255);
            }else{
            	*beg = 0;	
            } 
            ++beg; 
        }
        return copyLHS;
    }

//I inserted this as it would not comile without explicitly declaring it here.
namespace DHSDEA001{

    void operator >>(std::istream& file,Image& img){
    	string str;
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
		parts >> img.height >> img.width >> ws;	

		//Skip the line ith 255 on it.
		getline(file,str);
		
		//Reading in the data..
		//Creating a new unsigned char array pointer.
		unique_ptr<unsigned char []> temp(new unsigned char [img.height*img.width]);
		
		//Adds each piece of binary data to the array.
        file.read((char *) temp.get(), img.height*img.width);

        img.data = move(temp);
	}

	void operator <<(std::ofstream& outFile,Image& img){
		//Write out thenecessary lines at the top of the file.
		outFile<<"P5"<<"\n"<<"# This is a comment"<<"\n"<<img.height<<" "<< img.width<<"\n"<<"255"<<endl;
		//Print the data to the file.s
		outFile.write((char *) img.data.get(), img.height*img.width);

	}
}
