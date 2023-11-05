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


GLuint program;
Core::Shader_Loader shaderLoader;

GLuint VAO, VBO;

glm::mat4 boxModel = glm::mat4(1.0f);

void renderScene(GLFWwindow* window)
{
	float time = glfwGetTime();
	glClearColor(0.0f, 1.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	float rotationAngle = glm::radians(45.0f) + time;
	boxModel = glm::eulerAngleXYZ(rotationAngle, rotationAngle, 0.0f);

	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, glm::value_ptr(boxModel));
	glDrawArrays(GL_TRIANGLES, 0, 36);

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
	program = shaderLoader.CreateProgram("shaders/shader_2_1.vert", "shaders/shader_2_1.frag");
	// Dokładny opis działania funkcji z poniższych punktów można znaleźć na slajdach z wykładu, w dokumentacji https://www.khronos.org/registry/OpenGL-Refpages/gl4/ funkcje są opisane także na stronach https://learnopengl.com/Getting-started/Hello-Triangle https://learnopengl.com/Getting-started/Shaders oraz https://open.gl/drawing
	// W tablicy box są pozycje i kolory kostki, celem zajęć jest narysowanie tej kostki 
	// Zainicjalizuj VertexArrayObject (VAO) i zapisz w nim atrybuty prostopadłościanu
	// I Stwórz VAO
	// 1. Stwórz nowy VAO za pomocą glGenVertexArrays i przypisz jego adres do zmiennej globalnej
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box), &box, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
	glBindVertexArray(0);
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