
#ifndef SGOMFILES_H
#define SGOMFILES_H

#include <vector>
#include <string>
#include <optional>
#include <map>

#include <QTextStream>

/*!
 * \brief The SGOMFiles class is meant help with the localization of files for the game
 */
class SGOMFiles {

    /*!
     * \brief Initialize the directories and files for the game, if needed
     */
    SGOMFiles();

public:

    using DataEntryFileInfo = std::vector<std::pair<std::string, std::vector<std::string> > >;
    using EntryFileInfo = std::map<std::string, std::vector<std::string> >;
    using ConfigFileInfo = std::map<std::string, std::map<std::string, std::string> >;
    using DataFileInfo = std::vector<std::pair<std::string, std::map<std::string, std::string> > >;

    /*!
     * \brief Return the path to the base directory for all the game's files and directories
     * \return The path to the base directory where this game information is saved
     */
    const std::string& getBasePath() const { return _base_path; }

    /*!
     * \brief Return the path where the characters are saved
     * \return Path to the directories with the files with the information about the characters
     */
    const std::string& getCharsPath() const { return _char_path; }

    /*!
     * \brief Return the path to the file where a character is saved
     * \param char_name Name of the character
     * \sa charExists(std::string), getCharsPath()
     * \return Path to the file where the information about the character is kept
     */
    std::string charFilePath(std::string char_name) const { return getCharsPath() + '/' + char_name + ".dat"; }

    /*!
     * \brief Verify if there is a file with the information about an especific character
     * \param char_name Name of the character
     * \sa charFilePath(std::string), characters(), removeChar(std::string)
     * \return true if the file is found, false otherwise
     */
    bool charExists(std::string char_name) const;

    /*!
     * \brief Return a list with the name all characters with saved information
     * \sa charExists(std::string), removeChar(std::string)
     * \return A list containing the names of all the characters saved in the filesystem
     */
    std::vector<std::string> characters() const;

    /*!
     * \brief Remove the file for a specific character
     * \param char_name Name of the character that will be deleted
     * \sa charExists(std::string), charFilePath(std::string), characters()
     */
    void removeChar(std::string char_name) const;

    /*!
     * \brief Return an object of SGOMFiles, the first time this method is called the object will be created
     * \brief When created it will initialize the directories and files for the game, if needed
     * \return An object of SGOMFiles
     */
    static SGOMFiles *get() { if(!_f) _f = new SGOMFiles; return _f; }

    static std::vector<std::string> findDataFiles(const std::string& dir);
    static std::vector<std::string> findDataFiles(const std::string& dir, const std::string& extension);

    static std::optional<DataEntryFileInfo> readSGOMDataEntryFile(const std::string& filename);

    static std::optional<EntryFileInfo> readSGOMEntryFile(const std::string& filename);

    static std::optional<ConfigFileInfo> readSGOMConfigFile(const std::string& filename);

    static std::optional<DataFileInfo> readSGOMDataFile(const std::string& filename);

    ConfigFileInfo readSGOMConfigFile();

    static ConfigFileInfo readSGOMDefaultConfigFile();

    static void writeSGOMConfigFile(const std::string& filename, const ConfigFileInfo& info);

    void writeSGOMConfigFile(const ConfigFileInfo& info);

    static void writeSGOMDataFile(const std::string& filename, const DataFileInfo& info);

private:

    static bool _read_SGOM_data_entry_file_loop(const std::string& filename,
                                                DataEntryFileInfo& result,
                                                std::string& section, QTextStream& in);

    static bool _read_SGOM_data_entry_file_brackets(const std::string& filename, const std::string& s, std::string& section);

    template <typename T>
    static bool _write_SGOM_data_file(const std::string& filename, const T& info);

    bool _create_dir_if_missing(const std::string& dir_name);

    static bool _append_data_entry(SGOMFiles::DataEntryFileInfo& result, const std::string& section, const std::string& s);
    static bool _create_section_data_entry(SGOMFiles::DataEntryFileInfo& result, const std::string& section);
    static std::pair<std::string, std::string> _split_equal_sign(const std::string& s);

    std::string _base_path;
    std::string _char_path;

    static SGOMFiles *_f;
};

#endif // SGOMFILES_H
