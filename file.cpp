#include "file.hpp"
#include <iostream>

using namespace std;

File::File(string filename) {
    fileName = filename;
    root = new TreeNode(0, "");
    root->setSnapshot("Initial commit");
    active_version = root;
    last_modified = time(nullptr);
    version_map.insert(root->getVersion(), (void*)root);
    total_versions = 1;
}

File::~File() {
    delete root;
}

void File::updateLastModified() {
    last_modified = time(nullptr);
}

time_t File::getLastModified() {
    return last_modified;
}

void File::insert(string newContent) {
    if (!active_version->isSnapshot()) {
        active_version->setContent(newContent);
        active_version->setModTime();
        updateLastModified();
    } else {
        TreeNode* newRoot = new TreeNode(total_versions, active_version->getContent() + newContent);
        newRoot->setParent(active_version);
        active_version->addChild(newRoot);
        active_version = newRoot;
        version_map.insert(newRoot->getVersion(), (void*)newRoot);
        updateLastModified();
        total_versions += 1;
    }
}

void File::update(string content) {
    if (!active_version->isSnapshot()) {
        active_version->replaceContent(content);
        active_version->setModTime();
        updateLastModified();
    } else {
        TreeNode* newRoot = new TreeNode(total_versions, content);
        newRoot->setParent(active_version);
        active_version->addChild(newRoot);
        active_version = newRoot;
        version_map.insert(newRoot->getVersion(), (void*)newRoot);
        updateLastModified();
        total_versions += 1;
    }
}

void File::snapshot(string message) {
    if (active_version->isSnapshot()) {
        cout << "ERROR: Active version is already a snapshot." << endl;
    } else {
        if (message.empty()) {
            cout << "ERROR: Snapshot message cannot be empty." << endl;
            return;
        }
        active_version->setSnapshot(message);
        cout << "Snapshot created for '" << fileName << "' with message: \"" << message << "\"" << endl;
    }
}

void File::rollback(int VersionID) {
    if (VersionID == -1) {
        if (active_version->getParent() != nullptr) {
            active_version = active_version->getParent();
        } else {
            cout << "ERROR: Cannot rollback. Already at the root version." << endl;
        }
    } else {
        TreeNode* node = getVerAdd(VersionID);
        if (node != nullptr) {
            active_version = node;
        } else {
            cout << "ERROR: Version ID " << VersionID << " does not exist!" << endl;
        }
    }
}

int File::getCurrVer() {
    if (active_version != nullptr) {
        return active_version->getVersion();
    } else {
        cout << "ERROR: No active version!";
        return -1;
    }
}

TreeNode* File::getVerAdd(int VersionID) {
    void* ptr = version_map.find(VersionID);
    if (ptr != nullptr) {
        return (TreeNode*)ptr;
    }
    return nullptr;
}

string File::getCurrCon() {
    if (active_version != nullptr) {
        return active_version->getContent();
    } else {
        cout << "ERROR: No active version!";
        return "";
    }
}

string File::getFileName() {
    return fileName;
}

int File::getTotalV() {
    return total_versions;
}

vector<string> File::getHistory() {
    vector<string> ans;
    vector<TreeNode*> path;
    TreeNode* curr = active_version;
    while (curr != nullptr) {
        if (curr->isSnapshot()) {
            path.push_back(curr);
        }
        curr = curr->getParent();
    }

    int n = path.size();
    for (int i = 0; i < n / 2; ++i) {
        swap(path[i], path[n - 1 - i]);
    }

    for (TreeNode* node : path) {
        string s;
        time_t snapTime = node->getSnapshotTime();
        string timeStr = ctime(&snapTime);
        if (!timeStr.empty() && timeStr.back() == '\n') {
            timeStr.pop_back();
        }
        s = "Version " + to_string(node->getVersion()) + ", Timestamp: " + timeStr + ", Message: " + node->getMessage();
        ans.push_back(s);
    }
    return ans;
}