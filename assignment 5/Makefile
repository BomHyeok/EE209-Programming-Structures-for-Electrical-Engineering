ish: dynarray.o lexicalanalysis.o
	$gcc209 dynarray.o lexicalanalysis.o -o ish

dynarray.o: dynarray.c dynarray.h
	$gcc209 -c dynarray.c

lexicalanalysis.o: dynarray.h lexicalanalysis.c
	$gcc209 -c lexicalanalysis.c
