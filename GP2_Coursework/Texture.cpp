#include "Texture.h"
// stb_image.h cannot be included in header files
#include "stb_image.h" 

Texture::Texture()
{
}

void Texture::Initialize(const std::string& fileName)
{
	// Creating variables to store width, height and number of components of image
	int width, height, numComponents;
	// Loading the image and storing its data
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	// Number of and addresses of textures
	glGenTextures(1, &textureHandler);
	// Defining the type of the texture
	glBindTexture(GL_TEXTURE_2D, textureHandler);

	// Wrapping the texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// Wrapping the texture outside height
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Linear filtering for minification (when texture is smaller than object)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Linear filtering for magnification (when texture is larger than object)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	// Deleting textures
	glDeleteTextures(1, &textureHandler);
}

void Texture::Bind(unsigned int unit)
{
	// Checking if working with one of 32 textures
	assert(unit >= 0 && unit <= 31);

	// Setting active texture unit
	glActiveTexture(GL_TEXTURE0 + unit);
	// Type of and texture to bind to unit
	glBindTexture(GL_TEXTURE_2D, textureHandler);
}
