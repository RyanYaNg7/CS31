//
//  12345.hpp
//  selflearning
//
//  Created by 杨子鸣 on 11/24/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#ifndef _2345_hpp
#define _2345_hpp

//
//  list.hpp
//  selflearning
//
//  Created by 杨子鸣 on 11/24/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#include "homework6.h"
#include "node.h"
#include<string>
#include<iostream>
#include<cassert>


class List
{
public:
    List() { }
    void push_back(std::string data);
    void insert(Iterator pos, std::string s);
    Iterator erase(Iterator pos);
    Iterator begin();
    Iterator end();
    
private:
    Node* first;
    Node* last;
    friend class Iterator;
};


#endif /* _2345_hpp */
