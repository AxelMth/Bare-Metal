# Rendu des exercices

Exercice 1 :

Pour des tailles différentes de y on obtient :

- 4 pour y défini comme un entier de 32 bits 
- 2 pour y défini comme un entier de 16 bits
- 1 pour y défini comme un entier de 8 bits

On peut donc penser que SYMBOLE représente ici la taille de y et non son adresse. Cette hypothèse est confortée lorsque l'on initialise un autre variable y2 exactement de la même manière. On voit dans la colonne symbole que y2 possède également une valeur de 4 dans la colonne SYMBOLE. Or, ceci ne peut pas correspondre à une adresse.

En regardant de plus près la documentation de objdump, on peut y lire :

The other common output format, usually seen with ELF based files, looks like this:

	00000000 l    d  .bss   00000000 .bss
        00000000 g       .text  00000000 fred

Here the first number is the symbol's value (sometimes refered to as its address).

Donc "souvent" cela correspond à son adresse sauf dans notre cas.

Exercice 2 :

A l'aide de readelf, on constate que l'ordre des sections par adresse croissante est :

.text, .rodata, .data, .bss

Pour savoir dans quel sens va la pile, on a décidé avec Robin Shin d'écrire un petit code C qui va créer des variables locales et qui retourne leur adresses. On constate que la variable crée en dernier à une adresse inférieure à l'adresse de la variable crée en premier. La pile croit vers le haut (si on considère que les adresses sont rangées dans l'ordre croissant du haut vers le bas).

On constate de plus que les adresses de la pile et du tas sont supérieures à l'adresse du .bss donc on a l'ordre suivant :

.test, .rodata, .data, .bss, .heap, .stack
