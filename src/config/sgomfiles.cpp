
#include <experimental/filesystem>

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

bool SGOMFiles::_create_dir_if_missing(const std::string& dir_name) {

    filesystem::path dir_path = dir_name;

    if(!filesystem::exists(dir_path)) return filesystem::create_directory(dir_path);

    return true;
}
