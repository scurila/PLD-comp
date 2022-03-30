
#include <string>
#include "Utils.h"

size_t typeSize(std::string typeName) 
{
    if(typeName == "int") {
        return 8;
    } 
    else if(typeName == "char") {
        return 1;
    }
    return -1; // TODO handle errors correctly
}

std::string makeInstrSuffix_x86(std::string instruction, std::string typeName) {
    switch(typeSize(typeName)) {
        case 4:
            return instruction + "l";
        case 8:
            return instruction + "q";
        case 2:
            return instruction + "w";
        case 1:
            return instruction + "b";
    }
    return "ERR";
}

std::string makeRegisterName_x86(std::string regName, std::string typeName) {
    switch (typeSize(typeName)) {
        case 8:
            return "%r" + regName;
        case 4:
            return "%e" + regName;
        case 2:
            return "%" + regName;
        case 1:
            regName.pop_back(); // remove 'x' suffix
            return "%" + regName + "l";
    }
    return "ERR";
}



