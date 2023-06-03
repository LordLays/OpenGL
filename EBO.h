#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
	public:
		// ID bufora
		GLuint ID;

		// Konstruktor
		EBO(GLuint* indices, GLsizeiptr size);

		// Bindowanie bufora
		void Bind();

		// Odbindowanie bufora
		void Unbind();

		// Usuwanie bufora
		void Delete();
};

#endif