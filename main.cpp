#include "vec4.h"
#include "GLM/glm.hpp"
#include <iostream>
#include <sys/time.h>

int main(){

	V4 v0(1,1,1,1);
	for (int i =0; i < 1000000000; i++){
		float f = (i%7) * .33f;
			v0.x(v0.x()+f);
	}
		
	std::cout << v0 << std::endl;
	return EXIT_SUCCESS;
}