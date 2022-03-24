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

Sur Windows, il peut être nécessaire d'exécuter la commande suivante pour créer les répertoires obj et save.
```make init```
obj est nécéssaire à la compilation tandis que save est nécéssaire à l'exécution du jeu.


Star Seeker est un rogue-like basé sur le thème spatial. Le joueur incarnera un voyageur de l’espace qui a pour objectif de se rendre sur la dernière planète d’une galaxie pour accomplir une mission qui lui est donnée : récupérer un artéfact ou battre un boss. Il devra ainsi se balader de planète en planète grâce à son vaisseau.
Pour atteindre les planètes les plus lointaines, il devra améliorer son vaisseau grâce aux débris mécaniques qu’il trouvera sur les planètes qu’il peut explorer. Sur son chemin, il rencontrera des monstres qu’il devra combattre pour avancer dans son aventure, voire résoudre quelques énigmes. Il peut également trouver des objets / améliorations / vies en plus, pour faciliter son avancée.
Nous souhaitons aussi laisser diriger le vaisseau au joueur lors du voyage d’une planète à une autre. Il devra limiter les dégâts pris par son vaisseau s’il espère voyager le plus loin possible en une traite.
