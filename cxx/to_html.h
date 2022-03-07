//
// Created by laurent on 05/02/2022.
//

#ifndef SOLID_ROTARY_PHONE_TO_HTML_H
#define SOLID_ROTARY_PHONE_TO_HTML_H


#include <sstream>
class Config ;

std::stringstream to_html(Config config) ;
void write_local_css(Config config,std::ostream& fout) ;

#endif //SOLID_ROTARY_PHONE_TO_HTML_H
