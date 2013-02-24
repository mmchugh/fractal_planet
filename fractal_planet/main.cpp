#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <GL/glew.h>

#include <GL/glfw.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "shader.h"
#include "controls.h"

#include "noise/noise.h"

#define SEED 1344
#define HSTEPS 50
#define VSTEPS 50
#define VARY 0.1

bool makePlanet(std::vector<glm::vec3> &out_vertices, std::vector<glm::vec3> &out_normals, int horizontalSteps, int verticalSteps)
{

	std::vector<unsigned int> vertexIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec3> temp_normals;
	double zenith, azimuth;
	double radius = 100.0;

	double value;
	noise::module::RidgedMulti ridgeModule;

	ridgeModule.SetSeed(SEED);

	for(int i=0; i <= verticalSteps; i++)
	{
		zenith = i * (3.14 / (double)verticalSteps);

		for(int j=0; j< horizontalSteps; j++)
		{
			azimuth = j * (6.28 / (double)horizontalSteps);

			glm::vec3 vertex;
			vertex.x = sin(zenith) * cos(azimuth);
			vertex.y = sin(zenith) * sin(azimuth);
			vertex.z = cos(zenith);

			value = (1 + ridgeModule.GetValue(vertex.x, vertex.y, vertex.z) * VARY) * radius;
			
			vertex *= value;

			temp_vertices.push_back(vertex);
		}
	}

	for(int i=0; i<verticalSteps; i++)
	{
		for(int j=0; j<horizontalSteps; j++)
		{
			int index1 = j + (i+1) *horizontalSteps;
			int index2 = (j+1) % horizontalSteps + i*horizontalSteps;
			int index3 = j + i*horizontalSteps;
			glm::vec3 normal = glm::cross(temp_vertices[index1] - temp_vertices[index2], temp_vertices[index1] - temp_vertices[index3]);

			out_vertices.push_back(temp_vertices[index1]);
			out_vertices.push_back(temp_vertices[index2]);
			out_vertices.push_back(temp_vertices[index3]);
			out_normals.push_back(normal);
			out_normals.push_back(normal);
			out_normals.push_back(normal);
			
			index1 = j + (i+1) *horizontalSteps;
			index2 = (j+1) % horizontalSteps + (i+1) *horizontalSteps;
			index3 = (j+1) % horizontalSteps + i*horizontalSteps;
			normal = glm::cross(temp_vertices[index1] - temp_vertices[index2], temp_vertices[index1] - temp_vertices[index3]);

			out_vertices.push_back(temp_vertices[index1]);
			out_vertices.push_back(temp_vertices[index2]);
			out_vertices.push_back(temp_vertices[index3]);

			out_normals.push_back(normal);
			out_normals.push_back(normal);
			out_normals.push_back(normal);
		}
	}

	return true;
}

