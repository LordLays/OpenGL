#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;
	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Generowanie tekstury
	glGenTextures(1, &ID);
	// Bindowanie tekstury
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Ustawianie parametrow tekstury
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Importowanie tekstury 
	stbi_set_flip_vertically_on_load(true);
	

	if (bytes)
	{
		glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
		glGenerateMipmap(texType);
	}
	else
	{
				std::cout << "Blad wczytywania tekstury: " << image << std::endl;
	}

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
		glBindTexture(type, ID);
}

void Texture::Unbind()
{
		glBindTexture(type, 0);
}

void Texture::Delete()
{
			glDeleteTextures(1, &ID);
}