# Structure du contenu - NotAloneInTheHouse

Ce fichier décrit l'organisation recommandée du contenu dans le dossier Content.

## Organisation par catégories

### Blueprints/
Organisation des Blueprints par fonctionnalité :

```
Blueprints/
├── GameMode/
│   ├── BP_NotAloneGameMode         # GameMode principal
│   ├── BP_GameState               # État global du jeu
│   └── BP_PlayerController        # Contrôleur du joueur
├── Player/
│   ├── BP_EscapePlayer            # Blueprint du joueur
│   ├── BP_PlayerHUD               # Interface utilisateur
│   └── BP_FearSystem              # Système de peur
└── Interactables/
    ├── BP_ClueObject              # Objets indices
    ├── BP_KeyObject               # Clés
    ├── BP_DoorObject              # Portes
    ├── BP_PuzzleObject            # Puzzles
    ├── BP_SupernaturalObject      # Objets hantés
    └── BP_FurnitureObject         # Mobilier
```

### Maps/
Niveaux de jeu organisés par zones :

```
Maps/
├── MainMenu                       # Menu principal
├── HauntedHouse_Main             # Niveau principal
├── TestLevel                     # Niveau de test
└── Sublevels/
    ├── GroundFloor               # Rez-de-chaussée
    ├── FirstFloor                # Premier étage
    ├── Attic                     # Grenier
    └── Basement                  # Cave
```

### Materials/
Matériaux organisés par utilisation :

```
Materials/
├── Architecture/
│   ├── M_Walls_Victorian         # Murs style victorien
│   ├── M_Floors_Wood            # Parquets
│   └── M_Ceiling_Plaster        # Plafonds
├── Props/
│   ├── M_Furniture_Wood         # Mobilier en bois
│   ├── M_Metal_Rusty           # Métaux rouillés
│   └── M_Fabric_Old            # Tissus vieillis
└── Effects/
    ├── M_Ghost_Transparent      # Effets fantômes
    ├── M_Particles_Dust        # Poussière
    └── M_Lighting_Candle       # Éclairage bougies
```

### Meshes/
Modèles 3D organisés par catégorie :

```
Meshes/
├── Architecture/
│   ├── Walls/                   # Murs et cloisons
│   ├── Doors/                   # Portes et fenêtres
│   ├── Stairs/                  # Escaliers
│   └── Decorative/             # Éléments décoratifs
├── Props/
│   ├── Furniture/
│   │   ├── SM_Chair_Victorian   # Chaise victorienne
│   │   ├── SM_Table_Dining     # Table de salle à manger
│   │   └── SM_Bookshelf        # Bibliothèque
│   ├── Items/
│   │   ├── SM_Key_Old          # Clés anciennes
│   │   ├── SM_Journal          # Journaux/livres
│   │   └── SM_Candle           # Bougies
│   └── Decorative/
│       ├── SM_Painting         # Tableaux
│       ├── SM_Vase             # Vases
│       └── SM_Clock            # Horloges
└── Characters/
    └── Ghosts/                 # Modèles d'entités spectrales
```

### Textures/
Textures organisées par type et utilisation :

```
Textures/
├── Architecture/
│   ├── Walls/
│   │   ├── T_Wall_Victorian_D   # Diffuse
│   │   ├── T_Wall_Victorian_N   # Normal
│   │   └── T_Wall_Victorian_R   # Roughness
│   └── Floors/
│       ├── T_Wood_Floor_D
│       ├── T_Wood_Floor_N
│       └── T_Wood_Floor_R
├── Props/
│   ├── Furniture/
│   └── Items/
├── Effects/
│   ├── Particles/
│   └── UI/
└── Environment/
    ├── Skybox/
    └── Lighting/
```

### Audio/
Fichiers audio organisés par type :

```
Audio/
├── SFX/
│   ├── Ambience/
│   │   ├── A_Wind_Howling       # Vent qui hurle
│   │   ├── A_House_Creaking     # Craquements de maison
│   │   └── A_Silence_Eerie      # Silence inquiétant
│   ├── Interactions/
│   │   ├── A_Door_Open          # Ouverture de porte
│   │   ├── A_Key_Pickup         # Ramassage de clé
│   │   └── A_Paper_Rustle       # Froissement de papier
│   ├── Supernatural/
│   │   ├── A_Whispers           # Chuchotements
│   │   ├── A_Ghost_Moan         # Gémissements
│   │   └── A_Chain_Rattle       # Cliquetis de chaînes
│   └── Footsteps/
│       ├── A_Footstep_Wood      # Pas sur bois
│       ├── A_Footstep_Stone     # Pas sur pierre
│       └── A_Footstep_Carpet    # Pas sur tapis
├── Music/
│   ├── M_MainTheme              # Thème principal
│   ├── M_Exploration            # Musique d'exploration
│   ├── M_Tension                # Musique de tension
│   └── M_Victory                # Musique de victoire
└── Voice/
    ├── V_Narrator               # Narration
    └── V_Whispers               # Voix spectrales
```

### UI/
Interface utilisateur :

```
UI/
├── HUD/
│   ├── W_MainHUD                # HUD principal
│   ├── W_Inventory              # Interface inventaire
│   ├── W_InteractionPrompt      # Prompt d'interaction
│   └── W_FearMeter              # Indicateur de peur
├── Menus/
│   ├── W_MainMenu               # Menu principal
│   ├── W_PauseMenu              # Menu pause
│   ├── W_SettingsMenu           # Menu paramètres
│   └── W_GameOverMenu           # Menu fin de partie
└── Textures/
    ├── T_Button_Normal          # Boutons normaux
    ├── T_Button_Hovered         # Boutons survolés
    └── T_Icons                  # Icônes diverses
```

### Particles/
Systèmes de particules :

```
Particles/
├── Environment/
│   ├── P_Dust_Floating          # Poussière flottante
│   ├── P_Cobwebs                # Toiles d'araignées
│   └── P_Candle_Flame           # Flammes de bougies
├── Supernatural/
│   ├── P_Ghost_Apparition       # Apparition fantôme
│   ├── P_Ectoplasm              # Ectoplasme
│   └── P_Spirit_Orbs            # Orbes spirituelles
└── Interactions/
    ├── P_Item_Pickup            # Ramassage d'objet
    └── P_Door_Dust              # Poussière de porte
```

## Conventions de nommage

### Préfixes recommandés
- **BP_** : Blueprints
- **M_** : Materials
- **MI_** : Material Instances
- **T_** : Textures
- **SM_** : Static Meshes
- **SK_** : Skeletal Meshes
- **A_** : Audio files
- **P_** : Particle Systems
- **W_** : Widgets (UI)

### Suffixes pour les textures
- **_D** : Diffuse/Albedo
- **_N** : Normal Map
- **_R** : Roughness
- **_M** : Metallic
- **_AO** : Ambient Occlusion
- **_E** : Emissive

### Exemple de nommage complet
```
T_Wall_Victorian_Bedroom_D.uasset
SM_Chair_Antique_Carved_LOD0.uasset
BP_Door_Wooden_Locked.uasset
A_SFX_Door_Creak_Long.uasset
```

## Recommandations

1. **Consistance** : Toujours utiliser les mêmes conventions
2. **Organisation** : Grouper les assets par fonctionnalité
3. **Optimisation** : Utiliser des LODs pour les meshes complexes
4. **Documentation** : Commenter les Blueprints complexes
5. **Tests** : Créer des niveaux de test pour chaque asset