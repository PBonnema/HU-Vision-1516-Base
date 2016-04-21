//Geimplementeerd met een 2-D contiguous row-major array

#include "IntensityImageStudent.h"

//Comment this line out to disable checking for out-of-bounds errors within the pixel access methods
//The out-of-bounds check also makes sure the image is initialized with a width>0 and height>0 before accessing any pixels because the default size is 0,0
//#define OUT_OF_BOUNDS_CHECK

#ifdef OUT_OF_BOUNDS_CHECK

#include <exception>
#include <string>
class IntensityImageException : public std::exception {
	std::string msg;
public:
	IntensityImageException(const std::string& msg) : msg(msg) {}
	const char* what() const override{
		return msg.c_str();
	}
};

#endif


IntensityImageStudent::IntensityImageStudent() : IntensityImage{}, pixelData{ nullptr }
{
}


IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) :
IntensityImage{ other.getWidth(), other.getHeight() },
pixelData{ new Intensity*[other.getHeight()] } //init pixelData as an array of rows (it's a row-major 2d array)
{
	int width = getWidth(), height = getHeight();

	//Init the whole memory as a contiguous block and let the first pointer point to the beginning of it.
	//This also serves as the pointer to the first row
	pixelData[0] = new Intensity[width * height];

	for(int y = 0; y < height; y++) { //we cannot skip the first row now because we need to copy other
		pixelData[y] = &(pixelData[0][width * y]); //init new rows

		//std::copy(std::begin(other), std::end(other), std::begin(pixelData[i]));

		//copy the row
		Intensity* row = pixelData[y];
		for(int x = 0; x < width; x++) {
			row[x] = other.getPixel(x, y);
		}
	}
}


IntensityImageStudent::IntensityImageStudent(const int width, const int height) :
IntensityImage{ width, height },
pixelData{ new Intensity*[height] } //init pixelData as an array of rows (it's a row-major 2d array)
{
	//Init the whole memory as a contiguous block and let the first pointer point to the beginning of it.
	//This also serves as the pointer to the first row
	pixelData[0] = new Intensity[width * height];

	//init the rest of the pointer to point to the individual rows within the contiguous block of memory
	for(int i = 1; i < height; i++) { //we can skip the first row now so i starts at 1
		pixelData[i] = &(pixelData[0][width * i]);
	}
}


IntensityImageStudent::~IntensityImageStudent() {
	if(pixelData != nullptr) { //don't attempt to delete when pixelData was never initialized
		delete[] pixelData[0]; //Delete the entire contiguous block of memory
		delete[] pixelData; //Delete the array of row pointers
	}
}


void IntensityImageStudent::set(const int width, const int height) {
	IntensityImage::set(width, height);
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)

	//delete old pixel storage only if it has been initialized
	if(pixelData != nullptr) {
		delete[] pixelData[0];
		delete[] pixelData;
	}

	//Init the whole memory as a contiguous block and let the first pointer point to the beginning of it.
	//This also serves as the pointer to the first row
	pixelData = new Intensity*[height];
	pixelData[0] = new Intensity[width * height];

	//init the rest of the pointer to point to the individual rows within the contiguous block of memory
	for(int i = 1; i < height; i++) { //we can skip the first row now so i starts at 1
		pixelData[i] = &(pixelData[0][width * i]);
	}
}


void IntensityImageStudent::set(const IntensityImageStudent &other) {
	IntensityImage::set(other.getWidth(), other.getHeight());
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)

	//delete old pixel storage only if it has been initialized
	if(pixelData != nullptr) {
		delete[] pixelData[0];
		delete[] pixelData;
	}

	int height = other.getHeight();
	int width = other.getWidth();

	//initialize some new memory with different dimensions
	pixelData = new Intensity*[height];

	//Init the whole memory as a contiguous block and let the first pointer point to the beginning of it.
	//This also serves as the pointer to the first row
	pixelData[0] = new Intensity[width * height];

	//copy other's pixelData
	for(int y = 0; y < height; y++) {
		pixelData[y] = &(pixelData[0][width * y]);

		//std::copy(std::begin(other), std::end(other), std::begin(pixelData[i]));

		//copy the row
		Intensity* row = pixelData[y];
		for(int x = 0; x < width; x++) {
			row[x] = other.getPixel(x, y);
		}
	}
}


void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
#ifdef OUT_OF_BOUNDS_CHECK
	if(x >= getWidth() || y >= getHeight()) {
		throw IntensityImageException("setPixel(int x, int y, Intensity pixel) x >= getWidth() || y >= getHeight()");
	}
#endif

	pixelData[y][x] = pixel;
}


void IntensityImageStudent::setPixel(int i, Intensity pixel) {
#ifdef OUT_OF_BOUNDS_CHECK
	if(i >= getWidth() * getHeight()) {
		throw IntensityImageException("setPixel(int i, Intensity pixel) i >= getWidth() * getHeight()");
	}
#endif

	pixelData[0][i] = pixel;
}


Intensity IntensityImageStudent::getPixel(int x, int y) const {
#ifdef OUT_OF_BOUNDS_CHECK
	if(x >= getWidth() || y >= getHeight()) {
		throw IntensityImageException("getPixel(int x, int y) x >= getWidth() || y >= getHeight()");
	}
#endif

	return pixelData[y][x];
}


Intensity IntensityImageStudent::getPixel(int i) const {
#ifdef OUT_OF_BOUNDS_CHECK
	if(i >= getWidth() * getHeight()) {
		throw IntensityImageException("getPixel(i) i >= getWidth() * getHeight()");
	}
#endif

	return pixelData[0][i];
}