//
// Created by rohith on 26/03/2024
//

#include "env/Env.h"
#include "utls/RuntimeError.h"

void Environment::define(std::string name, Object value) {
  values.insert({name, value});
}

void Environment::assign(Token *name, Object value) {
  if (values.find(name->lexeme) != values.end()) {
    values[name->lexeme] = value;
    return;
  }
  throw new RuntimeError(*name, "Undefined variable " + name->lexeme);
}

Object Environment::get(Token *name) {
  if (values.find(name->lexeme) != values.end())
    return values[name->lexeme];
  else {
    throw new RuntimeError(*name, "Unexpected variable " + name->lexeme);
  }
}
