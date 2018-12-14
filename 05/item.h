#ifndef ITEM_H
#define ITEM_H

typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B)                                                             \
	{                                                                          \
		Item t = A;                                                            \
		A = B;                                                                 \
		B = t;                                                                 \
	}
#define eq(A, B) (A == B)
#define NULLitem -999

#endif
