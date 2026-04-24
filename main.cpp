#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<unordered_map>
#include<vector>

using namespace std;

// Hassan Khalid
// Reg No : 2023242
// Faculty : Software Engineering
// ============================================================
// DSA CONCEPTS USED:
// 1. Doubly Linked List  - stores playlist songs
// 2. Stack (Linked List) - stores recently played songs
// 3. Binary Search Tree  - for fast song search & sorted display
// 4. HashMap             - stores named playlists
// 5. Bubble Sort         - sorts the linked list
// 6. File Handling       - persistent storage
// ============================================================

// Node structure for the doubly linked list
struct node {
    char song[100];
    struct node* next;
    struct node* prev;
} *top, *temp, *top1;

// Node structure for the binary search tree
struct TreeNode {
    char song[100];
    TreeNode* left;
    TreeNode* right;

    TreeNode(const char* songName) {
        strcpy(song, songName);
        left = right = nullptr;
    }
};

TreeNode* root = nullptr; // Root of the BST

// HashMap to store playlists (key: playlist name, value: list of songs)
unordered_map<string, vector<string>> playlistMap;

// ============================================================
// BST FUNCTIONS
// ============================================================

// Insert song into BST
TreeNode* insertBST(TreeNode* node, const char* song) {
    if (node == nullptr) {
        return new TreeNode(song);
    }
    if (strcmp(song, node->song) < 0) {
        node->left = insertBST(node->left, song);
    } else if (strcmp(song, node->song) > 0) {
        node->right = insertBST(node->right, song);
    }
    return node;
}

// Search in BST
bool searchBST(TreeNode* node, const char* song) {
    if (node == nullptr) return false;
    if (strcmp(node->song, song) == 0) return true;
    if (strcmp(song, node->song) < 0) return searchBST(node->left, song);
    return searchBST(node->right, song);
}

// Display BST in sorted order (In-order traversal)
void displayInOrder(TreeNode* node) {
    if (node == nullptr) return;
    displayInOrder(node->left);
    cout << node->song << endl;
    displayInOrder(node->right);
}

// Delete from BST
TreeNode* deleteFromBST(TreeNode* root, const char* song) {
    if (root == nullptr) {
        return nullptr;
    }
    if (strcmp(song, root->song) < 0) {
        root->left = deleteFromBST(root->left, song);
    } else if (strcmp(song, root->song) > 0) {
        root->right = deleteFromBST(root->right, song);
    } else {
        // Node to be deleted found
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // Node with two children: Get the inorder successor
        TreeNode* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        strcpy(root->song, temp->song);
        root->right = deleteFromBST(root->right, temp->song);
    }
    return root;
}

bool searchSongInBST(const char* song) {
    return searchBST(root, song);
}

// ============================================================
// FILE FUNCTIONS
// ============================================================

// Write new song to file
void tofile(char a[]) {
    fstream f1;
    f1.open("playlists.txt", ios::out | ios::app);
    f1 << a << endl;
    f1.close();
}

// Delete song from file
void delete_file(char a[]) {
    fstream f1, f2;
    string line;
    int x = 0;
    f1.open("playlists.txt", ios::in);
    f2.open("temp.txt", ios::out);
    while (getline(f1, line)) {
        if (strcmp(a, line.c_str()) != 0)
            f2 << line << endl;
        else
            x = 1;
    }
    f1.close();
    f2.close();
    remove("playlists.txt");
    rename("temp.txt", "playlists.txt");
    if (x == 0) {
        cout << "There is no song with the name you entered." << endl;
    } else {
        cout << "Song has been deleted from file." << endl;
    }
}

// ============================================================
// DOUBLY LINKED LIST FUNCTIONS
// ============================================================

// Add node to doubly linked list
void add_node(struct node* first, const string& song) {
    while (first->next != NULL) {
        first = first->next;
    }
    node* newNode = new node();
    strncpy(newNode->song, song.c_str(), sizeof(newNode->song) - 1);
    newNode->song[sizeof(newNode->song) - 1] = '\0';
    newNode->next = NULL;
    newNode->prev = first;
    first->next = newNode;

    // Add to BST
    root = insertBST(root, newNode->song);

    // FIX: Save to file
    tofile(newNode->song);
}

