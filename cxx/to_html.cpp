//
// Created by laurent on 05/02/2022.
//

#include "to_html.h"
#include "config.h"
#include "parse.h"
#include <iostream>
#include <cassert>
#include <regex>

std::string opening_tag(std::string tag) {
    return std::string("<")+tag+(">") ;
}

std::string closing_tag(std::string tag) {
    return std::string("</")+tag+(">") ;
}

void substitute_V(Item item,std::string& data) {
    data.replace(item.ending_, closing_tag(item.tag_).size(),"</div>") ;
    data.replace(item.starting_, opening_tag(item.tag_).size(),"<div class=\"verse\">") ;
    data = std::regex_replace(data,std::regex("\n"),"<br>") ;
}

void substitute_C(Item item,std::string& data) {
    data.replace(item.ending_, closing_tag(item.tag_).size(),"</div>") ;
    data.replace(item.starting_, opening_tag(item.tag_).size(),"<div class=\"chorus\">") ;
    data = std::regex_replace(data,std::regex("\n"),"<br>") ;
}

void substitute_T(Item item,std::string& data) {
    data.replace(item.ending_, closing_tag(item.tag_).size(),"</div>") ;
    data.replace(item.starting_, opening_tag(item.tag_).size(),"<div class=\"title\">") ;
}

void substitute_L(Item item,std::string& data) {
    data.replace(item.ending_, closing_tag(item.tag_).size(),"</div>") ;
    data.replace(item.starting_, opening_tag(item.tag_).size(),"<div class=\"lyrics\">") ;
}


std::string substitute_all_tags(std::string data) {

    int previous_length=1000 ;
    while (true) {
        std::vector<Item> items = parse(data) ;
        assert (items.size() < previous_length)  ;
        previous_length = items.size() ;
        if (items.empty()) break ;
        Item item = items.front() ;

        std::cout << "substitute " << item.starting_ << " -> " << item.ending_ << std::endl ;

        Tag etag = tag_of_name((item.tag_)) ;
        switch (etag) {
            case V:
                substitute_V(item,data) ;
                break ;
            case C:
                substitute_C(item,data) ;
                break ;
            case T:
                substitute_T(item,data) ;
                break ;
            case L:
                substitute_L(item,data) ;
                break ;
            default:
                throw std::runtime_error(std::string("case not managed : ")+item.tag_) ;
        }
    }

    return data ;


}


std::stringstream to_html(Config config) {

    std::stringstream oss;
    oss << R"here(
<html>
<head>
<style>

.wrapper {
	background-color: #ffffff;
	border: 10px solid #00ffff;
grid-column-gap: 30px;
grid-row-gap: 30px;
  display: grid;
  grid-template-columns: )here";

    for (auto i: config.cols) {
        oss << i << "cm ";
    }

    oss << R"here( ;
}

</style>
<link rel="stylesheet" href="style.css">
</head>
<body>


    )here";

    oss << "<div class=\"wrapper\">" << std::endl;
    for (unsigned int irow = 0; irow < config.rows; irow++) {
        for (unsigned int icol = 0; icol < config.cols.size(); icol++) {
            bool found = false;
            for (auto c: config.cells) {
                // std::cout << "loop " << c.what << std::endl ;
                if (c.irow != irow + 1) continue;
                if (c.icol != icol + 1) continue;
                found = true;
                oss << "<div>" << substitute_all_tags(c.data) << "</div>" << std::endl ;
            }
            if (!found) {
                oss << "<div>" << irow * config.cols.size() + icol << "</div>" << std::endl;
            }
        }
    }
    oss << "</div>" << std::endl;





//    oss << input ;

    oss << "</body></html>" << std::endl;

    return oss;

}

