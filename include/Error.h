//
// Created by Rohith on 1/8/24.
//

#ifndef CRUX_ERROR_H
#define CRUX_ERROR_H

#include "Token.h"
#include "utls/RuntimeError.h"
#include <string>

namespace crux {

extern bool hasError;
extern bool hadRuntimeError;

void report(int line, std::string_view where, std::string_view message);

void error(Token &token, std::string_view message);

void error(int line, std::string_view message);

void runtimeError(RuntimeError error);
} // namespace crux
#endif // CRUX_ERROR_H
