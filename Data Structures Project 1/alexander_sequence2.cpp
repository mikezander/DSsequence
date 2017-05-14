//  Michael Alexander
//  alexander_sequence2.cpp
//  Data Structures Programming Assignment 1

#include<cstdlib>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "sequence2.h"

namespace DSProject01 {
    
    const sequence::size_type sequence::DEFAULT_CAPACITY; // set to 30
    
    sequence::sequence(size_type initial_capacity){ // initial_capacity = DEFAULT_CAPACITY
    
        data = new value_type[initial_capacity];
        used = 0;
        current_index = 0;
        capacity = initial_capacity;
        
    }
    // Copy contructor
    sequence::sequence(const sequence& source){
        data = new value_type[source.capacity];
        used = source.used;
        current_index = source.current_index;
        capacity = source.capacity;
        
        std::copy(source.data, source.data + used, data);

    }
    
    sequence::~sequence( ){
    
        delete [] data;
    
    }
    // Resizes dynamic array to extend capacity
    void sequence::resize(size_type new_capacity){
    
        value_type * larger_data;
        
        if(new_capacity == capacity)
            return;
        
        if(new_capacity < used)
            new_capacity = used;
        
        larger_data = new value_type[new_capacity]; // creates pointer w new_capacity
        std::copy(data, data + used, larger_data); //copys member pointer to larger data
        delete [] data;
        
        data = larger_data; // data now points to larger data after deallocating
        capacity = new_capacity;
    }
    // Sets the sequence back to the first position
    void sequence::start( ){
    
        current_index = 0;
        
    }
    // Advances the sequences current position by one
    void sequence::advance( ){
    
        if(is_item())
            ++current_index;
    
    }
    // Places new value before current value
    void sequence::insert(const value_type& entry){
        
        int ten_percent = used * .10;

        if(used == capacity)
            resize(used + ten_percent); // resizing by 10%
        
        if(is_item() == false)
            current_index = 0;
        
        for(size_type i = used; i > current_index; --i)
            data[i] = data[i-1]; // shifts values foward for new value
        
        data[current_index] = entry;
        ++used;
        
    }
    // Places new value after current value
    void sequence::append(const value_type& entry){
        
        int ten_percent = used * .10;
        
        if (used >= capacity) // equal to or greater than capacity resize sequence 10%
            resize(used + ten_percent);
            
        if (used > 0)
        {
            for(size_type i = used-1; i > current_index; --i)
                data[i+1]=data[i]; // shifts values after, up a position.
            
            if(is_item() == false)
                data[current_index] = entry;
            else
                data[current_index+1] = entry; // add in new value and increment
            
            current_index += 1;
            used += 1;
        }
        else // (used == 0)
        {
            data[current_index] = entry;
            used += 1;
        }
    }
    // Removes current value
    void sequence::remove_current( ){
        
        assert(size()>0);
        
        for(size_type i = current_index+1; i < used; ++i)
        data[i-1] = data[i]; // erases current and shifts values after, back one position.
        
        --used;
        
    }
    
    void sequence::operator=(const sequence& source){
        
        value_type * new_value;
        
        if(capacity != source.capacity){
        
            new_value = new value_type[source.capacity]; // creating a pointer of new capacity
            delete [] data;
            data = new_value;
            capacity = source.capacity;
        
        }
        
        used = source.used;
        current_index = source.current_index;
        
        std::copy(source.data, source.data + used, data); // copying source sequence to member sequence
    }
    
    // returns the number of values in the sequence
    sequence::size_type sequence::size( ) const{
        return used;
    }
    
    // returns true if theres a value in current position and false if not
    bool sequence::is_item( ) const{
        return current_index < used;
    }
   
    // returns current value
    sequence::value_type sequence::current( ) const{
        return data[current_index];
    }
}


