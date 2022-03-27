//
// Created by laurent on 19/03/2022.
//
#include <fstream>
#include <regex>
#include <cassert>
#include "parse.h"
#include "config.h"
#include "to_html.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <array>
#include <sstream>
#include <set>
#include "util.h"

std::string exec(const char *cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


bool any_younger(const std::filesystem::path &p) {
    if (!std::filesystem::exists(p)) {
        return true;
    }
    std::filesystem::path d = p.parent_path();
    for (auto pp: d) {
        if (std::filesystem::last_write_time(d) < std::filesystem::last_write_time(p)) {
            return true;
        }

    }
    return false;
}



void generate_if_needed(std::filesystem::path target, std::vector<std::filesystem::path> sources,
                        std::string command) {
    bool is_needed = false;

    if (!std::filesystem::exists(target)) {
        is_needed = true;
    } else {
        for (auto s: sources) {
            if (std::filesystem::last_write_time(target) < std::filesystem::last_write_time(s)) {
                //std::cout << std::filesystem::last_write_time(target) << std::endl ;
                std::cout << target << " is newer than " << s << std::endl;
                is_needed = true;
                break;
            }
        }
    }
    if (any_younger(target)) {
        is_needed = true;
    }
    is_needed = true;
    if (!is_needed) return;
    std::cout << command << std::endl;
    exec(command.c_str());

    if (!std::filesystem::exists(target)) {
        std::ostringstream oss;
        oss << "command " << command << std::endl << "did not generate target " << std::endl << target << std::endl;
        throw (std::runtime_error(oss.str()));
    }

    return;
}

void clean_files(const std::filesystem::path &builddir) {
    std::set<std::string> extension_to_remove { ".tex",".texi",".count",".eps",".ly"} ;
    std::filesystem::path path = builddir  ;

    for ( auto const & direntry : std::filesystem::recursive_directory_iterator(path)) {
        if ( extension_to_remove.find(direntry.path().extension()) != extension_to_remove.end()) {
            // std::cout << "remove " << direntry.path().generic_string() << std::endl ;
            remove(direntry.path()) ;
        }
        if ( direntry.path().generic_string().find("-tmp-") != std::string::npos ) {
            remove(direntry.path()) ;
        }

    }

}


std::string  trim(const std::string& input) {
    int pos1=0 ;
    while (input[pos1]==' ' && pos1<input.size()) {
        pos1++ ;
    }
    int pos2=input.size()-1 ;
    while (input[pos2]==' ' && pos2>=0) {
        pos2-- ;
    }


    std::string ret(input) ;
    if (pos1 < input.size()) {
        ret = input.substr(pos1 , pos2-pos1+1);
    }
    return ret ;



}

std::vector<std::string> split_string(std::string input, std::string delim) {
    std::__1::vector<std::string> ret;
    int begin_index = 0;
    while (true) {
        auto found_index = input.find_first_of(delim, begin_index);
        if (found_index == std::string::npos) {
            ret.push_back(input.substr(begin_index, input.size() - begin_index));
            break;
        }
        ret.push_back(input.substr(begin_index, found_index - begin_index));
        begin_index = found_index + 1;
    }
    return ret;

}