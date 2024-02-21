//
// Created by Rohith on 1/8/24.
//

#ifndef CRUX_ERROR_H
#define CRUX_ERROR_H

#include <string>
#include "Token.h"
#include "utls/RuntimeError.h"

namespace crux {

    extern bool hasError;
    extern bool hadRuntimeError;

    void report(int line, std::string_view where, std::string_view message);

    void error(Token &token, std::string_view message);

    void error(int line, std::string_view message);

    void runtimeError(RuntimeError& error);
}
#endif //CRUX_ERROR_H
