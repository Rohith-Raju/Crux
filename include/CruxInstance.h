#ifndef CRUXINSTANCE_H
#define CRUXINSTANCE_H

#include "CruxClass.h"
#include "Token.h"
#include "utls/Object.h"
#include "utls/RuntimeError.h"
#include <map>
#include <string>

class CruxInstance {
public:
  CruxClass *klass;
  std::map<std::string, Object> fields;

  CruxInstance(CruxClass *klass) : klass(klass) {}

  Object get(Token *name) {
    if (fields.find(name->lexeme) != fields.end()) {
      return fields[name->lexeme];
    }
    throw RuntimeError(*name,
                       "Undefined Property " + name->lexeme + "not found");
  }

  std::string str() { return klass->name + " Instance"; }
};

#endif
