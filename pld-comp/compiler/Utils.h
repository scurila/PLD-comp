#pragma once

#include <string>

size_t typeSize(std::string typeName) 
{
    if(typeName == "int") {
        return 4;
    } 
    else if(typeName == "char") {
        return 1;
    }
    return -1; // TODO handle errors correctly
}



