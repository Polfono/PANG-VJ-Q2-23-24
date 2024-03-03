#ifndef _SHADER_PROGRAM_MANAGER_INCLUDE
#define _SHADER_PROGRAM_MANAGER_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"

class ShaderProgramManager {

public:
	static ShaderProgramManager& instance() {
		static ShaderProgramManager SPM;
		return SPM;
	}

	void init();
	ShaderProgram& getShaderProgram();
	void useShaderProgram();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;
};

#endif //_SHADER_PROGRAM_MANAGER_INCLUDE