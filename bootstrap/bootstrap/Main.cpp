#include "gl_core_4_4.h"
#include <glfw-3.2.1.bin.WIN32\include\GLFW\glfw3.h>
#include <stdio.h>
#include <glm\glm\vec2.hpp>
#include <glm\glm\vec3.hpp>
#include <glm\glm\vec4.hpp>
#include <assert.h>

#include <iostream>

int main()
{
	glm::vec3 v = glm::vec3(1, 1, 1);

	if (!glfwInit())
	{
		printf("glfw is not avalible");
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hi my name is Window", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}
	assert(window != nullptr);
	glfwMakeContextCurrent(window);

	//OpenGL load fails so the window closes.
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwTerminate();
		return -2;
	}

	//Retrives version of OpenGL being used
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	printf("GL: %i.%i\n", major, minor);
	//Sets color for the window
	glClearColor(0.12f, 0.12f, 0.30f, 1.0f);
	glm::vec4 clearcolor = glm::vec4(0.12f, 0.12f, 0.30f, 1.0f);
	while (true)
	{
		//Clears BUffers for Color and depth
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// a load of if statements mostly to change window color on input
		if (glfwWindowShouldClose(window))
			break;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_R))
			clearcolor.r += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_G))
			clearcolor.g += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_B))
			clearcolor.b += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_Q) || clearcolor.r >= 0.99f && clearcolor.g >= 0.99f && clearcolor.b >= 0.99f)
		{
			clearcolor.r = 0.12f;
			clearcolor.g = 0.12f;
			clearcolor.b = 0.30f;
		}

		//Colors Drawn. Can't be modified/updated without this
		glClearColor(clearcolor.r, clearcolor.g, clearcolor.b, clearcolor.a);
		glfwPollEvents();
		glfwSwapBuffers(window);


	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}