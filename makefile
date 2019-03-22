CC := gcc
CFLAGS := -MMD -g -O3 -Wall -I. -I.. -Icompare/ -Idata_structures/ -Iaux/
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

%: $(OBJ)/$(SORT)/%.o $(MAINO) $(AUXO) $(COMPO) $(DATAO)
	$(CC) $< $(MAINO) $(AUXO) $(COMPO) $(DATAO) -o $@ $(LDFLAGS)

$(OBJ)/$(AUX)/%.o: $(AUX)/%.c $(AUX)/%.h
	$(CC) $(SDLFLAG) $(CFLAGS) -c $< -o $@

$(OBJ)/$(COMP)/%.o: $(COMP)/%.c $(COMP)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/$(DATA)/%.o: $(DATA)/%.c $(DATA)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(MAINO): main.c
	$(CC) $(SDLFLAG) $(CFLAGS) -c $< -o $@


$(OBJ)/$(SORT)/%.o: $(SORT)/%.c
	$(CC) $(CFLAGS) -c $(SORT)/$(*F).c -o $@



clean:
	del obj/*/*.d
	del obj/*/*.o
	del obj/*.o
	del obj/*.d
	del vgcore.*
	del $(EXE)

.PHONY: all clean
