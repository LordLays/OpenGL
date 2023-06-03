#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		// ID programu
		GLuint ID;

		// Konstruktor buduj¹cy shader
		Shader(const char* vertexPath, const char* fragmentPath);

		// Aktywacja shadera
		void Activate();

		// Usuwanie shadera
		void Delete();
	private:
		// Funkcja pomocnicza do kompilacji shadera
		void compileErrors(unsigned int shader, const char* type);
};

#endif