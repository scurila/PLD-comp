
#include <string>
#include "Utils.h"

size_t typeSize(const std::string &typeName) 
{
    if(typeName == "int") {
        return 8;
    } 
    else if(typeName == "char") {
        return 1;
    }
    return -1; // TODO handle errors correctly
}

std::string makeInstrSuffix_x86(const std::string &instruction, const std::string &typeName) {
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

std::string makeRegisterName_x86(std::string regName, const std::string &typeName) {
    switch (typeSize(typeName)) {
        case 8: {
            if(regName.at(0) == 'r') {  // means r8, r9, r10...
                return "%" + regName;
            }

            return "%r" + regName;
        }

        case 4: {
            if(regName.at(0) == 'r') {  // means r8, r9, r10...
                return "%" + regName + "d";
            }

            return "%e" + regName;
        }
        case 2: {
            if(regName.at(0) == 'r') {  // means r8, r9, r10...
                return "%" + regName + "w";
            }

            return "%" + regName;
        }
        case 1: {
            if(regName.at(0) == 'r') {  // means r8, r9, r10...
                return "%" + regName + "b";
            }

            regName.pop_back(); // remove 'x' suffix
            return "%" + regName + "l";
        }
    }
    return "ERR";
}



