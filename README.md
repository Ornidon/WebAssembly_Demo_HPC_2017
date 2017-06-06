# WebAssembly_Demo_HPC_2017

## Introduction

Le but de cette démonstration est de tester et d'analyser les possibilités offertes par WebAssembly. Dans cette étude nous verrons le fonctionnement de WebAssembly, comment compiler et exporter du code C vers une page web utilisant javascript. Nous étudions également les différentes foncionalités disponibles via WebAssembly ainsi que les optimisations possibles.

Le code de démonstration permet de comparer la conversion d'une image en noir et blanc entre : 
 - C
 - JavaScript
 - JavaScript avec WebAssembly

Les tests ont été réalisés sur un processeur Intel : I7 4870HQ à 2.5GHz (Intel) et sur un processeur ARM : 

![ImageCouleur](src/chaton.jpg)
![ImageNoirBlanc](src/chaton.jpg)

## Pour déployer l'application

### Prérequis

Pour compiler vers WebAssembly, pour le moment nous avons besoin de compiler LLVM depuis les sources. Les outils suivants sont requis :
- Git. 
- CMake
- Host system compiler:
    - Linux : GCC
    - OS X : Xcode
    - Windows : Visual Studio 2015 Community avec update 3 ou supérieur
- Python 2.7.x. 

Après l'installation, assurez vous que cmake, python et git sont accessible dans le PATH.

###  Compilateur Emscripten

Le build de Emscripten depuis les sources s'effectue via les commandes suivantes :
```bash
$ git clone https://github.com/juj/emsdk.git
$ cd emsdk
$ ./emsdk install sdk-incoming-64bit binaryen-master-64bit
$ ./emsdk activate sdk-incoming-64bit binaryen-master-64bit
```
Une fois l'installation complete, pour entrer un compilateur Emscripten dans l'environement entrez :
```bash
$ source ./emsdk_env.sh
```

Sur Windows, il faut remplacer ./emsdk par emsdk, et source ./emsdk_env.sh par emsdk_env above.

### Déploiment de l'application

1. Il vous faut cloner le répertoire 
2. Ouvrir un terminal dans le répertoire cloné
3. Lancer les commandes suivantes :

```bash
  $ emcc hello.c -s WASM=1 -o hello.html
  $ emrun --no_browser --port 8080 
```

## Utilisation

 Ouvrir votre navigateur et allez sur localhost:8080

## Mesures

## Analyse

## Technologies 
Pour ce projet nous utilisons les technologies suivantes :
 - C
 - JavaScript ES2015
 - Emscripten
 - WebAssembly

## Pour plus d'informations


## Auteurs
Bastien Clément, Paul Ntawuruhunga, Thibaut Loiseau