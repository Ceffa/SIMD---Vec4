#include "vec4.h"
#include "GLM/glm.hpp"
#include <iostream>

int main(){

	V4 v0(1,1,1,1);
	v0.w(3);
	std::cout << v0 << std::endl;
	return EXIT_SUCCESS;
}