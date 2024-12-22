#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<unordered_map>
#include<vector>
using namespace std;

struct node
{
    char song[100];
    struct node *next;
    struct node *prev;
}*top,*temp,*top1;
struct TreeNode {
    char song[100];
    TreeNode* left;
    TreeNode* right;

TreeNode(const char* songName) {
        strcpy(song, songName);
        left = right = nullptr;
    }
};
TreeNode* root = nullptr; 


unordered_map<string, vector<string>> playlistMap;

// Function to insert song into BST
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
void tofile(char a[])
{
    fstream f1;
    f1.open("playlist.txt",ios::out|ios::app);
    f1<<a<<endl;
    f1.close();
}

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

   root = insertBST(root, newNode->song);
}


void push(char data[])
{
    if (top == NULL)
    {
        top =(struct node *)malloc(sizeof(struct node));
        top->next = NULL;
        strcpy(top->song,data);
    }
    else if (strcmp(top->song,data)!=0)
    {
        temp =(struct node *)malloc(sizeof(struct node));
        temp->next = top;
        strcpy(temp->song,data);
        top = temp;
    }
}

void delete_file(char a[])
{
    fstream f1,f2;
    string line;
    int x=0;
    f1.open("playlist.txt",ios::in|ios::out);
    f2.open("temp.txt",ios::in|ios::out);
    while(!f1.eof())
    {
        getline(f1,line);
        if(strcmp(a,line.c_str())!=0)
        f2<<line<<endl;
        else if (strcmp(a,line.c_str())==0)
        x=1;
    }
    f1.close();
    f2.close();
    remove("playlist.txt");
    rename("temp.txt","playlist.txt");
    if(x==0)
        {
        cout << "There is no song with name you entered." << endl;
        }
    else
        {
        cout << "Song has been deleted." << endl;
        }
    }

void deleteSong(struct node* start, const string& songName) {
    char songCStr[songName.size() + 1];
    strcpy(songCStr, songName.c_str());

    
struct node* current = start;
    struct node* previous = nullptr;
    bool foundInList = false;

while (current != nullptr) {
        if (strcmp(current->song, songCStr) == 0) { // Found the song
            foundInList = true;

           
 if (previous != nullptr) {
                previous->next = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = previous;
            }

            // Free memory
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

    // 2. Delete from the file
delete_file(songCStr);

    
}
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

        // Copy the inorder successor's content to this node
strcpy(root->song, temp->song);

        
 root->right = deleteFromBST(root->right, temp->song);
    }
    return root;
}
void add_node_file(struct node* first, string a) {
    while (first->next != NULL) {
        first = first->next;
    }
    first->next = (struct node*)malloc(sizeof(struct node));
    first->prev = first;
    first = first->next;
    strcpy(first->song, a.c_str());
    first->next = NULL;

    // Add to the BST
 root = insertBST(root, a.c_str());
}

// Functions for the binary search tree
void displayInOrder(TreeNode* node) {
    if (node == nullptr) return;
    displayInOrder(node->left);
    cout << node->song << endl;
    displayInOrder(node->right);
}
bool searchBST(TreeNode* node, const char* song) {
    if (node == nullptr) return false;
    if (strcmp(node->song, song) == 0) return true;
    if (strcmp(song, node->song) < 0) return searchBST(node->left, song);
    return searchBST(node->right, song);
}
void sort(struct node*& head) {
    if (head == NULL || head->next == NULL) {
        return; // Nothing to sort if the list is empty or has only one element
    }

 bool swapped;
    struct node* ptr1;
    struct node* lptr = NULL; 

 do {
        swapped = false;
        ptr1 = head;

while (ptr1->next != lptr) {
            if (strcmp(ptr1->song, ptr1->next->song) > 0) {
                // Swap the song names
                char temp[100];
                strcpy(temp, ptr1->song);
                strcpy(ptr1->song, ptr1->next->song);
                strcpy(ptr1->next->song, temp);
   swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; // Move the last pointer to the last sorted element
    } while (swapped);
}

bool searchSongInBST(const char* song) {
    return searchBST(root, song);
}
void create() {
    top = NULL;
}

void printlist(struct node* first) {
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
void display()
{
    top1 = top;
    if (top1 == NULL)
    {
        printf("\n\a\a\a\a=>NO recently played tracks.\n");
        return;
    }
    printf("\n\a\a\a\a#Recently played tracks-\n");
    while (top1 != NULL)
    {
        printf("%s", top1->song);
        printf("\n");
        top1 = top1->next;
    }
 }

void recent(){
    display();
}
void search1(struct node* first) {
    char song[100];
    cout << "\nEnter song To be Searched- ";
    scanf("%s", &song);

    if (searchSongInBST(song)) {
        cout << "\n#Song Found in BST" << endl;
    }
    else {
        cout << "\n#Song Not found" << endl;
    }
}

void play(struct node* first) {
    char song[100];
    printlist(first);
    cout << "\nChoose song you wish to play- ";
    scanf("%s", song);
    int flag = 0;

 while (first != NULL) {
        if (strcmp(first->song, song) == 0) {
            cout << "\n=>Now Playing......" << song << endl;
            flag++;
            push(song);
            break;
        }
        else {
            first = first->next;
        }
    }
    if (flag == 0) {
        cout << "\n#Song Not found" << endl;
    }
}
void addplaylist(struct node* start) {
    fstream f1;
    string line;
    f1.open("playlists.txt", ios::in);
    while (getline(f1, line)) {
        add_node_file(start, line);
    }
    cout << "Playlist Added" << endl;
    f1.close();
}
void count_nodes(struct node *first)
{
    int i=0;
    while (first->next!=NULL)
    {
        first=first->next;
        i++;
    }
    i++;
    cout<<"\nTotal songs-  "<<i-1<<endl;
}
struct node  *del_pos(struct node *pointer, int pos)
{
        struct node *n1,*prev1,*temp;
           prev1= ( struct node *)malloc(sizeof(node));
           temp= (struct node *)malloc(sizeof(node));
           int i=0;
           if(pos==1)
           {
                temp=pointer;
                delete_file(temp->song);
                pointer=pointer->next;
                pointer->prev = NULL;
                free(temp);
                 printf("\nThe list is updated\nUse the display function to check\n");
                 return pointer;
           }
           while(i<pos-1)
           {
               prev1=pointer;
               pointer=pointer->next;
                i++;
                }
                if(pointer->next==NULL)
            {
            temp=pointer;
            delete_file(temp->song);
            prev1->next->prev=NULL;
            prev1->next=NULL;
            free(temp);
             printf("\nThe list is updated\nUse the display function to check\n");
          }
          else
            {
            temp=pointer;
            delete_file(temp->song);
            prev1->next=temp->next;
            temp->next->prev=prev1;
            free(temp);
             printf("\nThe list is updated\nUse the display function to check\n");
            }

}
void search1(struct node *first)
{
    char song[100];
    cout<<"\n\a\a\a\aEnter song To be Searched- ";
    scanf("%s",&song);
    int flag=0;

while(first!=NULL)
    {
        if(strcmp(first->song,song)==0)
        {
            cout<<"\n\a\a\a\a#Song Found"<<endl;
            flag++;
            break;
        }
        else
        {
            first=first->next;
        }
    }
    if(flag==0)
    {
        cout<<"\n\a\a\a\a#Song Not found"<<endl;
    }
}

void create()
{
    top = NULL;
}

