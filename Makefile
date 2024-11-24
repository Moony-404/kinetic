
CFLAGS = -Wall
LDFLAGS = -lraylib -lGL -lm -lpthread -lrt -lX11
PROJECT_NAME = kinetic

devbuild : 
	g++ -g main.cpp $(CFLAGS) $(LDFLAGS) -o devbuild

release :
	g++ -O2 main.cpp $(CFLAGS) $(LDFLAGS) -o $(PROJECT_NAME) 

clean :
	@if [ -f ./devbuild ]; then 		rm -f ./devbuild; 	fi
	@if [ -f ./$(PROJECT_NAME) ]; then 		rm -f ./$(PROJECT_NAME); 	fi
