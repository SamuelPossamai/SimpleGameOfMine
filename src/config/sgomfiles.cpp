
#include <iostream>
#include <fstream>
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

    _create_dir_if_missing(_base_path + "/config");
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

std::optional<SGOMFiles::DataEntryFileInfo> SGOMFiles::readSGOMDataEntryFile(const std::string& filename) {

    QFile f(filename.c_str());

    f.open(QFile::ReadOnly);

    QTextStream in(&f);

    SGOMFiles::DataEntryFileInfo result;

    std::string section = "__global__";

    while(!in.atEnd()) {

        if(!read_SGOM_data_entry_file_loop(filename, result, section, in)) return std::nullopt;
    }

    return result;
}

std::optional<SGOMFiles::EntryFileInfo> SGOMFiles::readSGOMEntryFile(const std::string& filename) {

    auto opt = readSGOMDataEntryFile(filename);

    if(!opt) return std::nullopt;

    auto vec = *opt;

    EntryFileInfo result;

    for(auto& p : vec) result[p.first] = p.second;

    return result;
}

std::optional<SGOMFiles::ConfigFileInfo> SGOMFiles::readSGOMConfigFile(const std::string& filename) {

    auto opt = readSGOMEntryFile(filename);

    if(!opt) return std::nullopt;

    auto f_info = *opt;

    ConfigFileInfo ret;

    for(auto&& p : f_info) {

        auto & content_out = ret[p.first];

        for(auto&& v : p.second) {

            auto p = _split_equal_sign(v);

            content_out[p.first] = p.second;
        }
    }

    return ret;
}

std::optional<SGOMFiles::DataFileInfo> SGOMFiles::readSGOMDataFile(const std::string& filename) {

    auto opt = readSGOMDataEntryFile(filename);

    if(!opt) return std::nullopt;

    auto f_info = *opt;

    DataFileInfo ret;

    for(auto&& p : f_info) {

        ret.push_back({ p.first,  DataFileInfo::value_type::second_type() });

        for(auto&& v : p.second) {

            auto p = _split_equal_sign(v);

            ret.back().second[p.first] = p.second;
        }
    }

    return ret;
}

SGOMFiles::ConfigFileInfo SGOMFiles::readSGOMConfigFile() {

    static const char *default_file = ":/data/config/default.conf";

    QString config_file = QString::fromStdString(_base_path + "/config/sgom.conf");

    if(!QFile(config_file).exists()) {

        QFile::copy(default_file, config_file);
        QFile(config_file).setPermissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ReadGroup | QFile::ReadOther);
    }

    auto opt = readSGOMConfigFile(config_file.toStdString());

    if(!opt) {

        std::cerr << "An error ocurred reading the configuration file, default configuration will be adopted" << std::endl;

        return readSGOMDefaultConfigFile();
    }

    return *opt;
}

SGOMFiles::ConfigFileInfo SGOMFiles::readSGOMDefaultConfigFile() {

    static const char *default_file = ":/data/config/default.conf";

    return *readSGOMConfigFile(default_file);
}

void SGOMFiles::writeSGOMConfigFile(const std::string& filename, const ConfigFileInfo& info) {

    std::ofstream file(filename);

    for(auto&& section_pair : info) {

        file << '[' << section_pair.first << ']' << std::endl;

        for(auto&& p : section_pair.second) {

            file << p.first << '=' << p.second << std::endl;
        }
    }
}

void SGOMFiles::writeSGOMConfigFile(const ConfigFileInfo& info) {

    writeSGOMConfigFile(_base_path + "/config/sgom.conf", info);
}

bool SGOMFiles::read_SGOM_data_entry_file_loop(const std::string& filename,
                                          SGOMFiles::DataEntryFileInfo& result,
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

        if(!read_SGOM_data_entry_file_brackets(filename, s, section)) return false;
    }
    else {

        _create_section_data_entry(result, section);

        if(!_append_data_entry(result, section, s)) result.back().second.push_back(s);
    }

    return true;
}

bool SGOMFiles::read_SGOM_data_entry_file_brackets(const std::string& filename, const std::string& s, std::string& section) {

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

bool SGOMFiles::_append_data_entry(SGOMFiles::DataEntryFileInfo& result, const std::string& section, const std::string& s) {

    if(result.empty()) return false;

    auto & v = result.back();

    if(v.first != section) return false;

    auto & v_sec = v.second;

    if(v_sec.empty()) return false;

    auto & last_s = v_sec.back();

    if(last_s.empty()) return false;
    if(last_s.back() != '\\') return false;

    last_s.pop_back();
    last_s += s;

    return true;
}

bool SGOMFiles::_create_section_data_entry(SGOMFiles::DataEntryFileInfo& result, const std::string& section) {

    if(!result.empty()) if(result.back().first == section) return false;

    result.push_back({ section, DataEntryFileInfo::value_type::second_type() });

    return true;
}

std::pair<std::string, std::string> SGOMFiles::_split_equal_sign(const std::string& s) {

    auto eq_it = std::find(s.begin(), s.end(), '=');

    std::string first_str(s.begin(), eq_it);
    std::string second_str;

    if(eq_it != s.end()) second_str.assign(eq_it+1, s.end());

    return { first_str, second_str };
}
