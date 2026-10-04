#include "treenode.hpp"

TreeNode::TreeNode(int version, std::string c) {
    version_id = version;
    content = c;
    message = "";
    parent = nullptr;
    created_timestamp = time(nullptr);
    modified_timestamp = time(nullptr);
    snapshot_timestamp = 0;
}

TreeNode::~TreeNode() {
    for (TreeNode* child : children) {
        delete child;
    }
    children.clear();
}

void TreeNode::addChild(TreeNode* child) {
    children.push_back(child);
}

void TreeNode::setSnapshot(std::string snapshot_message) {
    message = snapshot_message;
    snapshot_timestamp = time(nullptr);
}

bool TreeNode::isSnapshot() {
    return snapshot_timestamp != 0;
}

void TreeNode::setModTime() {
    modified_timestamp = time(nullptr);
}

std::string TreeNode::getContent() {
    return content;
}

void TreeNode::setContent(std::string s) {
    content += s;
}

void TreeNode::replaceContent(std::string s) {
    content = s;
}

std::string TreeNode::getMessage() {
    return message;
}

int TreeNode::getVersion() {
    return version_id;
}

time_t TreeNode::getSnapshotTime() {
    return snapshot_timestamp;
}

time_t TreeNode::getModTime() {
    return modified_timestamp;
}

TreeNode* TreeNode::getParent() {
    return parent;
}

void TreeNode::setParent(TreeNode* p) {
    this->parent = p;
}