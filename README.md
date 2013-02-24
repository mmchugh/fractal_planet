Fractal planet
==============
Requirements: GLEW, glfw, glm, libnoise

Generate a spherical object using libnoise to perturb the surface. There are 2 different mappings of vertex data to the sphere. The first use a naive polar coordinate mapping. This causes alot of clustering near the poles of the planet. The second takes a cube and attempts to morph it so that it maps to a rough approximation of a sphere. I find this method gives a more even spread of vertices and a nicer looking planet.

By default running the program will generate a planet using polar coordinates. If you pass in the arg 'c' to the program, it will switch to using the cube mapping method.

Polar coordinates:
![Polar coordinates screenshot](/screenshots/polar-planet1.jpg)
![Polar coordinates screenshot](/screenshots/polar-planet2.jpg)
Cube mapping:
![Cube mapped screenshot](/screenshots/cube-planet1.jpg)
![Cube mapped screenshot](/screenshots/cube-planet2.jpg)