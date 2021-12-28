# Projet CPP

c++ version: c++11
c version: c11


## Exécutable
L'exécutable sera produit à la racine du projet, nommé `labh` ou `labh.exe` selon le système de compilation.

**Attention**, l'exécutable ne peut pas démarrer que dans ce répertoire.


## Compilation du projet
L'excutable est produit à l'aide du `makefile`. Il est compatible dans Linux et Windows, la compatibilité est unconnue en MacOS pour le moment.


## Structure du projet
- **build**: Sorties intermédiaires produites durant la compilation. Ses contenues serons supprimés par `make clean`.
- **doc**: Documents de ce projet, y compris le **rapport**.
- **include**: Tous les fichiers `.h`
- **lib**: Libraires externales, les `.o` précompilés.
- **res**: Toutes les ressources externes, comme images, sons.
- **src**: Codes source, on n'accepte que `.cc`
- **test**: Codes de test



énoncé
https://www.lri.fr/~pa/progcxx.html