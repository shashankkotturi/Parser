LD	2000, R1

Code: 1000
LD	2001, R2
ADD	R1, R2, R3
SD	R3, 2002
bob:
bill:
JMP [bob]
JMP [bill]