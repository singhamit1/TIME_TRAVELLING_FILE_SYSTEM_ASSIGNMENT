#ifndef FILE_HPP
#define FILE_HPP

#include "treenode.hpp"
#include "hashmap.hpp"
#include <string>
#include <vector>
#include <ctime>

class File {
private:
    std::string fileName;
    TreeNode* root;
    TreeNode* active_version;
    HashMap version_map;
    time_t last_modified;
    int total_versions;

public:
    File(std::string filename);
    ~File();
    void updateLastModified();
    time_t getLastModified();
    void insert(std::string newContent);
    void update(std::string content);
    void snapshot(std::string message);
    void rollback(int VersionID = -1);
    int getCurrVer();
    TreeNode* getVerAdd(int VersionID);
    std::string getCurrCon();
    std::string getFileName();
    int getTotalV();
    std::vector<std::string> getHistory();
};

#endif // FILE_HPP