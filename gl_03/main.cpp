#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "models.h"

#include "Model.h"
#include "TexturedModel.h"
#include "Transformation.h"
#include "AnimationController.h"
#include "RotationController.h"
#include "DrawableGroup.h"
#include "TimelineController.h"
#include "CameraController.h"
#include "Skybox.h"
#include "Box.h"

using namespace std;

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

glm::vec3 lightPosition = glm::vec3(0, 7, 7);
float lightIntensity = 50.f;
bool triggered = false;
bool running = false;

GLFWwindow* window;

int main() {
	if (glfwInit() != GL_TRUE) {
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try {
		window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - projekt", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");

		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDepthFunc(GL_LESS);

		glm::vec3 hammerHeadColour = glm::vec3(.0f, .0f, .0f);
		glm::vec3 hammerHandleColour = glm::vec3(.6f, .3f, .1f);
		glm::vec3 moldColour = glm::vec3(.1f, .1f, .1f);
		glm::vec3 tableColour = glm::vec3(.5f, .5f, .5f);

		ShaderProgram solidColourShader("solidColour.vert", "solidColour.frag");
		ShaderProgram texturedShader("textured.vert", "textured.frag");

		TexturedModel board(&board_vertices[0], _countof(board_vertices), &board_indices[0], _countof(board_indices), texturedShader, "brushed-metal.png", GL_TEXTURE0);

		TexturedModel hammerHolderL(hammer_holder_vertices, _countof(hammer_holder_vertices), hammer_holder_indices, _countof(hammer_holder_indices), texturedShader, "wood.png", GL_TEXTURE1);
		hammerHolderL.setModelMatrix(glm::translate(glm::vec3(-.80f, 0, 0)));

		Transformation hammerHolderR(glm::translate(glm::vec3(0, 0, 1.9f)), &hammerHolderL);

		TexturedModel table(&table_vertices[0], _countof(table_vertices), &table_indices[0], _countof(table_indices), texturedShader, "scratchedmetal.jpg", GL_TEXTURE2);

		TexturedModel mold(&moldBox.getVertices()[0], moldBox.verticesCount, &moldBox.getIndices()[0], moldBox.indicesCount, texturedShader, "rustymetal.jpg", GL_TEXTURE3);
		//TexturedModel mold(mold_verts, _countof(mold_verts), mold_inds, _countof(mold_inds), texturedShader, "rustymetal.jpg", GL_TEXTURE3);

		DrawableGroup moldGroup;
		moldGroup.addModel(&mold);
		//moldGroup.addModel(&moldBase);

		Transformation moldGroupTransformed(glm::translate(glm::vec3(0, 0, -0.25)), &moldGroup);

		Model hammerHandle(&hammer_handle_vertices[0], _countof(hammer_handle_vertices), &hammer_handle_indices[0], _countof(hammer_handle_indices), solidColourShader, hammerHandleColour);
		
		Model hammerHead(&hammer_head_vertices[0], _countof(hammer_head_vertices), &hammer_head_indices[0], _countof(hammer_head_indices), solidColourShader, hammerHeadColour);
		
		hammerHead.setModelMatrix(glm::translate(glm::vec3(0, -0.1, 0)));

		DrawableGroup hammer = DrawableGroup();
		hammer.addModel(&hammerHandle);
		hammer.addModel(&hammerHead);

		Transformation hammerTilted = Transformation(glm::rotate(glm::pi<float>() / 4, glm::vec3(0, 0, -1)), &hammer);

		RotationController hammerRotation(glm::pi<float>() / 4, glm::vec3(0, 0, -1));
		hammerRotation.addModel(&hammerTilted);
		RotationController hammerRotationBack(-glm::pi<float>() / 4, glm::vec3(0, 0, -1));
		hammerRotationBack.addModel(&hammerRotation);

		Transformation transformedHammer = Transformation(glm::translate(glm::vec3(-0.75, 2.2, 0)), &hammerRotationBack);

		glm::mat4 tForward = glm::translate(glm::vec3(0, 0, 2.));
		LinearAnimationController moldMovingForward(tForward);
		moldMovingForward.addModel(&moldGroupTransformed);

		glm::mat4 tBack = glm::translate(glm::vec3(0, 0, -2.));
		LinearAnimationController moldMovingBackward(tBack);
		moldMovingBackward.addModel(&moldMovingForward);

		Drawable *moldFinal = &moldMovingBackward;
		Drawable *hammerFinal = &transformedHammer;

		DrawableGroup boardFinal{};
		boardFinal.addModel(&board);
		boardFinal.addModel(&hammerHolderL);
		boardFinal.addModel(&hammerHolderR);

		// animation times

		TimelineController moldTimeline{};
		moldTimeline.addAnimation(&moldMovingForward, 0.0f, 0.23);
		moldTimeline.addAnimation(&moldMovingBackward, 0.5f, 0.73);
		moldTimeline.addDrawable(moldFinal);

		TimelineController hammerTimeline{};
		hammerTimeline.addAnimation(&hammerRotation, 0.45f, 0.5f);
		hammerTimeline.addAnimation(&hammerRotationBack, 0.6f, 1.0f);
		hammerTimeline.addDrawable(hammerFinal);

		double startTime = glfwGetTime();
		double acSpeed = 0.3;

		int animationStage = 0;


		// skybox

		ShaderProgram skyboxShader("skybox.vert", "skybox.frag");
		GLfloat skyboxVertices[] = {
			// Positions
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f,  1.0f
		};

		// Setup skybox VAO
		GLuint skyboxVAO, skyboxVBO;
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
		glBindVertexArray(0);

		// Cubemap (Skybox)
		vector<const GLchar*> faces;
		faces.push_back("skybox/browncloud_rt.jpg");
		faces.push_back("skybox/browncloud_lf.jpg");
		faces.push_back("skybox/browncloud_up.jpg");
		faces.push_back("skybox/browncloud_dn.jpg");
		faces.push_back("skybox/browncloud_bk.jpg");
		faces.push_back("skybox/browncloud_ft.jpg");
		GLuint cubemapTexture = Skybox::LoadCubemap(faces);
		// end of skybox

		CameraController camera = CameraController(window);

		glm::mat4 view;
		glm::mat4 projection;

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
				triggered = true;
			}
			camera.updateView();

			boardFinal.draw(camera.projectionMatrix, camera.viewMatrix);
			table.draw(camera.projectionMatrix, camera.viewMatrix);

			float frame = (glfwGetTime() - startTime) * acSpeed;
			float effectiveFrame = running ? frame : 0;

			moldTimeline.setFrame(effectiveFrame / 2 + animationStage * .5);
			moldTimeline.draw(camera.projectionMatrix, camera.viewMatrix);
			//std::cout << effectiveFrame << " " << animationStage << std::endl;

			hammerTimeline.setFrame(effectiveFrame);
			hammerTimeline.draw(camera.projectionMatrix, camera.viewMatrix);

			if (triggered && !running) {
				startTime = glfwGetTime();
				triggered = false;
				running = true;
			} else if (running) {
				if (frame > 1.) {
					animationStage = (animationStage + 1) % 2;
					running = false;
					triggered = false;
				}
			}


			// Draw skybox as last
			glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
			skyboxShader.Use();
			view = glm::mat4(glm::mat3(camera.viewMatrix));	// Remove any translation component of the view matrix
			projection = glm::mat4(glm::mat3(camera.projectionMatrix));

			glUniformMatrix4fv(glGetUniformLocation(skyboxShader.get_programID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(skyboxShader.get_programID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			// skybox cube
			glBindVertexArray(skyboxVAO);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			glDepthFunc(GL_LESS); // Set depth function back to default
			// end of skybox
			
			
			glfwSwapBuffers(window);
		}
	} catch (exception ex) {
		cout << ex.what() << endl;
	}

	glfwTerminate();

	return 0;
}
