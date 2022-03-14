//
// Created by laurent on 05/02/2022.
//

#include "to_html.h"
#include "config.h"
#include "parse.h"
#include <iostream>
#include <cassert>
#include <regex>
#include <array>
#include <fstream>


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

bool any_younger(const std::filesystem::path &p) {
    if (!std::filesystem::exists(p)) {
        return true;
    }
    std::filesystem::path d = p.parent_path();
    for (auto pp: d) {
        if (std::filesystem::last_write_time(d) < std::filesystem::last_write_time(p)) {
            return true;
        }

    }
    return false;
}


void generate_if_needed(std::filesystem::path target, std::vector<std::filesystem::path> sources,
                        std::string command) {
    bool is_needed = false;

    if (!std::filesystem::exists(target)) {
        is_needed = true;
    } else {
        for (auto s: sources) {
            if (std::filesystem::last_write_time(target) < std::filesystem::last_write_time(s)) {
                //std::cout << std::filesystem::last_write_time(target) << std::endl ;
                std::cout << target << " is newer than " << s << std::endl;
                is_needed = true;
                break;
            }
        }
    }
    if (any_younger(target)) {
        is_needed = true;
    }
    is_needed = true;
    if (!is_needed) return;
    std::cout << command << std::endl;
    exec(command.c_str());

    if (!std::filesystem::exists(target)) {
        std::ostringstream oss;
        oss << "command " << command << std::endl << "did not generate target " << std::endl << target << std::endl;
        throw (std::runtime_error(oss.str()));
    }

    return;
}

std::string opening_tag(std::string tag) {
    return std::string("<") + tag + (">");
}

std::string closing_tag(std::string tag) {
    return std::string("</") + tag + (">");
}

std::vector<std::string> split_string(std::string input, std::string delim) {
    std::vector<std::string> ret;
    int begin_index = 0;
    while (true) {
        auto found_index = input.find_first_of(delim, begin_index);
        if (found_index == std::string::npos) {
            ret.push_back(input.substr(begin_index, input.size() - begin_index));
            break;
        }
        ret.push_back(input.substr(begin_index, found_index - begin_index));
        begin_index = found_index + 1;
    }
    return ret;

}

std::string get_string_between_tags(std::string input, Item item) {
    std::string gdata = input.substr(item.starting_ + 2 + item.tag_.size(),
                                     item.ending_ - item.starting_ - 2 - item.tag_.size());
    return gdata;
}

void replace_string_between_tags(std::string &input, std::string replacement, Item item) {
    input.replace(item.starting_, item.ending_ - item.starting_ + item.tag_.size() + 3, replacement);
}


void substitute_V(Item item, std::string &input) {
    std::string data = get_string_between_tags(input, item);
    std::vector<std::string> lines = split_string(data, "\n");
    std::ostringstream oss;
    oss << "<div class=\"verse\">" << std::endl;
    for (auto line: lines) {
        if (!line.empty()) {
            oss << line << " <br>" << std::endl;
        }
    }
    oss << "</div>" << std::endl;
    replace_string_between_tags(input, oss.str(), item);
}

void substitute_C(Item item, std::string &input) {
    std::string data = get_string_between_tags(input, item);
    std::vector<std::string> lines = split_string(data, "\n");
    std::ostringstream oss;
    oss << "<div class=\"chorus\">" << std::endl;
    for (auto line: lines) {
        if (!line.empty()) {
            oss << line << " <br>" << std::endl;
        }
    }
    oss << "</div>" << std::endl;
    replace_string_between_tags(input, oss.str(), item);
}

void substitute_T(Item item, std::string &input) {
    input.replace(item.ending_, closing_tag(item.tag_).size(), "</div>");
    input.replace(item.starting_, opening_tag(item.tag_).size(), "<div class=\"title\">");
}

void substitute_L(Item item, std::string &input) {
    input.replace(item.ending_, closing_tag(item.tag_).size(), "</div>");
    input.replace(item.starting_, opening_tag(item.tag_).size(), "<div class=\"lyrics\">");
}

void substitute_N(Config config, Item item, std::string &input) {
    input.replace(item.ending_, closing_tag(item.tag_).size(), "</div>");
    input.replace(item.starting_, opening_tag(item.tag_).size(), "<div class=\"note\">");
}


