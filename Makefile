
PROJECT_NAME = kinetic
CFLAGS = -Wall
LDFLAGS = -lraylib -lGL -lm -lpthread -lrt -lX11
FILES = main.cpp display.cpp app.cpp

devbuild : 
	g++ -g $(FILES) $(CFLAGS) $(LDFLAGS) -o devbuild

release :
	g++ -O2 $(FILES) $(CFLAGS) $(LDFLAGS) -o $(PROJECT_NAME) 

clean :
	@if [ -f ./devbuild ]; then	\
		rm -f ./devbuild; \
	fi
	@if [ -f ./$(PROJECT_NAME) ]; then \
		rm -f ./$(PROJECT_NAME); \
	fi
