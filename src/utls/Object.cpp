//
// Created by Rohith on 2/20/24.
//
#include "utls/Object.h"
#include "CruxCallable.h"
#include "CruxClass.h"
#include "CruxInstance.h"

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

Object::Object(CruxCallable *type) {
  this->type = function_type;
  function = type;
}

Object::Object(CruxClass *type) {
  this->type = class_type;
  klass = type;
}

Object::Object(CruxInstance *type) {
  this->type = instance_type;
  instance = type;
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
  if (type == function_type) {
    return function->str();
  }
  if (type == class_type) {
    return klass->str();
  }
  if (type == instance_type) {
    return instance->str();
  }
  return "";
}
