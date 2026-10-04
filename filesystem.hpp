#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "file.hpp"
#include "heaps.hpp"
#include <vector>
#include <string>

// Declare global heap variables so other files know they exist.
extern Recent_Heap RecentFile;
extern Big_Heap BiggestFile;

class FileSystem {
private:
    std::vector<File*> info;
public:
    void createFile(std::string filename);
    std::string readfile(std::string name);
    void insertFile(std::string name, std::string content);
    void updateFile(std::string name, std::string content);
    void snapshotFile(std::string name, std::string message);
    void rollbackFile(std::string name, int versionID);
    void getFileHistory(std::string name);
};

#endif // FILESYSTEM_HPP