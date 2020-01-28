//
// Created by jake on 1/26/20.
//

#include "Game.h"

Game::Game() {

}

void Game::run() {
    init();

    while(isRunning){
        update();
        draw();
    }
}

void Game::init() {
    isRunning = true;

    window = std::make_shared<Window>(width, height, windowTitle, true);
    window->bind();
    window->setBackgroundColor(0.2f, 0.3f, 0.3f, 1.0f);
    window->hideCursor();

    basicShader = std::make_shared<Shader>("../src/graphics/shaders/vertShader1.glsl",
                                           "../src/graphics/shaders/fragShader1.glsl");
    containerTex = std::make_shared<Texture2D>("../textures/container.jpg", false);
    faceTex = std::make_shared<Texture2D>("../textures/awesomeface.png", true);

    camera = std::make_shared<Camera>(
            glm::radians(45.0f),
            float(width)/float(height),
            0.1f, 100.0f,
            glm::vec3(0, 0, 3));

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
    };

    float textCoords[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f
    };

//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &TVBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute

    glBindBuffer(GL_ARRAY_BUFFER, TVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textCoords), textCoords, GL_STATIC_DRAW);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
}

void Game::update() {
    processInput();
}

void Game::draw() {
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    window->clear();

    basicShader->bind();
    basicShader->setTexture("tex1", 0, *containerTex);
    basicShader->setTexture("tex2", 1, *faceTex);

    basicShader->setUniform("view", camera->getView());
    basicShader->setUniform("projection", camera->getProjection());

    for(unsigned int i = 0; i < 10; i++){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * (i + glfwGetTime());
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        basicShader->setUniform("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    window->update();
}

void Game::processInput() {
    if(window->isKeyPressed(GLFW_KEY_ESCAPE) || window->shouldClose()){
        isRunning = false;
    }

    glm::vec3 left(1.0f, 0.0f, 0.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    glm::vec3 forward(0.0f, 0.0f, 1.0f);

    const float cameraSpeed = 0.05f; // adjust accordingly
    if (window->isKeyPressed(GLFW_KEY_W))
        camera->moveCamera(cameraSpeed * forward);
    if (window->isKeyPressed(GLFW_KEY_S))
        camera->moveCamera(-cameraSpeed * forward);
    if (window->isKeyPressed(GLFW_KEY_A))
        camera->moveCamera(cameraSpeed * left);
    if (window->isKeyPressed(GLFW_KEY_D))
        camera->moveCamera(-cameraSpeed * left);
    if (window->isKeyPressed(GLFW_KEY_SPACE))
        camera->moveCamera(cameraSpeed * up);
    if (window->isKeyPressed(GLFW_KEY_LEFT_SHIFT))
        camera->moveCamera(-cameraSpeed * up);

    float cameraRotateSpeed = 0.2;
    auto mouseDelta = cameraRotateSpeed * window->getDeltaMousePos();
    camera->rotate(mouseDelta.x, -mouseDelta.y);

    camera->zoom(window->getMouseScroll().y);
}
