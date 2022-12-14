#include "store_bool_vector.h"

#include <vector>
#include <fstream>

bool save(const char *fn, const std::vector<bool> &v){
	std::ofstream s;
	s.open(fn);
	if(!s.is_open()){ return 1; }

	for(auto i : v){
		s << i;
	}

	s.close();

	return 1;
}

std::vector<bool> *load(const char *fn){
	std::vector<bool>* v = new std::vector<bool>;
	std::ifstream s;
	s.open(fn);
	if(!s.is_open()){ return NULL; }

	//the fact that (auto i : v){ s >> i; } doesnt work, makes me very upset
	//understanding why, makes me even more upset
	while(!s.eof()){
		char h;
		s >> h;
		if(h == '1'){
			(*v).push_back(1);
		}else{
			(*v).push_back(0);
		}
	}

	s.close();

	return v;
}
