#include "gl_core_4_4.h"
#include <glfw-3.2.1.bin.WIN32\include\GLFW\glfw3.h>
#include <stdio.h>
#include <glm\glm\vec2.hpp>
#include <glm\glm\vec3.hpp>
#include <glm\glm\vec4.hpp>
#include <assert.h>
#include <glm\glm\mat4x4.hpp>

#include "Gizmos.h"
#include <glm\glm\glm.hpp>
#include <glm\glm\ext.hpp>

#include <iostream>

int main()
{
	glm::vec3 v = glm::vec3(1, 1, 1);

	if (!glfwInit())
	{
		printf("glfw is not avalible");
	}

	GLFWwindow* window = glfwCreateWindow(800, 800, "Hi my name is Window", nullptr, nullptr);
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

	//Sets color for the window
	glClearColor(0.12f, 0.12f, 0.30f, 1.0f);
	glm::vec4 clearcolor = glm::vec4(0.12f, 0.12f, 0.30f, 1.0f);
	while (true)
	{
		//Clears BUffers for Color and depth
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

		Gizmos::clear();
		Gizmos::addTransform(glm::mat4(1));
		glm::vec4 white(1);
		glm::vec4 black(0, 0, 0, 1);

		glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
		glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
		for (int i = 0; i < 21; i++)
		{
			Gizmos::create();
			Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
				glm::vec3(-10 + i, 0, -10),
				i == 10 ? white : black);

			Gizmos::addLine(glm::vec3(10, 0, -10 + i),
				glm::vec3(10, 0, -10 + i),
				i == 10 ? white : black);
		}
		Gizmos::draw(projection * view);
		//Colors Drawn. Can't be modified/updated without this
		glClearColor(clearcolor.r, clearcolor.g, clearcolor.b, clearcolor.a);
		glfwPollEvents();
		glfwSwapBuffers(window);


	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}