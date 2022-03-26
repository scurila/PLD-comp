
# PLD Compilateur - Dépôt de mi-parcours 

Ce document a vocation à décrire l'état du projet au moment du rendu de mi-parcours.

### État des fonctionnalités implémentées

##### Éléments du langage C reconnus

- [x] Gestion d'un seul fichier source, en ignorant le préprocessing
- [x] Les commentaires sont ignorés
- [x] Déclaration de variables, à plusieurs endroits dans le code
- [x] Linéarisation d'expressions
- [x] Calcul des expressions arithmétiques (+, -, *, parenthèses)
- [x] Utilisation de variables et constantes numériques dans les expressions
- [ ] Utilisation de caractères dans les expressions
- [ ] Gestion des opérations logiques bit-à-bit
- [ ] Opérations de comparaisons
- [ ] Opérations unaires
- [ ] Affectations comme en C (avec retour de valeur)
- [x] Initialisations et déclarations de variables en une ligne (possiblement multiples)
  
- [ ] Utilisation des fonctions standard `putchar`/`getchar`
- [ ] Définition de fonctions avec paramètres, et type de retour int, char ou void
- [ ] Structures de blocs avec { et }
- [ ] Support des portées de variables et shadowing
- [ ] Structures de contrôle `if, else, while`
- [x] Support du `return` *expression*
- [ ] Division (reconnu mais non testé), et modulo
  
- [ ] Opérateurs d'affectation +=, -= (etc) et d'incrémentation/décrémentation ++, --
- [ ] Tableaux 1D
- [ ] Pointeurs
- [ ] `break` et `continue`
- [ ] Chaînes de caractères sous forme de tableaux de `char`
- [ ] `switch-case`
- [ ] Opérateurs logiques &&, ||

- [x] Support du type `int`
- [ ] Support des autres types de base entiers (juste char reconnu mais est un int32)
- [ ] Support des opérateurs arithmétiques et logiques <=, >=, <<, >> etc
- [ ] Structures de contrôle `for, do while`
- [ ] Variables globales

- [ ] Séparation des déclarations et définitions dans des fichiers distincts
- [ ] Support du préprocesseur
- [ ] Structures et unions


##### Aspects structurels / processus de compilation

- [ ] Vérification de la cohérence des appels de fonctions et leurs paramètres
- [x] Vérification qu'une variable utilisée a été déclarée préalablement
- [x] Vérification qu'une variable n'est pas déclarée plusieurs fois
- [ ] Vérification qu'une variable est utilisée au moins une fois

- [x] Reciblage vers plusieurs architectures **(supporté, mais pas encore de CLI)**
- [ ] Propagation simple de constantes
- [ ] Propagation de variables constantes (avec analyse du data-flow)

- [x] IR mise en place



### Structure de l'application

Le dossier `pld-comp` contient les fichiers du projet (les fichiers à la racine sont principalement des ressources ou des informations).

##### Le dossier `pld-comp`

Ce dossier contient deux sous-dossiers, `compiler`, qui contient notre compilateur, avec les fichiers nécessaires pour le compiler, et `tests`, qui permet d'exécuter une batterie de tests sur notre compilateur.

###### Le dossier `compiler`

Comme mentionné précedemment, ce dossier contient les sources de notre compilateur et les fichiers nécessaires à sa compilation. On retrouvera notamment dans le dossier `IR` les structures de données liées à l'IR, et le reste des fichiers source se trouve pour l'instant à la racine du dossier.

Le dossier `snippets` contient des exemples de code qui sont, pour la plupart, compilables correctement par notre compilateur.

Les dossiers `build` et `generated` contienent les fichiers nécessaires pour la compilation du compilateur.


###### Le dossier `tests`

Ce dossier contient les fichiers de test. Le sous-dossier `testfiles` contient la liste des fichiers correspondant aux différents testcases mis en place. Ceux-ci peuvent être lancés en utilisant le script python `ifcc-test.py`.


### Gestion projet

Dans un premier temps, nous avons fonctionné principalement en pair-programming, afin de mettre en place les premières briques du projet, et s'assurer que tout le monde comprenait la base. Nous avons ensuite, au fur et à mesure, parallélisé de plus en plus les fonctionnalités qui pouvaient l'être.

À l'heure de ce dépôt, l'IR ayant été finalement mise en place, nous allons pouvoir paralléliser encore plus de tâches (étant donné qu'il s'agissait d'un important élément bloquant).




