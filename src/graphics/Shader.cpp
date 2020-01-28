//
// Created by jake on 1/26/20.
//

#include "Shader.h"
#include "../misc/Utils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

int Shader::boundShaderID = 0;

Shader::Shader(std::string vertPath, std::string fragPath) {
    std::string vertSource = Utils::readTXTFile(vertPath);
    std::string fragSource = Utils::readTXTFile(fragPath);

    const char *const vertSourceCStr = vertSource.c_str();
    const char *const fragSourceCStr = fragSource.c_str();

    unsigned int vertID;
    vertID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertID, 1, &vertSourceCStr, NULL);
    glCompileShader(vertID);

    int success;
    char infoLog[512];
    glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertID, 512, NULL, infoLog);
        throw std::runtime_error(
                "vertex shader " + vertPath + " failed to compile with error: \n" +
                     std::string(infoLog));
    }

    unsigned int fragID;
    fragID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragID, 1, &fragSourceCStr, NULL);
    glCompileShader(fragID);

    glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertID, 512, NULL, infoLog);
        throw std::runtime_error(
                "fragment shader " + fragPath + " failed to compile with error: \n" +
                std::string(infoLog));
    }

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertID);
    glAttachShader(shaderID, fragID);
    glLinkProgram(shaderID);

    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        throw std::runtime_error("shader program" + vertPath + ", " + fragPath +
                                 " failed to compile with error: \n" +
                                 std::string(infoLog));
    }

    glDeleteShader(vertID);
    glDeleteShader(fragID);
}

Shader::~Shader() {
    glDeleteProgram(this->shaderID);
}

void Shader::bind() {
    if(this->shaderID != Shader::boundShaderID) {
        glUseProgram(this->shaderID);
        Shader::boundShaderID = this->shaderID;
    }
}

void Shader::unbind() {
    if(0 != Shader::boundShaderID) {
        glUseProgram(0);
        Shader::boundShaderID = 0;
    }
}

int Shader::getUniformLoc(std::string name) {
    if(uniformLocations.find(name) != uniformLocations.end()){
        return uniformLocations.at(name);
    } else {
        int uniformLoc = glGetUniformLocation(this->shaderID, name.c_str());
        if(uniformLoc == -1) {
            throw std::runtime_error("uniform " + name + " not found in shader");
        }
        uniformLocations.insert(std::pair<std::string, int>(name, uniformLoc));
        return uniformLoc;
    }
}

void Shader::setUniform(std::string name, int a) {
    int uniformLoc = this->getUniformLoc(name);
    glUniform1i(uniformLoc, a);
}

void Shader::setUniform(std::string name, float a) {
    int uniformLoc = this->getUniformLoc(name);
    glUniform1f(uniformLoc, a);
}

void Shader::setUniform(std::string name, float a, float b) {
    int uniformLoc = this->getUniformLoc(name);
    glUniform2f(uniformLoc, a, b);
}

void Shader::setUniform(std::string name, float a, float b, float c) {
    int uniformLoc = this->getUniformLoc(name);
    glUniform3f(uniformLoc, a, b, c);
}

void Shader::setUniform(std::string name, float a, float b, float c, float d) {
    int uniformLoc = this->getUniformLoc(name);
    glUniform4f(uniformLoc, a, b, c, d);
}

void Shader::setUniform(std::string name, glm::mat4 mat) {
    int uniformLoc = this->getUniformLoc(name);
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setTexture(std::string name, int loc, const Texture2D &texture) {
    glActiveTexture(GL_TEXTURE0 + loc);
    texture.bind();
    setUniform(name, loc);
}




