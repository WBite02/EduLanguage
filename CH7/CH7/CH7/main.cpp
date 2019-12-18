//
//  main.cpp
//  CH7
//
//  Created by Wbite02 on 18/12/2019.
//  Copyright © 2019 Wbite02 All rights reserved.
//

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    ifstream ifs("Hello.txt", std::ios::in);
    
    if(ifs.is_open())
    {
        int intTell = ifs.tellg();
        cout << "It is tellg pointer : " << intTell << endl;
        string getString;
        while(ifs)
        {
            getline(ifs, getString);
            cout << "Print File : " << getString << std::endl;
        }
        
    }
    
    ifs.close();
    
    ofstream ofs("Hello.txt", std::ios::app | std::ios::out);
    if (ofs.is_open())
    {
        for (int i = 0 ; i < 10 ; i++)
        {
            ofs << i;
            ofs << "Hello World!! Welcome to my world!!";
        }
    }
    
}
