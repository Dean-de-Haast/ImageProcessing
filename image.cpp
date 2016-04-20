//Assignment 3 - image file
//20 April, 2016
//Dean de Haast


#include "image.h"

using namespace DHSDEA001;

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
	void Image::load(std::string imageName) {
			
	}
