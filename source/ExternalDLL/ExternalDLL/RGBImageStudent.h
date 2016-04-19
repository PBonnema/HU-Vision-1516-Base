/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once

#include "RGBImage.h"
#include <vector>
#include <map>


class RGBImageStudent : public RGBImage {
public:

	RGBImageStudent();
	RGBImageStudent(const RGBImageStudent &other);
	RGBImageStudent(const int width, const int height);
	~RGBImageStudent();

	void set(const int width, const int height);
	void set(const RGBImageStudent &other);

	void setPixel(int x, int y, RGB pixel);
	void setPixel(int i, RGB pixel);

	RGB getPixel(int x, int y) const;
	RGB getPixel(int i) const;

private:
	//RGB* pixelData; //1-d array of pixel structs on heap
	RGB** pixelData; //column major 2-d array of pixel structs on heap
	//std::vector<RGB> pixelData; //1-d vector of pixel structs
	//std::vector<RGB*> pixelData; //column major vector of array's pixel structs
	//std::vector<std::vector<RGB>> pixelData; //column major 2-d vector of pixel structs
	//std::map<unsigned int, RGB> pixelData; //1-d map of pixel structs
	//std::map<unsigned int, RGB*> pixelData; //column major map of array's pixel structs
	//std::map<unsigned int, std::map<unsigned int, RGB>> pixelData; //column major 2-d map of pixel structs
};