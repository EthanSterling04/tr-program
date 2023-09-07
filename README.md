# tr-program

A clone of the standard Unix program tr, which is a filter program that performs transliteration.

## Background

* tr is a filter program that performs transliteration. Given two equal-length sequences of characters, from and to, it replaces all occurrences of characters appearing in from with the character in the corresponding position in to.
* The tr program takes the from and to character sequences as command-line arguments. Once the program is run, it takes in a string from user input, replaces the appropriate characters according to the from and to sequences, and prints out the result. In the simplest case, the from and to sequences are strings of the same length.
```
% ./tr abc xyz
a
x
bbbcd
yyyzd
tag the cat
txg the zxt
abracadabra
xyrxzxdxyrx
^D
% echo Hello, world. | ./tr e a
Hallo, world.
% echo Hello, world. | ./tr elo 310
H3110, w0r1d.
% echo Hello, world. | ./tr ',. ' ___
Hello__world_
```
* tr also understands ranges of characters and some backslash escape sequences:
```
% echo Hello, world. | ./tr a-z A-Z
HELLO, WORLD.
% echo Hello, world. | ./tr a-zA-Z. 'A-Za-z?'
hELLO, WORLD?
% echo Hello, world. | ./tr a-zA-Z n-za-mN-ZA-M
Uryyb, jbeyq.
% echo Hello, world. | ./tr a-zA-Z n-za-mN-ZA-M | ./tr a-zA-Z n-za-mN-ZA-M
Hello, world.
% echo Hello, world. | ./tr ' ' '\n'
Hello,
world.
%
```
