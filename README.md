# Compilateur Atlas - Machine À Pile (MAP)

Compilateur complet pour le **langage Atlas** avec simulateur de machine à pile.

## 📋 Structure du langage Atlas

### Syntaxe générale
```atlas
programme <nom>;
[const
    ent|bool <id> = <valeur>;
    ...]
[var
    ent|bool <id>, <id>, ...;
    ...]
debut
    <instructions>
fin.
```

### Types de données
- `ent`: entier (32 bits)
- `bool`: booléen (0=faux, 1=vrai)

### Opérateurs
- **Arithmétiques**: `+`, `-`, `*`, `/`, `%`, `puiss`, `valabs`
- **Logiques**: `et`, `ou`, `non`
- **Comparaison**: `>`, `>=`, `=`, `<=`, `<`, `<>`
- **Affectation**: `:=`

### Instructions
- Affectation: `ID := expression;`
- Lecture: `lire ID;` ou `lireRC ID;`
- Écriture: `ecrire ID;` ou `ecrireRC ID;`
- Impression: `imprimer 'texte';`
- Conditions: `si (cond) alors instr [sinon instr] fsi`
- Boucle for: `pour ID depuis vi jusqua vf [parpas pas] faire instr fpour`
- Boucle while: `tantque (cond) faire instr ftq`
- Vide: `passer;`

### Commentaires
```atlas
// commentaire jusqu'à fin de ligne
```

## 🛠️ Compilation

### Prérequis
```bash
apt-get install flex bison gcc
```

### Compilation du compilateur
```bash
make all
```

Cela génère:
- `atlas`: compilateur Atlas → MAP
- `simulateur`: simulateur de machine à pile

### Structure de compilation
```
atlas.l (Flex)     → lex.yy.c
atlas.y (Bison)    → atlas.tab.c, atlas.tab.h
                     ↓
               Compilation gcc
                     ↓
              atlas (compilateur)
```

## 🚀 Utilisation

### Compiler un programme Atlas
```bash
./atlas prog1.atlas
```

Génère:
- `prog1.map`: code MAP généré
- Affiche le code et l'exécute automatiquement

### Exemples fournis

#### **prog1.atlas** - Somme de deux nombres
```atlas
programme somme;
var ent a, b, c;
debut
    lire a;
    lire b;
    c := a + b;
    imprimer 'somme:';
    ecrire c;
fin.
```

**Exécution**:
```bash
./atlas prog1.atlas
10
20
somme: 30
```

#### **prog2.atlas** - Test conditionnel avec constante
```atlas
programme test;
const ent max = 100;
var ent a, b, c;
debut
    lire a;
    b := a * 2;
    si (b >= max) alors
        c := max;
    sinon
        c := b;
    fsi;
    ecrire c;
fin.
```

**Exécution**:
```bash
./atlas prog2.atlas
50
100
```

#### **prog3.atlas** - Factoriel avec boucle
```atlas
programme factoriel;
var ent n, f, i;
debut
    lire n;
    si (n < 0) alors
        imprimer 'impossible';
    sinon
        f := 1;
        pour i depuis 2 jusqua n faire
            f := f * i;
        fpour;
        ecrire f;
    fsi;
fin.
```

**Exécution**:
```bash
./atlas prog3.atlas
5
120
```

## 📂 Fichiers du projet

| Fichier | Rôle |
|---------|------|
| `atlas.l` | Analyseur lexical (Flex) |
| `atlas.y` | Grammaire et actions sémantiques (Bison) |
| `simulateur.c` | Simulateur de machine à pile |
| `main.c` | Orchestrateur (compilation + exécution) |
| `Makefile` | Automatisation compilation |
| `prog1.atlas` - `prog3.atlas` | Exemples de test |

## 🎯 Fonctionnalités implémentées

### Lexique
- ✅ Mots-clés: `programme`, `var`, `const`, `debut`, `fin`, `si`, `pour`, `tantque`, etc.
- ✅ Identifiants et nombres
- ✅ Opérateurs et séparateurs
- ✅ Commentaires `//`
- ✅ Chaînes littérales

