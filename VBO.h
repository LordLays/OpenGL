#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
	public:
		// ID bufora
		GLuint ID;

		// Konstruktor
		VBO(GLfloat* vertices, GLsizeiptr size);

		// Bindowanie bufora
		void Bind();

		// Odbindowanie bufora
		void Unbind();

		// Usuwanie bufora
		void Delete();
};

#endif