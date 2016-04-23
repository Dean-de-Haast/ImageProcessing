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

			//destructor
			~Image();

			//Method which calls addition 
			Image& add(Image& image);

			//method headers
			void load(std::string fileName);
			void save(std::string fileName);

			//Overiding the operators
			//Addition.
			Image& operator+(const Image& image);
			//Subtraction.
			Image& operator-(const Image& image);
			//Addition.
			Image& operator!();
			//Mask.
			Image& operator/(const Image& image);
			//Threshold.
			Image& operator*(int f);
	
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
						if (ptr != rhs.ptr){
							return true;
						}else return false;
					}

					//==
					bool operator ==(const iterator & rhs){
						if (ptr == rhs.ptr){
							return true;
						}else return false;
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
