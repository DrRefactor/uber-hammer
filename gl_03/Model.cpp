#include "Model.h"

#include <iostream>

extern float lightIntensity;
extern glm::vec3 lightPosition;

Model::Model(const GLfloat *vertices, size_t vertice_count, const GLuint *indices, size_t indice_count, ShaderProgram &shader, const glm::vec3 &colour) 
	: shader(shader), colour(colour) {
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertice_count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	// vertex geometry data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	// vertex normal data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_count * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	this->shader.Use();

	GLuint programID = this->shader.get_programID();
	this->MVP_location = glGetUniformLocation(programID, "MVP");
	this->V_location = glGetUniformLocation(programID, "V");
	this->M_location = glGetUniformLocation(programID, "M");

	this->colourLocation = glGetUniformLocation(programID, "colour");
	this->lightPositionLocation = glGetUniformLocation(programID, "LightPosition_worldspace");
	this->lightIntensityLocation = glGetUniformLocation(programID, "lightIntensity");

	this->indice_num = indice_count;
}

Model::~Model() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void Model::draw(const glm::mat4 projection, const glm::mat4 view, const glm::mat4 parentTransformation) {
	glm::mat4 M = parentTransformation * this->model;
	glm::mat4 MVP = projection * view * M;

	this->shader.Use();

	glUniformMatrix4fv(this->MVP_location, 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(this->V_location, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(this->M_location, 1, GL_FALSE, glm::value_ptr(M));

	glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPosition));
	glUniform3fv(colourLocation, 1, glm::value_ptr(colour));
	glUniform1f(lightIntensityLocation, lightIntensity);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glDrawElements(GL_TRIANGLES, this->indice_num, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Model::setFrame(const float t) {
}

void Model::setModelMatrix(const glm::mat4 & m) {
	this->model = m;
}
