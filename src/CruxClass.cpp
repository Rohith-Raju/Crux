#ifndef CRUXCLASS_CPP
#define CRUXCLASS_CPP

#include "CruxClass.h"
#include "CruxInstance.h"
#include "utls/Object.h"
#include <vector>

Object CruxClass::call(Interpreter *interpreter, std::vector<Object> args) {
  CruxInstance *instance = new CruxInstance(this);
  return Object(instance);
}

int CruxClass::arity() { return 0; }

#endif
