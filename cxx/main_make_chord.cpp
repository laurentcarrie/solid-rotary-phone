#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <functional>

// static int fontsize = 20 ;
// static int fontinterline = 20 ;



void write(std::ofstream &fout, const std::string &chord_name, const char letter, const std::string &font_name,int fontsize,int fontinterline) {
    //std::cout
    fout
    << "\\newcommand\\chord" << chord_name << "{{"

         << "\\" << font_name << "\\fontsize{" << fontsize << "pt}{" << fontinterline << "pt}\\selectfont "
         << letter << " ~ }}" << std::endl;
}

std::vector<std::pair<std::string, std::string>> data = {
        {"lolo", ""},
        {"loloflat", "f"},
        {"lolosharp", "s"},

};

int main(int argc, char **argv) {
    try {
        std::cout << "hello world" << std::endl;
        if (argc < 2) {
            throw std::runtime_error("first argument should be the path where to generate file 'chords.tex'");
        }
        std::filesystem::path outfile(argv[1]);
        outfile = outfile / "chords.tex";
        std::cout << "writing to " << outfile << std::endl;
        std::ofstream fout(outfile);
        fout << "% this file was generated with command " << argv[0] << " " << argv[1] << std::endl;

        int fontsize = 30 ;
        int fontinterline = 30 ;

        std::function<void(const std::string &chord_name, const char letter, const std::string &font_name)> write2
        = [&fout,&fontsize,&fontinterline](const std::string &chord_name, const char letter, const std::string &font_name) {
            write(fout,chord_name,letter,font_name,fontsize,fontinterline) ;
        };

        for (auto d: data) {
            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name = (c + d.second);
                write2(chord_name, c, d.first);
            }

            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name(c + d.second + std::string("m"));
                write2( chord_name, c + 7, d.first);
            }

            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name(c + d.second + std::string("sept"));
                write2( chord_name, c + 14, d.first);
            }

            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name(c + std::string("msept") + d.second);
                write2( chord_name, c + 21, d.first);
            }

            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name(c + std::string("septM") + d.second);
                write2( chord_name, 'c' - 'A' + i, d.first);
            }

        }

        write2("ERest", 'q', "lolosharp");
        write2( "QRest", 'r', "lolosharp");
        write2( "HRest", 's', "lolosharp");
        write2( "QHRest", 't', "lolosharp");

        fontsize=20 ;
        fontinterline=24 ;
        write2("RepeatDeux", '2', "lolo");
        write2("RepeatTrois", '3', "lolo");
        if (! fout.good() ) {
            throw std::runtime_error("fout is not good") ;
        }
        std::cout << "done." << std::endl ;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl ;
        std::cout << "failed" << std::endl ;
        exit(1) ;
    }

}