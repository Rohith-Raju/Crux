//
// Cruxcallable.h contains function definations that is overridden
// by CruxFunction and Crux Class
//
//
#pragma once

#include "utls/Object.h"
#include <string>
#include <vector>

class Interpreter;

class CruxCallable {
public:
  virtual int arity() = 0;
  virtual Object call(Interpreter *interpreter, std::vector<Object>) = 0;
  virtual std::string str() = 0;
};
