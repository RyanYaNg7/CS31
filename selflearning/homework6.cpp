
#include"homework6.h"
#include<string>
#include<iostream>
#include<cassert>




/*define functions of Iterator*/
std::string Iterator::operator *() const
{
    assert(position != nullptr);
    return position->data;
}

void Iterator::operator ++()
{
    assert (position != nullptr);
    position = position->next;
}

void Iterator::operator --()
{
    assert(position != container->first);
    if (position == nullptr)
        position = container->last;
    else
        position = position->previous;
    
}

bool Iterator::operator ==(Iterator b) const
{
    return position == b.position;
}









