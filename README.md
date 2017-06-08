# WebAssembly_Demo_HPC_2017

## Introduction

Le but de cette démonstration est de tester et d'analyser les possibilités offertes par WebAssembly. Dans cette étude nous verrons le fonctionnement de WebAssembly, comment compiler et exporter du code C vers une page web utilisant javascript. Nous étudions également les différentes foncionalités disponibles via WebAssembly ainsi que les optimisations possibles.


![ImageNoirBlanc](src/img_grayscale.png)
![ImageDither](src/dither.png)

Le code de démonstration permet de comparer le "dithering" d'une image en noir et blanc entre : 
 - C
 - JavaScript
 - JavaScript avec WebAssembly

Les tests ont été réalisés sur un processeur Intel : I7 4870HQ à 2.5GHz (Intel) et sur un processeur ARM : 



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

Sur Windows, il faut remplacer `./emsdk` par `emsdk`, et source `./emsdk_env.sh` par `emsdk_env`.

### Déploiment de l'application

1. Il vous faut cloner le répertoire 
2. Ouvrir un terminal dans le répertoire cloné
3. Lancer les commandes suivantes :

```bash
  $ emcc main.c -s WASM=1 -s SIDE_MODULE=1 -O3 -o main.wasm
  $ emrun --no_browser --port 8080 
```

## Utilisation
 Déployez l'application puis ouvrez votre navigateur et allez sur localhost:8080 ou compiliez le fichier grayscale.c à l'aide de la commande suivante :
```bash
  $ gcc grayscale.c -O3 -std=c11 -Wall -Wextra -g -I../stb/ -lm
```

## Mesures

La mesure de performance à simplement consisté en un comptage du nombre d'appel et d'execution de la méthode dither pendant une durée de 500ms. Nous obtenons les résultats suivants obtenus les résultats suivants sur AMD64:
 - Code C : 2074 itérations
 - Web Assembly : 1457 itérations
 - JS : 726 itérations
Et sur processeur ARM mobile :
 - Web Assembly : 219 itérations
 - Javascript : 123 itérations
 
 [ Note : Dans webassembly les mesures comprennent également l'overhead necessaire pour des appels des fonctions WebAssembly depuis JavaScript ( ex : Conversion des paramètres...) ]
 
## Analyse et Conclusion
Nous pouvons observer que nous gagnons environ 2 fois les performances du JS avec WebAssembly sur desktop contre environ 1,5 fois sur mobile. Au niveau des performances Web assembly se situe proche du C en offrant toutefois des performances légèrement moins bonne nottament en raison de l'overhead necessaire à l'appel des fonctions que nous mesurons également
Le format WebAssembly est portable en une seule compilation tant sur desktop que sur mobile. En effet il nous à fallut qu'une seule compilation pour nos différents ordinateur et téléphones, alors qu'une application classique necessiterait une compilation par plateforme. Ce qui fait de WebAssembly est un environnement d'exection commun entre les plateformes pouvant être utilisé à l'extérieur d'un navigateur tel que la JVM.
En utilisant les instructions SIMD on atteint en C plus de 20703 itération ce qui correspond à 10 fois plus de performances.
Une fois que les insctruction SIMD seront complètement intégrées dans WebAssembly on peut s'attendre à un gain de performances similaire.


## Technologies 
Pour ce projet nous utilisons les technologies suivantes :
 - C
 - JavaScript ES2015
 - Emscripten
 - WebAssembly

## Pour plus d'informations


## Auteurs
Bastien Clément, Paul Ntawuruhunga, Thibaut Loiseau
