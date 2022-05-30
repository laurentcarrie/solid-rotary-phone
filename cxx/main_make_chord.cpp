#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>


static int fontsize = 20 ;
static int fontinterline = 20 ;



void write(std::ofstream &fout, const std::string &chord_name, const char letter, const std::string &font_name) {
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
        for (auto d: data) {
            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name = (c + d.second);
                write(fout, chord_name, c, d.first);
            }

            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name(c + d.second + std::string("m"));
                write(fout, chord_name, c + 7, d.first);
            }

            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name(c + d.second + std::string("sept"));
                write(fout, chord_name, c + 14, d.first);
            }

            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name(c + std::string("msept") + d.second);
                write(fout, chord_name, c + 21, d.first);
            }

            for (int i = 'A'; i < 'A' + 7; ++i) {
                char c = char(i);
                std::string chord_name(c + std::string("septM") + d.second);
                write(fout, chord_name, 'c' - 'A' + i, d.first);
            }

        }

        write(fout, "ERest", 'q', "lolosharp");
        write(fout, "QRest", 'r', "lolosharp");
        write(fout, "HRest", 's', "lolosharp");
        write(fout, "QHRest", 't', "lolosharp");
        write(fout, "RepeatDeux", '2', "lolo");
        write(fout, "RepeatTrois", '3', "lolo");
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