// Add node from file (no file write needed)
void add_node_file(struct node* first, string a) {
    while (first->next != NULL) {
        first = first->next;
    }
    struct node* newNode = new node();
    strncpy(newNode->song, a.c_str(), sizeof(newNode->song) - 1);
    newNode->song[sizeof(newNode->song) - 1] = '\0';
    newNode->next = NULL;
    newNode->prev = first;  // FIX: was wrongly set to 'first = first->next' before
    first->next = newNode;

    // Add to BST
    root = insertBST(root, a.c_str());
}

// Delete song from linked list, file, and BST
void deleteSong(struct node* start, const string& songName) {
    // FIX: Use a fixed-size array instead of VLA
    char songCStr[100];
    strncpy(songCStr, songName.c_str(), sizeof(songCStr) - 1);
    songCStr[sizeof(songCStr) - 1] = '\0';

    // 1. Delete from linked list
    struct node* current = start->next; // skip dummy head
    struct node* previous = start;
    bool foundInList = false;

    while (current != nullptr) {
        if (strcmp(current->song, songCStr) == 0) {
            foundInList = true;
            previous->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = previous;
            }
            delete current;
            break;
        }
        previous = current;
        current = current->next;
    }

    if (foundInList) {
        cout << "Song '" << songName << "' deleted from playlist." << endl;
    } else {
        cout << "Song '" << songName << "' not found in playlist." << endl;
    }

    // 2. Delete from file
    delete_file(songCStr);

    // 3. Delete from BST
    root = deleteFromBST(root, songCStr);
}

// Print the linked list
void printlist(struct node* first) {
    first = first->next; // skip dummy head
    if (first == NULL) {
        cout << "Playlist is empty." << endl;
        return;
    }
    cout << "Playlist Songs: " << endl;
    while (first != NULL) {
        cout << first->song << endl;
        first = first->next;
    }
}

// Count songs in linked list
void count_nodes(struct node* start) {
    int i = 0;
    start = start->next; // skip dummy head
    while (start != NULL) {
        start = start->next;
        i++;
    }
    cout << "\nTotal songs- " << i << endl;
}

