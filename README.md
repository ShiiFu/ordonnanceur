# ordonnanceur

GOODWIN Jean-Paul  
LEROY Damien

Toutes les fonctionnalités jusqu'au scheduler_run ont été implémentées. Cela permet d'ajouter, créer et gérer différents processus.

Pour la gestion des signaux, si le processus père (l'ordonnanceur) est tué, alors tous ces fils le seront aussi. Il n'y a donc aucune question à se poser pour l'avenir des processus fils sans l'ordonnanceur.
Pour illustrer ceci, voici la généalogie des processus pendant l'exécution de l'ordonnanceur (ici main) :  
>    main  
>    ├─firefox  
>    ├─gedit  
>    └─xterm  

Lorsque l'ordonnanceur est arrêté, ses éventuels fils restants sont aussi arrêtés. Ils n'ont pas de nouveau père pour continuer à s'exécuter.  

Les règles d'ordonnancements devraient alors être écrites pour gérer ces processus.
