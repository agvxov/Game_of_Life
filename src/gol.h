#ifndef GOL_H
#define GOL_H

#include <ncurses.h>
#include <vector>

void simulate(std::vector<bool> &fauna, const bool &bmode);
inline void calc_bnull(const std::vector<bool> &fauna, std::vector<bool> &phantom, const unsigned int &pl);

#endif