// Bubble Sort on linked list
void sort(struct node*& head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    bool swapped;
    struct node* ptr1;
    struct node* lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->song, ptr1->next->song) > 0) {
                char temp[100];
                strcpy(temp, ptr1->song);
                strcpy(ptr1->song, ptr1->next->song);
                strcpy(ptr1->next->song, temp);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// ============================================================
// STACK FUNCTIONS (Recently Played)
// ============================================================

void create() {
    top = NULL;
}

// Push recently played song onto stack
void push(char data[]) {
    if (top == NULL) {
        top = (struct node*)malloc(sizeof(struct node));
        top->next = NULL;
        strcpy(top->song, data);
    } else if (strcmp(top->song, data) != 0) {
        temp = (struct node*)malloc(sizeof(struct node));
        temp->next = top;
        strcpy(temp->song, data);
        top = temp;
    }
}

// Display recently played songs (stack)
void display() {
    top1 = top;
    if (top1 == NULL) {
        cout << "\nNo recently played tracks." << endl;
        return;
    }
    cout << "\nRecently played tracks-" << endl;
    while (top1 != NULL) {
        cout << top1->song << endl;
        top1 = top1->next;
    }
}

void recent() {
    display();
}

// Show last played song (top of stack)
void topelement() {
    if (top == NULL) {
        cout << "\nNo last played tracks." << endl;
        return;
    }
    cout << "\nLast Played Song - " << top->song << endl;
}

// ============================================================
// SEARCH & PLAY FUNCTIONS
// ============================================================

void search1(struct node* first) {
    char song[100];
    cout << "\nEnter song to be searched- ";
    cin >> song;  // FIX: removed '&' from scanf, use cin instead

    if (searchSongInBST(song)) {
        cout << "\nSong Found in BST!" << endl;
    } else {
        cout << "\nSong Not Found." << endl;
    }
}

void play(struct node* first) {
    char song[100];
    printlist(first);
    cout << "\nChoose song you wish to play- ";
    cin >> song;
    int flag = 0;

    struct node* current = first->next; // skip dummy head
    while (current != NULL) {
        if (strcmp(current->song, song) == 0) {
            cout << "\nNow Playing...... " << song << endl;
            flag++;
            push(song);
            break;
        }
        current = current->next;
    }
    if (flag == 0) {
        cout << "\nSong Not Found." << endl;
    }
}

// ============================================================
// FILE LOAD FUNCTION
// ============================================================

void initializeFromFile(struct node* start) {
    fstream f1;
    string line;
    f1.open("playlists.txt", ios::in);
    while (getline(f1, line)) {
        if (!line.empty())
            add_node_file(start, line);
    }
    f1.close();
}

void addplaylist(struct node* start) {
    initializeFromFile(start);
    cout << "Playlist loaded from file." << endl;
}

// ============================================================
// HASHMAP PLAYLIST FUNCTIONS
// ============================================================

void addSongToPlaylist(const string& playlistName, const string& song) {
    playlistMap[playlistName].push_back(song);
    cout << "Song added to playlist '" << playlistName << "'." << endl;
}

void displayPlaylistFromMap(const string& playlistName) {
    if (playlistMap.find(playlistName) != playlistMap.end()) {
        cout << "Songs in Playlist '" << playlistName << "':" << endl;
        for (const string& song : playlistMap[playlistName]) {
            cout << song << endl;
        }
    } else {
        cout << "Playlist not found!" << endl;
    }
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    int choice;
    struct node* start;
    start = (struct node*)malloc(sizeof(struct node));
    start->next = NULL;
    start->prev = NULL;

    cout << "=============================" << endl;
    cout << "   MUSIC PLAYLIST MANAGER   " << endl;
    cout << "=============================" << endl;
    cout << "Please use '_' for spaces in song names." << endl;

    create();

    // Load songs from file at startup
    initializeFromFile(start);

    do {
        cout << "\n========== MENU ==========" << endl;
        cout << "1.  Add Song to Playlist" << endl;
        cout << "2.  Delete Song" << endl;
        cout << "3.  Display Playlist" << endl;
        cout << "4.  Total Songs" << endl;
        cout << "5.  Search Song (BST)" << endl;
        cout << "6.  Play Song" << endl;
        cout << "7.  Recently Played (Stack)" << endl;
        cout << "8.  Last Played Song" << endl;
        cout << "9.  Display Sorted Playlist (Bubble Sort)" << endl;
        cout << "10. Load Playlist from File" << endl;
        cout << "11. Display Songs in BST Order" << endl;
        cout << "12. Display Playlist from HashMap" << endl;
        cout << "13. Exit" << endl;
        cout << "==========================" << endl;
        cout << "Enter your choice- ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string playlistName, song;
                cout << "Enter Playlist Name: ";
                cin.ignore();
                getline(cin, playlistName);
                cout << "Enter Song Name: ";
                getline(cin, song);
                add_node(start, song);          // Add to doubly linked list + BST + file
                addSongToPlaylist(playlistName, song); // Add to HashMap
                break;
            }
            case 2: {
                string songToDelete;
                cout << "Enter the name of the song to delete: ";
                cin.ignore();
                getline(cin, songToDelete);
                deleteSong(start, songToDelete); // Delete from list + file + BST
                break;
            }
            case 3:  printlist(start); break;
            case 4:  count_nodes(start); break;
            case 5:  search1(start); break;
            case 6:  play(start); break;
            case 7:  recent(); break;
            case 8:  topelement(); break;
            case 9:
                sort(start->next);
                printlist(start);
                break;
            case 10: addplaylist(start); break;
            case 11:
                cout << "\nSongs in BST (Sorted Order):" << endl;
                displayInOrder(root);
                break;
            case 12: {
                string playlistName;
                cout << "Enter Playlist Name to Display: ";
                cin.ignore();
                getline(cin, playlistName);
                displayPlaylistFromMap(playlistName);
                break;
            }
            case 13:
                cout << "Goodbye!" << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 13);

    return 0;
}