#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
	public:
		// ID VAO
		GLuint ID;

		// Konstruktor
		VAO();

		// Linkowanie VBO do VAO
		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

		// Bindowanie VAO
		void Bind();

		// Odbindowanie VAO
		void Unbind();

		// Usuwanie VAO
		void Delete();
};

#endif