//
//  12345.cpp
//  selflearning
//
//  Created by 杨子鸣 on 11/24/17.
//  Copyright © 2017 杨子鸣. All rights reserved.
//

#include "12345.h"

#include"homework6.h"
#include<string>
#include<iostream>
#include<cassert>


/*define functions of list*/

Iterator List::begin()
{
    Iterator iter;
    iter.position = first;
    iter.container = this;
    return iter;
}

Iterator List::end()
{
    Iterator iter;
    iter.position = nullptr;
    iter.container = this;
    return iter;
}

void List::push_back(std::string data)
{
    Node* new_node = new Node(data);
    if (last == nullptr)
    {
        first = new_node;
        last = new_node;
    }
    else
    {
        new_node->previous = last;
        last->next = new_node;
        last = new_node;
    }
}

void List::insert(Iterator iter, std::string s)
{
    
    if (iter.position == nullptr)
    {
        push_back(s);
        return;
    }
    
    Node* after = iter.position;
    Node* before = after->previous;
    Node* new_node = new Node(s);
    new_node->previous = before;
    new_node->next = after;
    after->previous = new_node;
    if (before == nullptr)
        first = new_node;
    else
        before->next = new_node;
}

Iterator List::erase(Iterator pos)
{
    assert(pos.position != nullptr);
    Node* remove = pos.position;
    Node* before = remove->previous;
    Node* after = remove->next;
    before->next = after;
    after->previous = before;
    if (remove == first)
        first = after;
    else
        before->next = after;
    
    if (remove == last)
        last = before;
    else
        after->previous = before;
    Iterator r;
    r.position = after;
    r.container = this;
    return r;
}



