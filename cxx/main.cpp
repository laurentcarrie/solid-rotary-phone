#include <iostream>

#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <filesystem>
#include <cassert>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include "parse.h"
// #include <yaml-cpp/node/node.h>
// #include <yaml-cpp/node/parse.h>

#include "config.h"
#include "to_html.h"
#include "util.h"


std::string read_datafile(std::filesystem::path rootdir, std::string prefix) {
    std::filesystem::path filepath = rootdir / (prefix );
    std::ifstream fin(filepath);
    std::stringstream sss;
    if (std::filesystem::exists(filepath)) {
        sss << fin.rdbuf();
    } else {
        std::cout << "no " << filepath << std::endl;
        sss << "no " << filepath << std::endl;
    }
    return sss.str();
};


std::filesystem::path make_song(std::filesystem::path srcdir, std::string rel_path, std::filesystem::path builddir) {
    std::filesystem::create_directories(builddir / rel_path);
    std::filesystem::path master_file = srcdir / "songs" / rel_path / "master.yml";
    if (!std::filesystem::exists(master_file)) {
        throw std::runtime_error(std::string("no such file : ") + std::string(master_file));
    }
    auto config = read_master(srcdir,rel_path,builddir,master_file);


    for (std::vector<Cell>::iterator iter = config.cells.begin(); iter != config.cells.end(); ++iter) {
        std::string data = read_datafile(srcdir / "songs" / rel_path, iter->what);
        parse(data);
        (*iter).data = data;
    }

    std::filesystem::path result(builddir / rel_path / "out.html");

    {
        std::cout << "writing file " << result << std::endl;
        std::filesystem::create_directories(builddir);
        std::ofstream fout(result);
        if (!fout.is_open()) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__ << ", could not open file for writing " << result << std::endl;
            throw std::runtime_error(oss.str());
        }
        fout << to_html(config).rdbuf();
    }

    {
        std::filesystem::path result(builddir / rel_path / "local.css");
        std::cout << "writing file " << result << std::endl;
        std::filesystem::create_directories(builddir);
        std::ofstream fout(result);
        if (!fout.is_open()) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__ << ", could not open file for writing " << result << std::endl;
            throw std::runtime_error(oss.str());
        }
        write_local_css(config,  fout) ;
    }

    return result;
}


void make_book(std::filesystem::path srcdir, std::filesystem::path book_path, std::filesystem::path builddir) {
    auto book = read_book(book_path);

    for (std::vector<Song>::iterator iter = book.songs_.begin(); iter != book.songs_.end(); ++iter) {
        auto song = make_song(srcdir, iter->path_, builddir);
    }

}


void mount_files(std::filesystem::path srcdir,std::filesystem::path builddir) {
    std::function<std::string(std::string)> f = [srcdir,builddir](std::string name) {
        std::filesystem::path to = builddir / name ;
        std::filesystem::create_directories(to.parent_path());
        std::filesystem::path from = srcdir / name ;
        std::filesystem::copy_file(from, to, std::filesystem::copy_options::overwrite_existing);
        return "" ;
    };
    std::vector<std::string> names {"style/style.css","style/print.css","macros/macros.ly","style/lolo.ttf"};

    std::transform(names.begin(),names.end(),names.begin(),f) ;
}



int main(int argc, char **argv) {
    try {
        assert(argc > 3);

        std::cout << "Hello, World!" << std::endl;
        std::filesystem::path builddir = std::filesystem::path(argv[2]);
        std::filesystem::path srcdir = std::filesystem::path(argv[1]);
        std::string book_name(argv[3]);

        std::filesystem::path book = srcdir / "books" / (book_name+".yml") ;
        // assert(std::filesystem::exists(book)) ;


        mount_files(srcdir,builddir);
        make_book(srcdir, book, builddir);
        clean_files(builddir);


        // make_song(rootdir,builddir) ;
    }
    catch (std::exception &e) {
        std::cout << "exception caught... " << e.what();
        return 1;
    }

    std::cout << "done." << std::endl;


    return 0;
}
