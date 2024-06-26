#pragma once

#include "CruxCallable.h"
#include <chrono>
#include <string>
#include <vector>
class Interpreter;

class ClockFunction : public CruxCallable {
  virtual int arity() override { return 0; }

  virtual Object call(Interpreter *interpreter, std::vector<Object>) override {
    auto millisec_since_epoch =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    Object value((double)millisec_since_epoch / 1000.0);
    return value;
  }

  virtual std::string str() override { return "<native fn>"; }
};
