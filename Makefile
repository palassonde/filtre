#NOM et Prénom : LASSONDE Pierre-Alexandre
#Code permanent : LASP16128901
#
#NOM et Prénom : BAUMONT Florian
#Code permanent : BAUF12059008
#------------------------------------------
#DÈclaration de variables
CC = gcc
CFLAGS = -std=c99
LDFLAGS = -lm
#------------------------------------------
PROG = filtre
SRCS = filtre.c fonctions_spe.c fonctions_nonSpe.c affichage.c
#------------------------------------------

#------------------------------------------
OBJS = $(SRCS:.c=.o)
#------------------------------------------

$(PROG) : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(PROG)

#-------------------------------------------
filtre.o : filtre.c fonctions_spe.c fonctions_nonSpe.c affichage.c fonctions.h affichage.h
fonctions_spe.o : affichage.h fonctions.h
fonctions_nonSpe.o : affichage.h fonctions.h
affichage.o : affichage.h
#-------------------------------------------
clean:
	/bin/rm -f core *~ $(OBJS)
#-------------------------------------------