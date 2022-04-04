#pragma once

#include <string>

size_t typeSize(const std::string &typeName);

std::string makeInstrSuffix_x86(const std::string &instruction, const std::string &typeName);

std::string makeRegisterName_x86(std::string regName, const std::string &typeName);


