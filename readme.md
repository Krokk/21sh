## 21sh
mini UNIX command interpreter.

# Installation
```
$ git clone https://github.com/rfabrecode/21sh.git
```

# Utilisation
```
$ cd 21sh
$ make && ./21sh

```

## Builtins

| Nom           | Description            | Supporté ?  | Bonus ?  |
| ------------- |:----------------      | -----:| -----:|
|Cd       | Changer le répertoir de travail | ✓ | ✗ |
|Clear    | Effacer tout ce qui est sur le terminal          |   ✓ | ✓ |
|Echo     | Afficher les arguments dans le terminal  | ✓ | ✗ |
|Env      | Afficher les variables d'environements  | ✓ | ✗ |
|Setenv   | Modifier ou créer des variables d'environements  | ✓ | ✗ |
|Unset    | Supprimer une ou plusieurs variables d'environements  | ✓ | ✗ |
|Exit     | Quitter le terminal et libérer la memoire | ✓ | ✗ |
|Pwd      | Affiche le répertoire courrant | ✓ | ✓ |

## Edition de la ligne de commande

| Nom           | Description            | Supporté ?  | Bonus ?  |
| ------------- |:----------------      | -----:| -----:|
| <kbd>CTRL</kbd>+<kbd>C</kbd> | Supprime toute la ligne | ✓ | ✓ |
| <kbd>home</kbd>| Positionne le curseur au debut de la ligne | ✓ | ✓ |
| <kbd>end</kbd>| Positionne le curseur à la fin de la ligne | ✓ | ✓ |
| <kbd>backspace</kbd>| Supprime le caractère vers la gauche| ✓ | ✓ |
| <kbd>SHIFT</kbd> + <kbd>▶</kbd>| Position le curseur au prochain debut de mot | ✓ | ✓ |
| <kbd>SHIFT</kbd> + <kbd>◀</kbd>| Position le curseur au prochain debut de mot | ✓ | ✓ |
| <kbd>◀</kbd>| Position le curseur à gauche | ✓ | ✓ |
| <kbd>▶</kbd>| Position le curseur à droite | ✓ | ✓ |
| <kbd>▲</kbd>| Affiche le prochain historique le plus vieux | ✓ | ✓ |
| <kbd>▼</kbd>| Affiche le prochain historique le plus récent | ✓ | ✓ |

## Éxectution des commandes

| Nom           | Description            | Supporté?  | Bonus  |
| ------------- |:----------------      | -----:| -----:|
| Commande du path | Éxecute une commande depuis le path | ✓ | ✗ |
| Séparateur `;` | Éxecute une commande puis une autre | ✓ | ✓ |
| Opérateur `>` | Redirige la sortie standard vers un autre file descriptor| ✓ | ✓ |
| Opérateur `>>` | Redirige la sortie standard vers un autre file descriptor (ajout à la fin)| ✓ | ✓ |
| Opérateur `<<` | Heredoc |  ✓ | ✓ |
| Opérateur `<` | Redirige l'entrée standard vers la commande| ✓ | ✓ |
| Pipe <code>&#124;</code>| (ex ls <code>&#124;</code> base64)| ✓ | ✓ |
| Echappement des guillements dans les commandes | Exemple: "ls" | ✓ | ✓ |
| Agregateur de file descriptor | Exemple: ls nosuchfile 2>&- | ✓ | ✓ |
| Gestion avancée des erreurs | Exemple: ls ; ; | ✓ | ✓ |
| Gestion du tilde | Exemple: cd ~ | ✓ | ✓ |
| Gestion du des variables d'environement | Exemple: echo $PATH | ✓ | ✓ |

## Autres bonus

| Nom           | Description            | Supporté?  | Bonus  |
| ------------- |:----------------      | -----:| -----:|
| Multi line support | > | ✓ | ✓ |
| Dquote | double quote> | ✓ | ✓ |
| Squote | simple quote> | ✓ | ✓ |
