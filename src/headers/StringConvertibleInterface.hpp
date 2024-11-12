/*
    name:
        StringConvertible
    
    description:
        This is an interface for classes that can be converted to a string.
        It has a single method, toString(), which returns a string representation
        of the object.
*/
#pragma once

#include <iostream>

class StringConvertible {
public:
    virtual std::string toString() const = 0;
    virtual ~StringConvertible() = default;
};