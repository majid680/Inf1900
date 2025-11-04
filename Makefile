########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   Simon Barrette & Jerome Collin pour  #####
#####           INF1900 - 2016               #####
#####                                        #####
#####         Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################
#               Equipe 42 et 32                  #
#												 #
#        Massinissa Benabdeslam (2229884)        #
#     Raphael Streicher-Letourneau (2349325)     #
#           Anita Bou Malham (2365165)           #
#                Majid Khauly   (2434522)        #
#                                                #
#                                                #
#         Makefile de l'executable tp7           #
#                                                #
#                                                #
##################################################

# Ce Makefile vous permet de compiler des projets
# pour les microcontroleurs Atmel AVR sur
# Linux ou Unix, en utilisant l'outil AVR-GCC.
# Ce Makefile supporte C & C++


#####      Details specifique a la cible       #####
#####  Vous devez les adapter a votre projet   #####

# Nom du microcontroleur cible
# (exemple: 'at90s8515')
MCU=atmega324pa

# Nom de votre projet
# (utilisez un seul mot, exemple: 'monprojet')
PROJECTNAME=exec

# Fichiers sources
# Utilisez le suffixe .cpp pour les fichiers C++
# Listez tous les fichiers a compiler, separes par
# un espace. exemple: 'tp1.c tp2.cpp':
PRJSRC=$(wildcard *.cpp)

# Inclusions additionnels (ex: -I/path/to/mydir)
INC=-I../lib

# Libraires a lier (ex: -lmylib)
LIBS=-L../lib  -l:staticLibrary.a

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Ne pas changer
# Liste complete des IDs disponible avec avrdude
AVRDUDE_PROGRAMMERID=usbasp



####################################################
#####         Configuration terminee           #####
#####                                          #####
#####  Le reste de cette section contient les  #####
##### details d'implementation vous permettant #####
##### de mieux comprendre le fonctionnement de #####
#####   ce Makefile en vue de sa modification  #####
####################################################



####### variables #######

#compilateur utilise
CC=avr-gcc
#pour copier le contenu d'un fichier objet vers un autre
OBJCOPY=avr-objcopy
#pour permettre le transfert vers le microcontroleur
AVRDUDE=avrdude
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f
# HEXFORMAT -- format pour les fichiers produient .hex
HEXFORMAT=ihex



####### Options de compilation #######

# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
-std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall

# Flag supplémentaire pour retirer le bogue de "array subscript 0 is outside
# array bounds" sur avr-gcc v12
GCCVERSION := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 12)
ifeq "$(GCCVERSION)" "1"
	CFLAGS += --param=min-pagesize=0
endif

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions

# Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

ifdef DEBUG
    CFLAGS += -DDEBUG
endif

ifdef WRITE_PROGRAM
	CFLAGS += -DWRITE_PROGRAM
endif

####### Cible (Target) #######

#Nom des cibles par defaut
TRG=$(PROJECTNAME).elf
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex



####### Definition de tout les fichiers objets #######

# Cette fonction permet de differencier les fichiers .c
# des fichiers .cpp
# Fichier C
CFILES=$(filter %.c, $(PRJSRC))
# Fichier C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

# Liste de tout les fichiers objet que nous devons creer
OBJDEPS=$(CFILES:.c=.o) \
$(CPPFILES:.cpp=.o)

# Pour plus d'information sur cette section, consulter :
# http://bit.ly/257R53E	
# Les fonctions $(filter pattern…,text) &
# $(patsubst pattern,replacement,text) sont pertinentes



####### Creation des commandes du Makefile #######

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make install et make clean
.PHONY: all install clean

# Make all permet simplement de compiler le projet
#
all: $(TRG) $(HEXROMTRG)

# Implementation de la cible
$(TRG): $(OBJDEPS) ../lib/staticLibrary.a
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)

# Production des fichiers object
# De C a objet
%.o: %.c
	$(CC) $(CFLAGS) -c $<
# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# Verification des dependances (header dependencies)
-include *.d

# Pour plus d'information sur cette section, consulter:
# http://bit.ly/2580FU8

# Production des fichiers hex a partir des fichiers elf
%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

# Make install permet de compiler le projet puis
# d'ecrire le programme en memoire flash dans votre
# microcontroleur. Celui-ci doit etre branche par cable USB
install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
	-p $(MCU) -P usb -e -U flash:w:$(HEXROMTRG)


# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d


debug:
	$(MAKE) clean all DEBUG=1
	$(MAKE) install DEBUG=1
	    serieViaUSB -l 

write:
	$(MAKE) clean all WRITE_PROGRAM=1
	$(MAKE) install WRITE_PROGRAM=1
	    serieViaUSB/serieViaUSB -e -f instructionFile.bin
# Pour plus d'information sur les phony target, consulter:
# http://bit.ly/1WBQe61

# De plus, pour mieux comprendre les makefiles et
# leur fonctionnement, consulter la documentation de GNU Make:
# http://bit.ly/23Vpk8s

# Finalement, ce tutoriel en ligne constitut une bonne
# introduction au Makefile:
# http://bit.ly/1XvxsN3

#####                    EOF                   #####
