#pragma once

#define CPCTR_DEL(X) X(const X&) = delete;

#define MVCTR_DEL(X) X(X&&) = delete;

#define ASSIGN_OP_DEL(X) X& operator=(const X&) = delete;

