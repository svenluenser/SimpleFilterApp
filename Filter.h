//
// Created by sluenser on 2/24/16.
//

#ifndef FILTERAPP_FILTER_H
#define FILTERAPP_FILTER_H


#include "PPMImage.h"

template <std::size_t N>
class Filter
{
private:
	const int width=N;
	const int height=N;


public:
	double (*kernel)[N][N];
	/** initialize the filter kernel**/

	void init(double (*kernel)[N][N])
	{
		this->kernel = kernel;
	}

	/** convolution **/
    void convolve(PPMImage &srcImage, PPMImage &destImage)
    {
        for (int w = 0; w < srcImage.getWidth(); w++)
        {
            for (int h = 0; h < srcImage.getHeight(); h++)
            {
                double tmpR = 0;
                double tmpG = 0;
                double tmpB = 0;

                for (int kx = -width / 2; kx <= width / 2; kx++)
                {
                    for (int ky = -height / 2; ky <= height / 2; ky++)
                    {
                        int currentX = w + kx;
                        int currentY = h + ky;
                        //check bounds
                        if (currentX < 0) currentX = 0;
                        if (currentX > srcImage.getWidth() - 1) currentX = srcImage.getWidth() - 1;
                        if (currentY < 0) currentY = 0;
                        if (currentY > srcImage.getHeight() - 1) currentY = srcImage.getHeight() - 1;

                        tmpR += (*kernel)[ky + width / 2][kx + height / 2] *
                                srcImage[currentY * srcImage.getWidth() + currentX].r;
                        tmpG += (*kernel)[ky + width / 2][kx + height / 2] *
                                srcImage[currentY * srcImage.getWidth() + currentX].g;
                        tmpB += (*kernel)[ky + width / 2][kx + height / 2] *
                                srcImage[currentY * srcImage.getWidth() + currentX].b;
                    }
                }

                destImage[h * srcImage.getWidth() + w].r = tmpR;
                destImage[h * srcImage.getWidth() + w].g = tmpG;
                destImage[h * srcImage.getWidth() + w].b = tmpB;
            }
        }
    }

};


#endif //FILTERAPP_FILTER_H
