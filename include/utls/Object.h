//
// Created by Rohith on 2/20/24.
//

#ifndef CRUX_OBJECT_H
#define CRUX_OBJECT_H

#include <string>

enum ObjType{
    nullptr_type, num_type, string_type, bool_type,
};
class Object{
public:
    ObjType type;
    bool bool_literal;
    double num_literal;
    std::string string_literal;
    Object();
    Object(bool type);
    Object(double type);
    Object(std::string type);
    std::string str();
};
#endif //CRUX_OBJECT_H
