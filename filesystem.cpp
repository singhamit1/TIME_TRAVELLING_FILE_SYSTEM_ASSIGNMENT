#include "filesystem.hpp"
#include <iostream>

using namespace std;

// Define the global heap variables here, in one .cpp file.
Recent_Heap RecentFile;
Big_Heap BiggestFile;

void FileSystem::createFile(string filename) {
    for (int i = 0; i < info.size(); i++) {
        if (info[i]->getFileName() == filename) {
            cout << "ERROR: File '" << filename << "' already exists!" << endl;
            return;
        }
    }
    File* newfile = new File(filename);
    info.push_back(newfile);
    RecentFile.insert(newfile);
    BiggestFile.insert(newfile);
    cout << "File '" << filename << "' created successfully." << endl;
}

string FileSystem::readfile(string name) {
    for (int i = 0; i < info.size(); i++) {
        if (info[i]->getFileName() == name) {
            return info[i]->getCurrCon();
        }
    }
    cout << "ERROR: File '" << name << "' does not exist!" << endl;
    return "";
}

void FileSystem::insertFile(string name, string content) {
    File* targetFile = nullptr;
    for (int i = 0; i < info.size(); i++) {
        if (info[i]->getFileName() == name) {
            targetFile = info[i];
            break;
        }
    }
    if (targetFile != nullptr) {
        targetFile->insert(content);
        cout << "Content inserted into '" << name << "'. Active version is now " << targetFile->getCurrVer() << "." << endl;
        RecentFile.insert(targetFile);
        BiggestFile.insert(targetFile);
    } else {
        cout << "ERROR: File '" << name << "' does not exist!" << endl;
    }
}

void FileSystem::updateFile(string name, string content) {
    File* targetFile = nullptr;
    for (int i = 0; i < info.size(); i++) {
        if (info[i]->getFileName() == name) {
            targetFile = info[i];
            break;
        }
    }
    if (targetFile != nullptr) {
        targetFile->update(content);
        cout << "Content of '" << name << "' updated. Active version is now " << targetFile->getCurrVer() << "." << endl;
        RecentFile.insert(targetFile);
        BiggestFile.insert(targetFile);
    } else {
        cout << "ERROR: File '" << name << "' does not exist!" << endl;
    }
}

void FileSystem::snapshotFile(string name, string message) {
    for (int i = 0; i < info.size(); i++) {
        if (info[i]->getFileName() == name) {
            info[i]->snapshot(message);
            return;
        }
    }
    cout << "ERROR: File '" << name << "' does not exist!" << endl;
}

void FileSystem::rollbackFile(string name, int versionID) {
    for (int i = 0; i < info.size(); i++) {
        if (info[i]->getFileName() == name) {
            int oldVersion = info[i]->getCurrVer();
            info[i]->rollback(versionID);
            int newVersion = info[i]->getCurrVer();
            if (oldVersion != newVersion) {
                if (versionID == -1) {
                    cout << "File '" << name << "' rolled back to parent version " << newVersion << "." << endl;
                } else {
                    cout << "File '" << name << "' rolled back to version " << newVersion << "." << endl;
                }
            }
            return;
        }
    }
    cout << "ERROR: File '" << name << "' does not exist!" << endl;
}

void FileSystem::getFileHistory(string name) {
    for (int i = 0; i < info.size(); i++) {
        if (info[i]->getFileName() == name) {
            cout << "History for '" << name << "':" << endl;
            vector<string> history = info[i]->getHistory();
            if (history.empty()) {
                cout << "No snapshots found in the current path to root." << endl;
            } else {
                for (const string& entry : history) {
                    cout << " - " << entry << endl;
                }
            }
            return;
        }
    }
    cout << "ERROR: File '" << name << "' does not exist!" << endl;
}