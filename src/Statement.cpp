//
// Created by Rohith in 18/03/24
//

#include "Statement.h"

Statement::Statement(Statement_type type) : type(type) {}

Print::Print(Expr *expr) : Statement(StmntPrint_type), expression(expr) {}

Expression::Expression(Expr *expr)
    : Statement(StmntExpr_type), expression(expr) {}
