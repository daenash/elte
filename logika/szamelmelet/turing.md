#Turing gépek

## Kiszámító turing gépek

M=(Q,sum,A,delta,q0,qi,(qn))

Q -> Állatpotok
sum -> inputABC
A
delta
q0 -> kezdőállapot
qi -> elfogadóállatpo
qn -> nem jó állapot
A -> 

delta : Q X A   ->  Q X A X Direction
f     : sum*    ->  A*


PÉLDA:

sum = {a,b}

f   :   a  => a.length(u) mod 2 = 1
f   :   aa => a.length(u) mod 2 = 0

1. szalag => "abaab"
2. szalag => ""

q0  a,Ü / a,Ü ; R,S  => q1
q0  b,Ü / b,Ü ; R,S  => q0

q1  b,Ü / b,Ü ; R,S  => q1
q1  a,Ü / a,Ü ; R,S  => q0

// Kilépés ha páratlan és nem olvasunk a szalagról
q1  Ü,Ü / Ü,a ; S,S  => qi  // kilépés helyesen

// Kilépés ha páros. Először elküldjük q1-be és írunk egy 'a'-t az output szalagra
q0  Ü,Ü / Ü,a ; S,R  => q1


## Turing gép kódolása

M=(Q,sum,gamma,delta,q0,qi,qn)

Q = {p1....pk-1,pk} =>  p0 = q0
                    =>  pk-1 = qi
                    =>  pk = qn

sum = {0,1}
gamma = {x1,x2,x3...xm} =>  x1 = 0
                        =>  x2 = 1
                        =>  x3 = Ü

Directions = {L,R,S} == {1,2,3}

delta : (pi,xj) = (pr,xs,Dt)

// Egy állapot átmenet kódja
(0^i)1(0^j)1(0^r)1(0^s)1(0^t)

// Állapot átmenetek egymás mögött elválasztva
< kód 11 kód 11 ...... > 111 w (w => szó amit el kell dönteni)
       <Machine>

### Visszafejtés

gamma = {a,b,Ü}

Visszafejtendő kód:
01010100100
0100100100100
010001000010001000
001010010100
00100100100100
001000100010001000

visszafejtett delta:

01010100100
q0,a -> q0,b,Right

0100100100100
q0,b -> q1,b,Right

010001000010001000
q0,Ü -> qn,Ü,S

001010010100
q1,a -> q1,a,R

00100100100100
q1,b -> q1,b,R

001000100010001000
q1,Ü -> qi,Ü,S

aaab
bbbb

Generált nyelv => a*b+

## Bónusz feladat

input -> {a,b}*
f : a^n  ->  ĻM=(Q,sum,A,delta,q0,qi,(qn))ab^n


