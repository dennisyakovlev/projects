export PROJDIR=$(realpath $(CURDIR))
export BUILDIR=$(PROJDIR)/build

CC=g++

INCLUDE=-Isource
OPT=-O0
CFLAGS=-g $(INCLUDE) $(OPT)

OBJECTS=main.o

.PHONY: build source cleam

# create build directory first
all: build out

# look for targest and dependancies without their build tree
# prefix path, since the actual files are not there, they're
# in source tree. However, when looking for outputted make
# files, look in build tree
out: source $(OBJECTS)
	$(CC) -o $(BUILDIR)/$@ $(addprefix $(BUILDIR)/, $(OBJECTS)) -L$(BUILDIR)/source -lalgo

# create build directory
build:
	mkdir -p $@

# add sub directory
source:
	$(MAKE) -C source

%.o: %.cpp
	@echo here
	$(CC) $(CFLAGS) -c -o $(BUILDIR)/$@ $^ -Lsource -lalgo

clean:
	rm -fr $(BUILDIR)