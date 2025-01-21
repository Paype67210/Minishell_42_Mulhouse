<picture>
<img alt="Entête du dépôt Minishell_42_Mulhouse." src="https://github.com/Paype67210/Minishell_42_Mulhouse/blob/main/Tools/cover-minishell.png">
</picture>

## 🚀 Objectifs du projet  
- Comprendre et implémenter les bases d'un interpréteur de commandes.  
- Manipuler les appels système comme `fork`, `execve`, `pipe`, et `wait`.  
- Gérer les entrées/sorties, les processus, et les signaux.  
- Créer une application robuste capable d'exécuter des commandes comme un véritable shell.  

---

## 📖 Fonctionnalités à implémenter  
1. **Exécution de commandes simples** :  
   - Gérer les chemins relatifs et absolus.  
   - Implémenter un environnement minimal pour les commandes.  
2. **Redirections d'entrée/sortie** :  
   - Supporter les opérateurs `>`, `<`, `>>` (append), et `<<` (heredoc).  
3. **Pipes** :  
   - Chainer plusieurs commandes avec le caractère `|`.  
4. **Variables d'environnement** :  
   - Accéder et modifier les variables avec `export`, `unset`, et `$`.  
5. **Built-ins** :  
   Implémenter des commandes internes comme :  
   - `cd` : changer de répertoire.  
   - `echo` : afficher du texte avec ou sans options.  
   - `env` : afficher l'environnement courant.  
   - `exit` : fermer le shell proprement.  
   - `pwd` : afficher le chemin courant.  
6. **Gestion des erreurs** :  
   - Afficher des messages appropriés en cas d'erreurs (fichiers inexistants, permissions, etc.).  
7. **Signaux** :  
   - Gérer `Ctrl+C`, `Ctrl+D`, et `Ctrl+\` pour interrompre ou quitter des processus.  

---

## 💡 Compétences développées  
- Manipulation des **appels système Unix** pour gérer les processus, signaux, et entrées/sorties.  
- Gestion des **pipes** et des redirections dans un environnement concurrent.  
- Maîtrise des **listes chaînées** et des **parsers** pour interpréter les commandes utilisateur.  
- Renforcement des bases de la programmation système et de la gestion mémoire.
- Apprentissage du travail en groupe (projet réalisé en équipe de 2)

---

## ⚙️ Requis techniques  
- Respect des normes POSIX pour assurer la compatibilité avec un shell standard.  
- Code robuste, lisible, et modulaire.  
- Prévention des fuites mémoire grâce à des outils comme `valgrind`.  
- Gérer des cas complexes comme :  
  - Des redirections multiples.  
  - Des chaînes de pipes imbriquées.  
  - Des commandes incomplètes ou invalides.

---

## 🧪 Tests et cas limites  
- Exécution correcte de commandes simples et complexes (avec pipes et redirections).  
- Gestion des signaux dans différents scénarios.  
- Manipulation de variables d’environnement avec des caractères spéciaux ou non valides.  
- Validation des cas limites comme une commande vide, un fichier inaccessible, ou des redirections incorrectes.  

---

## 🛠️ Concepts clés abordés  
- **Gestion des processus** : Création, communication, et synchronisation entre processus avec `fork` et `pipe`.  
- **Manipulation des fichiers** : Gestion des descripteurs de fichiers pour rediriger les entrées et sorties.  
- **Parsers et lexers** : Analyse syntaxique des commandes utilisateur.  
- **Signaux** : Gestion des interruptions pour offrir une expérience utilisateur fluide.  

---

## 🌟 Pourquoi ce projet est important ?  
Minishell est une étape cruciale pour comprendre le fonctionnement interne des systèmes Unix et leur interaction avec les utilisateurs. Ce projet offre une opportunité unique de :  
- Renforcer vos compétences en **programmation système**.  
- Travailler sur un projet concret, proche d'un outil utilisé quotidiennement.  
- Appliquer des concepts avancés comme les redirections, pipes, et gestion des processus.

