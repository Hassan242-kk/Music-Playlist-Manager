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
