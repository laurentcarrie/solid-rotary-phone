#include <string>
#include "cell.h"



std::pair<std::string,std::string> style_and_glyph_of_chord(const std::string& chord) {
    std::string input = chord ;
    assert(chord.size()>0) ;
    char note= input[0] ;
    bool is_flat=false ;
    bool is_sharp=false ;
    input = input.substr(1,input.length()-1) ;
    if (input[0] == 'b') {
        input = input.substr(1,input.size()-1) ;
        is_flat=true ;
    }
    if (input[0] == 's') {
        input = input.substr(1,input.size()-1) ;
        is_sharp=true ;
    }
    if (input[0] == 'm') {
        note += 7 ;
        input = input.substr(1,input.size()-1) ;
    }

    if ( input.size()==0) {
        return std::make_pair("grid_chord_major",std::string(1,note)) ;
    }



    throw std::runtime_error("NOT implemented for '" + chord +"'") ;

}
