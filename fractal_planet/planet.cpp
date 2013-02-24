#include <stdlib.h>
#include <vector>
#include "glm/glm.hpp"

#include "planet.h"

Planet::Planet(int Steps)
{
    
    faces[0] = this->make_face(Top, Steps);
    faces[1] = this->make_face(Bottom, Steps);
    faces[2] = this->make_face(Left, Steps);
    faces[3] = this->make_face(Right, Steps);
    faces[4] = this->make_face(Front, Steps);
    faces[5] = this->make_face(Back, Steps);
    
	//for(int face=2; face<3; face++)
	//{
	int face = 2;
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

				vertices.push_back(vertice_face[index1]);
				vertices.push_back(vertice_face[index2]);
				vertices.push_back(vertice_face[index3]);
				normals.push_back(normal);
				normals.push_back(normal);
				normals.push_back(normal);

				index1 = j + (i+1) *(Steps*2+1);
				index2 = (j+1) % (Steps*2+1) + (i+1) *(Steps*2+1);
				index3 = (j+1) % (Steps*2+1) + i*(Steps*2+1);
				normal = glm::cross(vertice_face[index1] - vertice_face[index2], vertice_face[index1] - vertice_face[index3]);

				vertices.push_back(vertice_face[index1]);
				vertices.push_back(vertice_face[index2]);
				vertices.push_back(vertice_face[index3]);

				normals.push_back(normal);
				normals.push_back(normal);
				normals.push_back(normal);
			}
		}
//	}

}

std::vector<glm::vec3> Planet::make_face(face_direction direction, int Steps)
{
    std::vector<glm::vec3> face;
    double radius = 100.0, vary = 0.05;

	double value, x, y, z;
	noise::module::RidgedMulti noiseModule;
	//noise::module::Perlin noiseModule;
	
	noiseModule.SetSeed(1344);
	printf("making face\n");
	
    for(int i=0; i<Steps*2; i++)
    {
        for(int j=0; j<Steps*2; j++)
        {
            switch(direction)
            {
                case Top:
                    y = -1.0f;
                    x = ((double)i/Steps) * 2.0 - 1.0;
                    z = ((double)j/Steps) * 2.0 - 1.0;
                    break;
                case Bottom:
                    y = 1.0f;
                    z = ((double)i/Steps) * 2.0 - 1.0;
                    x = ((double)j/Steps) * 2.0 - 1.0;
                    break;
                case Left:
                    x = -1.0f;
                    z = ((double)i/Steps) * 2.0 - 1.0;
                    y = ((double)j/Steps) * 2.0 - 1.0;
                    break;
                case Right:
                    x = 1.0f;
                    y = ((double)i/Steps) * 2.0 - 1.0;
                    z = ((double)j/Steps) * 2.0 - 1.0;
                    break;
                case Front:
                    z = -1.0f;
                    y = ((double)i/Steps) * 2.0 - 1.0;
                    x = ((double)j/Steps) * 2.0 - 1.0;
                    break;
                case Back:
                    z = 1.0f;
                    x = ((double)i/Steps) * 2.0 - 1.0;
                    y = ((double)j/Steps) * 2.0 - 1.0;
                    break;
            }        
            glm::vec3 vertex;
            vertex.x = x * sqrt(1-(y*y/2) - (z*z/2) + (y*y*z*z/3));
            vertex.y = y * sqrt(1-(z*z/2) - (x*x/2) + (z*z*x*x/3));
            vertex.z = z * sqrt(1-(x*x/2) - (y*y/2) + (x*x*y*y/3));

            value = (1 + noiseModule.GetValue(vertex.x, vertex.y, vertex.z) * vary) * radius;

            vertex *= value;
            face.push_back(vertex);
            //printf("j:%d", j);
        }
//        printf("i: %d", i);
    }
    
    return face;
}

std::vector<glm::vec3> Planet::get_vertices()
{
    return this->vertices;
}

std::vector<glm::vec3> Planet::get_normals()
{
    return this->normals;
}
