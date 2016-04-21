#pragma once
#include "RGBImage.h"

class RGBImageStudent : public RGBImage
{
public:
	RGBImageStudent();
	RGBImageStudent(const RGBImageStudent &other);
	RGBImageStudent(const int width, const int height);
	virtual ~RGBImageStudent();

	void set(const int width, const int height) override;
	void set(const RGBImageStudent &other);

	void setPixel(int x, int y, RGB pixel) override;
	void setPixel(int i, RGB pixel) override;

	RGB getPixel(int x, int y) const override;
	RGB getPixel(int i) const override;

private:
	RGB** pixelData; //row major 2-d array of pixel structs on heap
};


//Comment this line out to disable checking for out-of-bounds errors within the pixel access methods
//The out-of-bounds check also makes sure the image is initialized with a width>0 and height>0 before accessing any pixels because the default size is 0,0
//#define OUT_OF_BOUNDS_CHECK

#ifdef OUT_OF_BOUNDS_CHECK

#include <exception>
#include <string>
class RGBImageException : public std::exception {
	std::string msg;
public:
	RGBImageException(const std::string& msg) : msg(msg) {}
	const char* what() const override{
		return msg.c_str();
	}
};

#endif


RGBImageStudent::RGBImageStudent() : RGBImage{}, pixelData{ nullptr }
{
}


RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) :
RGBImage{ other.getWidth(), other.getHeight() },
pixelData{ new RGB*[other.getHeight()] } //init pixelData as an array of rows (it's a row-major 2d array)
{
	int width = getWidth(), height = getHeight();

	//Init the whole memory as a contiguous block and let the first pointer point to the beginning of it.
	//This also serves as the pointer to the first row
	pixelData[0] = new RGB[width * height];

	for(int y = 0; y < height; y++) { //we cannot skip the first row now because we need to copy other
		pixelData[y] = &(pixelData[0][width * y]); //init new rows

		//std::copy(std::begin(other), std::end(other), std::begin(pixelData[i]));

		//copy the row
		RGB* row = pixelData[y];
		for(int x = 0; x < width; x++) {
			row[x] = other.getPixel(x, y);
		}
	}
}


RGBImageStudent::RGBImageStudent(const int width, const int height) :
RGBImage{ width, height },
pixelData{ new RGB*[height] } //init pixelData as an array of rows (it's a row-major 2d array)
{
	//Init the whole memory as a contiguous block and let the first pointer point to the beginning of it.
	//This also serves as the pointer to the first row
	pixelData[0] = new RGB[width * height];

	//init the rest of the pointer to point to the individual rows within the contiguous block of memory
	for(int i = 1; i < height; i++) { //we can skip the first row now so i starts at 1
		pixelData[i] = &(pixelData[0][width * i]);
	}
}


RGBImageStudent::~RGBImageStudent() {
	if(pixelData != nullptr) { //don't attempt to delete when pixelData was never initialized
		delete[] pixelData[0]; //Delete the entire contiguous block of memory
		delete[] pixelData; //Delete the array of row pointers
	}
}


void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)

	//delete old pixel storage only if it has been initialized
	if(pixelData != nullptr) {
		delete[] pixelData[0];
		delete[] pixelData;
	}

	//Init the whole memory as a contiguous block and let the first pointer point to the beginning of it.
	//This also serves as the pointer to the first row
	pixelData = new RGB*[height];
	pixelData[0] = new RGB[width * height];

	//init the rest of the pointer to point to the individual rows within the contiguous block of memory
	for(int i = 1; i < height; i++) { //we can skip the first row now so i starts at 1
		pixelData[i] = &(pixelData[0][width * i]);
	}
}


void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)

	//delete old pixel storage only if it has been initialized
	if(pixelData != nullptr) {
		delete[] pixelData[0];
		delete[] pixelData;
	}

	int height = other.getHeight();
	int width = other.getWidth();

	//initialize some new memory with different dimensions
	pixelData = new RGB*[height];

	//Init the whole memory as a contiguous block and let the first pointer point to the beginning of it.
	//This also serves as the pointer to the first row
	pixelData[0] = new RGB[width * height];

	//copy other's pixelData
	for(int y = 0; y < height; y++) {
		pixelData[y] = &(pixelData[0][width * y]);

		//std::copy(std::begin(other), std::end(other), std::begin(pixelData[i]));

		//copy the row
		RGB* row = pixelData[y];
		for(int x = 0; x < width; x++) {
			row[x] = other.getPixel(x, y);
		}
	}
}


void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
#ifdef OUT_OF_BOUNDS_CHECK
	if(x >= getWidth() || y >= getHeight()) {
		throw RGBImageException("setPixel(int x, int y, RGB pixel) x >= getWidth() || y >= getHeight()");
	}
#endif

	pixelData[y][x] = pixel;
}


void RGBImageStudent::setPixel(int i, RGB pixel) {
#ifdef OUT_OF_BOUNDS_CHECK
	if(i >= getWidth() * getHeight()) {
		throw RGBImageException("setPixel(int i, RGB pixel) i >= getWidth() * getHeight()");
	}
#endif

	pixelData[0][i] = pixel;
}


RGB RGBImageStudent::getPixel(int x, int y) const {
#ifdef OUT_OF_BOUNDS_CHECK
	if(x >= getWidth() || y >= getHeight()) {
		throw RGBImageException("getPixel(int x, int y) x >= getWidth() || y >= getHeight()");
	}
#endif

	return pixelData[y][x];
}


RGB RGBImageStudent::getPixel(int i) const {
#ifdef OUT_OF_BOUNDS_CHECK
	if(i >= getWidth() * getHeight()) {
		throw RGBImageException("getPixel(i) i >= getWidth() * getHeight()");
	}
#endif

	return pixelData[0][i];
}