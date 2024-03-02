//
// Created by Rohith on 2/20/24.
//
#include "utls/Object.h"

Object::Object() { type = nullptr_type; }

Object::Object(double type) {
  this->type = num_type;
  num_literal = type;
}

Object::Object(bool type) {
  this->type = bool_type;
  bool_literal = type;
}

Object::Object(std::string type) {
  this->type = string_type;
  string_literal = type;
}

std::string Object::str() {
  if (type == string_type) {
    return string_literal;
  }
  if (type == nullptr_type) {
    return "nil";
  }
  if (type == num_type) {
    return std::to_string(num_literal);
  }
  if (type == bool_type) {
    return bool_literal ? "true" : "false";
  }
  return "";
}
