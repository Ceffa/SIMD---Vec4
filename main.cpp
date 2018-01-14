#define  GLM_FORCE_SSE2
#include "vec4.h"
#include "GLM/glm.hpp"
#include <iostream>

int main(){

	glm::vec4 v0(1,2,3,4);
	for (I32 i = 0; i < 50; i++){
		v0 += glm::vec4(1,2,3,4);
	}
	std::cout << v0.x+ v0.y+ v0.x+ v0.w<< std::endl; 
	return EXIT_SUCCESS;
}