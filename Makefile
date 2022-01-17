# Parametres de la compilation
CC = gcc
CXXFLAGS = -std=c11 -Wall -g
LDFLAGS = 
INCLUDES = -I./include

# Parametres du makefile
APPNAME = ./bin/Star_Seeker
EXT = .c
SRCDIR = ./src
OBJDIR = ./obj

########################################################################

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

# Parametres OS type UNIX
RM = rm
DELOBJ = $(OBJ)

# Parametres Windows
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################

all: $(APPNAME)
	@echo Compilation reussie

# Compile
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo Tout les fichiers objets ont bien ete generes

# Construit les fichiers .o avec les .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Parametres de nettoyage pour OS type UNIX ################

# Supprime tout les fichiers objets et l'executable (.o et exe)
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(APPNAME)
	@echo Nettoyage de tout les fichiers generes reussi

#################### Parametres de nettoyage pour Windows ####################

# Supprime tout les fichiers objets et l'executable (.o et exe)
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(APPNAME)$(EXE)
	@echo Nettoyage de tout les fichiers generes reussi
