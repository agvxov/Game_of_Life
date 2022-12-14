#include "gol.h"
#include <ncurses.h>
#include <vector>

#define DELAY 3

extern unsigned int std_height;
extern unsigned int std_width;

// Rules:
//    1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
//    2. Any live cell with two or three live neighbours lives on to the next generation.
//    3. Any live cell with more than three live neighbours dies, as if by overpopulation.
//    4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

void simulate(std::vector<bool> &fauna, const bool &bmode){
	//init input
	noecho();
	curs_set(0);
	halfdelay(DELAY);

	//init map
	refresh();
	std::vector<bool> phantom;
	phantom.resize(fauna.size());

	unsigned int pl = fauna.size() / std_height;

	while(1){
		//render to screen
		move(0, 0);
		for(unsigned int i = 0; i < fauna.size(); i++){
			if(fauna[i]){
				addch('#');
			}else{
				addch(' ');
			}
		}
		//take input
		char input = getch();
		if(input == 'q'){
			return;
		}else if(input == 'p'){
			while(1){
				cbreak();
				input = getch();
				if(input == 'p'){
					halfdelay(DELAY);
					break;
				}
			}
		}
		//calculate
		if(!bmode){
			calc_bnull(fauna, phantom, pl);
			fauna = phantom;
		}else{
			//calc_bone(fauna, phantom, pl);
		}
	}

	return;
}

inline void calc_bnull(const std::vector<bool> &fauna, std::vector<bool> &phantom, const unsigned int &pl){

	for(unsigned int i = 0; i < fauna.size(); i++){
		//////this would be way easier if i werent using bloody vectors
		//border- left, right, top, bottom
		bool bl, br, bt, bb;
		//is border
		if((i % pl) == 0){ bl = true; }else{ bl = false; }							 //left
		if((i % pl) == (pl - 1)){ br = true; }else{ br = false; }					 //right
		if(((signed int)i - 1) < (signed int)pl){ bt = true; }else{ bt = false; }	 //top
		if((i + pl + 1) > fauna.size()){ bb = true; }else{ bb = false; }			 //bottom

		unsigned short neighbour_count = 0;
		//////i hope this gets optimezed away
		unsigned int ntl, ntt, ntr,
					 nml,      nmr,
					 nbl, nbb, nbr;
		ntl = i - pl - 1; ntt = i - pl; ntr = i - pl + 1;
		nml = i - 1;                    nmr = i + 1;
		nbl = i + pl - 1; nbb = i + pl; nbr = i + pl + 1;

		//main logic
		if(!(bl || bt)){ neighbour_count += fauna[ntl]; }
		if(!(bt)){ neighbour_count += fauna[ntt]; }
		if(!(br || bt)){ neighbour_count += fauna[ntr]; }
		if(!(bl)){ neighbour_count += fauna[nml]; }
		if(!(br)){ neighbour_count += fauna[nmr]; }
		if(!(bl || bb)){ neighbour_count += fauna[nbl]; }
		if(!(bb)){ neighbour_count += fauna[nbb]; }
		if(!(br || bb)){ neighbour_count += fauna[nbr]; }

		/* 1. */ if(fauna[i] && (neighbour_count < 2)){ phantom[i] = 0; }
		/* 2. */ if(fauna[i] && (neighbour_count == 2 || neighbour_count == 3)){ phantom[i] = 1; }
		/* 3. */ if(fauna[i] && (neighbour_count > 3)){ phantom[i] = 0; }
		/* 4. */ if(!fauna[i] && (neighbour_count == 3)){ phantom[i] = 1; }
	}

	return;
}
