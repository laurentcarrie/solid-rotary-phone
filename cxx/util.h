//
// Created by laurent on 19/03/2022.
//

#ifndef SOLID_ROTARY_PHONE_UTIL_H
#define SOLID_ROTARY_PHONE_UTIL_H

#include <filesystem>
#include <vector>
#include <string>

void generate_if_needed(std::filesystem::path target, std::vector<std::filesystem::path> sources,
                        std::string command)  ;

std::string  trim(const std::string& input) ;
void clean_files(const std::filesystem::path &builddir) ;
std::vector<std::string> split_string(std::string input, std::string delim) ;

#endif //SOLID_ROTARY_PHONE_UTIL_H
