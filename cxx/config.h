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
    std::string main_title ;
    std::filesystem::path srcdir ;
    std::filesystem::path builddir ;
    std::string relpath ;
    unsigned int rows;
    std::vector<unsigned int> cols;
    std::vector<Cell> cells;
};

Config read_master(std::filesystem::path srcdir,std::string relpath,std::filesystem::path builddir,std::filesystem::path p) ;


enum Tag {
    V=0,C,T,L,G,LY,LY_WAV
};

static std::vector<std::string> tags = {"V", "C", "T","L","G","LY","LY_WAV"};

Tag tag_of_name(std::string name) ;


class Song {
public:
    std::filesystem::path path_ ;
};

class Book {
public:
    std::string name_ ;
    std::vector<Song> songs_ ;
};

Book read_book(std::filesystem::path) ;

#endif //SOLID_ROTARY_PHONE_CONFIG_H

//