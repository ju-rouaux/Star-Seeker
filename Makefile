# Parametres de la compilation
CC = gcc
CXXFLAGS = -Wall -g 
LDFLAGS = -I./include -Llib -lSDL2

# Parametres du makefile
APPNAME = ./bin/generation_niveau
EXT = .c
SRCDIR = ./src
OBJDIR = ./obj

########################################################################

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm
DELOBJ = ./obj/*.o

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




# Supprime tout les fichiers objets et l'executable (.o et exe)
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(APPNAME)
	@echo Nettoyage de tout les fichiers generes reussi

