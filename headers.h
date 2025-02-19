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

void open_file(vector<letter> &freq, string file_name);
void sorted_freq(vector<letter> &freq);
void sorted_nodes_created(vector<struct node *> &nodes, vector<letter> &freq);
bool support_stable_sort_func(struct node *a, struct node *b);
void haffman_tree(vector<struct node *> &nodes);