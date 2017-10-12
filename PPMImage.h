//
// Created by sluenser on 2/24/16.
//

#ifndef FILTERAPP_IMAGE_H
#define FILTERAPP_IMAGE_H


#include <stddef.h>
#include <iosfwd>
#include <fstream>
#include <iostream>
#include <string.h>
#include <c++/4.8.3/cmath>

class PPMImage
{

public:
	struct Rgb
	{
		Rgb(){r=0; g=0; b=0;}
		Rgb(float r, float g, float b){this->r = r; this->g = g; this->b=b;}
		float r,g,b;
	};


	/** Constructor **/
	PPMImage(unsigned int width, unsigned int height, Rgb color = Rgb(0,0,0))
	{
		this->width = width;
		this->height = height;

		this->pixels = new Rgb[width*height];
		for(int i=0; i< width*height; i++)
		{
			this->pixels[i] = color;
		}
	}

    PPMImage(const PPMImage& image)
    {
        this->width = image.width;
        this->height= image.height;
        this->pixels = new Rgb[width*height];
        memcpy(this->pixels, image.pixels,sizeof(Rgb)*width*height);
    }


	Rgb& operator[] (const unsigned int &i) const
	{
		if(i >= width*height) throw("Index out of bounds!");
		return this->pixels[i];
	}


	void setColorAt(unsigned index, Rgb* color)
	{
		if(index >= width*height) throw("Index out of bounds");

		this->pixels[index] = *color;
	}

	unsigned getWidth()
	{
		return this->width;
	}

	unsigned getHeight()
	{
		return this->height;
	}


	void convertToGrayScale()
	{
		for(int i=0; i < getWidth()*getHeight(); i++)
		{
			float gray = pixels[i].r *0.21 + pixels[i].g * 0.72 + pixels[i].b * 0.07;
			pixels[i].r = gray;
			pixels[i].g = gray;
			pixels[i].b = gray;
		}
	}

	~PPMImage()
	{
		if(pixels != NULL)
		{
			delete[] pixels;
		}
	}

	static PPMImage *readFromFile(const char *filename)
	{
		std::ifstream ifs;
		ifs.open(filename, std::ios::binary);
		try
		{
			if(ifs.fail())
			{
				throw ("Can't open file!");
			}
			std::string header, comment;
			ifs >> header;
			if(strcmp(header.c_str(),"P6")!= 0) throw("Unknown input file format");
			//ifs.ignore(256,'\n'); // skip empty lines
			int width, height, colorres;
			ifs >> width >> height >> colorres;
			//std::cout << width <<" "<< height <<std::endl;
			PPMImage * img = new PPMImage(width, height);
			ifs.ignore(256,'\n'); // skip empty lines

            char* buffer = new char[3];
			for(int i=0; i < width*height; i++)
			{
				ifs.read(buffer, 3);
				//ifs.read(reinterpret_cast<char*>(buffer),3);
				Rgb* color = new Rgb(buffer[0]/255.0, buffer[1]/255.0, buffer[2]/255.0); // convert to float
				img->setColorAt(i,color);
			}
			ifs.close();
			return img;
		}
		catch(const char* err)
		{
			std::cout <<  err << std::endl;
			ifs.close();
		}

		return NULL;
	}

	static void saveToFile(PPMImage &img, const char *filename)
	{
		if(img.getWidth() == 0 || img.getHeight()==0)
		{
			std::cout << "Cant save an empty image";
			return;
		}

		std::ofstream ofs;
		try
		{
			ofs.open(filename, std::ios::binary);

			if(ofs.fail()) throw("Cant open output file");

			ofs << "P6\n"; // magicnumber
			ofs << img.getWidth() <<" "<<img.getHeight() << "\n255\n";

			for(int i=0; i < img.getHeight()*img.getWidth(); i++)
			{
				unsigned char r,g,b;
				r = static_cast<unsigned char>(std::min(1.f,img[i].r)*255);
				g = static_cast<unsigned char>(std::min(1.f,img[i].g)*255);
				b = static_cast<unsigned char>(std::min(1.f,img[i].b)*255);

				ofs << r << g << b;
                //std::cout <<"("<<(float) r <<"," <<(float) g <<"," <<(float)b<<") ";
			}
			ofs.close();
		}
		catch(const char* err)
		{
			std::cout << err << std::endl;
		}

	}


private:
	unsigned width;
	unsigned height;
	Rgb* pixels;
};


#endif //FILTERAPP_IMAGE_H
