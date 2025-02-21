#include "headers.h"
#include <vector>
#include <map>
#include <iostream>
#include <cstdio>

using namespace std;
int main(){    
    string file_name;
    string file_name1 = "compressed.txt";
        string file_name2 = "decompress.txt";
    cout<<"compress - 0, decompress - 1"<<endl;
    int mode;
    cin>>mode;
    if (mode == 0)
    {
        cout << "GIVE ME A FILE NAME" << endl;
    
        cin>>file_name;
     
        
        vector<letter> freq(SIZE);
        open_file(freq, file_name);
        sorted_freq(freq);
        vector<struct node* > nodes;
        sorted_nodes_created(nodes, freq);
        haffman_tree(nodes);
        if (nodes.size() != 1){inorder(nodes[nodes.size() - 1], "");}
        print_code_to_file(nodes, file_name, file_name1);
        cout << "done" << endl;
    }
    if (mode == 1){
        decode(file_name1, file_name2);
        cout << "done" << endl;
    }
}

