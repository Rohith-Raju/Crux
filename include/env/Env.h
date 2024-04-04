//
// Created by rohith on 26/03/2024
//

#include "Token.h"
#include "utls/Object.h"
#include <string>
#include <unordered_map>

class Environment {
private:
  std::unordered_map<std::string, Object> values;

public:
  void define(std::string name, Object value);
  void assign(Token *name, Object value);
  Object get(Token *name);
};
