#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <random>
#include <bitset>

#include "LSystem.h"
#include "Prism.h"

int main(int argc, char** argsv)
{
	float deltaTime{ 0 };
	float oldTime{ 0 };

	float pointPos = 0.25f;
	///DELTATIME AND FPS COUNTING
	deltaTime = clock() - oldTime;
	oldTime = clock();
	pointPos += deltaTime;

	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return 1;
	}

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		return 1;
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unable to initialise GLEW",
			(char*)glewGetErrorString(glewError), NULL);
	}

	//create VAO
	GLuint VertexArryID;
	glGenVertexArrays(1, &VertexArryID);
	glBindVertexArray(VertexArryID);

	// An array of 3 vectors which represents 3 vertices
	std::vector<GLfloat> g_vertex_buffer_data_vector;

	std::vector<GLuint> g_vertex_indices_vector;

	{
		std::random_device r;
		int i = (r() % 127);
		std::bitset<7> b(i);
		std::cout << b;

		// Generate L-System
		LSystem lSystem;
		std::vector<Prism> prisms = lSystem.GenLSystem("F", b);

		for (int i = 0; i < prisms.size(); i++) {
			prisms[i].SetVerticesArray(g_vertex_buffer_data_vector);
		}
	}

	//This will identify our vertex buffer
	GLuint vertexbuffer;
	//Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	//the following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//give our verticies to opengl
	glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data_vector.size() * sizeof(float),
		g_vertex_buffer_data_vector.data(), GL_STATIC_DRAW);
	//1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,							//attribute 0
		3,							//size
		GL_FLOAT,				    //type
		GL_FALSE,					//normalised?
		3 * sizeof(GL_FLOAT),		//stride
		(void*)0					//array
	);
	////1st attribute buffer : vertices
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(
	//	1,
	//	3,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	6 * sizeof(GL_FLOAT),
	//	(void*)(3 * sizeof(GL_FLOAT))
	//);

	//GLuint elementbuffer;
	//glGenBuffers(1, &elementbuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_vertex_indices), g_vertex_indices, GL_STATIC_DRAW);

	//shader set up
	//create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("vertShader.glsl", "fragShader.glsl");

	// Transforms
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(20.f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	//model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 mvp, view, projection;
	glm::vec3 position(0, 0, 5), forward(0, 0, -1), rotation(0);
	const glm::vec4 cameraFace(0, 0, -1, 0);
	const float walkSpeed = 0.5f, rotSpeed = 0.1f;


	unsigned int transformLoc = glGetUniformLocation(programID, "transform");


	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;
	while (running)
	{
		//Poll for the events which have happened in this frame
		//https://wiki.libsdl.org/SDL_PollEvent
		while (SDL_PollEvent(&ev))
		{
			//Switch case for every message we are intereted in
			switch (ev.type)
			{
				//QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;
				//KEYDOWN Message, called when a key has been pressed down
			case SDL_MOUSEMOTION:
			{
				rotation.y -= ev.motion.xrel * rotSpeed;
				rotation.x -= ev.motion.yrel * rotSpeed;
				glm::mat4 viewRotate(1.0f);
				viewRotate = glm::rotate(viewRotate, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
				viewRotate = glm::rotate(viewRotate, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
				forward = glm::normalize(glm::vec3(viewRotate * cameraFace));
				break;
			}
			case SDL_KEYDOWN:
				//Check the actual key code of the key that has been pressed
				switch (ev.key.keysym.sym)
				{
					//Escape key
				case SDLK_ESCAPE:
					running = false;
					break;

				case SDLK_w:
					position += walkSpeed * forward;
					break;

				case SDLK_s:
					position -= walkSpeed * forward;
					break;

				case SDLK_a:
					position += walkSpeed * glm::cross(-forward, glm::vec3(0, 1, 0));
					break;

				case SDLK_d:
					position += walkSpeed * glm::cross(forward, glm::vec3(0, 1, 0));
					break;
				}
			}
		}
		glClearColor(1.0f, .7f, .7f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		view = glm::lookAt(
			position,
			position + forward,
			glm::vec3(0, 1, 0)
		);

		projection = glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 100.0f);
		mvp = projection * view * model;

		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp));

		//draw the triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3); // starting from vertex 0; 3 vertices total -> 1 triangle

		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, g_vertex_buffer_data_vector.size());

		SDL_GL_SwapWindow(window);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

	return 0;
}