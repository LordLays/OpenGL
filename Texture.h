#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shaderClass.h"

class Texture
{
	public:
		// ID tekstury
		GLuint ID;
		GLenum type;

		// Konstruktor (inicjalizacja tekstury)
		Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

		void texUnit(Shader& shader, const char* uniform, GLuint unit);

		// Bindowanie tekstury
		void Bind();

		// Unbind tekstury
		void Unbind();

		// Usuwanie tekstury
		void Delete();
};

#endif
