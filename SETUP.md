# Guide d'installation - NotAloneInTheHouse

## Prérequis

### Logiciels requis
- **Unreal Engine 5.4** ou version supérieure
- **Visual Studio 2022** (pour Windows) avec les composants C++
- **Git** pour le clonage du repository

### Spécifications système minimales
- **OS** : Windows 10/11 64-bit, macOS 10.15+, ou Ubuntu 18.04+
- **Processeur** : Quad-core Intel ou AMD, 2.5 GHz ou plus
- **Mémoire** : 8 GB RAM minimum (16 GB recommandés)
- **Graphiques** : DirectX 11 compatible
- **Stockage** : 5 GB d'espace libre

## Installation

### 1. Cloner le repository
```bash
git clone https://github.com/CodeX-Syndicate/NotAloneInTheHouse.git
cd NotAloneInTheHouse
```

### 2. Génération des fichiers de projet

#### Sur Windows
1. Clic droit sur `NotAloneInTheHouse.uproject`
2. Sélectionner "Generate Visual Studio project files"
3. Attendre la génération des fichiers

#### Sur Mac/Linux
```bash
# Depuis le dossier du projet
/path/to/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe -projectfiles -project="NotAloneInTheHouse.uproject" -game -rocket -progress
```

### 3. Compilation du projet

#### Via Unreal Engine Editor
1. Double-cliquer sur `NotAloneInTheHouse.uproject`
2. L'éditeur proposera de compiler le projet
3. Cliquer sur "Yes" et attendre la compilation

#### Via Visual Studio (Windows)
1. Ouvrir `NotAloneInTheHouse.sln`
2. Définir la configuration sur "Development Editor"
3. Build > Build Solution (Ctrl+Shift+B)

#### Via ligne de commande
```bash
# Windows
"C:\Program Files\Epic Games\UE_5.4\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" NotAloneInTheHouse Win64 Development -Project="NotAloneInTheHouse.uproject"

# Mac
/Users/Shared/Epic\ Games/UE_5.4/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool NotAloneInTheHouse Mac Development -Project="NotAloneInTheHouse.uproject"

# Linux
/home/user/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool NotAloneInTheHouse Linux Development -Project="NotAloneInTheHouse.uproject"
```

## Configuration initiale

### 1. Ouverture dans l'éditeur
- Double-cliquer sur `NotAloneInTheHouse.uproject`
- L'éditeur Unreal Engine s'ouvrira avec le projet

### 2. Vérification des paramètres du projet
1. Aller dans **Edit > Project Settings**
2. Vérifier les sections :
   - **Game > Game Mode** : S'assurer que le GameMode par défaut est configuré
   - **Input > Bindings** : Vérifier les contrôles (WASD, souris, E pour interagir)
   - **Rendering** : Adapter selon les performances souhaitées

### 3. Configuration du niveau de test
1. Créer un nouveau niveau : **File > New Level**
2. Choisir "Empty Level" ou "Default"
3. Ajouter les éléments de base :
   - Player Start
   - Quelques objets interactifs pour tester
   - Éclairage basique

## Test du jeu

### 1. Test rapide dans l'éditeur
1. Cliquer sur le bouton **Play** dans la barre d'outils
2. Utiliser **WASD** pour se déplacer
3. **Souris** pour regarder autour
4. **E** ou **Clic gauche** pour interagir avec les objets

### 2. Vérification des logs
1. Ouvrir **Window > Output Log**
2. Rechercher les messages "NotAloneInTheHouse:" et "EscapeGamePlayer:"
3. Vérifier qu'il n'y a pas d'erreurs de compilation

### 3. Build standalone
1. **File > Package Project > Windows/Mac/Linux**
2. Choisir un dossier de destination
3. Attendre la création du build
4. Lancer l'exécutable généré

## Résolution des problèmes courants

### Erreurs de compilation
- **"Module not found"** : Régénérer les fichiers de projet
- **"Missing includes"** : Vérifier les #include dans les fichiers .cpp
- **"Link errors"** : S'assurer que tous les modules sont listés dans le .Build.cs

### Problèmes de performance
- Réduire la qualité graphique dans les paramètres du projet
- Désactiver les effets de post-processing coûteux
- Optimiser les meshes et textures

### Contrôles qui ne fonctionnent pas
- Vérifier les Input Bindings dans Project Settings
- S'assurer que le PlayerController est correctement configuré
- Vérifier les logs pour les erreurs d'input

## Développement

### Structure recommandée pour le développement
1. **Toujours compiler** avant de tester dans l'éditeur
2. **Sauvegarder régulièrement** le projet
3. **Utiliser le contrôle de version** (Git) pour les changements
4. **Tester fréquemment** dans l'éditeur et en build standalone

### Extensions recommandées
- **Visual Studio Code** avec l'extension Unreal Engine
- **Perforce** ou **Git LFS** pour les gros assets
- **Blueprint Assist** pour l'organisation des Blueprints

## Support

En cas de problème :
1. Consulter la documentation officielle d'Unreal Engine
2. Vérifier les logs dans l'Output Log de l'éditeur
3. Chercher dans les forums de la communauté Unreal Engine
4. Créer une issue sur le repository GitHub

---

*Bonne chance pour votre évasion de la maison hantée !*