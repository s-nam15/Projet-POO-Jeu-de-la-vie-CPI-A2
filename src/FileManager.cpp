#include "FileManager.h"
#include <filesystem>

namespace fs = std::filesystem;

FileManager::FileManager() {}

std::string FileManager::getBaseName(const std::string& filepath) {
    // Extraire le nom du fichier sans le chemin
    std::string filename = filepath.substr(filepath.find_last_of("/\\") + 1);
    
    // Retirer l'extension
    size_t dotPos = filename.find_last_of('.');
    if (dotPos != std::string::npos) {
        return filename.substr(0, dotPos);
    }
    
    return filename;
}

std::string FileManager::createOutputDirectory(const std::string& baseName) {
    std::string outputDir = baseName + "_out";
    
    if (!fs::exists(outputDir)) {
        fs::create_directory(outputDir);
    }
    
    return outputDir;
}

bool FileManager::fileExists(const std::string& filepath) {
    return fs::exists(filepath);
}