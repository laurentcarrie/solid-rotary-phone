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


void generate_if_needed(std::filesystem::path target, std::vector<std::filesystem::path> sources,
                        std::string command) {
    bool is_needed = false;

    if (!std::filesystem::exists(target)) {
        is_needed = true ;
    }
    else {
        for (auto s: sources) {
            if (std::filesystem::last_write_time(target) < std::filesystem::last_write_time(s)) {
                //std::cout << std::filesystem::last_write_time(target) << std::endl ;
                std::cout << target << " is newer than " << s << std::endl;
                is_needed = true;
                break;
            }
        }
    }
    if (!is_needed) return ;
    std::cout << command << std::endl ;
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

void substitute_LY(Config config, Item item, std::string &input) {
    std::string data = get_string_between_tags(input, item);
    replace_string_between_tags(input, std::string("<div><img class=\"ly\" src=\"") + data + (".png\"></div>"), item);
    std::ostringstream oss;
    oss << "lilypond -dbackend=eps -dresolution=600 --png --output ";
    std::filesystem::path target(config.builddir / config.relpath / data);
    target.replace_extension(".png");

    oss << config.builddir / config.relpath / data;
    std::filesystem::path source(config.srcdir / config.relpath / data);
    source.replace_extension(".ly");
    oss << " " << source;
    // oss << /home/laurent/work/solid-rotary-phone/build/cranberries/zombies/png_solo /home/laurent/work/solid-rotary-phone/source/cranberries/zombies/png_solo.ly" ;
    // std::cout << oss.str() << std::endl;
    generate_if_needed(target, {source}, oss.str());


}

void substitute_LY_WAV(Config config, Item item, std::string &input) {
    std::string data = get_string_between_tags(input, item);
    std::stringstream oss;
    auto ly_path = config.srcdir / config.relpath / data;
    ly_path.replace_extension(".ly");
    auto midi_path = config.builddir / config.relpath / data;
    midi_path.replace_extension(".midi");
    auto wav_path = config.builddir / config.relpath / data;
    wav_path.replace_extension(".wav");

    {
        // make midi
        std::ostringstream oss;
        auto midi_path_without_extension = midi_path ;
        midi_path_without_extension.replace_extension("") ;
        oss << "lilypond -dmidi-extension=midi --output " << midi_path_without_extension << " " << ly_path;
        generate_if_needed(midi_path,{ly_path},oss.str()) ;

    }
    {
        // make wav
        std::ostringstream oss;

        std::vector<std::filesystem::path> maybe_soundfont_paths = {
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
        oss << "fluidsynth -F " << wav_path << " " << existing_soundfont_paths.front() << " " << midi_path;
        generate_if_needed(wav_path, {midi_path}, oss.str());


    }
    {
        std::ostringstream oss;
        oss << R"here(<div><a class="wav" href=")here" << data << R"here(.wav">)here" << data << "</a></div>";
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
            oss << "<td><div style=\"width: 50px\" >" << cell << "</div></td>";
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
                substitute_LY(config, item, data);
                break;
            case LY_WAV:
                substitute_LY_WAV(config, item, data);
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


std::stringstream to_html(Config config) {

    std::stringstream oss;
    oss << R"here(
<html>
<head>
<style>

.wrapper {
	background-color: #ffffff;
	border: 1px solid #00ffff;
grid-column-gap: 30px;
grid-row-gap: 30px;
  display: grid;
  grid-template-columns: )here";

    for (auto i: config.cols) {
        oss << i << "cm ";
    }

    oss << R"here( ;
}

</style>
<link rel="stylesheet" type="text/css" href="../../style/style.css">
<link rel="stylesheet" type="text/css" href="../../style/print.css" media="print" />
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
    </head>
<body>
<div class="main-title">

    )here";

    oss << config.main_title << "</div>" << std::endl;

    oss << "<div class=\"wrapper\">" << std::endl;
    for (unsigned int irow = 0; irow < config.rows; irow++) {
        for (unsigned int icol = 0; icol < config.cols.size(); icol++) {
            bool found = false;
            for (auto c: config.cells) {
                // std::cout << "loop " << c.what << std::endl ;
                if (c.irow != irow + 1) continue;
                if (c.icol != icol + 1) continue;
                found = true;
                oss << "<div>" << substitute_all_tags(config, c.data) << "</div>" << std::endl;
            }
            if (!found) {
                oss << "<div>" << irow * config.cols.size() + icol << "</div>" << std::endl;
            }
        }
    }
    oss << "</div>" << std::endl;





//    oss << input ;

    oss << "</body></html>" << std::endl;

    return oss;

}