void substitute_LY(Config config, Item item, std::string &input,bool with_rhytm,bool with_chords,bool with_lyrics) {
    std::string data = get_string_between_tags(input, item);
    generate_png_ly(config, data, with_rhytm,with_chords,with_lyrics);
    std::string stem = data + "_image";
    replace_string_between_tags(input, std::string("<div><img class=\"ly\"  src=\"") + stem + (".png\"></div>"), item);
    std::ostringstream oss;
    oss << "lilypond -dbackend=eps -dresolution=600 --png --output ";
    std::filesystem::path target(config.builddir / config.relpath / stem);
    target.replace_extension(".png");

    oss << config.builddir / config.relpath / stem;
    std::filesystem::path source(config.builddir / config.relpath / stem);
    source.replace_extension(".ly");
    oss << " " << source;
    generate_if_needed(target, {source}, oss.str());

}

void substitute_LY_WAV(Config config, Item item, std::string &input) {
    std::string data = get_string_between_tags(input, item);
    generate_midi_ly(config, data);
    std::string stem = data + "_midi";
    std::stringstream oss;
    auto ly_path = config.builddir / config.relpath / stem;
    ly_path.replace_extension(".ly");
    auto midi_path = config.builddir / config.relpath / stem;
    midi_path.replace_extension(".midi");
    auto wav_path = config.builddir / config.relpath / stem;
    wav_path.replace_extension(".wav");


    {
        // make midi
        std::ostringstream oss;
        auto midi_path_without_extension = midi_path;
        midi_path_without_extension.replace_extension("");
        oss << "lilypond -dmidi-extension=midi --output " << midi_path_without_extension << " " << ly_path;
        generate_if_needed(midi_path, {ly_path}, oss.str());

    }
    {
        // make wav
        std::ostringstream oss;

        std::vector<std::filesystem::path> maybe_soundfont_paths = {
                // "/Users/laurent/softs/sounds/sf2/Timpani v2.0.sf2",
                "/Users/laurent/softs/sounds/sf2/FluidR3_GM.sf2",
                "/Users/laurent/softs/sounds/sf2/SGM-v2.01-YamahaGrand-Guit-Bass-v2.7.sf2",
                "/opt/homebrew/Cellar/fluid-synth/2.2.5/share/fluid-synth/sf2/VintageDreamsWaves-v2.sf2",
                "/usr/share/sounds/sf2/FluidR3_GM.sf2"};
        std::vector<std::filesystem::path> existing_soundfont_paths;
        std::copy_if(maybe_soundfont_paths.begin(), maybe_soundfont_paths.end(),
                     std::back_inserter(existing_soundfont_paths), [](const std::filesystem::path &p) {
                    return std::filesystem::exists(p);
                });

        if (existing_soundfont_paths.empty()) {
            throw std::runtime_error("no path found for soundpaths");
        }
        if (true) {
            oss << "fluidsynth -F " << wav_path << " " << existing_soundfont_paths.front() << " " << midi_path;
        } else {
            oss << "fluidsynth -F " << wav_path << " ";
            for (auto p: existing_soundfont_paths) {
                oss << p << " ";
            }
            oss << midi_path;
        }
        generate_if_needed(wav_path, {midi_path}, oss.str());


    }
    {
        std::ostringstream oss;
        oss << R"here(<div><a class="wav" href=")here" << stem << R"here(.wav">)here" << data << "</a></div>";
        replace_string_between_tags(input, oss.str(), item);
    }


}


