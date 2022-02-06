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

std::vector<std::string> split_string(std::string input,std::string delim) {
    std::vector<std::string> ret ;
    int begin_index = 0 ;
    while(true) {
        auto found_index = input.find_first_of(delim, begin_index) ;
        if ( found_index == std::string::npos ) {
            ret.push_back(input.substr(begin_index,input.size()-begin_index)) ;
            break ;
        }
        ret.push_back(input.substr(begin_index,found_index-begin_index)) ;
        begin_index = found_index+1 ;
    }
    return ret ;

}

std::string get_string_between_tags(std::string input,Item item) {
    std::string gdata = input.substr(item.starting_+2+item.tag_.size(),item.ending_-item.starting_-2-item.tag_.size()) ;
    return gdata ;
}

void replace_string_between_tags(std::string& input,std::string replacement,Item item) {
    input.replace(item.starting_,item.ending_-item.starting_+item.tag_.size()+3,replacement) ;
}


void substitute_V(Item item,std::string& input) {
    std::string data = get_string_between_tags(input,item) ;
    std::vector<std::string> lines = split_string(data,"\n") ;
    std::ostringstream oss ;
    oss << "<div class=\"verse\">" << std::endl ;
    for ( auto line : lines ) {
        if (!line.empty()) {
            oss << line << " <br>" << std::endl;
        }
    }
    oss << "</div>" << std::endl ;
    replace_string_between_tags(input,oss.str(),item) ;
}

void substitute_C(Item item,std::string& input) {
    std::string data = get_string_between_tags(input,item) ;
    std::vector<std::string> lines = split_string(data,"\n") ;
    std::ostringstream oss ;
    oss << "<div class=\"chorus\">" << std::endl ;
    for ( auto line : lines ) {
        if (!line.empty()) {
            oss << line << " <br>" << std::endl;
        }
    }
    oss << "</div>" << std::endl ;
    replace_string_between_tags(input,oss.str(),item) ;
}

void substitute_T(Item item,std::string& input) {
    input.replace(item.ending_, closing_tag(item.tag_).size(), "</div>") ;
    input.replace(item.starting_, opening_tag(item.tag_).size(), "<div class=\"title\">") ;
}

void substitute_L(Item item,std::string& input) {
    input.replace(item.ending_, closing_tag(item.tag_).size(), "</div>") ;
    input.replace(item.starting_, opening_tag(item.tag_).size(), "<div class=\"lyrics\">") ;
}

void substitute_G(Item item,std::string& input) {
    std::string gdata = get_string_between_tags(input, item) ;
    // data.replace(item.ending_, closing_tag(item.tag_).size(),"</table></div>") ;
    // data.replace(item.starting_, opening_tag(item.tag_).size(),"<div><table class=\"redtable\">") ;
    // data = std::regex_replace(data,std::regex("#"),"&#x266F;") ;
    std::vector<std::string> lines = split_string(gdata,"\n") ;
    std::ostringstream oss ;
    oss << "<div><table class=\"redtable\">" << std::endl ;
    for ( auto line : lines ) {
        oss << "<tr>" ;
        std::vector<std::string> cells = split_string(line,"|") ;
        for ( auto cell : cells ) {
            oss << "<td><div style=\"width: 50px\" >" << cell << "</div></td>" ;
        }
        oss << "</tr>" << std::endl ;
    }
    oss << "</table></div>" ;

    // data.replace(item.starting_,item.ending_-item.starting_+std::string("</G>").size(),oss.str()) ;
    replace_string_between_tags(input, oss.str(), item) ;
    // data = std::regex_replace(data,std::regex("#"),"&#x266F;") ;
    // std::cout << input << std::endl ;

}


std::string substitute_all_tags(std::string data) {

    int previous_length=1000 ;
    while (true) {
        std::vector<Item> items = parse(data) ;
        assert (items.size() < previous_length)  ;
        previous_length = items.size() ;
        if (items.empty()) break ;
        Item item = items.front() ;

        // std::cout << "substitute " << item.starting_ << " -> " << item.ending_ << std::endl ;

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
            case G:
                substitute_G(item,data) ;
                break ;
            default:
                throw std::runtime_error(std::string("case not managed : ")+item.tag_) ;
        }
    }
    // data = std::regex_replace(data,std::regex("<br>"),"<br>\n") ;
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
	border: 1px solid #00ffff;
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

