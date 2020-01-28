//
// Created by jake on 1/26/20.
//

#ifndef DEBUG_SHADER_H
#define DEBUG_SHADER_H

#include <string>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture2D.h"

class Shader {
private:
    static int boundShaderID;
    unsigned int shaderID;
    std::map<std::string, int> uniformLocations;
public:
    Shader(std::string vertPath, std::string fragPath);
    ~Shader();

    void bind();
    void unbind();

    int getUniformLoc(std::string name);

    void setTexture(std::string name, int loc, const Texture2D& texture);

    void setUniform(std::string name, int a);
    void setUniform(std::string name, float a);
    void setUniform(std::string name, float a, float b);
    void setUniform(std::string name, float a, float b, float c);
    void setUniform(std::string name, float a, float b, float c, float d);
    void setUniform(std::string name, glm::mat4 mat);
};


#endif //DEBUG_SHADER_H
