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
void inorder(struct node *root, string code)
{
    if (root == NULL)
        return;
    inorder(root->left, code + "1");
    root->code = code;
    if (root->isSymb == 1)
    {
        return;
    }
    inorder(root->right, code + "0");
    root->code = code;
    if (root->isSymb == 1)
    {
        return;
    }
}

void print_code_to_file(vector<struct node *> &nodes, string file_name, string file_name1)
{
    std::cout << file_name << endl;
    FILE *fr3 = fopen(file_name.c_str(), "rb");
    FILE *fr1 = fopen(file_name1.c_str(), "wb");
    std::map<char, string> myMap;

    for (int i = 0; i < nodes.size(); ++i)
    {
        myMap.insert(std::pair<char, string>(nodes[i]->symb, nodes[i]->code));
    }
    fseek(fr3, 0L, SEEK_END);
    long length = ftell(fr3);
    fseek(fr3, 0L, SEEK_SET);
    if (myMap.size() < 100 && myMap.size() > 9){
        fseek(fr1, 5, SEEK_SET);
    }
    else if (myMap.size() > 99  ){
        fseek(fr1, 6, SEEK_SET);
    }
    else {
        fseek(fr1, 4, SEEK_SET);
    }
    vector<int> buffer(0, 0);
    for (auto it = myMap.begin(); it != myMap.end();++it){
        string str ="";
        str+= it->first;
        str+= " ";
        str+= it->second;
        str+= "\n";
        fputs(str.c_str(), fr1);
    }
    
    for (int i = 0; i < length; ++i)
    {
        char c = fgetc(fr3);
        int ind = 0;
        auto currentElement = myMap.find(c);
        string code = currentElement->second;
        for (int q = 0; q < code.size(); ++q)
        {
            if (buffer.size() < 8)
            {
                buffer.push_back(code[q] - '0');
            }
            else
            {
                char to_file = (buffer[7]) + (buffer[6]) * 2 + buffer[5] * 4 + buffer[4] * 8 + buffer[3] * 16 + buffer[2] * 32 + buffer[1] * 64 + buffer[0] * 128;
                fputc(to_file, fr1);
                buffer.erase(buffer.begin(), buffer.begin() + 8);
                buffer.push_back(code[q] - '0');
            }
        }
    }
    int lastByteEffectiveBits = buffer.size();
    if (buffer.size() > 0)
    {
        char to_file;
        for (int i = 0; i < buffer.size(); ++i)
        {
            to_file += buffer[i] * pow(2, buffer.size() - i - 1);
        }

        fputc(to_file, fr1);
    }    
    
    fseek(fr1, 0, SEEK_SET);
    if (myMap.size()>1){
    string s2 = to_string(myMap.size()-1);
    fputs(s2.c_str(), fr1);
    }
    else{
        string s2 = to_string(myMap.size());
        fputs(s2.c_str(), fr1);
    }

    
    fputs ("\n", fr1);


    string s = to_string(lastByteEffectiveBits);
    fputs (s.c_str(), fr1);
    fputs ("\n", fr1);
    fseek(fr1, 0, SEEK_SET);

    //сверху map_size
    //снизу lastByteEffectiveBits

    fclose(fr3);
    fclose(fr1);
    
}