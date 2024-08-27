//
// Created by Rohith on 2/20/24.
//

#ifndef CRUX_OBJECT_H
#define CRUX_OBJECT_H

#include <string>

class CruxCallable;
class CruxClass;
class CruxInstance;

enum ObjType {
  nullptr_type,
  num_type,
  string_type,
  bool_type,
  function_type,
  class_type,
  instance_type
};

class Object {
public:
  ObjType type;
  double num_literal;
  bool bool_literal;
  std::string string_literal;
  CruxCallable *function;
  CruxClass *klass;
  CruxInstance *instance;

  Object();
  Object(bool type);
  Object(double type);
  Object(std::string type);
  Object(CruxCallable *func);
  Object(CruxClass *klass);
  Object(CruxInstance *instance);
  std::string str();
};
#endif // CRUX_OBJECT_H
