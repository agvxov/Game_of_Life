CXX:=g++
LDLIBS:=$(shell pkg-config --libs ncurses)
CFLAGS:=-g

COMP:=$(CXX) $(CFLAGS) $(LDFLAGS) $(LDLIBS)


SRCD:=src/
OBJD:=obj/
SRC:=$(shell find src/ | grep .cpp)
OBJ:=$(subst ${SRCD},${OBJD},$(subst .cpp,.o,$(SRC)))

OUTPUT:=gol.out



main: $(OBJ)
	$(COMP) $(OBJ) -o ${OUTPUT}

obj/%.o: src/%.cpp
	$(COMP) $(LDFLAGS) $< -c -o $@

clean:
	-rm -v ${OBJ} 
	-rm -v ${OUTPUT}
