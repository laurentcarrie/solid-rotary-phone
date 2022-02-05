//
// Created by laurent on 05/02/2022.
//

#ifndef SOLID_ROTARY_PHONE_PARSE_H
#define SOLID_ROTARY_PHONE_PARSE_H

#include <string>
#include <vector>

class Item {

public:
    std::string tag_ ;
    // std::string value_ ;
    int starting_ ;
    int ending_ ;

};


std::vector<Item> parse(std::string) ;

#endif //SOLID_ROTARY_PHONE_PARSE_H
