
#include <iostream>
#include <experimental/filesystem>

#include <QDir>
#include <QFile>

#include "sgomfiles.h"

using namespace std::experimental;

SGOMFiles *SGOMFiles::_f;

SGOMFiles::SGOMFiles() {

    _base_path = std::getenv("HOME");
    _base_path += "/.sgom";

    _create_dir_if_missing(_base_path);

    _char_path += _base_path + "/chars";

    _create_dir_if_missing(_char_path);
}

bool SGOMFiles::charExists(std::string char_name) const {

    return filesystem::exists(getCharsPath() + '/' + char_name + ".dat");
}

void SGOMFiles::removeChar(std::string char_name) const {

    filesystem::remove(getCharsPath() + '/' + char_name + ".dat");
}

std::vector<std::string> SGOMFiles::characters() const {

    decltype(characters()) chars;

    for(auto& dir_entry : filesystem::directory_iterator(getCharsPath())){

        filesystem::path p = dir_entry.path();

        if(!filesystem::is_regular_file(p)) continue;

        if(p.extension() != ".dat") continue;

        p.replace_extension();

        chars.push_back(p.filename());
    }

    return chars;
}

std::optional<std::map<std::string, std::vector<std::string> > > SGOMFiles::readSGOMEntryFile(const std::string& filename) {

    QFile f(filename.c_str());

    f.open(QFile::ReadOnly);

    QTextStream in(&f);

    std::map<std::string, std::vector<std::string> > result;

    std::string section = "Global";

    while(!in.atEnd()) {

        if(!read_SGOM_entry_file_loop(filename, result, section, in)) return std::nullopt;
    }

    return result;
}


bool SGOMFiles::read_SGOM_entry_file_loop(const std::string& filename,
                                          std::map<std::string, std::vector<std::string> >& result,
                                          std::string& section, QTextStream& in) {


    QString in_s = in.readLine();

    if(in_s.size() == 0) return true;
    if(in_s.front() == ';') return true;

    int start_brac_count = in_s.count('[');
    int end_brac_count = in_s.count(']');

    std::string s = in_s.toStdString();

    if(start_brac_count > 1 || start_brac_count != end_brac_count) {

        std::cerr << "Error reading line \'" << s << "\' from " << filename << std::endl;
        return false;
    }

    if(start_brac_count == 1) {

        if(!read_SGOM_entry_file_brackets(filename, s, section)) return false;
    }
    else {

        auto& v = result[section];

        if(v.size() && v.back().back() == '\\') {

            v.back().pop_back();
            v.back() += s;
        }
        else v.push_back(s);
    }

    return true;
}

bool SGOMFiles::read_SGOM_entry_file_brackets(const std::string& filename, const std::string& s, std::string& section) {

    auto st_it = std::find(s.begin(), s.end(), '[');
    auto end_it = std::find(s.begin(), s.end(), ']');

    if(std::string(s.begin(), st_it).size() != 0 || std::string(end_it+1, s.end()).size() != 0) {

        std::cerr << "Error reading line \'" << s << "\' from " << filename << std::endl;
        return false;
    }

    section = std::string(st_it+1, end_it);

    return true;
}

std::vector<std::string> SGOMFiles::findDataFiles(const std::string& dir) {

    QDir d(QString::fromStdString(":/data/" + dir));

    std::vector<std::string> ret;

    for(auto&& f : d.entryList()) ret.push_back((d.path() + '/' + f).toStdString());

    return ret;
}

std::vector<std::string> SGOMFiles::findDataFiles(const std::string& dir, const std::string& extension) {

    std::vector<std::string> ret;

    for(auto&& f : findDataFiles(dir)) {

        if(std::string(std::find(std::find(f.rbegin(), f.rend(), '/').base(), f.end(), '.'), f.end()) == extension) {

            ret.push_back(f);
        }
    }

    return ret;
}

bool SGOMFiles::_create_dir_if_missing(const std::string& dir_name) {

    filesystem::path dir_path = dir_name;

    if(!filesystem::exists(dir_path)) return filesystem::create_directory(dir_path);

    return true;
}


