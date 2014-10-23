#pragma once

typedef decltype(sizeof(int)) size_t;
typedef decltype((int*)100 - (int*)80) ptrdiff_t;
typedef decltype(nullptr) nullptr_t;

#define NULL nullptr
