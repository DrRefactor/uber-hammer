#pragma once
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "shprogram.h"
#include "Drawable.h"

class TexturedModel :
	public Drawable {
public:
	TexturedModel(const GLfloat *vertices, size_t vertice_count, const GLuint *indices, size_t indice_count, ShaderProgram &shader, const char* textureFile, GLuint textId);
	void draw(const glm::mat4 projection, const glm::mat4 view, const glm::mat4 parentTransformation = glm::mat4(1));
	void setFrame(const float t);
	void setModelMatrix(const glm::mat4 &m);

	virtual ~TexturedModel();
private:
	size_t indice_num;

	GLuint texture;
	GLuint textureID;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLuint MVP_location;
	GLuint P_location;
	GLuint V_location;
	GLuint M_location;

	GLuint lightPositionLocation;
	GLuint lightIntensityLocation;

	glm::mat4 model = glm::mat4(1.f);

	ShaderProgram &shader;
};

