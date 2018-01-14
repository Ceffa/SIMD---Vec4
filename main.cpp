#include "vec4.h"
#include "GLM/glm.hpp"
#include <iostream>

int main(){

	vec4 v0(1,1,1,1);
	vec4 v1(-1,-1,-1,-1);
	std::cout << v0.dot(v1) << std::endl; 
	return EXIT_SUCCESS;
}