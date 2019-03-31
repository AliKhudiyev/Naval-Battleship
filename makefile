GCC		= g++
FLGS	= -g -Wextra --std=c++17 
LIBS = `sdl-config --cflags --libs`

SRC_DIR	= src
OBJ_DIR	= obj
INCLUDE	= lib
DEP_DIR	= dep

SRC		= $(wildcard $(SRC_DIR)/*.cpp)
LIB		= $(subst lib/,,$(wildcard $(INCLUDE)/*.hpp))
OBJ		= $(subst $(SRC_DIR),$(OBJ_DIR),$(patsubst %.cpp,%.o,$(SRC)))
DEP		= $(subst $(SRC_DIR),$(DEP_DIR),$(SRC:.cpp=.dep))

# -include $(DEP)

# $(DEP_DIR)/%.dep: $(SRC_DIR)%.cpp
	# $(GCC) $(FLGS) $< -MM -MT$(@:.dep=.o)>$@

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
	@echo
	@echo $(DEP)

clean:
	$(RM) $(OBJ)