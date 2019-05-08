CC=g++
CFLAGS=-c -Wall -pedantic -std=c++11 -Wno-long-long -O0 -ggdb

OUT=./vokalvoj
OBJS := main.o Card.o Game.o Hero.o HeroType.o Mage.o Warrior.o OutFunctions.o IOhandler.o

all: vokalvoj

run:
	$(OUT)

doc:
	doxygen ./src/doxyConf

vokalvoj: $(OBJS)

compile: $(OBJS)
	@$(CC) -o $(OUT) $(OBJS)
	@echo "executable created: $(OUT)"

main.o: ./src/main.cpp
	@$(CC) $(CFLAGS) -o $@ $<
	@echo "$@ generated"

HeroType.o: ./src/HeroType.h
	@$(CC) $(CFLAGS) -x c++ -o $@ $<
	@echo "$@ generated"

%.o: ./src/%.cpp
	@$(CC) $(CFLAGS) -o $@ $<
	@echo "$@ generated"

clean:
	rm -rf $(OBJS) $(OUT) ./doc
