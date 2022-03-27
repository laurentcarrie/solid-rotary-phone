//
// Created by laurent on 05/02/2022.
//
#include <algorithm>
#include <yaml-cpp/yaml.h>
#include <cassert>
#include <iostream>
#include <map>

#include "config.h"

namespace YAML {
    template<>
    struct convert<Cell> {
        static Node encode(Cell const &rhs) {
            assert(false);
            Node node;
            /*
            std::vector<qint16> newVec;
            newVec.push_back(rhs.first);
            newVec.push_back(rhs.second);
            node = newVec;
             */
            return node;
        }


        static bool decode(Node const &node, Cell &rhs) {
            // std::cout << "node : " << node << std::endl ;
            assert(node["row_start"]) ;
            unsigned int row_start = node["row_start"].as<unsigned int>();
            assert(node["row_end"]) ;
            unsigned int row_end = node["row_end"].as<unsigned int>();
            assert(node["col_start"]) ;
            unsigned int col_start = node["col_start"].as<unsigned int>();
            assert(node["col_end"]) ;
            unsigned int col_end = node["col_end"].as<unsigned int>();
            assert(node["what"]) ;
            std::string what = node["what"].as<std::string>();
            std::string background_color = "white" ;
            if ( node["background_color"]) {
                background_color = node["background_color"].as<std::string>() ;
            }
            rhs = {0,row_start,row_end,col_start,col_end, what, "",background_color};
            return true;
        }
    } ;

    template<>
    struct convert<Song> {
        static Node encode(Song const &rhs) {
            assert(false) ;
        }

        static bool decode(Node const &node,Song &rhs) {
            std::string spath(node.as<std::string>()) ;
            std::filesystem::path path(spath) ;
            rhs = {path};
            return true ;
        }
    };
}



Book read_book(std::filesystem::path p) {
    try {
        YAML::Node yaml = YAML::LoadFile(p);
        std::string name = yaml["name"].as<std::string>();
        std::vector<Song> songs = yaml["songs"].as<std::vector<Song>>();

        Book book{name, songs};
        return book;
    }
    catch (std::exception& e) {
        std::cout << "Error while reading " << p << std::endl << e.what() << std::endl ;
        throw(e) ;
    }
}




Config read_master(std::filesystem::path srcdir,std::string relpath,std::filesystem::path builddir,std::filesystem::path p) {
    try {
        YAML::Node yaml = YAML::LoadFile(p);
        unsigned int nb_rows = yaml["nb_rows"].as<unsigned int>();
        assert(yaml["nb_rows"]) ;
        unsigned int nb_cols = yaml["nb_cols"].as<unsigned int>();
        assert(yaml["cells"]) ;
        std::vector<Cell> cells = yaml["cells"].as<std::vector<Cell>>() ;
        for (unsigned int i=0;i<cells.size();++i) {
            cells[i].index = i ;
        }
        assert (yaml["title"]) ;
        std::string main_title = yaml["title"].as<std::string>();

        Config config{main_title, srcdir / "songs", builddir, relpath, nb_rows, nb_cols, cells};
        return config;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl ;
        std::cerr << "exception in yaml load of " << p << std::endl ;
        throw(e) ;
    }
}


Tag tag_of_name(std::string name) {
    for (unsigned int i=0;i<tags.size();++i) {
        if (tags[i] == name) {
            return static_cast<Tag>(i) ;
        }
    }
    throw std::runtime_error(std::string("tag not found : " )+name) ;
}
