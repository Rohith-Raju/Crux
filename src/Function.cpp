//
// created by rohith on 20-04-2024
//

#include "Function.h"
#include "Interpreter.h"
#include "env/Env.h"
#include "utls/Object.h"
#include <string>

CruxFunction::CruxFunction(Function *declaration) : declaration(declaration) {}

int CruxFunction::arity() { return declaration->params.size(); }

Object CruxFunction::call(Interpreter *interpreter, std::vector<Object> args) {
  Environment *env = new Environment(interpreter->globals);
  for (int i = 0; i < declaration->params.size(); i++) {
    env->define(declaration->params[i], args[i]);
  }
  interpreter->excecuteBlock(declaration->body, env);
  return Object();
}

std::string CruxFunction::str() {
  return "<\"fn" + declaration->name->lexeme + ">\"";
}