void substitute_G(Item item, std::string &input) {
    std::string gdata = get_string_between_tags(input, item);
    // data.replace(item.ending_, closing_tag(item.tag_).size(),"</table></div>") ;
    // data.replace(item.starting_, opening_tag(item.tag_).size(),"<div><table class=\"redtable\">") ;
    // data = std::regex_replace(data,std::regex("#"),"&#x266F;") ;
    std::vector<std::string> lines = split_string(gdata, "\n");
    std::ostringstream oss;
    oss << "<div><table class=\"blueTable\">" << std::endl;
    for (auto line: lines) {
        if (line == "") continue;
        oss << "<tr>";
        std::vector<std::string> cells = split_string(line, "|");
        for (auto cell: cells) {
            char str_re[] = "<span [a-zA-Z0-9]+>";
            std::regex re(str_re);
            std::smatch m;
            std::regex_search(cell, m, re);
            std::optional<int> span;
            span.reset();
            for (auto x: m) {
                std::string y(x);
                auto s1 = std::string("<span ").size();
                cell = cell.substr(0,cell.size()-y.size()) ;
                int span_value = std::stoi(y.substr(s1, y.size() - s1 - 1));
                std::cout << span_value << std::endl;
                span = span_value;
            }
            oss << "<td";

            if (span.has_value()) {
                oss << " colspan=\"" << span.value() << "\"";
            }
            oss << ">" << cell << "</td>";

        }
        oss << "</tr>" << std::endl;
    }
    oss << "</table></div>";

    // data.replace(item.starting_,item.ending_-item.starting_+std::string("</G>").size(),oss.str()) ;
    replace_string_between_tags(input, oss.str(), item);
    // data = std::regex_replace(data,std::regex("#"),"&#x266F;") ;
    // std::cout << input << std::endl ;

}


std::string substitute_all_tags(Config config, std::string data) {

    int previous_length = 1000;
    while (true) {
        std::vector<Item> items = parse(data);
        assert (items.size() < previous_length);
        previous_length = items.size();
        if (items.empty()) break;
        Item item = items.front();

        // std::cout << "substitute " << item.starting_ << " -> " << item.ending_ << std::endl ;

        Tag etag = tag_of_name((item.tag_));
        switch (etag) {
            case V:
                substitute_V(item, data);
                break;
            case C:
                substitute_C(item, data);
                break;
            case T:
                substitute_T(item, data);
                break;
            case L:
                substitute_L(item, data);
                break;
            case G:
                substitute_G(item, data);
                break;
            case LY:
                substitute_LY(config, item, data,false,false,false);
                break;
            case LY_C:
                substitute_LY(config, item, data,false,true,false);
                break;
            case LY_R:
                substitute_LY(config, item, data,true,false,false);
                break;
            case LY_RC:
                substitute_LY(config, item, data,true,true,true);
                break;
            case LY_WAV:
                substitute_LY_WAV(config, item, data);
                break;
            case N:
                substitute_N(config, item, data);
                break;
            default:
                std::ostringstream oss;
                oss << __FILE__ << ":" << __LINE__ << " ; case not managed : '" << item.tag_ << "'";
                throw std::runtime_error(oss.str());
        }
    }
    // data = std::regex_replace(data,std::regex("<br>"),"<br>\n") ;
    return data;


}

void write_local_css(Config config, std::ostream &fout) {
    fout << R"here(
.wrapper {
            display: grid;
            grid-template-columns: repeat()here";
    fout << config.nb_cols;
    fout << R"here(, 1fr);
            grid-auto-rows: minmax(100px, auto);
}
)here";

    for (auto cell: config.cells) {
        fout << ".box_" << cell.index << " { " << std::endl
             << "    grid-row-start: " << cell.row_start << " ;" << std::endl
             << "    grid-row-end: " << cell.row_end << " ;" << std::endl
             << "    grid-column-start: " << cell.col_start << " ;" << std::endl
             << "    grid-column-end: " << cell.col_end << " ;" << std::endl;
        if (cell.background_color.has_value()) {
            fout << "    background-color: " << cell.background_color.value() << " ;" << std::endl;
        }
        fout << "}" << std::endl;
    }
}


std::stringstream to_html(Config config) {

    std::stringstream oss;
    oss << R"here(
<html>
<title>)here";
    oss << config.main_title;
    oss << R"here(</title>
<head>
<style>



</style>
<link rel="stylesheet" type="text/css" href="../../style/style.css">
<link rel="stylesheet" type="text/css" href="../../style/print.css" media="print" />
<link rel="stylesheet" type="text/css" href="local.css" />
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
    </head>
<body>
<div class="main-title">

    )here";

    oss << config.main_title << "</div>" << std::endl;

    oss << "<div class=\"wrapper\">" << std::endl;
    for (auto cell: config.cells) {
        oss << "<div class=\"box_" << cell.index << "\">" << substitute_all_tags(config, cell.data) << "</div>"
            << std::endl;
    }


    oss << "</div>" << std::endl;





//    oss << input ;

    oss << "</body></html>" << std::endl;

    return oss;

}

