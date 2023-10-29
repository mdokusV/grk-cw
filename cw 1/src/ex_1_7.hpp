#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "ext.hpp"
#include <vector>
#include <thread>
#include <chrono>

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint quadVAO;
glm::vec3 quadPos;
int quadRot;

Core::Shader_Loader shaderLoader;

std::vector<glm::vec3> quadsPositions;

void renderScene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	float time = glfwGetTime();

    glUseProgram(program);
    
    glm::vec3 translaitonVector = glm::vec3(-0.5f, sin(time) / 2, 0);
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translaitonVector);


    
    glm::mat4 quadPosnMatrix = glm::translate(glm::mat4(1.0f), quadPos);

    float angleInRadians = glm::radians(float(quadRot));
    glm::vec3 rotationVector = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), time + angleInRadians, rotationVector);

    glm::mat4 transformation;
    transformation = quadPosnMatrix*translationMatrix * rotationMatrix;

    glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&transformation);
    Core::drawVAOIndexed(quadVAO, 6);

    glUseProgram(0);

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    printf("%f,%f\n", xpos, ypos);
}


void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    program = shaderLoader.CreateProgram("shaders/shader_1_2.vert", "shaders/shader_1_2.frag");

    //Przekopiuj kod do ladowania z poprzedniego zadania

    const float quad[] =
    { -0.2f,-0.2f, 0.0f, 1.0f,
     -0.2f,0.2f, 0.0f, 1.0f,
     0.2f,-0.2f, 0.0f, 1.0f,
     0.2f,0.2f, 0.0f, 1.0f };


    const unsigned int tiangles[] =
    { 0, 1, 3,
      0, 3, 2 };

    quadVAO = Core::initVAOIndexed(quad, tiangles, 4, 4, 6);

    quadPos = glm::vec3(0.0f, 0.0f, 0.0f);
    quadRot = 0;
}

void shutdown(GLFWwindow* window)
{
    shaderLoader.DeleteProgram(program);
}

//obsluga wejscia
void processInput(GLFWwindow* window)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        quadPos.y += 0.05f;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        quadPos.y -= 0.05f;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        quadPos.x += 0.05f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        quadPos.x += -0.05f;
    }
    else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        quadRot += 1;
    }   
    else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        quadRot -= 1;
    }
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