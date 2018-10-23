//
//  main.cpp
//  dis week1 hw'
//
//  Created by 杨子鸣 on 9/30/16.
//  Copyright © 2016 杨子鸣. All rights reserved.
//


#include <iostream>
#include <string>
using namespace std;
int rotateLeft(string a[], int n, int pos);

int main()
{
    string blank[] = { "" };
    if(rotateLeft(blank, 0, 0) == -1)
        cout << "yes";
    cout << rotateLeft(blank,0,0);
}

int rotateLeft(string a[], int n, int pos)
{
    if (n < 0)
        return -1;
    string posedOne = a[pos];       //store the original value
    for (int k = pos; k < (n-1); k++)              //scoot the array
    {
        a[k] = a[k+1];
    }
    a[n-1] = posedOne;              //set the last element
    return pos;
}