#include "IntensityImageStudent.h"

//Comment this line out to disable checking for out-of-bounds errors within the pixel access methods
//The out-of-bounds check also makes sure the image is initialized with a width>0 and height>0 before accessing any pixels because the default size is 0,0
#define OUT_OF_BOUNDS_CHECK

IntensityImageStudent::IntensityImageStudent() : IntensityImage(), pixelData{ nullptr } {
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) :
IntensityImage(other.getWidth(), other.getHeight()),
pixelData{ new Intensity*[other.getWidth()] } //init pixelData as an array of columns (it's a column-major 2d array)
{
	int width = getWidth(), height = getHeight();
	for(int x = 0; x < width; x++) {
		pixelData[x] = new Intensity[height]; //init new columns

		//std::copy(std::begin(other), std::end(other), std::begin(pixelData[i]));

		//copy the column
		Intensity* column = pixelData[x];
		for(int y = 0; y < height; y++) {
			column[y] = other.getPixel(x, y);
		}
	}
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) :
IntensityImage(width, height),
pixelData{ new Intensity*[width] } //init pixelData as an array of columns (it's a column-major 2d array)
{
	for(int i = 0; i < width; i++) {
		pixelData[i] = new Intensity[height]; //init all columns
	}
}

IntensityImageStudent::~IntensityImageStudent() {
	if(pixelData != nullptr) { //don't attempt to delete when pixelData was never initialized
		int width = getWidth();
		for(int i = 0; i < width; i++) {
			delete pixelData[i];
		}
		delete pixelData;
	}
}

void IntensityImageStudent::set(const int width, const int height) {
	int oldWidth = getWidth();
	IntensityImage::set(width, height);
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)

	//delete old pixel storage
	for(int i = 0; i < oldWidth; i++) {
		delete pixelData[i];
	}
	delete pixelData;

	//initialize some new memory with different dimensions
	pixelData = new Intensity*[width];
	for(int i = 0; i < width; i++) {
		pixelData[i] = new Intensity[height]; //init all columns
	}
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	int width = getWidth();
	IntensityImage::set(other.getWidth(), other.getHeight());
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)

	//delete old pixel storage
	for(int i = 0; i < width; i++) {
		delete pixelData[i];
	}
	delete pixelData;

	//copy other's pixelData
	width = other.getWidth();
	int height = other.getHeight();
	for(int x = 0; x < width; x++) {
		pixelData[x] = new Intensity[height]; //init new columns

		//std::copy(std::begin(other), std::end(other), std::begin(pixelData[i]));

		//copy the column
		Intensity* column = pixelData[x];
		for(int y = 0; y < height; y++) {
			column[y] = other.getPixel(x, y);
		}
	}
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
#ifdef OUT_OF_BOUNDS_CHECK
	if(x >= getWidth() || y >= getHeight()) {
		throw "setPixel(int x, int y, Intensity pixel) x >= getWidth() || y >= getHeight()";
		int throwError = 0, e = 1 / throwError;
	}
#endif

	pixelData[x][y] = pixel;
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
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
		throw "setPixel(int i, Intensity pixel) i >= width * getHeight()";
		int throwError = 0, e = 1 / throwError;
	}
#endif

	pixelData[i % width][i / width] = pixel;
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
#ifdef OUT_OF_BOUNDS_CHECK
	if(x >= getWidth() || y >= getHeight()) {
		throw "Intensity::getPixel(int x, int y) x >= getWidth() || y >= getHeight()";
		int throwError = 0, e = 1 / throwError;
	}
#endif

	return pixelData[x][y];
}

Intensity IntensityImageStudent::getPixel(int i) const {
	int width = getWidth();

#ifdef OUT_OF_BOUNDS_CHECK
	if(i >= width * getHeight()) {
		throw "Intensity::getPixel(int i) i >= width * getHeight()";
		int throwError = 0, e = 1 / throwError;
	}
#endif

	return pixelData[i % width][i / width];
}