#ifndef FUNCTION_H
#define FUNCTION_H

#include "CruxCallable.h"
#include "Statement.h"
#include "env/Env.h"

class CruxFunction : public CruxCallable {
public:
  Function *declaration;
  Environment *closure;
  CruxFunction(Function *declaration, Environment *closure);
  virtual int arity() override;
  virtual Object call(Interpreter *interpreter, std::vector<Object>) override;
  virtual std::string str() override;
};

#endif // FUNCTION_H
