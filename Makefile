# Parametres de la compilation
CC = gcc
CXXFLAGS = -Wall -g 
LDFLAGS = -I./include -Llib -lSDL2main -lSDL2 -lSDL2_ttf -lm

# Parametres du makefile
APPNAME = ./bin/star-seeker
EXT = .c
SRCDIR = ./src
OBJDIR = ./obj

########################################################################

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm
DELOBJ = $(OBJ)

########################################################################

# Compiler le projet
all: init $(APPNAME)
	@echo Compilation reussie

# Générer les répertoires nécéssaires
init:
	mkdir -p obj
	mkdir -p save

# Test algo génération
algogen: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ obj/test_niveau.o $(LDFLAGS)

# Compiler
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo Tout les fichiers objets ont bien ete generes

# Construire les fichiers .o avec les .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

########################################################################

# Supprimer les fichiers du projet (.exe pour Windows)
.PHONY: clean
clean:
	$(RM) -f $(OBJDIR)/*.o
	$(RM) -f $(APPNAME)
	$(RM) -f $(APPNAME).exe
	@echo Clean effectue !

########################################################################
#Macros

.PHONY: doc
doc:
	doxygen gen_doxygen
	@echo Documentation generee

#Compiler et lancer le programme
.PHONY: start
start: all
	$(APPNAME)