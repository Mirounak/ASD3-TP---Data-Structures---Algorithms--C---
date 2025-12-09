#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Very simple Node
struct Node {
    string name;
    string type; // file/folder
    int size;    
    vector<Node*> children;

    Node(string n, string t, int s = 0) {
        name = n;
        type = t;
        size = s;
    }
};

// Create root folder
Node* root = new Node("/", "folder", 0);

// Simple add (only under root)
void add(Node* parent, string name, string type, int size = 0) {
    if (parent->type != "folder") {
        cout << "Error: cannot add under a file!\n";
        return;
    }

    if (type == "file" && size <= 0) {
        cout << "Error: file size must be positive!\n";
        return;
    }

    if (type == "folder") size = 0;

    parent->children.push_back(new Node(name, type, size));
    cout << type << " '" << name << "' added!\n";
}

// Show all files and folders under root
void show(Node* folder) {
    cout << "\nRoot content:\n";
    for (Node* child : folder->children) {
        if (child->type == "file")
            cout << "File: " << child->name << " (" << child->size << " KB)\n";
        else
            cout << "Folder: " << child->name << "\n";
    }
}


int computeSize(Node* folder) {
    int total = 0;

    for (Node* child : folder->children) {
        if (child->type == "file")
            total += child->size;
    }

    return total;
}





int main() {
    int choice;

    while (true) {
        cout << "\n--- Simple File System ---\n";
        cout << "1. Add file/folder\n";
        cout << "2. Show all\n";
        cout << "3. Compute total size\n";
        cout << "4. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            string name, type;
            int size;

            cout << "Enter name: ";
            cin >> name;

            cout << "Enter type (file/folder): ";
            cin >> type;

            if (type == "file") {
                cout << "Enter size: ";
                cin >> size;
            } else size = 0;

            add(root, name, type, size);
        }
        else if (choice == 2) {
            show(root);
        }
        else if (choice == 3) {
            cout << "Total size = " << computeSize(root) << " KB\n";
        }
        else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}