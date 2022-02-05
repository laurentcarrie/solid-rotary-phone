//
// Created by laurent on 05/02/2022.
//

#include <map>
#include "parse.h"
#include <string>
#include <iostream>
#include <list>
#include <cassert>
#include <algorithm>
#include <sstream>

std::vector<std::string> tags = {"V", "C", "T"};

struct tag_position {
    int pos_;
    bool opening_;
    std::string tag_;
    int pos_closing_;
};

bool myCompare(const tag_position &pos1, const tag_position &pos2) {
    return pos1.pos_ < pos2.pos_;
}

std::list<int> find(std::string input, std::string tag) {
    std::list<int> ret;
    for (size_t pos = 0;;) {
        size_t pos2 = input.find(tag, pos);
        if (pos2 == std::string::npos) {
            break;
        }
        ret.push_back(pos2);
        pos = pos2 + 1;
    }
    return ret;
}

std::vector<std::pair<int, bool>> find_tags(std::string input, std::string tag) {
    std::list<int> opening = find(input, std::string("<") + tag + ">");
    std::list<int> closing = find(input, std::string("</") + tag + ">");
    std::vector<std::pair<int, bool>> ret;
    for (;;) {
        if (opening.empty() && closing.empty()) {
            break;
        }
        if (closing.empty()) {
            throw std::runtime_error(std::string("missing closing for " + tag));
        }
        if (opening.empty()) {
            int c = closing.front();
            closing.pop_front();
            ret.push_back(std::make_pair(c, false));
            continue;
        }
        int o = opening.front();
        int c = closing.front();
        if (o < c) {
            opening.pop_front();
            ret.push_back(std::make_pair(o, true));
        } else {
            closing.pop_front();
            ret.push_back(std::make_pair(c, false));
        }
    }
    return ret;
}


std::vector<Item> parse(std::string input) {

    std::map<std::string, std::vector<std::pair<int, bool>>> positions;

    for (auto tag: tags) {
        std::vector<std::pair<int, bool>> ppp = find_tags(input, tag);
        positions[tag] = ppp;
    }

    std::vector<tag_position> nesting_vector;

    for (auto tag: tags) {
        int level = 0;
        for (auto pair: positions[tag]) {
            std::cout << tag << " : " << pair.first << " => " << pair.second << std::endl;
            nesting_vector.push_back({pair.first, pair.second, tag, -1});
            if (pair.second) {
                level++;
            } else {
                level--;
            }
        }
        if (level != 0) {
            throw std::runtime_error(std::string("bad nesting for tag ") + tag);
        }
    }

    std::sort(nesting_vector.begin(), nesting_vector.end(), myCompare);

    for (auto i: nesting_vector) {
        std::cout << i.pos_ << " : " << i.opening_ << " ; " << i.tag_ << std::endl;
    }


    for (unsigned int i = 0; i < nesting_vector.size() - 1; i++) {
        tag_position &current = nesting_vector[i];
        const tag_position &next = nesting_vector[i + 1];
        if (current.opening_ and !next.opening_) {
            // current est une ouverture et next une fermeture, ce doit etre pour la meme balise
            if (current.tag_ != next.tag_) {
                std::ostringstream oss;
                oss << "position " << current.pos_ << " sees opening tag " << current.tag_
                    << ", but at next position " << next.pos_ << " there is closing tag " << next.tag_;
                throw std::runtime_error(oss.str());

            }
        }

        if (current.opening_) {

            for (unsigned int j = i + 1; j < nesting_vector.size(); j++) {
                const tag_position &closing = nesting_vector[j];
                if (closing.opening_) continue;
                if (closing.tag_ != current.tag_) continue;
                current.pos_closing_ = closing.pos_;
                break;
            }
        }

    }

    for (auto i: nesting_vector) {
        std::cout << i.pos_ << " : " << i.opening_ << " ; " << i.tag_ << " ( to " << i.pos_closing_ << " )"
                  << std::endl;
    }

    std::vector<Item> ret ;
    for (auto i: nesting_vector) {
        if ( ! i.opening_) continue ;
        ret.push_back({i.tag_,i.pos_,i.pos_closing_}) ;

    }


    return ret ;


}