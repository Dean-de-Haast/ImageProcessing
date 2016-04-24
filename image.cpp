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
        Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = i.begin(), inEnd = i.end();

		while ( beg != end){
			//cout<<"COPY@@@@@"<<endl;
			*beg = *inStart; 
			++beg; 
			++inStart;
		} 
    }

	//move constructor
	Image::Image(Image&& i) {
		width = i.width;
        height = i.height;
        data = std::move(i.data);
        i.width = 0;
        i.height = 0;
        i.data = nullptr;
		
	}

	//destructor
	Image::~Image() {
		data = nullptr;
		height = 0;
		width = 0;
	}

	//Copy assignment operator
	Image& Image::operator=(const Image& other){
		cout<<"Called"<<endl;

        width = other.width;
       	height = other.height;
       	//data.reset(nullptr);

       	unique_ptr<unsigned char []> temp (new unsigned char[this->width*this->height]); 

		this->data = std::move(temp);

		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = other.begin(), inEnd = other.end();

       // USING ITERATORS
        while (beg != end){
        	*beg =*inStart;
        	++beg;
        	++inStart;
        }

        return *this;
    }
    
    //Assignment move operator
    Image& Image::operator=(Image&& other){
       	Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = other.begin(), inEnd = other.end();

        height = other.height;
        width = other.width;
        data = std::move(other.data);

        other.width = 0;
        other.height = 0;
        other.data = nullptr;
        return *this;
    }


    //Reading in from the file
	void Image::load(string fileName) {
		
		//Checks if file can be opened.
		ifstream file(fileName);
		if(!file){
			cerr << "File open failed!";
		}
		//Loads the file, using the overiden >> operator.
		file >> *this;
		

		file.close();	
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

            while ( beg != end){ 

                int tempAddition = *beg + *inStart;
                //if the value is more than 255 then  set it to 255 else set it to the addition of both images.
                if (tempAddition <255){
                	*beg = u_char(tempAddition);
                }else{
                	*beg =u_char(255);
                } 

                ++beg; 
            	++inStart; 
            }
        }

        return copyLHS;
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

			while ( beg != end){ 

                int tempAddition = *beg - *inStart;
                //Subtract the value if the total is bigger than 0 else set it to 0.
                if (tempAddition >0){
                	*beg = u_char(tempAddition);
                }else{
                	*beg =u_char(0);
                } 

                ++beg; 
            	++inStart; 
            }
        }
        return copyLHS;
    }

    //Overiding the ! operator.
    Image Image::operator!()const{

    	Image copyLHS = *this;

    	Image::iterator beg = copyLHS.begin(), end = copyLHS.end();

        while ( beg != end){

        	*beg= u_char(255 - *beg);

        	++beg; 
        } 
        return copyLHS;
    }
    
    //Overiding the / operator.
    Image Image::operator/(const Image& image)const{

    	//Create two temp images.
		Image copyLHS = *this;
		Image copyRHS = image;

    	Image::iterator beg = copyLHS.begin(), end = copyLHS.end();
		Image::iterator inStart = copyRHS.begin(), inEnd = copyRHS.end();

        if(width == image.width && height==image.height){
	        while ( beg != end){

	        	if(*beg!=255){
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

        while ( beg != end){

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

    istream& operator >>(std::istream& file,Image& img){
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


        img.data = std::move(temp);

        return file;
	}

	ofstream& operator <<(std::ofstream& outFile,Image& img){
		//Write out thenecessary lines at the top of the file.
		outFile<<"P5"<<endl;
		outFile<<"# This is a comment"<<endl;
		outFile<< img.height<<" "<< img.width <<endl;
		outFile<<"255"<<endl;
		//Print the data to the file.s
		outFile.write((char *) img.data.get(), img.height*img.width);

	}
}
