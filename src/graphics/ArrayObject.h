//
// Created by jake on 1/28/20.
//

#ifndef DEBUG_ARRAYOBJECT_H
#define DEBUG_ARRAYOBJECT_H


class ArrayObject {
private:
    unsigned int arrayID;
public:
    ArrayObject();

    void bind();
    void addBuffer();
    void compile();
    void draw();
};


#endif //DEBUG_ARRAYOBJECT_H
