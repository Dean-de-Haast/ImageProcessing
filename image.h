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
			Image(const Image& image);

			//move constructor
			Image(Image&& image);

			//destructor
			~Image();

			//method headers
			void load(std::string fileName);
			void save(std::string fileName);
	
			//Iterator class
			class iterator {
				private:
					unsigned char *ptr;
					// construct only via Image class (begin/end)
					iterator(u_char *p) : ptr(p) {}

				public:					
					//copy construct is public
					iterator( const iterator & rhs) : ptr(rhs.ptr) {}

					iterator & operator=(const iterator & rhs) {}	

			}; 
	}; 

}

#endif