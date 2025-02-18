#include "headers.h"
#include <iostream>
#include <vector>
using namespace std;
void sorted_nodes_created(vector<struct node *> &nodes, vector<letter> &freq)
{
    for (int i = 0; i < SIZE; ++i)
    {
        if (freq[i].count != 0)
        {
            struct node *new_node = new node;
            new_node->symb = freq[i].key;
            new_node->freq = freq[i].count;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->parent = NULL;
            new_node->isSymb = 1;
            new_node->level = 0;
            new_node->code = '\0';
            nodes.push_back(new_node);
        }
    }
}