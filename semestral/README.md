# PJC - Semestrální práce 

### Zadání

Nejkratší cesty mezi všemi vrcholy (shortest paths)

Další z velmi dobře prozkoumaných grafových algoritmů, které mají využití jak ve fyzickém světě, tak ve světě počítačů. Na výstupu je seznam dvojic vrcholů s délkou minimální cesty mezi nimi (pokud existuje) a vypsanou cestou.


- jednovláknová aplikace
- vícevláknová aplikace

### Implementace

Aplikace načte předaná data do vlastní grafové struktury, která je optimalizovaná 
pro jednorázové načtení a poté častý přístup k datům.

K prohledávání nezáporně ohodnocených hran grafu je použit [dijkstrův algoritmus](https://cs.wikipedia.org/wiki/Dijkstrův_algoritmus).

Ve vícevláknové verzi je prohledávání z jednotlivých počátečních vrcholů delegováno vždy dalšímu volnému vláknu.

Na výstupu je poté seznam nejkratších vzdáleností z daného počátečního vrcholu do všech ostatních vrcholů grafu.


### Použití

Aplikace se spouští konzolovým voláním:

```
semestral [cesta-k-datum] [přepínač]</code>
```

- [cesta-k-datum] - aplikace přijímá strukturovaná data grafu

- [přepínač] - je možné zvolit přepínač "-t" pro výpočet ve více vláknech

##### struktura dat

```
[number-of-nodes] [number-of-edges]
[from] [to] [cost]
```

##### Help

```
usage: semestral source_file [options]
   
   general options:
       -h   --help            print help
       -V   --version         print version
   
   additional options:
       -t                     multithread computation
```

### Měření

Na větších datech byla vícevláknová verze mírně lepší než jednovláknová.   