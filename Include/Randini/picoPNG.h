// picoPNG version 20101224
// Copyright (c) 2005-2010 Lode Vandevenne
//

#include <vector>

namespace Randini
{
	//paramters: takes an out image of unsigned chars for rgba values and fills it with from a png filem, image width and image height tells the program the dimensions
	//of the png file, in png is the png data that will be loaded for example it will write to a vector and read form a char*,
	//size_t will be the size of the char*, finally this tell it if its going to convert the data into rgba vlaues set true by default as 32bits is what I want
	extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);
}
