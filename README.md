# Star-Seeker
Projet d'étudiants en L2 Informatique

## Compiler le projet
Pour compiler le projet, changez la première variable du Makefile selon votre système d'exploitation.
```
#Systeme d'exploitation (win pour windows, sinon n'importe quoi par défaut)
ARCH = linux
``` 

Ensuite exécutez 
```
make all
```

Sur Windows, il peut être nécessaire d'exécuter la commande suivante pour créer les répertoires bin, obj et save. <br />
**Les répertoires bin et obj sont nécessaires pour la compilation tandis qu'un répertoire save est nécessaire pour la sauvegarde des parties.**
```
make init
```

#  Présentation du jeu
Star Seeker est un rogue-like basé sur le thème de l’espace (inspiré de The Binding of Isaac). Le but du jeu est d’explorer des planètes, dans des galaxies générées aléatoirement, afin d’abattre des monstres et gagner en expérience. Le joueur conserve son expérience au fil des parties, qui deviennent de plus en plus dures : les monstres deviennent plus forts, et plus nombreux. L’objectif est d’atteindre une galaxie de 10 planètes, la taille maximale.


## Contrôles par défaut

#### ----- Déplacements -----
```Z``` : Aller vers le haut<br />
```S``` : Aller vers le bas<br />
```D``` : Aller vers la droite<br />
```Q``` : Aller vers la gauche<br />

#### ----- Attaque -----
```⬆️``` : Attaque vers le haut<br />
```⬇️``` : Attaque vers le bas<br />
```➡️``` : Attaque vers la droite<br />
```⬅️``` : Attaque vers la gauche<br />

#### ----- Autres compétences -----
```ESPACE``` : Esquive (dash)<br />
```E``` : Interaction<br />
```ESC``` : Voyage sur une autre planète, et accès menu principal<br />
```TAB``` : Afficher la carte<br />
