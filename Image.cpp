#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h" // Ref: https://github.com/nothings/stb
#include "stb_image_write.h"
#include "Image.h"

Image::Image(const char* filename){
    if(read(filename)) {
		printf("Read %s\n", filename);
        size = w*h*channels;
		
    }
	else {
		printf("Failed to read %s\n", filename);
	}
} 
Image::Image(int w, int h, int channels){ //0 or black constructor
    size = w*h*channels;
    data = new uint8_t[size];

}
Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
	memcpy(data, img.data, size); // copy data from other
}
Image::~Image(){
    stbi_image_free(data); // will clean up all data (Please check the link for documentation)
} 

bool Image::read(const char* filename){
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data !=NULL;
}

bool Image::write(const char* filename) {
	ImageType type = get_file_type(filename);
	int success;
  switch (type) {
    case PNG:
      success = stbi_write_png(filename, w, h, channels, data, w*channels);
      break;
    case BMP:
      success = stbi_write_bmp(filename, w, h, channels, data);
      break;
    case JPG:
      success = stbi_write_jpg(filename, w, h, channels, data, 100); // 100 is quality of the image in percentage. Please read the stb_image_write.h file for details
      break;
    case TGA:
      success = stbi_write_tga(filename, w, h, channels, data);
      break;
  }
  if(success != 0) {
    printf("\e[32mWrote \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
    return true;
  }
  else {
    printf("\e[31;1m Failed to write \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
    return false;
  }
}

ImageType Image::get_file_type(const char* filename) {
	const char* ext = strrchr(filename, '.');
	if(ext != nullptr) {
		if(strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if(strcmp(ext, ".jpg") == 0) {
			return JPG;
		}
		else if(strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if(strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}
	return PNG;
}

// Grascale Conversion
Image& Image::grayscale_avg() {
	if(channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
	}
	else {
		for(int i = 0; i < size; i+=channels) {
			int gray = (data[i] + data[i+1] + data[i+2])/3; // Average of RGB Values
			memset(data+i, gray, 3);
		}
	}
	return *this;
}

