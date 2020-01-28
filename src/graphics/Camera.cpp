//
// Created by jake on 1/27/20.
//

#include "Camera.h"

Camera::Camera(float fovy, float aspect, float znear, float zfar, glm::vec3 position)
    :position(position), fovy(fovy), aspect(aspect), znear(znear), zfar(zfar) {
    phi = 0, theta = 0;
}

glm::mat4 Camera::getProjection() {
    return glm::perspective(fovy, aspect, znear, zfar);
}

glm::mat4 Camera::getView() {
    return glm::lookAt(position,
            position + frontVector(),
            up);
}

void Camera::moveCamera(glm::vec3 delta) {
    position += delta.x * leftVector() +
                delta.y * upVector() +
                delta.z * frontVector();
}

void Camera::moveCameraAbsolute(glm::vec3 delta) {
    position += delta;
}

glm::vec3 Camera::frontVector() {
    double x = cos(theta) * cos(phi);
    double y = sin(theta);
    double z = cos(theta) * sin(phi);
    return glm::vec3(x, y, z);
}

glm::vec3 Camera::upVector() {
    return up;
}

glm::vec3 Camera::leftVector() {
    return glm::normalize(glm::cross(upVector(), frontVector()));
}

void Camera::rotate(double deltaPhi, double deltaTheta) {
    phi += glm::radians(deltaPhi);
    theta += glm::radians(deltaTheta);

    if(theta > glm::radians(89.0f))
        theta = glm::radians(89.0f);
    else if(theta < glm::radians(-89.0f))
        theta = glm::radians(-89.0f);

    phi = fmod(phi, 2*M_PI);
}

void Camera::zoom(double deltYFov) {
    fovy -= glm::radians(deltYFov);
}

float Camera::getFovY() {
    return fovy;
}
