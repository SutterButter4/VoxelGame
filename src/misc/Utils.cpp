//
// Created by jake on 1/25/20.
//

#include "Utils.h"

#include <iostream>
#include <fstream>

std::string Utils::readTXTFile(std::string fileName) {
    //again open file in read mode
    std::fstream file;
    file.open(fileName, std::ios::in);

    if(!file) {
        throw std::runtime_error("couldnt read file " + fileName);
    }

    //read untill end of file is not found.
    std::string result("");
    std::string line("");

    while(!file.eof())
    {
        getline(file, line);
        result += (line + "\n");
    }

    file.close(); //close file

    return result;
}
