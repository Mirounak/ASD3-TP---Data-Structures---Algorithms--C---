#include <iostream>
#include <vector>

using namespace std;

struct Node {
string name; // file/folder name
string type; // "file" or "folder"
int size; // size in KB, (Files have size, folders size = 0)

vector <Node*> children; //subfiles/subfolders (only for folders)
Node(string n, string t, int s) : name(n), type(t), size(s) {}
};

// Add a file/folder under a given folder
void add(Node* parent, string name, string type, int size = 0) {
    Node* newNode = new Node(name, type, size);
    if (type == "file" && size <= 0) {
        cerr << "Error: File size must be greater than 0." << endl;
        delete newNode; 
        return;
    }
    if (type != "file" && type != "folder") {
        cerr << "Error: Type must be 'file' or 'folder'." << endl;
        delete newNode; 
        return;
    }
    if (type == "file" && parent->type != "folder") {
        cerr << "Error: Cannot add a file under a non-folder." << endl;
        delete newNode; 
        return;
    }
    parent->children.push_back(newNode);
}

// Compute the total size of a folder (DFS) 
// Total size = sum of sizes of all descendants. 
/* Algorithm (DFS) 
1. Start at folder node 
2.For each child: 
o If file → add its size 
o If folder → recursive DFS 
3.Return accumulated size
*/

int computeFolderSize(Node* folder) {
    if (folder->type != "folder") {
        cerr << "Error: Only folders can have their size computed." << endl;
        return 0;
    }
    
    int totalSize = 0;
    for (Node* child : folder->children) {
        if (child->type == "file") {
            totalSize += child->size;
        } else if (child->type == "folder") {
            totalSize += computeFolderSize(child);
        }
    }
    return totalSize;
}

/*List all files using BFS (breadth-first search)
Use BFS algorithm to print each folder with all its files, level by level. 
Example
Folder: /
Files: ...
Folder: Documents
Files: ...
Folder: Images
Files: ...
...
​*/

void listFilesBFS(Node* root){
    if (root->type != "folder") {
        cerr << "Error: Only folders can be listed." << endl;
        return;
    }

    vector<Node*> queue;
    queue.push_back(root);

    while (!queue.empty()) {
        Node* current = queue.front();
        queue.erase(queue.begin());

        cout << "Folder: " << current->name << endl;
        cout << "Files: ";
        for (Node* child : current->children) {
            if (child->type == "file") {
                cout << child->name << " ";
            } else if (child->type == "folder") {
                queue.push_back(child);
            }
        }
        cout << endl;
    }
}

/*Find the deepest file path.
A path is something like:
Root/ Documents/ Projects/ Work/ A1/report.txt

Use DFS algorithm:  
• Traverse the entire tree
• Maintain:
-currentDepth 
-maxDepth 
-currentPath
-bestPath
• Update bestPath when a leaf file at deeper level is found
*/

void dfsDeepestFile(Node* root, vector<string>& currentPath, int currentDepth, int& maxDepth, vector<string>& bestPath) {
    if (root->type == "file") {
        if (currentDepth > maxDepth) {
            maxDepth = currentDepth;
            bestPath = currentPath;
            bestPath.push_back(root->name);
        }
        return;
    }

    for (Node* child : root->children) {
        currentPath.push_back(child->name);
        dfsDeepestFile(child, currentPath, currentDepth + 1, maxDepth, bestPath);
        currentPath.pop_back();
    }
}

vector<string> findDeepestFilePath(Node* root) {
    vector<string> currentPath;
    vector<string> bestPath;
    int maxDepth = -1;
    currentPath.push_back(root->name);
    dfsDeepestFile(root, currentPath, 0, maxDepth, bestPath);
    return bestPath;
}

/*
The program must:
• Start with a root folder: "Root" or "/".
• Provide a menu-like interface to test functions:
1. Add file/folder 
2.Compute folder size
3.List files (BFS)
4.Show deepest file path
5.Exit 
Edge Cases to Handle:
• Adding a file under a non-existing folder
• Adding a folder under a file (must be rejected)
• Two subitems with the same name under one folder
• Folder with no children (size = 0)
• Multiple deepest paths (choose any or take lexicographically smallest)
​*/

int main() {
    Node* root = new Node("/", "folder", 0);
    int choice;
    
    add(root, "Documents", "folder");
    add(root, "Images", "folder");
    add(root, "Documents/Projects", "folder");
    add(root->children[0], "file1.txt", "file", 10);
    add(root->children[0], "file2.txt", "file", 20);
    add(root->children[1], "image1.png", "file", 30);
    add(root->children[2], "Work", "folder");
    add(root->children[2], "A1", "folder");

    do {
        cout << "Menu:\n1. Add file/folder\n2. Compute folder size\n3. List files (BFS)\n4. Show deepest file path\n5. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            string parentName, name, type;
            int size = 0;
            cout << "Enter parent folder name: ";
            cin >> parentName;
            cout << "Enter name of file/folder to add: ";
            cin >> name;
            cout << "Enter type (file/folder): ";
            cin >> type;
            if (type == "file") {
                cout << "Enter size (KB): ";
                cin >> size;
            }

            // Find parent folder
            vector<Node*> queue = {root};
            Node* parent = nullptr;
            while (!queue.empty()) {
                Node* current = queue.front();
                queue.erase(queue.begin());
                if (current->name == parentName && current->type == "folder") {
                    parent = current;
                    break;
                }
                for (Node* child : current->children) {
                    if (child->type == "folder") {
                        queue.push_back(child);
                    }
                }
            }

            if (parent) {
                add(parent, name, type, size);
            } else {
                cout << "Parent folder not found or is not a folder." << endl;
            }

        } else if (choice == 2) {
            string folderName;
            cout << "Enter folder name to compute size: ";
            cin >> folderName;

            // Find folder
            vector<Node*> queue = {root};
            Node* folder = nullptr;
            while (!queue.empty()) {
                Node* current = queue.front();
                queue.erase(queue.begin());
                if (current->name == folderName && current->type == "folder") {
                    folder = current;
                    break;
                }
                for (Node* child : current->children) {
                    if (child->type == "folder") {
                        queue.push_back(child);
                    }
                }
            }

            if (folder) {
                int size = computeFolderSize(folder);
                cout << "Total size of folder '" << folderName << "' is: " << size
                        << " KB" << endl;
            } else {
                cout << "Folder not found." << endl;
            }
        } else if (choice == 3) {
            listFilesBFS(root);
        } else if (choice == 4) {
            vector<string> deepestPath = findDeepestFilePath(root);
            cout << "Deepest file path: ";
            for (const string& part : deepestPath) {
                cout << part << "/";
            }
            cout << endl;
        }   
    } while (choice != 5);

 return 0;

}