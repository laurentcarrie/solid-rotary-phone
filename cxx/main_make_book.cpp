#include <cassert>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>
#include <fstream>
#include <optional>

std::string exec(const char *cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


void scan_lilypond_body(const std::filesystem::path &lilypondfile,const std::filesystem::path& buildpath) {
    std::cout << "scan lilypond body " << lilypondfile.string() << std::endl ;
    auto fin = std::ifstream(lilypondfile.string());
    std::string data;
    std::function<std::string(const std::string &)> f = [&lilypondfile,&buildpath](const std::string &data) {
        std::smatch sm;
        regex_search(data, sm, std::regex(R"(^[ \t]*?\\include.*?\"(.*)\")"));
        if (sm.size() == 0) return data;
        if (sm.size() < 2) {
            throw std::runtime_error("huh ?");
        }
        auto x = sm[1];
        if (!x.matched) {
            throw std::runtime_error("huh ?");
        }
        std::cout << "==> '" << sm[1].str() << "'" << std::endl ;
        if ( sm[1].str() == "../../../../macros/macros.ly") {
            return std::string(R"(\include "macros.ly")") ;
        }

        std::filesystem::path p = (lilypondfile.parent_path() / x.str()).lexically_normal();
        std::cout << " ly include : " << std::filesystem::absolute(p).string() << std::endl;
        if (!std::filesystem::exists(p)) {
            throw std::runtime_error(std::string("file does not exist : " + std::filesystem::absolute(p).string()));
        }
        std::string song = p.parent_path().filename() ;
        std::string artist = p.parent_path().parent_path().filename() ;
        scan_lilypond_body(p,buildpath) ;
        return std::string("\\include \"") + artist + "_" + song + "_" + p.filename().string() +"\"" ;
    };
    std::string song = lilypondfile.parent_path().filename() ;
    std::string artist = lilypondfile.parent_path().parent_path().filename() ;
    std::filesystem::path outtexfile = buildpath / (artist + "_" + song + "_" + lilypondfile.filename().string());

    std::ofstream fout(outtexfile);


    while (true) {
        getline(fin, data);
        std::string ret = f(data);
        fout << ret << std::endl;
        if (fin.eof()) break;
    }


    return;

}

void scan_song_body(const std::filesystem::path &texfile,const std::filesystem::path& buildpath) {
    std::cout << "scan song body " << texfile.string() << std::endl ;
    auto fin = std::ifstream(texfile.string());
    std::string data;
    std::function<std::string(const std::string &)> f = [&texfile,&buildpath](const std::string &data) {
        std::smatch sm;
        regex_search(data, sm, std::regex(R"(^[ \t]*?\\input\{(.*)\})"));
        if (sm.size() == 0) return data;
        if (sm.size() < 2) {
            throw std::runtime_error("huh ?");
        }
        auto x = sm[1];
        if (!x.matched) {
            throw std::runtime_error("huh ?");
        }
        if (x.str() == "../macros/preamble.tex") {
            return std::string("\\input{preamble.tex}");
        }
        if (x.str() == "../macros/chords.tex") {
            return std::string("\\input{chords.tex}") ;
        }
        std::filesystem::path p = (texfile.parent_path() / x.str()).lexically_normal();
        std::cout << " input : " << std::filesystem::absolute(p).string() << std::endl;
        if (!std::filesystem::exists(p)) {
            throw std::runtime_error(std::string("file does not exist : " + std::filesystem::absolute(p).string()));
        }
        scan_song_body(p,buildpath) ;
        std::string song = p.parent_path().filename() ;
        std::string artist = p.parent_path().parent_path().filename() ;
        return std::string("\\input{") + artist + "_" + song + "_" + p.filename().string() + "}" ;
    };
    std::function<std::string(const std::string &)> g = [&texfile,&buildpath](const std::string &data) {
        std::smatch sm;
        regex_search(data, sm, std::regex(R"(^[ \t]*?\\lilypondfile(.*?)\{(.*)\})"));
        if (sm.size() == 0) return data;
        if (sm.size() < 3) {
            throw std::runtime_error("huh ?");
        }
        auto x = sm[2];
        if (!x.matched) {
            throw std::runtime_error("huh ?");
        }
        std::filesystem::path p = (texfile.parent_path() / x.str()).lexically_normal();
        std::cout << " input : " << std::filesystem::absolute(p).string() << std::endl;
        if (!std::filesystem::exists(p)) {
            throw std::runtime_error(std::string("file does not exist : " + std::filesystem::absolute(p).string()));
        }
        scan_lilypond_body(p,buildpath) ;
        std::string song = p.parent_path().filename() ;
        std::string artist = p.parent_path().parent_path().filename() ;
        return std::string("\\lilypondfile")+sm[1].str()+"{" + artist + "_" + song + "_" + p.filename().string() + "}" ;
    };
    std::string song = texfile.parent_path().filename() ;
    std::string artist = texfile.parent_path().parent_path().filename() ;
    std::filesystem::path outtexfile = buildpath / (artist + "_" + song + "_" + texfile.filename().string());

    std::ofstream fout(outtexfile);


    while (true) {
        getline(fin, data);
        std::string ret = g(f(data));
        fout << ret << std::endl;
        if (fin.eof()) break;
    }


    return;


}

void scan_main(const std::filesystem::path &texfile, const std::filesystem::path &buildpath) {
    auto fin = std::ifstream(texfile.string());
    std::string data;

    std::function<std::string(const std::string &)> f = [&texfile,&buildpath](const std::string &data) {
        std::smatch sm;
        regex_search(data, sm, std::regex(R"(^[ \t]*?\\input\{(.*)\})"));
        if (sm.size() == 0) return data;
        if (sm.size() < 2) {
            throw std::runtime_error("huh ?");
        }
        auto x = sm[1];
        if (!x.matched) {
            throw std::runtime_error("huh ?");
        }
        if (x.str() == "../macros/preamble.tex") {
            return std::string("\\input{preamble.tex}");
        }
        if (x.str() == "../macros/chords.tex") {
            return std::string("\\input{chords.tex}") ;
        }
        std::filesystem::path p = (texfile.parent_path() / x.str()).lexically_normal();
        std::cout << " input : " << std::filesystem::absolute(p).string() << std::endl;
        if (!std::filesystem::exists(p)) {
            throw std::runtime_error(std::string("file does not exist : " + std::filesystem::absolute(p).string()));
        }
        std::string song = p.parent_path().filename() ;
        std::string artist = p.parent_path().parent_path().filename() ;
        scan_song_body(p,buildpath) ;
        return std::string("\\input{") + artist + "_" + song + "_" + "body.tex" + "}" ;
    };

    // std::cout << "texfile : " << std::filesystem::absolute(texfile).string() << std::endl ;

    std::filesystem::path outtexfile = buildpath / texfile.filename();

    std::ofstream fout(outtexfile);


    while (true) {
        getline(fin, data);
        std::string ret = f(data);
        fout << ret << std::endl;
        if (fin.eof()) break;
    }


    return;

}


int main(int argc, char **argv) {
    assert(argc > 2);
    std::filesystem::path texfile(argv[1]);
    texfile = std::filesystem::absolute(std::filesystem::canonical(texfile)) ;
    std::filesystem::path buildpath(argv[2]);
    if (!std::filesystem::exists(texfile)) {
        throw std::runtime_error(std::string("file does not exist : ") +
                                 std::filesystem::absolute(texfile).string());
    }

    std::filesystem::create_directories(buildpath) ;

    scan_main(texfile, buildpath);

    std::filesystem::path macrospath = texfile.parent_path().parent_path() / "macros" ;
    if (!std::filesystem::exists(macrospath)) {
        throw std::runtime_error(std::string("does not exist : ")+std::filesystem::absolute(macrospath).string()) ;
    }
    assert(std::filesystem::exists(macrospath)) ;
    std::filesystem::copy_file(macrospath/"preamble.tex",buildpath/"preamble.tex",std::filesystem::copy_options::overwrite_existing) ;
    std::filesystem::copy_file(macrospath/"chords.tex",buildpath/"chords.tex",std::filesystem::copy_options::overwrite_existing) ;
    std::filesystem::copy_file(macrospath/"macros.ly",buildpath/"macros.ly",std::filesystem::copy_options::overwrite_existing) ;

    /*
    std::ostringstream oss ;
    oss << "cd " << buildpath.string() << " ; lilypond-book --output toto --format=latex --pdf " << texfile.filename().string() ;
    exec(oss.str().c_str()) ;
    exec(oss.str().c_str()) ;
    exec(oss.str().c_str()) ;
    */


}