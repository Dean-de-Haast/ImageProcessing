//Assignment 3 - Image header file
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
			//variables
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
			void loadImage(std::string imageName);
			void saveImage(std::string imageName);
	};
}