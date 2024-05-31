//
// Created by rohith on 26/03/2024
//

#ifndef ENV_H
#define ENV_H

#include "Token.h"
#include "utls/Object.h"
#include <string>
#include <unordered_map>

class Environment {
private:
  Environment *enclosing;
  std::unordered_map<std::string, Object> values;

public:
  Environment();
  //~Environment();
  Environment(Environment *enclosing);
  void define(Token *tkn, Object value);
  void define(std::string name, Object value);
  void assign(Token *name, Object value);
  void assignAt(int distance, Token *name, Object value);
  Object get(Token *name);
  void deepClean(Environment *enclosing);
  Object getAt(int distance, std::string name);
  Environment *ancestor(int distance);
};

#endif
