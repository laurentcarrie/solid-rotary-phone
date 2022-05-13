#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>


void write(std::ofstream &fout, const std::string &chord_name, const char letter, const std::string &font_name) {
    //std::cout
    fout
    << "\\newcommand\\chord" << chord_name << "{{"
         << "\\" << font_name << "\\selectfont "
         << letter << " ~ }}" << std::endl;
}

std::vector<std::pair<std::string, std::string>> data = {
        {"lolo", ""},
        {"loloflat", "b"},
        {"lolosharp", "s"},

};

int main(int argc, char **argv) {
    std::cout << "hello world" << std::endl;
    std::filesystem::path outfile(argv[1]);
    outfile = outfile / "chords.tex";
    std::cout << "writing to " << outfile << std::endl ;
    std::ofstream fout(outfile);
    for (auto d: data) {
        for (int i = 'A'; i < 'A' + 7; ++i) {
            char c = char(i) ;
            std::string chord_name = (c+d.second) ;
            write(fout,chord_name,c,d.first);
        }

        for (int i = 'A' ;i < 'A' +  7; ++i) {
            char c = char(i) ;
            std::string chord_name(c+std::string("m")+d.second) ;
            write(fout,chord_name,c+7,d.first);
        }

        for (int i = 'A' ;i < 'A' +  7; ++i) {
            char c = char(i) ;
            std::string chord_name(c+std::string("sept")+d.second) ;
            write(fout,chord_name,c+14,d.first);
        }

        for (int i = 'A' ;i < 'A' +  7; ++i) {
            char c = char(i) ;
            std::string chord_name(c+std::string("msept")+d.second) ;
            write(fout,chord_name,c+21,d.first);
        }
    }
}