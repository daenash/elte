# Bitvektor tömörítés

## Átalakító script

Python script:<br>
[bitvector.py](bitvector.py)

## A kódolás lépései:

1. Addig olvasunk, amíg `1` bitet nem találunk.
2. Az előtte álló `0` bitek számát összeadjuk és binárissá alakítjuk
3. Megnézzük hány biten fér el az így kapott bináris szám, legyen `i`
4. Beszúrunk `i-1` db `1` bitet és 1 db `0` bitet a kódolt stringbe, illetve mögé az átalakított bináris számot

## Például:

Kódolandó **bitvektor**<br>
`10000000000000000000000010000000101`

Olvassuk sorban a biteket, amíg `1` bitet nem találunk.

_Input_: `1`<br>
Nincs előtte nulla, ezért beszúrunk egy 0 méretű bináris számot.<br>
_Beszúrandó string:_ `00`<br>
**Beszúrás utáni kódolt string:** `00`<br>

> (standard, ha az `1` bit előtt nincs `0`)

_Input_: `000000000000000000000001`<br>
23 db nullát olvastunk, ez binárisan `10111`. Ezt 5 biten tudjuk ábrázolni, szóval beszúrunk 4 db `1` bitet és 1 db `0` bitet, majd a bináris számot.<br>
_Beszúrandó string:_ `1111010111`<br>
**Beszúrás utáni kódolt string:** `001111010111`

_Input_: `00000001`<br>
7 db nullát olvastunk, ez binárisan `111`. Ezt 3 biten tudjuk ábrázolni, szóval beszúrunk 2 db `1` bitet és 1 db `0` bitet, majd a bináris számot.<br>
_Beszúrandó string:_ `110111`<br>
**Beszúrás utáni kódolt string:** `001111010111110111`

_Input_: `01`<br>
1 db nullát olvastunk, ez binárisan `1`. Ezt 1 biten tudjuk ábrázolni, szóval beszúrunk 0 db `1` bitet és 1 db `0` bitet, majd a bináris számot.<br>
_Beszúrandó string:_ `01`<br>
**Beszúrás utáni kódolt string:** `00111101011111011101`
