#include<iostream>
#include<string>
#include "homework6.h"
#include "node.h"
#include "12345.h"



int main()
{
    
    
    List newlist;
    newlist.push_back("12");
    newlist.push_back("13");
    newlist.push_back("14");
    
    Iterator iter;
    iter == newlist.begin();
    //++iter;
    std::cout << *iter << "\n";
    system("pause");
    return 0;
}
