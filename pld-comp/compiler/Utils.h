#pragma once

#include <string>

size_t typeSize(std::string typeName);

std::string makeInstrSuffix_x86(std::string instruction, std::string typeName);

std::string makeRegisterName_x86(std::string regName, std::string typeName);


