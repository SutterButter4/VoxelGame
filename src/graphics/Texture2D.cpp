//
// Created by jake on 1/26/20.
//

#include "Texture2D.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>

unsigned int Texture2D::boundTextureID = 0;

Texture2D::Texture2D(std::string filename, bool alpha) {

    glGenTextures(1, &(this->textureID));
    this->bind();

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load the texture from the file
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

    int channels = alpha ? GL_RGBA : GL_RGB;

    //check that it loaded properly, and if so then we generate it
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, channels, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        throw std::runtime_error("couldnt load texture: " + filename + " in Texture2D constructor");
    }

    this->unbind();

    stbi_image_free(data);
}

void Texture2D::bind() const {
    if(this->textureID != Texture2D::boundTextureID){
        glBindTexture(GL_TEXTURE_2D, this->textureID);
        Texture2D::boundTextureID = this->textureID;
    }
}

void Texture2D::unbind() const {
    if(this->textureID != 0){
        glBindTexture(GL_TEXTURE_2D, 0);
        Texture2D::boundTextureID = 0;
    }
}
