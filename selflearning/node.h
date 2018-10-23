//
//  node.hpp
//  selflearning
//
//  Created by 杨子鸣 on 11/24/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//
#ifndef node_hpp
#define node_hpp

#include "12345.h"
#include "homework6.h"

#include<string>
#include<iostream>
#include<cassert>

class Node
{
public:
    Node(std::string s):data(s){}
    
private:
    std::string data;
    Node* previous;
    Node* next;
    friend class List;
    friend class Iterator;
};

#endif
