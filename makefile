GCC		= g++
FLGS	= -g -Wextra --std=c++11 
LIBS = `sdl-config --cflags --libs`

SRC_DIR	= src
OBJ_DIR	= obj
INCLUDE	= lib

SRC		= $(wildcard $(SRC_DIR)/*.cpp)
LIB		= $(subst lib/,,$(wildcard $(INCLUDE)/*.hpp))
OBJ		= $(subst $(SRC_DIR),$(OBJ_DIR),$(patsubst %.cpp,%.o,$(SRC)))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(GCC) $(FLGS) -c -I\$(INCLUDE) $^ -o $@ 

bs: $(OBJ)
	$(GCC) $(FLGS) $^ -o $@ $(LIBS)

what:
	@echo $(SRC)
	@echo
	@echo $(LIB)
	@echo
	@echo $(OBJ)

clean:
	$(RM) $(OBJ)