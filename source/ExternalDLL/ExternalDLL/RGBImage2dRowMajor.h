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

RGBImageStudent::RGBImageStudent() : RGBImage{}, pixelData{ nullptr } {
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) :
RGBImage{ other.getWidth(), other.getHeight() },
pixelData{ new RGB*[other.getHeight()] } //init pixelData as an array of rows (it's a row-major 2d array)
{
	int width = getWidth(), height = getHeight();
	for(int y = 0; y < height; y++) {
		pixelData[y] = new RGB[width]; //init new rows

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
	//init the rest of the pointer to point to the individual rows
	for(int i = 0; i < height; i++) {
		pixelData[i] = new RGB[width];
	}
}

RGBImageStudent::~RGBImageStudent() {
	if(pixelData != nullptr) { //don't attempt to delete when pixelData was never initialized
		int height = getHeight();
		for(int i = 0; i < height; i++) {
			delete[] pixelData[i];
		}
		delete[] pixelData; //Delete the array of row pointers
	}
}

void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)

	//delete old pixel storage only if it has been initialized
	if(pixelData != nullptr) {
		int height = getHeight();
		for(int i = 0; i < height; i++) {
			delete[] pixelData[i];
		}
		delete[] pixelData;
	}

	//Init some new memory with different dimensions
	pixelData = new RGB*[height];

	//init the rest of the pointer to point to the individual rows
	for(int i = 0; i < height; i++) {
		pixelData[i] = new RGB[width];
	}
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)

	//delete old pixel storage only if it has been initialized
	if(pixelData != nullptr) {
		int height = getHeight();
		for(int i = 0; i < height; i++) {
			delete[] pixelData[i];
		}
		delete[] pixelData;
	}

	int height = other.getHeight();
	int width = other.getWidth();

	//Init some new memory with different dimensions
	pixelData = new RGB*[height];

	//init the rest of the pointer to point to the individual rows
	for(int y = 0; y < height; y++) {
		pixelData[y] = new RGB[width];

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
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/

	int width = getWidth();
#ifdef OUT_OF_BOUNDS_CHECK
	if(i >= width * getHeight()) {
		throw RGBImageException("setPixel(int i, RGB pixel) i >= getWidth() * getHeight()");
	}
#endif

	pixelData[i / width][i % width] = pixel;
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
	int width = getWidth();
#ifdef OUT_OF_BOUNDS_CHECK
	if(i >= width * getHeight()) {
		throw RGBImageException("getPixel(i) i >= getWidth() * getHeight()");
	}
#endif

	return pixelData[i / width][i % width];
}