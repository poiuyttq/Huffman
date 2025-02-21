#include "headers.h"
#include <iostream>
#include <vector>

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
void haffman_tree(vector<struct node *> &nodes)
{
    if (nodes.size() == 1)
    {
        nodes[0]->code = "0";
        return;
    }
    for (int i = 1; i < nodes.size(); i += 2)
    {
        struct node *new_node = new node;
        new_node->freq = nodes[i - 1]->freq + nodes[i]->freq;
        new_node->symb = 0;
        new_node->right = nodes[i - 1];
        new_node->left = nodes[i];
        new_node->parent = NULL;
        new_node->isSymb = 0;
        new_node->level = 0;
        new_node->code = '\0';
        nodes[i - 1]->parent = new_node;
        nodes[i]->parent = new_node;
        nodes.push_back(new_node);
        stable_sort(nodes.begin(), nodes.end(), support_stable_sort_func);
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

    //сверу map_size
    //снизу lastByteEffectiveBits

    fclose(fr3);
    fclose(fr1);
    
}



void decode(string file_name1, string file_name2){
    
    FILE *fr3 = fopen(file_name1.c_str(), "rb");
    FILE *fr2 = fopen(file_name2.c_str(), "wb");
    fseek(fr3, 0L, SEEK_END);
    long length = ftell(fr3);
    fseek(fr3, 0, SEEK_SET);
    fseek(fr2, 0, SEEK_SET);
    int lastByteEffectiveBits;
    int map_size;   
    size_t last = (size_t)lastByteEffectiveBits;
    fscanf(fr3, "%d", &map_size);
    fscanf(fr3, "%d", &lastByteEffectiveBits);
    //cout << "map_size " << map_size << endl;
    //cout << "lastByteEffectiveBits " << lastByteEffectiveBits << endl;

    std::map<char, string> myMap;
    fgetc(fr3);

    for (int i = 0; i < map_size; ++i)
    {
        char c = fgetc(fr3);
        struct node *new_node = new node;
        new_node->symb = c;
        fgetc(fr3);
        string code;

        while (c != '\n')
        {

            char new_c = fgetc(fr3);
            if (new_c == '1'){

            }
            if (new_c == '\n'){
                break;
            }
            code += new_c;
        }
        new_node->code = code;
        myMap.insert(std::pair<char, string>(c, code));
        delete new_node;
    }


    std::map<string, char> myMap2;
    for (auto it = myMap.begin(); it != myMap.end();++it){
        myMap2.insert(std::pair<string, char>( it->second,it->first));
    }
    for (auto it = myMap2.begin(); it != myMap2.end();++it){
        //cout<<it->first<< " "<<it->second <<endl;
    }
    long length1 = ftell(fr3);
    string buff = "";
    for (int i = 0;i < length-length1-1;++i){
        char c = fgetc(fr3);
        bitset<8> bs(c);
        for (int j = 7; j >= 0; j--){
            if (bs[j] == 1){
                buff += "1";
            } else {
                buff += "0";
            }
            //cout << buff.c_str();
            if (myMap2.find(buff.c_str()) != myMap2.end()){
            
                char curr = myMap2.find(buff)->second;
                fputc(curr, fr2);
                buff.clear(); 
            }
        }
    }
    char c = fgetc(fr3) ;
    bitset<8> bs(c);
    for (int j = lastByteEffectiveBits-1; j >= 0; j--){
        if (bs[j] == 1){
            buff += "1";
        } else {
            buff += "0";
        }
        //cout << buff.c_str();
        if (myMap2.find(buff.c_str()) != myMap2.end()){
        
            char curr = myMap2.find(buff)->second;
            fputc(curr, fr2);
            buff.clear(); 
        }
    }
    fclose(fr2);
    fclose(fr3);

}

    