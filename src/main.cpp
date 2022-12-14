#include <ncurses.h>
#include <array>
#include "menu.h"
#include "store_bool_vector.h"
#include "draw.h"
#include "gol.h"

#define MENU_WIDTH 20
#define MENU_HEIGHT 20

bool running = false;

unsigned int std_height = 0;
unsigned int std_width = 0;


signed main(){
	//init
	initscr();
	running = true;

	//vars
	std::vector<bool> *fauna = new std::vector<bool>;

	getmaxyx(stdscr, std_height, std_width);
	int menu_x_start = (std_width - MENU_WIDTH) / 2;
	const char* menu_points[] = {"Simulate", "Edit", "Save", "Load", "Quit"};
	const int menu_size = 5; 									//there must be an std macro for this
	const int menu_longest = sizeof("simulate") - 1; 			//the "-1" is because of the 0 termination


	//main loop
	int choise = 0;

	while(running){
		choise = menu(MENU_HEIGHT, MENU_WIDTH, 1, 1, menu_points, menu_size, menu_longest);
		if(choise == 0){		//run
			simulate(*fauna, 0);
		}else if(choise == 1){	//edit
			draw(*fauna);
		}else if(choise == 2){	//save
			char file[21];
			echo();
			curs_set(2);
			WINDOW* i = newwin(1, 20, std_height - 1, 0);
			wscanw(i, "%s", file);
			save(file, *fauna);
			delwin(i);
		}else if(choise == 3){	//load
			char file[21];
			echo();
			curs_set(2);
			WINDOW* i = newwin(1, 20, std_height - 1, 0);
			wscanw(i, "%s", file);
			delete fauna;
			void* guard = (void*)load(file);
			if(guard != NULL){ fauna = (std::vector<bool>*)guard; }
			fauna->resize(std_height * std_width);
			delwin(i);
		}else if(choise == 4){	//quit
			running = false;
		}
	}

	//clean up
	delete fauna;
	endwin();
	return 0;
}
