
#ifndef SGOMFILES_H
#define SGOMFILES_H

#include <vector>
#include <string>

/*!
 * \brief The SGOMFiles class is meant help with the localization of files for the game
 */
class SGOMFiles {

    /*!
     * \brief Initialize the directories and files for the game, if needed
     */
    SGOMFiles();

public:

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

private:

    bool _create_dir_if_missing(const std::string& dir_name);

    std::string _base_path;
    std::string _char_path;

    static SGOMFiles *_f;
};

#endif // SGOMFILES_H
