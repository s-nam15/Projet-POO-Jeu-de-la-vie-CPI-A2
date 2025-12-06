#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager {
public:
    FileManager();
    ~FileManager() = default;
    
    // Extrait le nom de base d'un fichier (sans extension)
    static std::string getBaseName(const std::string& filepath);
    
    // Crée un dossier de sortie
    static std::string createOutputDirectory(const std::string& baseName);
    
    // Vérifie si un fichier existe
    static bool fileExists(const std::string& filepath);
};

#endif