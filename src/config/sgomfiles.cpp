
#include <iostream>
#include <fstream>

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>

#include "utility/stringutils.h"
#include "sgomfiles.h"

using namespace utility::stringutils;

SGOMFiles *SGOMFiles::_f = nullptr;

SGOMFiles::SGOMFiles() {

    _base_path = std::getenv("HOME");
    _base_path += "/.sgom";

    _char_path += _base_path + "/chars";

    auto config_path = _base_path + "/config";

    const char *paths_to_create[] = { _char_path.c_str(), config_path.c_str() };
    for(const char *path : paths_to_create){

       if(!QDir().mkpath(path)) std::cerr << "Failed to create directory '" << path << "'" << std::endl;
    }
}

bool SGOMFiles::charExists(std::string char_name) const {

    return QFile::exists(QString::fromStdString(getCharsPath() + '/' + char_name + ".dat"));
}

void SGOMFiles::removeChar(std::string char_name) const {

    QFile::remove(QString::fromStdString(getCharsPath() + '/' + char_name + ".dat"));
}

std::vector<std::string> SGOMFiles::characters() const {

    decltype(characters()) chars;

    for(auto it = QDirIterator(QString::fromStdString(getCharsPath())); it.hasNext(); it.next()){

        QFileInfo p = it.filePath();

        if(!p.isFile()) continue;

        if(p.completeSuffix() != "dat") continue;

        chars.push_back(p.baseName().toStdString());
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

        if(!_read_SGOM_data_entry_file_loop(filename, result, section, in)) return std::nullopt;
    }

    return std::move(result);
}

std::optional<SGOMFiles::EntryFileInfo> SGOMFiles::readSGOMEntryFile(const std::string& filename) {

    auto opt = readSGOMDataEntryFile(filename);

    if(!opt) return std::nullopt;

    auto vec = *opt;

    EntryFileInfo result;

    for(auto& p : vec) result[p.first] = p.second;

    return std::move(result);
}

std::optional<SGOMFiles::ConfigFileInfo> SGOMFiles::readSGOMConfigFile(const std::string& filename) {

    auto opt = readSGOMEntryFile(filename);

    if(!opt) return std::nullopt;

    auto f_info = *opt;

    ConfigFileInfo ret;

    for(auto&& p : f_info) {

        auto & content_out = ret[p.first];

        for(auto&& v : p.second) {

            auto split_p = splitSingle(v, '=');

            content_out[split_p.first] = Variant::fromString(split_p.second);
        }
    }

    return std::move(ret);
}

std::optional<SGOMFiles::DataFileInfo> SGOMFiles::readSGOMDataFile(const std::string& filename) {

    auto opt = readSGOMDataEntryFile(filename);

    if(!opt) return std::nullopt;

    auto f_info = *opt;

    DataFileInfo ret;

    for(auto&& p : f_info) {

        ret.push_back({ p.first,  DataFileInfo::value_type::second_type() });

        for(auto&& v : p.second) {

            auto p = splitSingle(v, '=');

            ret.back().second[p.first] = Variant::fromString(p.second);
        }
    }

    return std::move(ret);
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

void SGOMFiles::writeSGOMDataFile(const std::string& filename, const DataFileInfo& info) {

    std::ofstream file(filename);

    for(auto&& section_pair : info) {

        file << '[' << section_pair.first << ']' << std::endl;

        for(auto&& p : section_pair.second) {

            file << p.first << '=' << p.second << std::endl;
        }
    }
}

bool SGOMFiles::_read_SGOM_data_entry_file_loop(const std::string& filename,
                                                SGOMFiles::DataEntryFileInfo& result,
                                                std::string& section, QTextStream& in) {


    QString in_s = in.readLine();

    if(in_s.size() == 0) return true;
    if(in_s[0] == ';') return true;

    int start_brac_count = in_s.count('[');
    int end_brac_count = in_s.count(']');

    std::string s = in_s.toStdString();

    if(start_brac_count > 1 || start_brac_count != end_brac_count) {

        std::cerr << "Error reading line \'" << s << "\' from " << filename << std::endl;
        return false;
    }

    if(start_brac_count == 1) {

        if(!_read_SGOM_data_entry_file_brackets(filename, s, section)) return false;
    }
    else {

        _create_section_data_entry(result, section);

        if(!_append_data_entry(result, section, s)) result.back().second.push_back(s);
    }

    return true;
}

bool SGOMFiles::_read_SGOM_data_entry_file_brackets(const std::string& filename, const std::string& s, std::string& section) {

    auto st_it = std::find(s.begin(), s.end(), '[');
    auto end_it = std::find(s.begin(), s.end(), ']');

    if(std::string(s.begin(), st_it).size() != 0 || std::string(end_it+1, s.end()).size() != 0) {

        std::cerr << "Error reading line \'" << s << "\' from " << filename << std::endl;
        return false;
    }

    section = std::string(st_it+1, end_it);

    return true;
}

std::vector<std::string> SGOMFiles::findFiles(const std::string& dir) {

    QDir d(QString::fromStdString(dir));

    std::vector<std::string> ret;

    for(auto&& f : d.entryList()) ret.push_back((d.path() + '/' + f).toStdString());

    return ret;
}

std::vector<std::string> SGOMFiles::findFiles(const std::string& dir, const std::string& extension) {

    std::vector<std::string> ret;

    for(auto&& f : findFiles(dir)) {

        if(std::string(std::find(std::find(f.rbegin(), f.rend(), '/').base(), f.end(), '.'), f.end()) == extension) {

            ret.push_back(f);
        }
    }

    return ret;
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

template <typename T>
bool SGOMFiles::_write_SGOM_data_file(const std::string& filename, const T& info) {

    std::ofstream file(filename);

    for(auto&& section_pair : info) {

        file << '[' << section_pair.first << ']' << std::endl;

        for(auto&& p : section_pair.second) {

            file << p.first << '=' << p.second << std::endl;
        }
    }

    return true;
}
