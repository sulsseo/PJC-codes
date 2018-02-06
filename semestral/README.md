# PJC - Semestrální práce 

### 1. zadání

Nejkratší cesty mezi všemi vrcholy (shortest paths)

Další z velmi dobře prozkoumaných grafových algoritmů, které mají využití jak ve fyzickém světě, tak ve světě počítačů. Na výstupu je seznam dvojic vrcholů s délkou minimální cesty mezi nimi (pokud existuje) a vypsanou cestou.


- jednovláknová aplikace
- vícevláknová aplikace

### 2. implementace



### 3. použití

Aplikace se spouští konzolovým voláním:

<code>semestral [cesta-k-datum] [přepínač]</code>

<b>[cesta-k-datum]</b> - aplikace přijímá strukturovaná data grafu:

<code>
&lt;number-of-nodes> &lt;number-of-edges> <br>
&lt;from> &lt;to> &lt;cost>
</code>

<b>[přepínač]</b> - je možné zvolit přepínač "-t" pro výpočet ve více vláknech