//
// Created by laurent on 05/02/2022.
//

#ifndef SOLID_ROTARY_PHONE_TO_HTML_H
#define SOLID_ROTARY_PHONE_TO_HTML_H


#include <sstream>
class Config ;

std::stringstream to_html(Config config) ;
void write_local_css(Config config,std::ostream& fout) ;
void generate_png_ly(const Config& config,const std::string& stem,bool with_rhythm) ;
void generate_midi_ly(const Config& config,const std::string& stem) ;

#endif //SOLID_ROTARY_PHONE_TO_HTML_H
