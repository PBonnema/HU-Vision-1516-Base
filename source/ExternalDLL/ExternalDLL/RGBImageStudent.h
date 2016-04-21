/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once

#include "RGBImage.h"
//#include <vector>
//#include <map>

#include "RGBImage.h"

class RGBImageStudent : public RGBImage
{
public:
	RGBImageStudent();
	RGBImageStudent(const RGBImageStudent &other);
	RGBImageStudent(const int width, const int height);
	virtual ~RGBImageStudent();

	virtual void set(const int width, const int height);
	virtual void set(const RGBImageStudent &other);

	virtual void setPixel(int x, int y, RGB pixel);
	virtual void setPixel(int i, RGB pixel);

	virtual RGB getPixel(int x, int y) const;
	virtual RGB getPixel(int i) const;

private:
	//RGB* pixelData; //1-d array of pixel structs on heap
	RGB** pixelData; //row major 2-d array of pixel structs on heap
	//std::vector<RGB> pixelData; //1-d vector of pixel structs
	//std::vector<RGB*> pixelData; //column major vector of array's pixel structs
	//std::vector<std::vector<RGB>> pixelData; //column major 2-d vector of pixel structs
	//std::map<unsigned int, RGB> pixelData; //1-d map of pixel structs
	//std::map<unsigned int, RGB*> pixelData; //column major map of array's pixel structs
	//std::map<unsigned int, std::map<unsigned int, RGB>> pixelData; //column major 2-d map of pixel structs
};