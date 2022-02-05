//
// Created by laurent on 05/02/2022.
//

#ifndef SOLID_ROTARY_PHONE_CONFIG_H
#define SOLID_ROTARY_PHONE_CONFIG_H

#include <string>
#include <vector>
#include <filesystem>

class Cell {
public:
    unsigned int irow;
    unsigned int icol;
    std::string what;
    std::string data;
};

class Config {
public:
    unsigned int rows;
    std::vector<unsigned int> cols;
    std::vector<Cell> cells;
};

Config read_master(std::filesystem::path p) ;


enum Tag {
    V=0,C,T,L
};

static std::vector<std::string> tags = {"V", "C", "T","L"};

Tag tag_of_name(std::string name) ;


#endif //SOLID_ROTARY_PHONE_CONFIG_H
