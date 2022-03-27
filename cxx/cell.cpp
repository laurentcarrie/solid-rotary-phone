#include <string>
#include "cell.h"
#include "util.h"
#include <vector>

namespace songs {

    enum Note_e {
        regular, flat, sharp, rest
    };

    enum Chord_e {
        major, minor, minor7, major7, M7, Mm5
    };

    int offset_in_font(Chord_e e) {
        switch (e) {
            case major:
                // @todo : implement power chords
            case Mm5:
                return 0;
            case minor:
                return 7;
            case major7:
                return 14;
            case minor7:
                return 21;
            case M7:
                return 28;
            default:
                throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + "\nnot implemented");

        }
    }

    std::string font_of_alteration(Note_e note_e) {
        switch (note_e) {
            case flat:
                return "grid_chord_flat";
            case sharp:
                return "grid_chord_sharp";
            case rest:
                return "grid_chord_sharp";
            case regular :
                return "grid_chord";
            default:
                throw std::runtime_error(
                        std::string(__FILE__) + ":" + std::to_string(__LINE__) + "\nNOT implemented'");
        }
    }


    std::string glyph_of_one_chord(const std::string &chord) {
        std::string input = chord;
        if (chord.length()==0) {
            return "" ;
        }
        assert(chord.size() > 0);
        char note = input[0];
        input = input.substr(1, input.length() - 1);

        auto note_e = regular;
        auto chord_e = major;


        if ((note < 'A' || note > 'G') && (note != 'r')) {
            throw std::runtime_error(
                    std::string(__FILE__) + ":" + std::to_string(__LINE__) + "\nno such note '" + std::string(1, note) +
                    "'");

        }


        if (input.length() > 0) {
            if (input[0] == 'b') {
                input = input.substr(1, input.size() - 1);
                note_e = flat;
            }
            if (input[0] == '#') {
                input = input.substr(1, input.size() - 1);
                note_e = sharp;
            }
            if (input[0] == 'm') {
                input = input.substr(1, input.size() - 1);
                chord_e = minor;
            }
        }

        if (input.length() > 0) {
            if (input[0] == '7') {
                input = input.substr(1, input.size() - 1);
                switch (chord_e) {
                    case major:
                        chord_e = major7;
                        break;
                    case minor:
                        chord_e = minor7;
                        break;
                    default:
                        throw std::runtime_error(
                                std::string(__FILE__) + ":" + std::to_string(__LINE__) + "\nlogic error '" + chord);
                }
            }
            if (input[0] == '5') {
                input = input.substr(1, input.size() - 1);
                switch (chord_e) {
                    case major:
                        chord_e = Mm5;
                        break;
                    default:
                        throw std::runtime_error(
                                std::string(__FILE__) + ":" + std::to_string(__LINE__) + "\nlogic error '" + chord);
                }
            }
        }
        if (input.length() > 0) {
            if (input[0] == 'M') {
                input = input.substr(1, input.size() - 1);
                switch (chord_e) {
                    case major:
                        chord_e = M7;
                        break;
                    default:
                        throw std::runtime_error(
                                std::string(__FILE__) + ":" + std::to_string(__LINE__) + "\nlogic error '" + chord);
                }
            }
        }

        if (note == 'r') {
            // parce que la glyphe de rest est là
            note_e = rest;

        }


        if (input.size() == 0) {
            return std::string("<span class=\"") + font_of_alteration(note_e) +
                   "\">" + std::string(1, note +
                                          offset_in_font(chord_e)) +
                   "</span>";
        }


        throw std::runtime_error(
                std::string(__FILE__) + ":" + std::to_string(__LINE__) + "\nNOT implemented for '" + chord + "'");

    }

    std::string glyphs_of_cell(const std::string &cell) {

        std::vector<std::string> v = split_string(cell, " ");

        std::string ret;
        for (auto c: v) {
            ret += glyph_of_one_chord(c);
        }

        return ret;
    }
}