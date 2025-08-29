# NotAloneInTheHouse
*Un jeu d'évasion en première personne dans une maison hantée*

## Description

**NotAloneInTheHouse** est un jeu vidéo d'évasion (escape game) développé avec Unreal Engine 5.4. Le joueur se retrouve piégé dans une maison hantée mystérieuse et doit résoudre des énigmes, collecter des indices et éviter les événements surnaturels pour s'échapper.

## Caractéristiques principales

### 🎮 Gameplay
- **Vue à la première personne** pour une immersion maximale
- **Système d'interaction** avec les objets de l'environnement
- **Collecte d'indices** nécessaire pour progresser dans le jeu
- **Système d'inventaire** pour gérer les objets trouvés
- **Puzzles et énigmes** à résoudre pour débloquer de nouvelles zones

### 👻 Éléments surnaturels
- **Système de peur** qui affecte le joueur
- **Événements paranormaux** déclenchés dynamiquement
- **Activité surnaturelle** qui s'intensifie au fur et à mesure de la progression
- **Objets hantés** avec des comportements spéciaux

### 🏠 Environnement
- **Maison victorienne** avec une atmosphère gothique
- **Salles verrouillées** nécessitant des clés spécifiques
- **Objets interactifs** dispersés dans l'environnement
- **Éclairage dynamique** pour créer une ambiance inquiétante

## Structure du projet

### Code Source (C++)
- `NotAloneInTheHouseGameModeBase` - Gestion du mode de jeu et des événements surnaturels
- `EscapeGamePlayer` - Contrôleur de joueur avec système de peur et d'inventaire
- `InteractableObject` - Classe de base pour tous les objets interactifs

### Organisation du contenu
```
Content/
├── Blueprints/
│   ├── GameMode/          # Modes de jeu et logique principale
│   ├── Player/            # Blueprints du joueur
│   └── Interactables/     # Objets interactifs
├── Maps/                  # Niveaux de jeu
├── Materials/             # Matériaux et shaders
├── Meshes/
│   ├── Props/            # Objets et meubles
│   └── Environment/      # Architecture et décors
├── Textures/             # Textures et images
├── Audio/
│   ├── SFX/             # Effets sonores
│   └── Music/           # Musique d'ambiance
├── UI/                   # Interface utilisateur
└── Particles/           # Effets de particules
```

## Types d'objets interactifs

1. **Indices (Clues)** - Éléments à collecter pour progresser
2. **Clés (Keys)** - Ouvrent des portes verrouillées
3. **Portes (Doors)** - Accès à de nouvelles zones
4. **Puzzles** - Énigmes à résoudre
5. **Objets surnaturels** - Déclenchent des événements paranormaux
6. **Mobilier** - Exploration et recherche d'objets cachés
7. **Journaux** - Révèlent l'histoire de la maison

## Système de progression

- Le joueur doit collecter **10 indices** pour s'échapper de la maison
- Chaque indice trouvé augmente l'**activité paranormale**
- Les événements surnaturels déclenchent la **peur** chez le joueur
- Certaines zones nécessitent des **clés spécifiques** pour être déverrouillées

## Événements surnaturels

- Claquement de portes
- Scintillement des lumières
- Chuchotements mystérieux
- Zones de froid intense
- Mouvement d'ombres
- Déplacement d'objets
- Bruits de pas fantômes
- Sons mystérieux

## Configuration requise

- **Unreal Engine 5.4** ou supérieur
- **Plateformes supportées** : Windows, Mac, Linux
- **Modules requis** : Engine, CoreUObject, InputCore, NavigationSystem, AIModule

## Installation et utilisation

1. Clonez ce repository
2. Ouvrez le fichier `NotAloneInTheHouse.uproject` avec Unreal Engine
3. Compilez le projet (Build > Build Solution)
4. Lancez le jeu dans l'éditeur ou créez un build standalone

## Développement

Ce projet utilise une architecture modulaire avec :
- **Code C++** pour la logique de base et les performances
- **Blueprints** pour le prototypage rapide et les interactions visuelles
- **Système d'événements** pour la communication entre les composants

## Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

---

*"Dans cette maison, vous n'êtes jamais vraiment seul..."*