#include <fstream>
#include <iostream>

#include "../Ex0301_StringAbstractDataType/MyString.h"

using namespace std;

int main()
{
    char line[2000];
    ifstream ifile;
    ifile.open("./temp.txt");

    int line_number = 0;
    while(ifile.getline(line, sizeof(line)))
    {
        cout << line_number << " : ";
        cout << line << endl;

        line_number += 1;
    }

    ifile.close();

    return 0;
}