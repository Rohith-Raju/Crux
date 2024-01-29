//
// Created by Rohith on 1/8/24.
//

#ifndef CRUX_ERROR_H
#define CRUX_ERROR_H


extern bool hasError;

void report(int line, const char *message);

void error(int line, const char *message);

#endif //CRUX_ERROR_H
