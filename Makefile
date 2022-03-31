#Systeme d'exploitation (win pour windows, sinon n'importe quoi par défaut)
ARCH = linux

include Makefile.compilation

# Parametres de la compilation
CC = gcc
CXXFLAGS = -Wall -g

# Parametres du makefile
APPNAME = ./bin/star-seeker
EXT = .c
SRCDIR = ./src
OBJDIR = ./obj

########################################################################

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm

########################################################################

# Compiler le projet
all: $(CIBLE_ARCH) $(APPNAME)
	@echo -- Compilation reussie --

# Générer les répertoires nécessaires s'ils sont manquants
init:
	mkdir $(PARAM_INIT) obj save

# Test algo génération
algogen: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ obj/test_niveau.o $(LDFLAGS)

# Compiler
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo -- Tout les fichiers objets ont bien ete generes --

# Construire les fichiers .o avec les .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $< $(LDFLAGS)

########################################################################

# Supprimer les fichiers du projet (.exe pour Windows)
.PHONY: clean
clean:
	$(RM) $(PARAM_CLEAN) $(OBJDIR)/*.o
	@echo -- Objets supprimes ! --
	$(RM) $(PARAM_CLEAN) $(APPNAME)$(EXTAPP)
	@echo -- Executable supprime ! --

########################################################################

#Macros

#Générer la documentation
.PHONY: doc
doc:
	doxygen gen_doxygen
	@echo Documentation generee

#Compiler et lancer le programme
.PHONY: start
start: all
	$(APPNAME)

#Supprime les fichiers du projet, recompile et lance le programme
mrproper: clean start
