#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Position = position;
	this->width = width;
	this->height = height;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	camMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}


void Camera::Inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += speed * Orientation;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position -= speed * Orientation;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position -= glm::normalize(glm::cross(Orientation, Up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += glm::normalize(glm::cross(Orientation, Up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Position += Up * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		Position -= Up * speed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		Orientation = glm::rotate(Orientation, speed, Up);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		Orientation = glm::rotate(Orientation, speed, -Up);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		Orientation = glm::rotate(Orientation, speed, glm::normalize(glm::cross(Orientation, Up)));
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		Orientation = glm::rotate(Orientation, speed, glm::normalize(glm::cross(-Orientation, Up)));
	else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		speed = 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		speed = 0.03f;

}