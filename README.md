# Star-Seeker
Projet d'étudiants en L2 Informatique

## Compiler le projet
Pour compiler le projet, changer la variable du Makefile selon votre système d'exploitation.
```
#Systeme d'exploitation (win pour windows, sinon n'importe quoi par défaut)
ARCH = linux
``` 

Ensuite exécutez 
```
make all
```

Sur Windows, il peut être nécessaire d'exécutez la commande suivante pour créer les répertoires obj et save.
```make init```
obj est nécessaire à la compilation tandis que save est nécessaire à l'exécution du jeu.


Star Seeker est un rogue-like basé sur le thème spatial. Le joueur incarne un voyageur de l’espace qui a pour objectif de se rendre sur la dernière planète d’une galaxie pour accomplir une mission qui lui est donnée : récupérer un artéfact ou battre un boss. 
Pour atteindre les planètes les plus lointaines, il doit améliorer son vaisseau grâce aux débris mécaniques qu’il trouve sur les planètes qu’il peut explorer. 
Sur son chemin, il rencontre des monstres qu’il doit combattre pour avancer dans son aventure. Il peut également trouver des objets / améliorations / vies en plus, pour faciliter son avancée.
