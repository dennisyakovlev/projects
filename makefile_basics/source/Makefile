CC:=g++

INCLUDE=-I.
OPT:=-O0
CFLAGS:=-g $(INCLUDE) $(OPT)

OBJECTS=header.o

.PHONY: source clean

all: source libalgo.a

libalgo.a: $(OBJECTS)
	ar rcs $(BUILDIR)/source/$@ $(addprefix $(BUILDIR)/source/, $^)

source:
	mkdir -p $(BUILDIR)/source

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $(BUILDIR)/source/$@ $^

clean:
	rm -fr libalgo.a $(OBJECTS)