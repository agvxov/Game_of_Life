#include "draw.h"
#include <ncurses.h>
#include <vector>

extern unsigned int std_height;
extern unsigned int std_width;

void draw(std::vector<bool> &fauna){

	//initialize input
	cbreak();
	noecho();
	curs_set(0);

	//initialize map
	refresh();
	unsigned int y = std_height / 2;
	unsigned int x = std_width / 2;
	unsigned int prev_y = y;
	unsigned int prev_x = x;
	fauna.resize(std_height * std_width);

	char input;	
	bool change = true;
	while(1){	//the fact that the visible map and fauna are independent of each other will most certently cause bugs at some point;;; somehow it did not
		//render cursor
		if(change){
			//unhighlight previously selected possition
			if(fauna[prev_y * std_width + prev_x] == 0){	//this section executes obsolitely on the firts passthrought; now considering its a bloody console C++ program it shouldnt matter as theres no human alive that could notice the preformance impact, but damn it annoys me
				mvaddch(prev_y, prev_x, ' ');
			}else{
				mvaddch(prev_y, prev_x, '#');
			}
			//highlight selected possition
			attron(A_REVERSE);
			if(fauna[y * std_height + x] == 0){
				mvaddch(y, x, ' ');
			}else{
				mvaddch(y, x, '#');
			}
			attroff(A_REVERSE);
			change = false;
		}
		//get and handle input
		input = getch();
		if(input == 'j' && !(y >= std_height)){
				prev_x = x;
				prev_y = y;
				y += 1;
				change = true;
		}else if(input == 'k' && !(y == 0)){
				prev_x = x;
				prev_y = y;
				y -= 1;
				change = true;
		}else if(input == 'h' && !(x == 0)){
				prev_y = y;
				prev_x = x;
				x -= 1;
				change = true;
		}else if(input == 'l' && !(x >= std_width)){
				prev_y = y;
				prev_x = x;
				x += 1;
				change = true;
		}else if(input == 'w'){
			attron(A_REVERSE);
			if(fauna[y * std_width + x] == 0){
				fauna[y * std_width + x] = 1;
				mvaddch(y, x, '#');
			}else{
				fauna[y * std_width + x] = 0;
				mvaddch(y, x, ' ');
			}
			attroff(A_REVERSE);
		}else if(input == 'q'){
			return;
		}
	}
}
