#ifndef CRUXCLASS_H
#define CRUXCLASS_H

#include "CruxCallable.h"
#include <string>

class CruxClass : public CruxCallable {
public:
  std::string name;

  CruxClass(std::string name) : name(name) {}

  virtual Object call(Interpreter *interpreter,
                      std::vector<Object> args) override;

  virtual int arity() override;

  virtual std::string str() override { return name; }
};

#endif
