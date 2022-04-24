#include <string>
#include "cell.h"
#include "util.h"
#include <vector>
#include <optional>
#include <iostream>

namespace songs {

    struct Chord {
        enum color {
            major, minor, minor7, major7, M7, Mm5
        };
        enum alter {
            none,flat,sharp
        };
        char note_ ; /* A to G */
        alter alter_ ;
        color color_ ;
        Chord(char n,alter a,color c) : note_(n),alter_(a),color_(c) {
            if (c>1) {
                std::cout << "color " << c << std::endl;
            }
        } ;
    private:
        Chord() ;
    };

    struct Rest {
        int duration_ ;
    };

    struct Repeat {
        int count_ ;
        Repeat(int count) : count_(count) {}
    private:
        Repeat() ;
    };

    struct Symbol {
        enum t {
            eChord,eRest,eRepeat
        };
        t t_ ;
        std::optional<Chord> chord_ ;
        std::optional<Rest> rest_ ;
        std::optional<Repeat> repeat_ ;
        Symbol(const Chord&c) : t_(eChord),chord_(c) {}
        Symbol(const Rest&c) : t_(eRest),rest_(c) {}
        Symbol(const Repeat&c) : t_(eRepeat),repeat_(c) {}

    };

    struct Glyph {
        char c_ ;
        std::string class_ ;
    };

    Glyph glyph_of_chord(const Chord& chord) {
        char note =0 ;
        switch (chord.color_) {
            case Chord::major:
                note = chord.note_ ;
                break ;
            case Chord::minor:
                note = char(int(chord.note_) + 7) ; break ;
            case Chord::major7:
                note = char(int(chord.note_) + 14) ; break ;
            default:
                throw std::runtime_error(std::string(__FILE__)+":"+std::to_string(__LINE__)+" NOT IMPLEMENTED") ;
        }
        std::string klass = [&chord]() {
            switch (chord.alter_) {
                case Chord::none:
                    return "grid_chord";
                case Chord::flat:
                    return "grid_chord_flat";
                case Chord::sharp:
                    return "grid_chord_sharp";
                default:
                    assert(false);
            }
        }() ;
        return Glyph{note,klass} ;
    }

    Glyph glyph_of_rest(const Rest& rest) {
        return Glyph{'A',"grid_chord"} ;
    }

    Glyph glyph_of_repeat(const Repeat& repeat) {
        return Glyph{char(repeat.count_+'2'-2),"grid_chord"} ;
    }

    Glyph glyph_of_symbol(const Symbol&s) {
        switch (s.t_) {
            case Symbol::eChord : {
                Glyph g = glyph_of_chord(s.chord_.value());
                return g;
            }
            case Symbol::eRest : return glyph_of_rest(s.rest_.value()) ;
            case Symbol::eRepeat : return glyph_of_repeat(s.repeat_.value()) ;
            default:
                assert(false) ;
        }
    }

    Chord chord_of_input(const std::string& input) {
        std::string buf(input) ;
        char note=buf[0] ;
        buf=buf.substr(1,size(input)-1) ;
        Chord::alter alter ;

        switch (buf[0]) {
            case 'b' :
                alter=Chord::flat ;
                buf=buf.substr(1,size(input)-1) ;
                break ;
            case '#' :
                alter=Chord::sharp ;
                buf=buf.substr(1,size(input)-1) ;
                break ;
            default:
                alter=Chord::none ;
                break ;

        }

        Chord::color color ;
        if (buf=="") {
            color = Chord::major ;
        }
        else if (buf=="m") {
            color = Chord::minor ;
        }
        else if (buf=="7") {
            color = Chord::major7 ;
        }
        else {
            throw std::runtime_error(std::string(__FILE__)+":"+std::to_string(__LINE__)+" : NOT IMPLEMENTED : "+input) ;
        }
        return Chord {note,alter,color} ;
    }
    Rest rest_of_input(const std::string& input) {
        return Rest {} ;
    }
    Repeat repeat_of_input(const std::string& input) {
        int count ;
        try {
            count = std::atoi(input.substr(1,size(input)-1).c_str()) ;
        }
        catch (std::exception& e) {
            std::cout << e.what() << " " << input << std::endl;
            throw(e) ;
        }
        return Repeat (count) ;
    }


    const Symbol& symbol_of_input(const std::string& input) {
        if (input[0]=='r') {
            return Symbol(rest_of_input(input)) ;
        }
        else if (input[0]=='x') {
            return Symbol(repeat_of_input(input)) ;
        }
        else if (input[0]>='A' && input[0]<='G') {
            return Symbol(chord_of_input(input)) ;
        }
        else {
            throw std::runtime_error(std::string(__FILE__) + ":" +
            std::to_string(__LINE__)+"\nbad input : '"+input+"'") ;
        }
    }


    std::string glyph_of_one_chord(const std::string &input) {
        auto symbol = symbol_of_input(input) ;
        auto glyph = glyph_of_symbol(symbol) ;
            return std::string("<span class=\"") + glyph.class_ +
                   "\">" + std::string(1,glyph.c_) +
                   "</span>";
    }


    std::vector<std::string> glyphs_of_cell(const std::string &cell) {

        std::vector<std::string> v = split_string(cell, " ");

        std::vector<std::string> ret;
        for (auto c: v) {
            if (c!="") {
                ret.push_back(songs::glyph_of_one_chord(c));
            }
        }

        return ret;
    }

}