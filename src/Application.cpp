
/*
	GLEW needs to be imported before everything else
	related with OpenGl
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* GLEW needs a valid OpenGl context */
	if (glewInit() != GLEW_OK)
		std::cout << "Error with glewInit()" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
		-0.5f, -0.5f,0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	/* create an vertex buffer */
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	Shader shader("res/shaders/BasicTextureShader.shader");
	shader.Bind();

	shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

	Texture texture("res/textures/texture.png");
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	shader.Unbind();
	vb.Unbind();
	ib.Unbind();

	Renderer renderer;

	IMGUI_CHECKVERSION();
	const char* glsl_version = "#version 130";
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	/* Loop until the user closes the window */
	float r = 0.0f;
	float increment = 0.05f;

	glm::vec3 translation(0.5, 0.5f, 0);
	glm::vec3 translation2(1.0, 0.5f, 0);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();
		renderer.Draw(va, ib, shader);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;

			shader.Bind();
			shader.SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(va, ib, shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation2);
			glm::mat4 mvp = proj * view * model;

			shader.Bind();
			shader.SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(va, ib, shader);
		}


		if (r > 1.0f || r < 0.0f)
			increment = increment*-1;
		r += increment;

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			//ImGui::Begin("");                          // Create a window called "Hello, world!" and append into it.

			ImGui::SliderFloat3("Translate 1", &translation.x, -2.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat3("Translate 2", &translation2.x, -2.0f, 2.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	//ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	shader.Unbind();
	glfwTerminate();
	return 0;
}