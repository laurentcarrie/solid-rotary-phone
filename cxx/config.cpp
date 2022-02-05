//
// Created by laurent on 05/02/2022.
//
#include <algorithm>
#include <yaml-cpp/yaml.h>
#include <cassert>

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
            unsigned int irow = node["row"].as<unsigned int>();
            unsigned int icol = node["col"].as<unsigned int>();
            std::string what = node["what"].as<std::string>();
            rhs = {irow, icol, what,""} ;
            return true;
        }
    };
}





Config read_master(std::filesystem::path p) {
    YAML::Node yaml = YAML::LoadFile(p);
    unsigned int rows = yaml["rows"].as<unsigned int>();
    std::vector<unsigned int> cols = yaml["cols"].as<std::vector<unsigned int>>();
    std::vector<Cell> cells = yaml["cells"].as<std::vector<Cell>>();

    Config config{rows, cols, cells};
    return config;
}


Tag tag_of_name(std::string name) {
    for (unsigned int i=0;i<tags.size();++i) {
        if (tags[i] == name) {
            return static_cast<Tag>(i) ;
        }
    }
    throw std::runtime_error(std::string("tag not found : " )+name) ;
}
