#ifndef homework6_H
#define homework6_H

#include "12345.h"
#include "node.h"
#include<string>
#include<iostream>
#include<cassert>

class Iterator
{
public:
    Iterator(){}
    std::string operator *() const;
    void operator ++();
    void operator --();
    bool operator ==(Iterator b) const;
    
private:
    Node* position;
    List* container;
    friend class List;
    
};



#endif
