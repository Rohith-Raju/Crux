//
// Created by rohith on 26/03/2024
//

#include "env/Env.h"
#include "utls/Object.h"
#include "utls/RuntimeError.h"

Environment::Environment() : enclosing(nullptr) {}

Environment::Environment(Environment *enclosing) : enclosing(enclosing) {}

void Environment::define(std::string name, Object value) {
  values.insert({name, value});
}

void Environment::assign(Token *name, Object value) {
  if (values.find(name->lexeme) != values.end()) {
    values[name->lexeme] = value;
    return;
  }

  if (enclosing != nullptr) {
    enclosing->assign(name, value);
    return;
  }

  throw RuntimeError(*name, "Undefined variable " + name->lexeme);
}

Object Environment::get(Token *name) {
  if (values.find(name->lexeme) != values.end()) {
    Object obj = values[name->lexeme];
    if (obj.type == nullptr_type)
      throw RuntimeError(*name, "Uninitalized variable " + name->lexeme +
                                    " can't be computed");
    return values[name->lexeme];
  }

  if (enclosing != nullptr) {
    return enclosing->get(name);
  }
  throw RuntimeError(*name, "Unexpected variable " + name->lexeme);
}

Environment::~Environment() { delete enclosing; }
