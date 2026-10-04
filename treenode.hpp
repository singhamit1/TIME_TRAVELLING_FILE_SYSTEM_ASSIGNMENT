#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <string>
#include <vector>
#include <ctime>

class TreeNode {
private:
    int version_id;
    std::string content;
    std::string message;
    time_t created_timestamp;
    time_t modified_timestamp;
    time_t snapshot_timestamp;
    TreeNode* parent;
    std::vector<TreeNode*> children;

public:
    TreeNode(int version, std::string c = "");
    ~TreeNode();
    void addChild(TreeNode* child);
    void setSnapshot(std::string snapshot_message);
    bool isSnapshot();
    void setModTime();
    std::string getContent();
    void setContent(std::string s);
    void replaceContent(std::string s);
    std::string getMessage();
    int getVersion();
    time_t getSnapshotTime();
    time_t getModTime();
    TreeNode* getParent();
    void setParent(TreeNode* parent);
};

#endif // TREENODE_HPP