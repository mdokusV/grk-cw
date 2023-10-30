#pragma once
#include "glew.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>

#include "Shader_Loader.h"
#include "Render_Utils.h"

#include "Box.cpp"
float points[] = {
0.0f,1.0f,0.f,1.f,
0.7818314824680298f,0.6234898018587336f,0.f,1.f,
0.9749279121818236f,-0.22252093395631434f,0.f,1.f,
0.43388373911755823f,-0.900968867902419f,0.f,1.f,
-0.433883739117558f,-0.9009688679024191f,0.f,1.f,
-0.9749279121818236f,-0.2225209339563146f,0.f,1.f,
-0.7818314824680299f,0.6234898018587334f,0.f,1.f,
};
float hues[] = {
	0.0f, 
	0.7142857142857143f, 
	0.42857142857142855f, 
	0.14285714285714285f, 
	0.8571428571428571f, 
	0.5714285714285714f, 
	0.2857142857142857f
};



GLuint program;
Core::Shader_Loader shaderLoader;

unsigned int VAO;
GLuint VBO;

void renderScene(GLFWwindow* window)
{
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    // Create and bind a Vertex Buffer Object (VBO) for the star vertices
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Create and bind an Element Buffer Object (EBO) for the star indices
    GLuint EBO;
    glGenBuffers(1, &EBO);
    // Define the indices to draw the star using GL_LINE_STRIP
    GLuint indices[] = { 0, 1, 2, 3, 4, 5, 6, 0 };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set up the shader attributes and uniforms
    GLuint posAttrib = glGetAttribLocation(program, "position");
    GLuint colorAttrib = glGetAttribLocation(program, "color");

    glEnableVertexAttribArray(posAttrib);
    glEnableVertexAttribArray(colorAttrib);

    glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(colorAttrib, 1, GL_FLOAT, GL_FALSE, 0, hues);

    // Draw the star using GL_LINE_STRIP
    glDrawElements(GL_LINE_STRIP, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

    // Clean up
    glDisableVertexAttribArray(posAttrib);
    glDisableVertexAttribArray(colorAttrib);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glUseProgram(0);
    glfwSwapBuffers(window);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void init(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);
	program = shaderLoader.CreateProgram("shaders/shader_2_1b.vert", "shaders/shader_2_1b.frag");

}

void shutdown(GLFWwindow* window)
{
	shaderLoader.DeleteProgram(program);
}

//obsluga wejscia
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// funkcja jest glowna petla
void renderLoop(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		renderScene(window);
		glfwPollEvents();
	}
}
//}