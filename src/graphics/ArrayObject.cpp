//
// Created by jake on 1/28/20.
//

#include "ArrayObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

ArrayObject::ArrayObject() {
    glGenVertexArrays(1, &arrayID);
}
