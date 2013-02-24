#include <GL/glfw.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

#include "controls.h"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix()
{
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix()
{
	return ProjectionMatrix;
}

glm::vec3 position = glm::vec3( 0, 0, 500 ); 
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;
float speed = 100.0f;
float mouseSpeed = 0.005f;


void computeMatrices()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();

	float deltaTime = float(currentTime - lastTime);

	int xpos, ypos;
	glfwGetMousePos(&xpos, &ypos);

	glfwSetMousePos(1024/2, 768/2);

	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	if(verticalAngle > 3.14/2.0)
		verticalAngle = 3.14f/2.0f;
	if(verticalAngle < -3.14/2.0)
		verticalAngle = -3.14f/2.0f;

	//double distance = glm::distance(glm::vec3(0,0,0), position);
	//speed = distance / 5.0;

	glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle));
	
	glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f));
	
	glm::vec3 up = glm::cross( right, direction );

	if (glfwGetKey( 'W' ) == GLFW_PRESS || glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) )
		position += direction * deltaTime * speed;

	if (glfwGetKey( 'S' ) == GLFW_PRESS)
		position -= direction * deltaTime * speed;

	if (glfwGetKey( 'D' ) == GLFW_PRESS)
		position += right * deltaTime * speed;

	if (glfwGetKey( 'A' ) == GLFW_PRESS)
		position -= right * deltaTime * speed;

	if (glfwGetKey( 'Z' ) == GLFW_PRESS || glfwGetKey( GLFW_KEY_SPACE ) == GLFW_PRESS)
		position += up * deltaTime * speed;

	if (glfwGetKey( 'X' ) == GLFW_PRESS)
		position -= up * deltaTime * speed;

	if (glfwGetKey( 'R' ) == GLFW_PRESS)
	{
		horizontalAngle = 3.14f;
		verticalAngle = 0.0f;
	}

	float FoV = initialFoV - 5 * glfwGetMouseWheel();

	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 1000.0f);
	ViewMatrix = glm::lookAt(position, position+direction, up);

	lastTime = currentTime;
}
