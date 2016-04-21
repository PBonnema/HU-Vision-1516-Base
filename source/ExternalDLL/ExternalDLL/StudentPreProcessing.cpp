#include "StudentPreProcessing.h"
#include "ImageFactory.h"
#include <cmath>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImage* result = ImageFactory::newIntensityImage(image.getWidth(), image.getHeight());

	const int pixels = image.getWidth() * image.getHeight();
	for(int i = 0; i < pixels; i++)
	{
		RGB color{ image.getPixel(i) };
		//Gleam method of conversion
		result->setPixel(i, Intensity(255 * ( //scale end result back from [0,1] to [0,255]
			std::pow(color.r / 255., 1.1) + //Scale color value into the range [0,1]; then perform a gamma correction t' = t^(1/2.2)
			std::pow(color.g / 255., 1.1) +
			std::pow(color.b / 255., 1.1)
			) / 3.));


		//result->setPixel(i, (color.r + color.g + color.b) / 3.);
	}
	return result;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}