#ifndef STORE_BOOL_VECTOR_H
#define STORE_BOOL_VECTOR_H

#include <vector>
#include <fstream>

bool save(const char *fn, const std::vector<bool> &v);
std::vector<bool> *load(const char *fn);

#endif
