//
// Created by jake on 1/27/20.
//

#ifndef DEBUG_CAMERA_H
#define DEBUG_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../misc/Utils.h"
#include <iostream>

class Camera {
private:
    glm::vec3 position = glm::vec3(0, 0, 0);

    float fovy, aspect, znear, zfar;

    //theta is the angle from the xz plane, phi the angle from the x along the xz plane
    double phi, theta;

    //up always points straight up
    glm::vec3 up    = glm::vec3(0.0f, 1.0f, 0.0f);
public:
    Camera(float fovy, float aspect, float znear, float zfar, glm::vec3 position);

    glm::mat4 getProjection();
    glm::mat4 getView();

    //moves the camera the given amount in the right, up, forward direction, whatever that is for the camera
    void moveCamera(glm::vec3 delta);
    //changes the absolute position of the camera in the given direction
    void moveCameraAbsolute(glm::vec3 delta);

    //phi is distance to
    void rotate(double phi, double theta);

    //zoom(negative values for zoom out)
    void zoom(double deltYFov);
    float getFovY();

    glm::vec3 frontVector();
    glm::vec3 upVector();
    glm::vec3 leftVector();
};


#endif //DEBUG_CAMERA_H
