//  Created by Stepan on 29.04.16.

#ifndef stack_h
#define stack_h

#include "MyException.h"
#include "HeapArray.h"
#include "Print.h"

#define CHECK_STACK checkForExtension(); if(bad()) throw my_exception("not ok", nullptr, PLACE); 
#define PLACE place(__FILE__, __LINE__, __PRETTY_FUNCTION__)

namespace mah
{
    template <typename valType>
    class Stack
    {
    private:
        
        //MARK: Parameters
        HeapArray<valType> data;
        int counter = 0;
        size_t size;
        
        //MARK: Private methods
        void checkForExtension();
    
    public:
        
        //MARK: Setup and destruct
        Stack():
            data(HeapArray<valType>(16)), size(16)
        {}
        
        explicit Stack(int size):
            data(HeapArray<valType>(size)), size(size)
        {}
        
        Stack( const Stack& other ) {
            throw my_exception("you cant copy it.\n for the present", nullptr, PLACE);
        }
        Stack( const Stack&& other) {
             throw my_exception("you cant move it.\n for the present", nullptr, PLACE);
        }
        
        //MARK: Methods
        void push(valType);
        valType pop();
        
        void dump();
        bool bad ();
    
    };
}

using namespace mah;

template <typename valType>
void Stack<valType>::push (valType val)
{
    CHECK_STACK
    
    if (counter >= 0 && counter < size)
    {
        data[counter] = val;
        counter++;
        
        printf ("pushed %d\n", val);
    }
    else
    {
        throw my_exception("push failed", nullptr, PLACE);
    }
    
    CHECK_STACK
}

template <typename valType>
valType Stack<valType>::pop ()
{
    CHECK_STACK
    
    if (counter > 0)
    {
        counter--;
        printf("popped %d\n", data[counter]);
        return data[counter];
    }
    else
    {
        throw my_exception("pop failed", nullptr, PLACE);
    }
    
    CHECK_STACK
}

//  This method returns true if stack object is invalid
template <typename valType>
bool Stack<valType>::bad()
{
    bool isStackBad = false;
    
    if(data.bad()) isStackBad = true;
    if(counter < 0 || counter >= size) isStackBad = true;
    
    return isStackBad;
}

//  Check if stack dynamic memory should extend
template <typename valType>
void Stack<valType>::checkForExtension() {
    if (counter == size-1) {
        data.extend();
        size = data.len();
    }
}

template <typename valType>
void Stack<valType>::dump()
{
    printf ("\n----\nDUMP\nmy_stack\nsize = %zu\ncounter = %d\ncontains:\n", size, counter);
    for (int i = 0; i < counter; i++)
    {
        if ((i+1)%10 == 0)
        {
            print::print(data[i]);
            printf("\n");
        }
        else
        {
            print::print(data[i]);
            printf(" ");
        }
    }
    printf ("\n----\n\n");
}

#undef CHECK_STACK
#endif
