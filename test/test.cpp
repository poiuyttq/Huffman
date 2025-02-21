#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
int main(){
    string file_name1 = "text.txt";
    string file_name2 = "decompress.txt";
    FILE *fr3 = fopen(file_name1.c_str(), "r");
    FILE *fr2 = fopen(file_name2.c_str(), "r");
    fseek(fr3, 0L, SEEK_END);
    long length = ftell(fr3);
    fseek(fr3, 0L, SEEK_SET);
    fseek(fr2, 0L, SEEK_END);
    long length2 = ftell(fr2);
    fseek(fr2, 0L, SEEK_SET);
    if (length != length2){
        cout << "ERROR" << endl;
        return 0;
    }
    for (int i = 0; i < length; ++i){
        char c = fgetc(fr3);
        char c2 = fgetc(fr2);
        if (c != c2){
            cout << "ERROR" << endl;
            cout<<i<<endl;
            return 0;
        }
    }
    cout << "OK" << endl;
}