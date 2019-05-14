CC := gcc -pg -no-pie
CFLAGS := -MMD -g -O3 -Wall -Wpedantic -I. -I.. -Icompare/ -Idata_structures/ -Iaux/
SDLFLAG := `sdl2-config --cflags`
LDFLAGS := `sdl2-config --libs` -lSDL2_image -lm -pthread


OBJ := obj
COMP := compare
SORT := sort
DATA := data_structures
AUX := aux


AUXC := $(wildcard $(AUX)/*.c)
AUXH := $(AUXC:.c=.h)
AUXO := $(addprefix $(OBJ)/, $(AUXC:.c=.o))

COMPC := $(wildcard $(COMP)/*.c)
COMPH := $(COMPC:.c=.h)
COMPO := $(addprefix $(OBJ)/, $(COMPC:.c=.o))

DATAC := $(wildcard $(DATA)/*.c)
DATAH := $(DATAC:.c=.h)
DATAO := $(addprefix $(OBJ)/, $(DATAC:.c=.o))

SORTC := $(wildcard $(SORT)/*.c)
SORTO := $(addprefix $(OBJ)/, $(SORTC:.c=.o))
EXE :=  $(subst $(SORT)/,,$(SORTC:.c=))

MAINO := $(OBJ)/main.o

-include $(OBJ)/*/*.d

.DEFAULT_GOAL = all


all: $(EXE)

%: $(OBJ)/$(SORT)/%.o $(MAINO) $(AUXO) $(COMPO) $(DATAO) | $(OBJ)
	$(CC) $< $(MAINO) $(AUXO) $(COMPO) $(DATAO) -o $@ $(LDFLAGS)

$(OBJ)/$(AUX)/%.o: $(AUX)/%.c $(AUX)/%.h | $(OBJ)/$(AUX)
	$(CC) $(SDLFLAG) $(CFLAGS) -c $< -o $@

$(OBJ)/$(COMP)/%.o: $(COMP)/%.c $(COMP)/%.h | $(OBJ)/$(COMP)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/$(DATA)/%.o: $(DATA)/%.c $(DATA)/%.h | $(OBJ)/$(DATA)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAINO): main.c
	$(CC) $(SDLFLAG) $(CFLAGS) -c $< -o $@


$(OBJ)/$(SORT)/%.o: $(SORT)/%.c | $(OBJ)/$(SORT)
	$(CC) $(CFLAGS) -c $(SORT)/$(*F).c -o $@

$(OBJ):
	mkdir $(OBJ)

$(OBJ)/$(COMP): | $(OBJ)
	mkdir $(OBJ)/$(COMP)

$(OBJ)/$(SORT): | $(OBJ)
	mkdir $(OBJ)/$(SORT)

$(OBJ)/$(DATA): | $(OBJ)
	mkdir $(OBJ)/$(DATA)

$(OBJ)/$(AUX): | $(OBJ)
	mkdir $(OBJ)/$(AUX)

clean:
	del obj/*/*.d
	del obj/*/*.o
	del obj/*.o
	del obj/*.d
	del vgcore.*
	del $(EXE)

.PHONY: all clean
