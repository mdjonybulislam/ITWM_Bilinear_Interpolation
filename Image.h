#include <stdint.h>
#include <cstdio>
#include <complex>

enum ImageType {
	PNG, JPG, BMP, TGA
};


struct Image
{
    uint8_t* data = NULL; // unsigned int 
	size_t size = 0; 
	int w; //width
	int h; //height
	int channels; // Color channel. e.g. RGB = 3 

    Image(const char* filename); //constructor for file name
	Image(int w, int h, int channels); // blank image creation (if needed)
	Image(const Image& img); //image copy constructor if needed
	~Image(); 

    bool read(const char* filename); //function for constructor about the data
	bool write(const char* filename);

    ImageType get_file_type(const char* filename);

	Image& grayscale_avg(); // Transform Image to Grayscale with average value of RGB Image
};
