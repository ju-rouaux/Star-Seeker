# Parametres de la compilation
CC = gcc
CXXFLAGS = -Wall -g 
LDFLAGS = -I./include -Llib -lSDL2main -lSDL2

# Parametres du makefile
<<<<<<< HEAD
APPNAME = ./bin/deplacement
=======
APPNAME = ./bin/generation_niveau
>>>>>>> cc0ba498f9eaa3975bd10b01257c66915ebd8ff3
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