bool makePlanetCube(std::vector<glm::vec3> &out_vertices, std::vector<glm::vec3> &out_normals, int Steps)
{
	std::vector<std::vector<glm::vec3> > faces;

	std::vector<glm::vec3> temp_vertices; 
	double radius = 100.0;

	double value;
	noise::module::RidgedMulti ridgeModule;

	ridgeModule.SetSeed(SEED);

	double x,y,z;

	y=-1.0;
	for(int i=0; i<=Steps*2; i++)
	{
		for(int j=0; j<=Steps*2; j++)
		{
				x = ((double)i/Steps) * 2.0 - 1.0;
				z = ((double)j/Steps) * 2.0 - 1.0;
				glm::vec3 vertex;
				vertex.x = x * sqrt(1-(y*y/2) - (z*z/2) + (y*y*z*z/3));
				vertex.y = y * sqrt(1-(z*z/2) - (x*x/2) + (z*z*x*x/3));
				vertex.z = z * sqrt(1-(x*x/2) - (y*y/2) + (x*x*y*y/3));
				
				value = (1 + ridgeModule.GetValue(vertex.x, vertex.y, vertex.z) * VARY) * radius;
			
				vertex *= value;

				temp_vertices.push_back(vertex);
		}
	}

	faces.push_back(temp_vertices);
	temp_vertices.clear();

	y=1.0;
	for(int i=0; i<=Steps*2; i++)
	{
		for(int j=0; j<=Steps*2; j++)
		{
				z = ((double)i/Steps) * 2.0 - 1.0;
				x = ((double)j/Steps) * 2.0 - 1.0;
				glm::vec3 vertex;
				vertex.x = x * sqrt(1-(y*y/2) - (z*z/2) + (y*y*z*z/3));
				vertex.y = y * sqrt(1-(z*z/2) - (x*x/2) + (z*z*x*x/3));
				vertex.z = z * sqrt(1-(x*x/2) - (y*y/2) + (x*x*y*y/3));
				
				value = (1 + ridgeModule.GetValue(vertex.x, vertex.y, vertex.z) * VARY) * radius;
			
				vertex *= value;

				temp_vertices.push_back(vertex);
		}
	}

	faces.push_back(temp_vertices);
	temp_vertices.clear();

	x=-1.0;
	for(int i=0; i<=Steps*2; i++)
	{
		for(int j=0; j<=Steps*2; j++)
		{
			z = ((double)i/Steps) * 2.0 - 1.0;
			y = ((double)j/Steps) * 2.0 - 1.0;
				glm::vec3 vertex;
				vertex.x = x * sqrt(1-(y*y/2) - (z*z/2) + (y*y*z*z/3));
				vertex.y = y * sqrt(1-(z*z/2) - (x*x/2) + (z*z*x*x/3));
				vertex.z = z * sqrt(1-(x*x/2) - (y*y/2) + (x*x*y*y/3));
				
				value = (1 + ridgeModule.GetValue(vertex.x, vertex.y, vertex.z) * VARY) * radius;
			
				vertex *= value;

				temp_vertices.push_back(vertex);
		}
	}

	faces.push_back(temp_vertices);
	temp_vertices.clear();

	x=1.0;
	for(int i=0; i<=Steps*2; i++)
	{
		for(int j=0; j<=Steps*2; j++)
		{
			y = ((double)i/Steps) * 2.0 - 1.0;
			z = ((double)j/Steps) * 2.0 - 1.0;
				glm::vec3 vertex;
				vertex.x = x * sqrt(1-(y*y/2) - (z*z/2) + (y*y*z*z/3));
				vertex.y = y * sqrt(1-(z*z/2) - (x*x/2) + (z*z*x*x/3));
				vertex.z = z * sqrt(1-(x*x/2) - (y*y/2) + (x*x*y*y/3));
				
				value = (1 + ridgeModule.GetValue(vertex.x, vertex.y, vertex.z) * VARY) * radius;
			
				vertex *= value;

				temp_vertices.push_back(vertex);
		}
	}

	faces.push_back(temp_vertices);
	temp_vertices.clear();

	z=-1.0;
	for(int i=0; i<=Steps*2; i++)
	{
		for(int j=0; j<=Steps*2; j++)
		{
			y = ((double)i/Steps) * 2.0 - 1.0;
			x = ((double)j/Steps) * 2.0 - 1.0;
				glm::vec3 vertex;
				vertex.x = x * sqrt(1-(y*y/2) - (z*z/2) + (y*y*z*z/3));
				vertex.y = y * sqrt(1-(z*z/2) - (x*x/2) + (z*z*x*x/3));
				vertex.z = z * sqrt(1-(x*x/2) - (y*y/2) + (x*x*y*y/3));
				
				value = (1 + ridgeModule.GetValue(vertex.x, vertex.y, vertex.z) * VARY) * radius;
			
				vertex *= value;

				temp_vertices.push_back(vertex);
		}
	}

	faces.push_back(temp_vertices);
	temp_vertices.clear();

	z=1.0;
	for(int i=0; i<=Steps*2; i++)
	{
		for(int j=0; j<=Steps*2; j++)
		{
			x = ((double)i/Steps) * 2.0 - 1.0;
			y = ((double)j/Steps) * 2.0 - 1.0;
				glm::vec3 vertex;
				vertex.x = x * sqrt(1-(y*y/2) - (z*z/2) + (y*y*z*z/3));
				vertex.y = y * sqrt(1-(z*z/2) - (x*x/2) + (z*z*x*x/3));
				vertex.z = z * sqrt(1-(x*x/2) - (y*y/2) + (x*x*y*y/3));
				
				value = (1 + ridgeModule.GetValue(vertex.x, vertex.y, vertex.z) * VARY) * radius;
			
				vertex *= value;

				temp_vertices.push_back(vertex);
		}
	}

	faces.push_back(temp_vertices);

	for(int face=0; face<6; face++)
	{
		std::vector<glm::vec3> vertice_face;
		vertice_face = faces[face];

		for(int i=0;i<Steps;i++)
		{
		
			for(int j=0; j<Steps; j++)
			{
				int index1 = j + (i+1) *(Steps*2+1);
				int index2 = (j+1) % (Steps*2+1) + i*(Steps*2+1);
				int index3 = j + i*(Steps*2+1);
				glm::vec3 normal = glm::cross(vertice_face[index1] - vertice_face[index2], vertice_face[index1] - vertice_face[index3]);

				out_vertices.push_back(vertice_face[index1]);
				out_vertices.push_back(vertice_face[index2]);
				out_vertices.push_back(vertice_face[index3]);
				out_normals.push_back(normal);
				out_normals.push_back(normal);
				out_normals.push_back(normal);

				index1 = j + (i+1) *(Steps*2+1);
				index2 = (j+1) % (Steps*2+1) + (i+1) *(Steps*2+1);
				index3 = (j+1) % (Steps*2+1) + i*(Steps*2+1);
				normal = glm::cross(vertice_face[index1] - vertice_face[index2], vertice_face[index1] - vertice_face[index3]);

				out_vertices.push_back(vertice_face[index1]);
				out_vertices.push_back(vertice_face[index2]);
				out_vertices.push_back(vertice_face[index3]);

				out_normals.push_back(normal);
				out_normals.push_back(normal);
				out_normals.push_back(normal);
			}
		}
	}

	return true;
}


int main( int argc, char *argv[] )
{
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        return -1;
    }

	glewExperimental = GL_TRUE; // issue with glew supporting core, it seems.
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle( "Planetary" );

	glfwEnable( GLFW_STICKY_KEYS );
	glfwSetMousePos(1024/2, 768/2);

	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
	
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

    bool res;
    if(argc == 2 && *argv[1] == 'c')
    {
        fprintf(stdout, "Creating planet using cube mapping\n");
        res = makePlanetCube(vertices, normals, HSTEPS);
    }
    else
    {
        fprintf(stdout, "Creating planet using polar coordinates\n");
        res = makePlanet(vertices, normals, HSTEPS, VSTEPS);
    }

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		computeMatrices();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(200,200,200);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(2);

        glfwSwapBuffers();

    }
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED) );

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(programID);

    glfwTerminate();

    return 0;
}

