# **Time-Travelling File System**

This project is a simple version control system, like a mini-Git, built from scratch in C++. It lets you create files, edit them, save versions (called "snapshots"), and look back at old versions. The whole system runs in memory.

## **How to Compile and Run**

1\. Compile the Code  
Place all the project files (.cpp and .hpp) in the same folder. Run the compile.bat script from your terminal:  
compile.bat

This will create an executable file named filesystem.exe.

2\. Run the Program  
To start the program, run the executable:  
filesystem.exe

The program will now wait for you to type in commands.

## **How It Works (The Big Picture)**

The program works by reading commands you type, one line at a time. The main FileSystem object keeps track of all your files.

* **Files and Versions:** Each file has its own history, which is stored like a tree. A new version of a file is just a new node in that tree.  
* **The Snapshot Rule:** This is the most important rule\! You can freely change the most recent version of a file with INSERT or UPDATE. However, once you use the SNAPSHOT command, that version is "frozen." The *next* time you INSERT or UPDATE, the program will automatically create a new version for your changes, leaving the old one untouched.

## **Data Structures Used**

As required by the assignment, the three main data structures were built from scratch.

### **1\. Tree (for Version History)**

Each file's history is a tree of versions. Each version (TreeNode) keeps track of:

* The file's **content** at that version.  
* A pointer to its **parent** version, which lets you go back in time (ROLLBACK and HISTORY).  
* A list of **child** versions for any new branches.

### **2\. HashMap (for Fast Lookups)**

A HashMap is used inside each File object to quickly find any version just by using its ID number.

* **How it works:** It uses a simple formula (key % capacity) to decide where to store each version.  
* **Collisions:** If two different version IDs happen to land in the same spot, it just creates a short linked list there to hold both.

### **3\. Heaps (for Analytics)**

Two Max-Heaps are used to quickly find the "top" files for the analytics commands.

* **Recent\_Heap:** Keeps the most recently modified file at the top. It compares files based on their last-edit timestamp.  
* **Big\_Heap:** Keeps the file with the most versions at the top. It compares files based on their total version count.

## **Commands Guide**

Here are all the commands the program understands:

| Command | Description | Example |
| :---- | :---- | :---- |
| CREATE \<filename\> | Creates a new, empty file. | CREATE notes.txt |
| READ \<filename\> | Shows the content of the current version of a file. | READ notes.txt |
| INSERT \<filename\> \<content\> | Adds content to the end of the current version. | INSERT notes.txt Hello |
| UPDATE \<filename\> \<content\> | Replaces the current version's content completely. | UPDATE notes.txt New text |
| SNAPSHOT \<filename\> \<message\> | "Freezes" the current version with a save message. | SNAPSHOT notes.txt First draft |
| ROLLBACK \<filename\> \[id\] | Goes back to a previous version. No ID means go to parent. | ROLLBACK notes.txt 1 |
| HISTORY \<filename\> | Shows the list of all saved snapshots for a file. | HISTORY notes.txt |
| RECENT\_FILES \[num\] | Lists the most recently edited files. | RECENT\_FILES 3 |
| BIGGEST\_TREES \[num\] | Lists the files that have the most versions. | BIGGEST\_TREES 3 |
| EXIT | Closes the program. | EXIT |

## **Error Handling**

The program tries to handle mistakes very efficiently. If you give a command for a file that doesn't exist, provide the wrong number of arguments, or try to roll back past the beginning, it will print a clear ERROR: message explaining what went wrong.