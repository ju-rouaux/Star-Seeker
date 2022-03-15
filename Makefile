# Parametres de la compilation
CC = gcc
CXXFLAGS = -Wall -g 
LDFLAGS = -I./include -Llib -lSDL2main -lSDL2 -lSDL2_ttf -lm

# Parametres du makefile
APPNAME = ./bin/save
EXT = .c
SRCDIR = ./src
OBJDIR = ./obj

########################################################################

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################

all: $(APPNAME)
	@echo Compilation reussie

#Test algo génération
algogen: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ obj/test_niveau.o $(LDFLAGS)

# Compile
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo Tout les fichiers objets ont bien ete generes

# Construit les fichiers .o avec les .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)