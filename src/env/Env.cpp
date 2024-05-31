//
// Created by rohith on 26/03/2024
//

#include "env/Env.h"
#include "Token.h"
#include "utls/Object.h"
#include "utls/RuntimeError.h"

Environment::Environment() : enclosing(nullptr) {}

// Environment::~Environment() {
//   if (enclosing != nullptr) {
//     deepClean(enclosing);
//   }
//   enclosing = nullptr;
// }

void Environment::deepClean(Environment *enclosing) {
  if (enclosing != nullptr)
    deepClean(enclosing);

  enclosing->values.clear();
  enclosing = nullptr;
  return;
}

Environment::Environment(Environment *enclosing) : enclosing(enclosing) {}

void Environment::define(Token *tkn, Object value) {
  define(tkn->lexeme, value);
}

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

void Environment::assignAt(int distance, Token *name, Object value) {
  ancestor(distance)->values[name->lexeme] = value;
}

Object Environment::get(Token *name) {
  if (values.find(name->lexeme) != values.end()) {
    Object obj = values[name->lexeme];
    if (obj.type == nullptr_type)
      throw RuntimeError(*name, "Uninitalized variable :" + name->lexeme +
                                    " nil values can't be computed");
    return obj;
  }

  if (enclosing != nullptr) {
    return enclosing->get(name);
  }
  throw RuntimeError(*name, "Unexpected variable " + name->lexeme);
}

Object Environment::getAt(int distance, std::string name) {
  return ancestor(distance)->values[name];
}

Environment *Environment::ancestor(int distance) {
  Environment *env = this;
  for (int i = 0; i < distance; i++) {
    env = env->enclosing;
  }
  return env;
}
