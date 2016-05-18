father(me,sarah).

male('Nat King Cole').
parent( 'Nat King Cole', 'Nathalie Cole').
% rules :
father(X,Y) :- male(X), parent(X,Y).


