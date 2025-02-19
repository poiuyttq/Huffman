#pragma once
#include <vector>
#include <map>
#include <cstdio>
#include <string>
using namespace std;
#define SIZE 256
#define MAX_COUNT_NODES 511
struct letter
{
    int key;
    int count;
};

typedef struct node {
	unsigned char symb; //<-freq.key
	unsigned char isSymb; //лист или не лист
	unsigned int freq; //<-freq.count
	string code;
	int level; 
	struct node * left, *right, *parent;
}NODE;

void sorted_nodes_created(vector<struct node *> &nodes, vector<letter> &freq);
void inorder(struct node* root,string code);
void print_code_to_file(vector <struct node*> &nodes, string file_name, string file_name1);