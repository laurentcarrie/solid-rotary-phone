//
// Created by laurent on 12/03/2022.
//

#include <iostream>
#include <cassert>
#include <regex>
#include <array>
#include <fstream>
#include "to_html.h"
#include "config.h"
#include "parse.h"

void generate_png_ly(const Config& config,const std::string& stem,bool with_rhythm,bool with_chords,bool with_lyrics) {

    // @todo fix
    with_lyrics = false ;

    std::cout << "stem : " << stem << std::endl ;
    std::filesystem::path lypath = config.srcdir / config.relpath / stem ;
    lypath.replace_extension(".ly") ;
    std::cout << lypath << std::endl ;
    if ( ! std::filesystem::exists(lypath)) {
        throw std::runtime_error(std::string("no such path : ")+lypath.generic_string()) ;
    }
    std::filesystem::path target = config.builddir / config.relpath / (stem+"_image") ;
    target.replace_extension(".ly") ;
    std::ofstream fout (target) ;
    fout << "\\version \"2.22.1\"" << std::endl ;
    fout << "\\include \"../../macros/macros.ly\"" << std::endl ;
    fout << "\\include " << lypath << std::endl ;

    fout << R"here(
    \paper {
      #(include-special-characters)
      indent = 0\mm
      line-width = 210\mm
      oddHeaderMarkup = ""
      evenHeaderMarkup = ""
      oddFooterMarkup = ""
      evenFooterMarkup = ""

      #(add-text-replacements!
        '(
           ("100" . "hundred")
           ("dpi" . "dots per inch")
           ))

    }

    \score {
            <<
)here" ;

    if (with_chords) {
        fout << R"here(
        \new ChordNames {
            \set chordChanges = ##t
            \song_chords
        }
        )here";
    }

    fout << R"here(
                \new TabStaff {
                    \tempo 4 = \song_tempo
                    \tabFullNotation
                    \override Score.BarNumber.break-visibility = ##(#t #t #t)
                    \lead

                }
)here" ;

    // @todo : fix this
    with_lyrics=false ;
    if (with_lyrics) {
        fout << R"here(
        \new Staff {
            \new Voice = "one" {
                \song_voice
            }
        }
        \new Lyrics {
            \lyricsto "one" { \song_lyrics }
        }
)here" ;
    }

    if (with_rhythm) {
        fout << R"here(
                \new TabStaff {
                    \tempo 4 = \song_tempo
                    \tabFullNotation
                    \override Score.BarNumber.break-visibility = ##(#t #t #t)
                    \rhythm
                }
)here" ;
        }
    fout << R"here(
            >>

            \layout {}
    }
 )here" ;

}

void generate_midi_ly(const Config& config, const std::string& stem) {
    std::cout << "stem : " << stem << std::endl ;
    std::filesystem::path lypath = config.srcdir / config.relpath / stem ;
    lypath.replace_extension(".ly") ;
    std::cout << lypath << std::endl ;
    if ( ! std::filesystem::exists(lypath)) {
        throw std::runtime_error(std::string("no such path : ")+lypath.generic_string()) ;
    }
    std::filesystem::path target = config.builddir / config.relpath / (stem+"_midi") ;
    target.replace_extension(".ly") ;
    std::ofstream fout (target) ;
    fout << "\\version \"2.22.1\"" << std::endl ;
    fout << "\\include \"../../macros/macros.ly\"" << std::endl ;
    fout << "\\include " << lypath << std::endl ;
    fout << R"here(
    \score {
        \unfoldRepeats {
        <<
            \new DrumStaff
                \tempo 4 = \song_tempo
                <<
                    \new DrumVoice {  \drumbarshh }
                    \new DrumVoice {  \drumbars }
                >>

            \new Staff {
                  \rhythm
                  \set Staff.midiMinimumVolume = #0.2
                  \set Staff.midiMaximumVolume = #0.2
                  %\set Staff.midiInstrument = "electric guitar (clean)"
                  \set Staff.midiInstrument = "bass"
                  %\set Staff.midiInstrument = "clarinet"
            }
            \new Staff {
                  \lead
                  \set Staff.midiMinimumVolume = #0.9
                  \set Staff.midiMaximumVolume = #0.9
                  \set Staff.midiInstrument = "electric guitar (clean)"
            }
            %\new Staff {
            %      \song_voice
            %      \set Staff.midiMinimumVolume = #0.9
            %      \set Staff.midiMaximumVolume = #0.9
            %      \set Staff.midiInstrument = "electric guitar (clean)"
            %}
        >>
        }

       \midi {
            \tempo 4 = \song_tempo
      }
    }
 )here" ;

}