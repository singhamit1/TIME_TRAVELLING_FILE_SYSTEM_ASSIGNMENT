#include "filesystem.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    FileSystem fs;
    string command;

    while (cin >> command) {
        if (command == "CREATE") {
            string filename;
            cin >> filename;
            fs.createFile(filename);
        } else if (command == "READ") {
            string filename;
            cin >> filename;
            string content = fs.readfile(filename);
            if (content.empty()) { // The second check handles non-existent files
                cout << "File is empty" << endl;
            }else if(!content.empty()){
                cout << content << endl;
            }
        } else if (command == "INSERT") {
            string filename, content;
            cin >> filename;
            // This reads the rest of the *same line* for content.
            getline(cin, content); 

            // Remove the leading space, if it exists
            if (!content.empty() && content[0] == ' ') {
                content = content.substr(1);
            }
            fs.insertFile(filename, content);
        } else if (command == "UPDATE") {
            string filename, content;
            cin >> filename;
            getline(cin, content);

            if (!content.empty() && content[0] == ' ') {
                content = content.substr(1);
            }
            fs.updateFile(filename, content);
        } else if (command == "SNAPSHOT") {
            string filename, message;
            cin >> filename;
            getline(cin, message);

            if (!message.empty() && message[0] == ' ') {
                message = message.substr(1);
            }
            fs.snapshotFile(filename, message);
        } else if (command == "ROLLBACK") {
            string filename;
            cin >> filename;
            if (cin.peek() != '\n' && cin.peek() != EOF) {
                int versionID;
                if (cin >> versionID) {
                    fs.rollbackFile(filename, versionID);
                } else {
                    cout << "ERROR: Invalid Version ID provided." << endl;
                    cin.clear();
                    string dummy;
                    getline(cin, dummy);
                }
            } else {
                fs.rollbackFile(filename, -1);
            }
        } else if (command == "HISTORY") {
            string filename;
            cin >> filename;
            fs.getFileHistory(filename);
        } else if (command == "RECENT_FILES") {
            int num = 2147483647;
            if (cin.peek() != '\n' && cin.peek() != EOF) {
                cin >> num;
            }
            cout << "--- Recent Files ---" << endl;
            int count;
            if (num < RecentFile.size()) {
                count = num;
            } else {
                count = RecentFile.size();
            }
            if (count == 0) {
                cout << "No files to show." << endl;
            } else {
                vector<File*> sortedFiles = RecentFile.getSortedFiles(count);
                for (File* file : sortedFiles) {
                    cout << file->getFileName() << endl;
                }
            }
        } else if (command == "BIGGEST_TREES") {
            int num = 2147483647;
            if (cin.peek() != '\n' && cin.peek() != EOF) {
                cin >> num;
            }
            cout << "--- Biggest Trees ---" << endl;
            int count;
        if (num < BiggestFile.size()) {
            count = num;
        } else {
            count = BiggestFile.size();
        }
            if (count == 0) {
                cout << "No files to show." << endl;
            } else {
                vector<File*> sortedFiles = BiggestFile.getSortedFiles(count);
                for (File* file : sortedFiles) {
                    cout << file->getFileName() << " (" << file->getTotalV() << " versions)" << endl;
                }
            }
        }else if (command == "EXIT") {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }
        else {
            cout << "ERROR: Unknown command '" << command << "'" << endl;
            string dummy;
            getline(cin, dummy);
        }
    }
    return 0;
}