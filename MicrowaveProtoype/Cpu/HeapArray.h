//  Created by Stepan on 30/09/16.

#ifndef HeapArray_h
#define HeapArray_h

#define CHECK_ARRAY if (bad()) throw my_exception("not ok", nullptr, PLACE);
#define PLACE place(__FILE__, __LINE__, __PRETTY_FUNCTION__)

#include <stdio.h>

template <typename valType>
class HeapArray {

private:
    
    //MARK: Parameters
    valType* data;
    size_t size;

public:
    
    //MARK: Constructors
    explicit HeapArray():
    data(new valType [0]), size(size)
    {}
    explicit HeapArray(int size):
    data(new valType [size]), size(size)
    {}
    
    HeapArray( const HeapArray& other ) {
        throw my_exception("you cant copy it.\n for the present", nullptr, PLACE); //NOMACROSES
    }
    HeapArray( const HeapArray&& other) {
        throw my_exception("you cant move it.\n for the present", nullptr, PLACE ); //NOMACROSES
    }
    
    ~HeapArray()
    { delete [] data; }
    
    
    //MARK: Methods
    bool bad();
    
    valType& operator[](size_t index)       {
        CHECK_ARRAY
        if (index < size && index >= 0) {
            return data[index];
        }
        else {
            throw my_exception("invalid index", nullptr, PLACE);
        }
    }
   
    const valType& operator[](size_t index) const {
        CHECK_ARRAY
        if (index < size && index >= 0) {
            return data[index];
        }
        else {
            throw my_exception("invalid index", nullptr, PLACE);
        }
    }
    
    void extend();
    size_t len () { return size; }
    
    
};

//  This method returns true if an array object is invalid
template <typename valType>
bool HeapArray<valType>::bad() {
    bool isArrayBad = false;
    if(!data) isArrayBad = true;
    return isArrayBad;
}

//  Array doubles its size
template <typename valType>
void HeapArray<valType>::extend() {
    CHECK_ARRAY
    
    valType* newData = new valType [size*2];
    
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    
    data = newData;
    size *= 2;
    
    CHECK_ARRAY
}

#undef CHECK_ARRAY
#undef PLACE

#endif
