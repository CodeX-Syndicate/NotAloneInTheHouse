# Guide de développement - NotAloneInTheHouse

## Architecture du jeu

### Classes principales

#### NotAloneInTheHouseGameModeBase
Cette classe gère l'état global du jeu :
- Suivi de la progression (indices collectés)
- Gestion des événements surnaturels
- Conditions de victoire
- Niveau d'activité paranormale

**Fonctions clés :**
- `StartGame()` - Initialise le jeu
- `FindClue()` - Appelée quand un indice est trouvé
- `TriggerSupernaturalEvent()` - Déclenche un événement paranormal
- `CheckVictoryCondition()` - Vérifie si le joueur a gagné

#### EscapeGamePlayer
Contrôleur du joueur avec :
- Mouvement en première personne
- Système d'interaction avec les objets
- Gestion de l'inventaire
- Système de peur

**Systèmes principaux :**
- **Mouvement** : WASD + souris pour regarder
- **Interaction** : Détection par raycast, activation par clic
- **Inventaire** : Stockage limité d'objets
- **Peur** : Niveau qui augmente avec les événements surnaturels

#### InteractableObject
Classe de base pour tous les objets avec lesquels le joueur peut interagir :
- Types multiples (indices, clés, portes, puzzles, etc.)
- Système d'événements Blueprint
- Logique spécifique par type d'objet

## Système d'interaction

### Détection d'objets
Le joueur utilise un raycast depuis la caméra pour détecter les objets interactifs :
```cpp
// Dans EscapeGamePlayer::UpdateInteractable()
FVector Start = FirstPersonCamera->GetComponentLocation();
FVector End = Start + (FirstPersonCamera->GetForwardVector() * InteractionRange);
```

### Tags d'identification
Tous les objets interactifs doivent avoir le tag "Interactable" :
```cpp
Tags.Add(TEXT("Interactable"));
```

### Types d'interaction
Chaque objet a un type spécifique qui détermine son comportement :
- **Clue** : Collecté et compte vers la victoire
- **Key** : Ajoutée à l'inventaire pour ouvrir des portes
- **Door** : Peut être verrouillée, nécessite une clé
- **Puzzle** : Déclenche une séquence de puzzle
- **SupernaturalObject** : Augmente la peur et déclenche des événements

## Système de peur

Le niveau de peur du joueur affecte l'expérience de jeu :
- **Augmente** avec les événements surnaturels
- **Diminue** lentement avec le temps
- **Influence** les effets visuels et sonores (via Blueprint)

```cpp
void IncreaseFear(float Amount);
void DecreaseFear(float Amount);
```

## Événements surnaturels

### Types d'événements
- Door Slam
- Lights Flicker
- Whispers
- Cold Spot
- Shadow Movement
- Object Movement
- Footsteps
- Mysterious Sound

### Déclenchement
Les événements peuvent être déclenchés :
1. Automatiquement quand un indice est trouvé
2. Par interaction avec des objets surnaturels
3. Manuellement via le GameMode

## Intégration Blueprint

### Événements implémentables
Plusieurs fonctions sont définies comme `BlueprintImplementableEvent` pour permettre l'implémentation visuelle :

**GameMode :**
- `OnGameStart()`
- `OnClueFound(int32 CluesRemaining)`
- `OnVictory()`
- `OnSupernaturalEvent(const FString& EventName)`

**Player :**
- `OnFearLevelChanged(float NewFearLevel)`
- `OnInventoryChanged()`

**InteractableObject :**
- `OnInteractionStart(AActor* InteractingActor)`
- `OnInteractionEnd(AActor* InteractingActor)`

### Extension via Blueprint
Chaque classe C++ peut être étendue en Blueprint pour :
- Ajouter des effets visuels
- Configurer les meshes et matériaux
- Implémenter des animations
- Créer des interfaces utilisateur

## Conseils de développement

### Ajout de nouveaux objets interactifs
1. Hériter de `AInteractableObject`
2. Définir le `InteractableType` approprié
3. Configurer les propriétés dans l'éditeur
4. Ajouter le tag "Interactable"

### Création de nouveaux événements surnaturels
1. Ajouter le nom de l'événement dans `SupernaturalEvents`
2. Implémenter la logique dans `OnSupernaturalEvent` (Blueprint)
3. Configurer les objets pour déclencher l'événement

### Optimisation
- Utiliser `bCanEverTick = false` pour les objets statiques
- Limiter le nombre d'objets avec collision complexe
- Grouper les objets similaires pour réduire les draw calls

## Structure recommandée des niveaux

1. **Zone de départ** - Introduction et premiers indices
2. **Salon principal** - Hub central avec accès aux autres pièces
3. **Cuisine** - Indices liés à l'histoire de la famille
4. **Bibliothèque** - Puzzles et journaux
5. **Chambres** - Objets personnels et clés
6. **Grenier** - Zone finale avec les derniers indices
7. **Cave** - Zone optionnelle avec événements surnaturels intenses

Chaque zone doit contenir :
- 1-2 indices obligatoires
- 1 clé pour débloquer la zone suivante
- 2-3 objets surnaturels pour l'ambiance
- Des éléments de narration (journaux, photos, etc.)