### Grammaire
- ✅ Déclarations de constantes et variables
- ✅ Expressions arithmétiques et logiques
- ✅ Instructions de contrôle (si/sinon/fsi, pour, tantque)
- ✅ Entrées/sorties (lire, ecrire, imprimer)
- ✅ Affectations

### Vérifications sémantiques
- ✅ Type checking (ent/bool)
- ✅ Détection des déclarations multiples
- ✅ Validation des lvalues
- ✅ Conditions de type bool
- ✅ Opérandes compatibles pour les opérateurs
- ✅ Messages d'erreur avec numéro de ligne

### Génération de code MAP
- ✅ Instructions arithmétiques: `plus`, `moins`, `mult`, `div`, `mod`, `puiss`
- ✅ Instructions de comparaison: `egal`, `dif`, `pps`, `pgs`, `pp-egal`, `pg-egal`
- ✅ Instructions logiques: `et`, `ou`, `non`
- ✅ Contrôle de flux: `bsf`, `bsv`, `bra`
- ✅ Gestion de pile: `empiler-val`, `empiler-adr`, `valeur-pile`, `affect`
- ✅ Entrées/sorties: `lire`, `ecrire`, `imprimer`
- ✅ Étiquettes pour sauts

### Simulateur
- ✅ Exécution de toutes les instructions MAP
- ✅ Gestion de la pile (1000 entiers)
- ✅ Compteur ordinale pour les sauts
- ✅ Support de l'arithmétique et logique
- ✅ Gestion des erreurs (débordement, division par zéro)

## 🧪 Tests

Exécuter tous les tests:
```bash
make test1 test2 test3
```

Ou individuellement:
```bash
make test1    # Somme
make test2    # Conditionnel
make test3    # Factoriel
```

## 🧹 Nettoyage

```bash
make clean
```

Supprime: fichiers générés, exécutables, fichiers `.map`.

## 📊 Architecture

```
┌─────────────────────────────────────────┐
│        Fichier Atlas (.atlas)           │
└────────────────┬────────────────────────┘
                 │
                 ▼
        ┌────────────────┐
        │  Lexeur (Flex) │
        └────────┬───────┘
                 │ Tokens
                 ▼
        ┌────────────────┐
        │ Parser (Bison) │ ◄─ Vérifications sémantiques
        └────────┬───────┘
                 │ Code MAP
                 ▼
        ┌────────────────────┐
        │  Fichier .map      │
        └────────┬───────────┘
                 │
                 ▼
        ┌────────────────────┐
        │  Simulateur (C)    │
        └────────┬───────────┘
                 │
                 ▼
        ┌────────────────────┐
        │   Résultat/Sortie  │
        └────────────────────┘
```

## 🐛 Messages d'erreur

- `Erreur syntaxique ligne N`: Erreur de syntaxe
- `Erreur ligne N: Déclaration multiple de 'ID'`: Variable déjà déclarée
- `Erreur ligne N: Variable 'ID' non déclarée`: Utilisation d'une variable inconnue
- `Erreur ligne N: 'ID' n'est pas une lvalue`: Tentative d'affectation invalide
- `Erreur ligne N: Type incompatible`: Problème de type
- `Erreur ligne N: La condition doit être booléenne`: Condition incorrecte

## 📝 Format du fichier .map

```
<numéro>    <instruction>       [<argument>]
1           ouverture-bloc
2           reserver-var        3
3           empiler-adr         0
4           lire
...
```

Chaque ligne: numéro → instruction → argument optionnel

## 📌 Limitations et contraintes

- Taille maximale de la pile: **1000 entiers**
- Table des symboles: **100 entrées maximum**
- Pas d'imbrication de blocs `debut...fin`
- Types statiques (ent, bool)
- Portée globale pour toutes les variables

## 🎓 Concepts compilateur couverts

1. **Analyse lexicale**: Flex - reconnaissance des tokens
2. **Analyse syntaxique**: Bison - parseur LALR
3. **Analyse sémantique**: Vérifications de types, table des symboles
4. **Génération de code**: Productions de code MAP
5. **Machine virtuelle**: Simulateur d'exécution

## 👨‍💻 Auteur

Développé comme compilateur pédagogique pour le langage Atlas.

---

**Bon développement! 🚀**
