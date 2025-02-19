#include "headers.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void open_file(vector<letter> &freq, string file_name)
{
    FILE *fr = fopen(file_name.c_str(), "rb");
    fseek(fr, 0L, SEEK_END);
    long length = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    for (int i = 0; i < length; ++i)
    {
        unsigned char c = fgetc(fr);
        freq[c].key = c;
        freq[c].count++;
    }

    fclose(fr);
}
void sorted_freq(vector<letter> &freq)
{

    for (int i = 0; i < freq.size(); ++i)
    {
        for (int j = i + 1; j < freq.size(); ++j)
        {
            if (freq[i].count > freq[j].count)
            {
                swap(freq[i], freq[j]);
            }
        }
    }
}
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
bool support_stable_sort_func(struct node *a, struct node *b)
{
    return a->freq < b->freq;
}
