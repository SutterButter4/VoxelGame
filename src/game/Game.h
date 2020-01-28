//
// Created by jake on 1/26/20.
//

#ifndef DEBUG_GAME_H
#define DEBUG_GAME_H

#include "../graphics/graphics.h"
#include <memory>
#include <math.h>
#include <iostream>


class Game {
private:
    const int width = 800;
    const int height = 600;
    const std::string windowTitle = "VoxelGame";

    bool isRunning = false;

    std::shared_ptr<Window> window;
    std::shared_ptr<Shader> basicShader;
    std::shared_ptr<Texture2D> containerTex, faceTex;
    std::shared_ptr<Camera> camera;

    unsigned int TVBO, VBO, VAO;

    void init();
    void update();
    void processInput();
    void draw();
public:
    Game();

    void run();
};


#endif //DEBUG_GAME_H
