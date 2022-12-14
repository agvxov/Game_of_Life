#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

//NOTE: if the evenness of dim_y and longest are different, 
//       ie if (dim_y % 2 != longest % 2) is true, the text cannot possible be centered,
//		 resulting in it looking like shite
int menu(const int &dim_y, const int &dim_x, const int &pos_y, const int &pos_x,
			const char** points, const unsigned int &count, unsigned int longest = 0){

	//check whether all menu points can fit on the screen
	if((dim_y + 2 < count) or (longest != 0 && longest + 2 /*border*/ + 2 /*brackets*/ + 4 /*spaces*/ < dim_x )){ assert(("menu points wont fit", 1)); }

	//init imput
	cbreak();
	noecho();
	curs_set(0);

	//draw the menu
	WINDOW* m = newwin(dim_y, dim_x, pos_y, pos_x);
	wborder(m, '|', '|', '-', '-', '+', '+', '+', '+');
	unsigned int lpp = (dim_y - 2) / count;
	unsigned int offset = lpp / 2;
	unsigned int hoffset = (dim_y % count / 2) + (lpp - offset);
	if(lpp != 1 && offset % 2 != 0){ offset -= 1; }
	unsigned int cs = (dim_x - 2 - 6 - longest) / 2;
	for(unsigned int i = 0; i < count; i++){
		wmove(m, 1 + hoffset + (lpp * i) + offset, 1);
		for(unsigned int h = 0; h < cs; h++){
			waddch(m, ' ');
		}
		wprintw(m, " [ ");
		unsigned int padding = (longest - strlen(points[i])) / 2;
		for(unsigned int h = 0; h < padding; h++){
			waddch(m, ' ');
		}
		wprintw(m, "%s", points[i]);
		for(unsigned int h = 0; h < padding; h++){
			waddch(m, ' ');
		}
		wprintw(m, " ]");
	}

	unsigned int prev_at = UINT_MAX;
	unsigned int at = 0;
	char input;
	while(1){
		//unhighlight the previous selected menupoint
		if(prev_at != UINT_MAX){
			wmove(m, 1 + hoffset  + (lpp * prev_at) + offset, 1 + cs + 1);
			wprintw(m, "[ ");
			unsigned int padding = (longest - strlen(points[prev_at])) / 2;
			for(unsigned int h = 0; h < padding; h++){
				waddch(m, ' ');
			}
			wprintw(m, "%s", points[prev_at]);
			for(unsigned int h = 0; h < padding; h++){
				waddch(m, ' ');
			}
			wprintw(m, " ]");
		}

		//highlight selected menupont
		wattron(m, A_REVERSE);
		wmove(m, 1 + hoffset + (lpp * at) + offset, 1 + cs + 1);
		wprintw(m, "[ ");
		unsigned int padding = (longest - strlen(points[at])) / 2;
		for(unsigned int h = 0; h < padding; h++){
			waddch(m, ' ');
		}
		wprintw(m, "%s", points[at]);
		for(unsigned int h = 0; h < padding; h++){
			waddch(m, ' ');
		}
		wprintw(m, " ]");
		wattroff(m, A_REVERSE);

		//get input and act accordingly
		input = wgetch(m);
		if(input == 'j'){
			prev_at = at;
			at += 1;
			if(at >= count){			//maybe a bool should be passed to determine whether to loop
				at = count - 1;
				prev_at = UINT_MAX;
			}
		}else if(input == 'k'){
			if(at != 0){
				prev_at = at;
				at -= 1;
			}else{
				prev_at = UINT_MAX;
			}
		}else if(input == 'w'){
			delwin(m);
			return at;
		}
	}
}

#endif
