enigma: main.o machine.o component.o plugboard.o rotor.o position.o reflector.o
	g++ -g main.o machine.o component.o plugboard.o rotor.o position.o reflector.o -o enigma

main.o: main.cpp machine.h constants.h errors.h
	g++ -Wall -g -c main.cpp

machine.o: machine.cpp machine.h component.h plugboard.h rotor.h position.h constants.h errors.h 
	g++ -Wall -g -c machine.cpp

component.o: component.cpp component.h constants.h errors.h
	g++ -Wall -g -c component.cpp

rotor.o: rotor.cpp rotor.h component.h constants.h errors.h
	g++ -Wall -g -c rotor.cpp

reflector.o: reflector.cpp reflector.h component.h constants.h errors.h
	g++ -Wall -g -c reflector.cpp

plugboard.o: plugboard.cpp plugboard.h component.h constants.h errors.h
	g++ -Wall -g -c plugboard.cpp

position.o: position.cpp position.h component.h constants.h errors.h
	g++ -Wall -g -c position.cpp

clean:
	rm *.o
