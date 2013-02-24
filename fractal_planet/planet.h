#ifndef _PLANET_H
#define _PLANET_H

#include <stdlib.h>
#include <vector>

#include "glm/glm.hpp"
#include "noise/noise.h"

enum face_direction{
Top,
Bottom,
Left,
Right,
Front,
Back
};

class Planet
{
    std::vector< glm::vec3 > vertices, normals;
    std::vector< glm::vec3 > faces[6];
    
    public:
        Planet(int Steps);
        std::vector<glm::vec3> get_vertices();
        std::vector<glm::vec3> get_normals();
    private:
        
        std::vector<glm::vec3> make_face(face_direction direction, int Steps);
};

#endif
