#include <iostream>
#include <thread>
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"


int main()
{

    GLfloat lightPyramidVertices[] =
    { //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
    };

    GLuint lightPyramidIndices[] =
    {
        0, 1, 2, // Bottom side
        0, 2, 3, // Bottom side
        4, 6, 5, // Left side
        7, 9, 8, // Non-facing side
        10, 12, 11, // Right side
        13, 15, 14 // Facing side
    };

    GLfloat lightCubeVertices[] = {
    -0.1f, -0.1f, 0.1f,
    -0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, 0.1f,
    -0.1f, 0.1f, 0.1f,
    -0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, 0.1f,
    };

    GLuint lightCubeIndices[] = {
        0,1,2,
        0,2,3,
        0,4,7,
        0,7,3,
        3,7,6,
        3,6,2,
        2,6,5,
        2,5,1,
        1,5,4,
        1,4,0,
        4,5,6,
        4,6,7
    };
    GLfloat PyramidVertices[] = {
        //Pozycje				Kolor       	    Tekstura
        -0.5f, 0.0f, 0.5f,		1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,		1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
        0.5f, 0.0f, -0.5f,		1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        0.5f, 0.0f, 0.5f,		1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        0.0f, 0.8f, 0.0f,		0.0f, 0.0f, 1.0f,   0.5f, 0.5f
    };

    GLuint PyramidIndices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };



        //Create table of vertices of a pyramid with an 11-sided regulare base, with the apex in red color and the base in blue color
    GLfloat N11PyramidVertices[] = {
        //Pozycje				            Kolor
        1.0f,       0.0f,  0.0f,		    0.0f, 0.0f, 0.5f, //0
        0.809017f,  0.0f,  0.5887785f,		0.0f, 0.0f, 0.5f, //1
        0.415415f,  0.0f,  0.850651f,		0.0f, 0.0f, 0.5f, //2
        -0.142315f, 0.0f,  0.989821f,		0.0f, 0.0f, 0.5f, //3
        -0.654861f, 0.0f,  0.755750f,		0.0f, 0.0f, 0.5f, //4
        -0.959493f, 0.0f,  0.281733f,		0.0f, 0.0f, 0.5f, //5
        -0.959493f, 0.0f, -0.281733f,		0.0f, 0.0f, 0.5f, //6
        -0.654861f, 0.0f, -0.755750f,		0.0f, 0.0f, 0.5f, //7
        -0.142315f, 0.0f, -0.989821f,		0.0f, 0.0f, 0.5f, //8
        0.415415f,  0.0f, -0.850651f,		0.0f, 0.0f, 0.5f, //9
        0.809017f,  0.0f, -0.587785f,		0.0f, 0.0f, 0.5f, //10
        0.0f,       1.0f,  0.0f,		    0.0f, 0.0f, 0.0f //11

    };

    GLuint N11PytamidIndicies[]
    {
		0,1,11,
        1,2,11,
        2,3,11,
        3,4,11,
        4,5,11,
        5,6,11,
        6,7,11,
        7,8,11,
        8,9,11,
        9,10,11,
		10,0,11
	};

    const int numPoints = 200; // liczba punktów na spirali
    const float angleIncrement = 0.1f; // krok zmiany k¹ta dla spirali

    GLfloat spiralPoints[2*numPoints];
    float radius = 0.1f;
    float angle = 0.0f;

    for (int i = 0; i < numPoints; ++i) {
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        spiralPoints[2 * i] = x;
        spiralPoints[2 * i + 1] = y;

        angle += angleIncrement;
        radius += 0.01f;
    }
    GLuint spiralIndices[numPoints];
    for (int i = 0; i < numPoints; ++i)
    {
	    		spiralIndices[i] = i;
	}
    


    // Wymiary okna
    const unsigned int width = 800;
    const unsigned int height = 600;


    // Inicjalizacja GLFW, OpenGL 3.3 tylko funcje modern
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Ustawienie okna
    GLFWwindow* window = glfwCreateWindow(width, height, "Pyramida", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
    	std::cout << "Nie udalo sie utworzyc okna GLFW" << std::endl;
		glfwTerminate();
		return -1;
    }

    // Inicjalizacja GLAD
    gladLoadGL();



    // Obszar renderowania od 0,0 do 800,600
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    // Kompilacja shaderow
    Shader basicShader("basic.vert", "basic.frag");
    Shader lightShader("light.vert", "light.frag");


    // Tworzenie VAO, VBO, EBO dla œwiat³a
    VAO lightVAO;
    lightVAO.Bind();

    VBO lightVBO(lightCubeVertices, sizeof(lightCubeIndices));
    EBO lightEBO(lightCubeIndices, sizeof(lightCubeIndices));

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    lightVAO.Unbind();

    //Pozycja œwiat³a i kolor

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 1.5f, 1.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    // Tworzenie VAO, VBO, EBO dla light piramidy

    VAO lightPyramidVAO;
    lightPyramidVAO.Bind();

    VBO lightPyramidVBO(lightPyramidVertices, sizeof(lightPyramidVertices));
    EBO lightPyramidEBO(lightPyramidIndices, sizeof(lightPyramidIndices));

    lightPyramidVAO.LinkAttrib(lightPyramidVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    lightPyramidVAO.LinkAttrib(lightPyramidVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    lightPyramidVAO.LinkAttrib(lightPyramidVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    lightPyramidVAO.LinkAttrib(lightPyramidVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    lightPyramidVAO.Unbind();
    lightPyramidEBO.Unbind();

    // Kompilacja tekstur
    Texture crate("crate.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture wood("wood.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture ground("ground_01.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGBA, GL_UNSIGNED_BYTE);

    crate.texUnit(basicShader, "tex0", 0);
    wood.texUnit(basicShader, "tex0", 1);
    ground.texUnit(basicShader, "tex0", 2);

    // VAO , VBO, EBO
    VAO VAO1, VAO2, VAO3;

    //Piramida
    VAO1.Bind();
    VBO VBO1(PyramidVertices, sizeof(PyramidVertices));
    EBO EBO1(PyramidIndices, sizeof(PyramidIndices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));

    VBO1.Unbind();

    //Pozycja piramidy
    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    //11nPiramida
    VAO2.Bind();
    VBO VBO2(N11PyramidVertices, sizeof(N11PyramidVertices));
    EBO EBO2(N11PytamidIndicies, sizeof(N11PytamidIndicies));

    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
    
    VAO2.Unbind();

    VAO3.Bind();
    VBO VBO3(spiralPoints, sizeof(spiralPoints));
    EBO EBO3(spiralIndices, sizeof(spiralIndices));

    VAO3.LinkAttrib(VBO3, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);

    VAO3.Unbind();

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
    glEnable(GL_DEPTH_TEST);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);



    // Pêtla renderuj¹ca
    while (!glfwWindowShouldClose(window))
    {
        float rotationAngle = glfwGetTime() * 45.0f;

        glClearColor(0.3451f, 0.4745f, 0.5843f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        basicShader.Activate();
        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        camera.Matrix(basicShader, "camMatrix");

        pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
        pyramidModel = glm::mat4(1.0f);
        pyramidModel = glm::translate(pyramidModel, pyramidPos);
        pyramidModel = glm::rotate(pyramidModel, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(basicShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
        glUniform4f(glGetUniformLocation(basicShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(basicShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        wood.Bind();
        lightPyramidVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightPyramidIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        pyramidPos = glm::vec3(1.0f, 0.0f, 1.0f);
        pyramidModel = glm::mat4(1.0f);
        pyramidModel = glm::translate(pyramidModel, pyramidPos);
        pyramidModel = glm::rotate(pyramidModel, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(basicShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
        glUniform4f(glGetUniformLocation(basicShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(basicShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        ground.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightPyramidIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        pyramidPos = glm::vec3(2.0f, 0.0f, 0.0f);
        pyramidModel = glm::mat4(1.0f);
        pyramidModel = glm::translate(pyramidModel, pyramidPos);
        pyramidModel = glm::rotate(pyramidModel, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(basicShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
        glUniform4f(glGetUniformLocation(basicShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(basicShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        crate.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightPyramidIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightCubeIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        //VAO3.Bind();
        //glDrawArrays(GL_LINE_STRIP, 0, numPoints);

        glfwSwapBuffers(window);
        glfwPollEvents();
        
        
    }

    // Zamykanie okna GLFW
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    basicShader.Delete();
    lightShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}