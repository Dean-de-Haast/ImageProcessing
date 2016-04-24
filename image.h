//Assignment 3 - image header file
//20 April, 2016
//Dean de Haast

#include <memory>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#ifndef IMAGE_H
#define IMAGE_H

namespace DHSDEA001 {

	class Image {
		private:
			int width, height;
			std::unique_ptr<unsigned char[]> data;

		public:
			//default constructor
			Image();

			//copy constructor
			Image(const Image& i); 

			//move constructor
			Image(Image&& i);

			//copy assignment operator
			Image & operator=(const Image & rhs);

			//  move assignment operator
			Image & operator=(Image && rhs);

			//destructor
			~Image();

			//Method which calls addition 
			Image& add(Image& image);

			//method headers
			void load(std::string fileName);
			void save(std::string fileName);

			//Overiding the operators
			//Addition.
			Image operator+(const Image& image)const;
			//Subtraction.
			Image operator-(const Image& image) const;
			//Addition.
			Image operator!() const;
			//Mask.
			Image operator/(const Image& image)const;
			//Threshold.
			Image operator*(int f) const;

			friend std::istream & operator>>(std::istream& file, Image& img);
			friend std::ofstream & operator<<(std::ofstream& file, Image& img);

	
			//Iterator class
			class iterator {
				//Doesn't work without the friend part..

				friend class Image;
				private:
					unsigned char *ptr;
					iterator(u_char *p) : ptr(p) {}

				public:		
					//Copy constructor			
					iterator( const iterator & rhs) : ptr(rhs.ptr) {}

					//overide = operator.
					iterator& operator=(const iterator & rhs) {
						ptr =rhs.ptr;
						return *this;
					}	

					//overide ++ operator.
					void operator++() {
						++ptr;
					}

					//overide -- operator.
					void operator--() {
						--ptr;
					}

					//overide * operator.
					unsigned char & operator*() {
						return *ptr;
					}

					//!=
					bool operator!=(const iterator & rhs) {
						return (ptr != rhs.ptr);
					}

					//==
					bool operator ==(const iterator & rhs){
						return (ptr == rhs.ptr);
					}

			}; 

			iterator begin(void) const{
				return iterator(data.get());
			} 

			iterator end(void) const{
				return iterator(data.get()+ (width*height));
			} 
	}; 

}

#endif
