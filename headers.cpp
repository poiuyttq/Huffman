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
        char c = fgetc(fr);
        int flag = 1;
        for (int j = 0; j < SIZE; ++j)
        {
            if (freq[j].key == c)
            {
                freq[j].count++;
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            freq[i].key = c;
            for (int j = 0; j < SIZE; ++j)
                if (freq[j].key == c)
                {
                    freq[j].count++;
                    break;
                }
        }
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