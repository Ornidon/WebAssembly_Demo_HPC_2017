# WebAssembly_Demo_HPC_2017

## Introduction

Le but de cette démonstration est de tester et d'analyser les possibilités offertes par WebAssembly. Dans cette étude nous verrons le fonctionnement de WebAssembly, comment compiler et exporter du code C vers une page web utilisant JavaScript. Nous étudions également les différentes foncionalités disponibles via WebAssembly ainsi que les optimisations possibles.

![ImageNoirBlanc](src/img_grayscale.png)
![ImageDither](src/dither.png)

Le code de démonstration permet de comparer la vitesse d'exécution de la fonction `grayscale_dither_ordered` réalisée au Labo 07 entre des implémentations: 
 - C
 - JavaScript
 - JavaScript avec WebAssembly
 
Pour des raisons liées au manque de support des instructions SIMD en WebAssembly (fonctionnalité prévue mais pas encore complétement disponible), une version simple basée sur le code fourni au début du laboratoire sera utilisée. Une version utilisant les instructions SSE2 sera également testée en environement Desktop pour comparaison.

Les tests ont été réalisés sur un processeur Intel I5 3427U à 1.8GHz pour la plateforme Desktop et sur un processeur ARM : Qualcomm S-600 à 1,9 GHz pour le cas du mobile.

## Pour déployer l'application

### Prérequis

Pour compiler vers WebAssembly, pour le moment, il est nécessaire de compiler LLVM depuis les sources. Les outils suivants sont requis :
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

### Déploiement de l'application

1. Il vous faut cloner le répertoire 
2. Ouvrir un terminal dans le répertoire cloné
3. Lancer les commandes suivantes :

```bash
  $ emcc main.c -s WASM=1 -s SIDE_MODULE=1 -O3 -o main.wasm
  $ emrun --no_browser --port 8080 
```

La première commande compile le code source de l'application WebAssembly dans un format binaire portable exécutable par le navigateur (`.wasm`) tandis que la deuxième commande exécute un serveur web de développement pour accéder à la page `index.html`.

Il est en effet indispensable que les différents fichiers composant l'application web soient fourni depuis un serveur web HTTP. Il n'est pas possible de charger une application WebAssembly depuis le système de fichier local (protocole `file://`).

## Utilisation

Déployez l'application puis ouvrez votre navigateur et rendez-vous sur `localhost:8080` (dans le cas de WebAssembly). 
Le serveur local de `emrun` peut également être utilisé pour accéder à l'application depuis un terminal mobile.

Pour l'application C classique, compilez le fichier `grayscale.c` à l'aide de la commande suivante :
```bash
  $ gcc grayscale.c -O3 -std=c11 -Wall -Wextra -g -I../stb/ -lm
```

## Mesures

La mesure de performance a simplement consisté en un comptage du nombre d'appels et d'executions de la méthode `dither` pendant une période de 500ms. Nous obtenons les résultats suivants sur la plateforme Desktop (AMD64):

 - Code C : 2074 itérations
 - Web Assembly : 1457 itérations
 - Javascript : 726 itérations
 
Et sur processeur ARM mobile :
 - Web Assembly : 219 itérations
 - Javascript : 123 itérations

*Note2 : Les tests ont été réalisés sur un processeur Intel I5 3427U à 1.8GHz et sur un processeur ARM : Qualcomm S-600 à 1,9 GHz*
 
## Analyse et Conclusion

Nous pouvons observer que nous gagnons environ 2 fois les performances du JS avec WebAssembly sur desktop contre environ 1.5 fois sur mobile. Au niveau des performances, Webassembly se situe proche du C en offrant toutefois des performances légèrement moins bonne.

Nous devons cependant noter que pour WebAssembly, les mesures comprennent également l'overhead necessaire pour effectuer l'appel des fonctions WebAssembly depuis JavaScript (ce qui inclu par ex: Conversion des paramètres, ...). Ceci est lié au fait est que la plateforme Web disponible en JavaScript fourni de nombreux outils permettant de réaliser simplement un tel benchmark alors que la plupart des appels systèmes, par exemple pour obtenir l'heure courrante ne sont pas disponible directement lorsque le code WebAssembly est compilé en tant que module accessible en JavaScript. 

En réalité, nous pouvons donc nous attendre à des performances légergement supérieurs du code WebAssembly si le calcul effecté côté C est significatif (l'overhead de l'appel étant constant). Ceci est très probablement comparable avec les FFIs (`Foreign Function Interface`) diponibles dans de nombreux langages dont l'oveahead est en principe important et dont l'usage ne se justifie que lorsque qu'il est amorti par un temps important de cacul dans le langage appelé. Ainsi il n'est pas optimale de remplacer une addition par un appel à une fonction C WebAssembly, tandis que l'implémentation d'un algorithme de *dithering* semble un usage plus approprié.

Le format WebAssembly est également portable: une seule compilation depuis une machin Intel permet d'exécuter le code sur toutes les plateformes supportées par WebAssembly, notament les plateformes mobile ARM. Dans le cas d'une application C classique, il est en principe nécessaire de recompiler le code source pour chaque plateformes sur lesquelles il doit être exécuté. Ceci fait de WebAssembly une plateforme d'exécution portable à la façon de la JVM dont les fonctionnalités de *sandbox* peuvent en justifier un usage hors du contexte des navigateurs web, par exemple pour exécuter du code non-sûr provenant de sources tierse et peut être d'autres architectures.

Une note également concernant les performances de la version SIMD en C pure: les résultats montrent des perforamnces jusqu'à 10 fois plus élevée que le code classique SISD avec 20703 itérations / 500 ms. Ceci illustre, comme le Labo 07, le potentiel des instructions SIMD et nous permet d'être optimistes concernant les gains de performance futures pour WebAssembly lorsque ces instructions seront plainement supportées.

## Technologies 
Pour ce projet nous utilisons les technologies suivantes :
 - C
 - JavaScript ES2015
 - Emscripten
 - WebAssembly

## Pour plus d'informations

?

## Auteurs
Bastien Clément, Paul Ntawuruhunga, Thibaut Loiseau
