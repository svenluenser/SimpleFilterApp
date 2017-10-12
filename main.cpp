#include <iostream>
#include <cmath>
#include "PPMImage.h"
#include "Filter.h"
#include "Kernel.h"

/** PROTOTYPES **/
PPMImage& calcMagnitudeForEveryChannel(PPMImage&, const PPMImage&, const PPMImage&);
PPMImage& filterImage(Filter<3>&, PPMImage&);

using namespace std;


int main()
{

	PPMImage image = *PPMImage::readFromFile("img/lena.ppm");
	std::cout << "Width :" << image.getWidth() << "\n" << "Height :" << image.getHeight() << std::endl;
	//image.convertToGrayScale();

	Filter<3> filter;

	/* LOWPASS FILTER */
	filter.init(&k2);                /** choose the right filterkernel to do a low-pass filter  (see Kernel.h) **/
	PPMImage& blur = filterImage(filter, image);
    for(int i=0; i< 4; i++)
        blur = filterImage(filter, blur);


	/* DETECT HORIZONTAL EDGES */
	filter.init(&k4);               /** choose the right filterkernel to find horizontal edges  (see Kernel.h) **/
	PPMImage& horizontalEdges = filterImage(filter, blur);

	/* DETECT VERTICAL EDGES */
	filter.init(&k3);              /** choose the right filterkernel to find vertical edges  (see Kernel.h) **/
	PPMImage& verticalEdges = filterImage(filter, blur);

	/* COMBINE HORIZONTAL- AND VERTICAL EDGE IMAGES TO ONE RESULT (CALC MAGNITUDE!) */
	PPMImage& out = calcMagnitudeForEveryChannel(image, horizontalEdges, verticalEdges);
	PPMImage::saveToFile(out, "img/lena_out.ppm");

	delete &blur, &horizontalEdges, &verticalEdges, &out;
	return 0;
}


PPMImage& filterImage(Filter<3> &filter, PPMImage &image)
{
	PPMImage* result = new PPMImage(image.getWidth(), image.getHeight());
	filter.convolve(image, *result);
	return *result;
}

PPMImage& calcMagnitudeForEveryChannel(PPMImage &image, const PPMImage &horizontalEdges, const PPMImage &verticalEdges)
{
	PPMImage* out = new PPMImage(image.getWidth(), image.getHeight());
	for(int i=0; i < image.getWidth()*image.getHeight(); i++)
	{
		/* CALC MAGNITUDE FOR RED CHANNEL */
		(*out)[i].r = sqrt(verticalEdges[i].r * verticalEdges[i].r + horizontalEdges[i].r * horizontalEdges[i].r);
		/* CALC MAGNITUDE FOR GREEN CHANNEL */
		(*out)[i].g = sqrt(verticalEdges[i].g * verticalEdges[i].g + horizontalEdges[i].g * horizontalEdges[i].g);
		/* CALC MAGNITUDE FOR BLUE CHANNEL */
		(*out)[i].b = sqrt(verticalEdges[i].b * verticalEdges[i].b + horizontalEdges[i].b * horizontalEdges[i].b);
	}
	return *out;
}
