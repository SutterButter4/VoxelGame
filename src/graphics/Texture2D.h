//
// Created by jake on 1/26/20.
//

#ifndef DEBUG_TEXTURE2D_H
#define DEBUG_TEXTURE2D_H


#include <string>

class Texture2D {
private:
    static unsigned int boundTextureID;
    unsigned int textureID;
public:
    Texture2D(std::string filename, bool alpha);

    void bind() const;
    void unbind() const;
};


#endif //DEBUG_TEXTURE2D_H
