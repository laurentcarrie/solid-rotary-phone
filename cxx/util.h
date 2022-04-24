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


#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class my_exception : public std::runtime_error {
    std::string msg;
public:
    my_exception(const std::string &arg, const char *file, int line) :
            std::runtime_error(arg) {
        std::ostringstream o;
        o << file << ":" << line << ": " << arg;
        msg = o.str();
    }
    ~my_exception() throw() {}
    const char *what() const throw() {
        return msg.c_str();
    }
};
#define throw_line(arg) throw my_exception(arg, __FILE__, __LINE__);

#endif //SOLID_ROTARY_PHONE_UTIL_H
