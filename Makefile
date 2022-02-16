# Parametres de la compilation
CC = gcc
CXXFLAGS = -Wall -g 
LDFLAGS = -I./include -Llib -lSDL2

# Parametres du makefile
APPNAME = ./bin/event
EXT = .c
SRCDIR = ./src
OBJDIR = ./obj

########################################################################

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm
DELOBJ = $(OBJ)

########################################################################

all: $(APPNAME)
	@echo Compilation reussie

# Compile
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -g
	@echo Tout les fichiers objets ont bien ete generes

# Construit les fichiers .o avec les .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)


# Supprime tout les fichiers objets et l'executable (.o et exe)
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(APPNAME)
	@echo Nettoyage de tout les fichiers generes reussi
