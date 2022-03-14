//
// Created by laurent on 05/02/2022.
//

#ifndef SOLID_ROTARY_PHONE_CONFIG_H
#define SOLID_ROTARY_PHONE_CONFIG_H

#include <string>
#include <vector>
#include <optional>
#include <filesystem>

class Cell {
public:
    unsigned int index ;
    unsigned int row_start;
    unsigned int row_end;
    unsigned int col_start;
    unsigned int col_end;
    std::string what;
    std::string data;
    std::optional<std::string> background_color ;
};

class Config {
public:
    std::string main_title ;
    std::filesystem::path srcdir ;
    std::filesystem::path builddir ;
    std::string relpath ;
    unsigned int nb_rows;
    unsigned int nb_cols;
    std::vector<Cell> cells;
};

Config read_master(std::filesystem::path srcdir,std::string relpath,std::filesystem::path builddir,std::filesystem::path p) ;


enum Tag {
    V=0,C,T,L,G,LY,LY_C,LY_R,LY_RC,LY_WAV,N
};

static std::vector<std::string> tags = {"V", "C", "T","L","G","LY","LY_C","LY_R","LY_RC","LY_WAV","N"};

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