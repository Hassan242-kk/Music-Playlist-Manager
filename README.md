#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>

using namespace std;

struct node
{
    char song[100];
    struct node *next;
    struct node *prev;
}*top,*temp,*top1;
void tofile(char a[])
{
    fstream f1;
    f1.open("playlist.txt",ios::out|ios::app);
    f1<<a<<endl;
    f1.close();
}

void add_node(struct node *first)
    {
    char a[100];
    while(first->next!=NULL)
    {
        first=first->next;
    }
    first->next=(struct node*)malloc(sizeof(struct node));
    first->prev=first;
    first=first->next;
    cout<<"\n\a\a\a\aEnter Song name-  ";
    scanf("%s",&a);
    strcpy(first->song,a);
    tofile(a);
    first->next=NULL;
}
void add_node_file(struct node *first,string a)
    {
    while(first->next!=NULL)
    {
        first=first->next;
    }
    first->next=(struct node*)malloc(sizeof(struct node));
    first->prev=first;
    first=first->next;
    strcpy(first->song,a.c_str());
    first->next=NULL;
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


void del_node(struct node *first)
{
    while((first->next)->next!=NULL)
    {
        first=first->next;
    }
    struct node *temp;
    temp=(first->next)->next;
    first->next=NULL;
    free(temp);
   cout<<"Deleted"<<endl;
}
void printlist(struct node *first)
{
    cout<<"\nPlaylist Name- ";
    while(first->next!=NULL)
    {
        cout<<first->song<<endl;
        first=first->next;
    }
    cout<<first->song<<endl;
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

