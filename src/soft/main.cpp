#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <display3d/Shader.h>
#include <display3d/Mesh.h>
#include <display3d/Camera.h>

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include <glm/matrix.hpp>

int initialisations(GLFWwindow* &window, int width, int height)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Example OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	return 0;
}

int main()
{
	int width = 800, 
		height = 600;
	GLFWwindow* window = NULL;
	int res = initialisations(window, width, height);
	if (res != 0)
		return res;
	glViewport(0, 0, width, height);

	std::shared_ptr<Shader> basic_shader = std::make_shared<Shader>("basicVertexShader.vert", "basicFragmentShader.frag");
	std::shared_ptr<Shader> textured_shader = std::make_shared<Shader>("texturedVertexShader.vert", "texturedFragmentShader.frag");
	Mesh mesh;
	Camera cam(width, height);
	

	mesh.loadOBJ("../ressources/cube.obj",
				 "../ressources/tex.jpg");
	bool cur_shader_is_tex = true;
	mesh.setShader(textured_shader);

	cam.setPosition();
	cam.setPosition(glm::vec3(0.0, 0.0, 10.0));
	
	double xpos_prev, ypos_prev;
	double dx_speed = 0.01;
	double dy_speed = 0.01;
	bool clicked = false;
	bool space_pressed = false;
	
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		mesh.display(cam.getExtrinsics(), cam.getIntrinsics());

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			if(clicked)
			{
				double dx = xpos - xpos_prev;
				double dy = ypos - ypos_prev;
				
				cam.setPosition();
				glm::vec4 diry = glm::transpose(cam.getExtrinsics()) * glm::vec4(0.0, 1.0, 0.0, 0.0);
				cam.rotate(-dx * dx_speed * M_PI/4.0, glm::vec3(diry.x, diry.y, diry.z));
				glm::vec4 dirx = glm::transpose(cam.getExtrinsics()) * glm::vec4(1.0, 0.0, 0.0, 0.0);
				cam.rotate(dy * dy_speed * M_PI/4.0, glm::vec3(dirx.x, dirx.y, dirx.z));
				cam.setPosition(glm::vec3(0.0, 0.0, 10.0));
			}
			
			xpos_prev = xpos;
			ypos_prev = ypos;
			
			clicked = true;
		}
		else
		{
			clicked = false;
		}
		
		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !space_pressed)
		{
			if(cur_shader_is_tex)
				mesh.setShader(basic_shader);
			else
				mesh.setShader(textured_shader);
			cur_shader_is_tex = !cur_shader_is_tex;
			space_pressed = true;
		}
		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		{
			space_pressed = false;
		}
		
	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	

	return 0;
}
