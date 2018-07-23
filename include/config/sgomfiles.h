
#ifndef SGOMFILES_H
#define SGOMFILES_H

#include <vector>
#include <string>

class SGOMFiles {

    SGOMFiles();

public:

    std::vector<std::string> characters() const;

    bool charExists(std::string char_name) const;
    void removeChar(std::string char_name) const;

    std::string charFilePath(std::string char_name) const { return getCharsPath() + '/' + char_name + ".dat"; }

    const std::string& getBasePath() const { return _base_path; }
    const std::string& getCharsPath() const { return _char_path; }

    static SGOMFiles *get() { if(!_f) _f = new SGOMFiles; return _f; }

private:

    bool _create_dir_if_missing(const std::string& dir_name);

    std::string _base_path;
    std::string _char_path;

    static SGOMFiles *_f;
};

#endif // SGOMFILES_H
