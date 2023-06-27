F = -std=c++17 -g

all: string alloc gltf tlsf 
	mv *.o obj/ && g++ $(F) obj/string.o obj/alloc.o obj/gltf.o obj/tlsf.o main.cpp -o bin && ./bin

gltf: glTF.cpp string alloc
	g++ -c glTF.cpp -o gltf.o

string: String.cpp alloc
	g++ -c String.cpp -o string.o

alloc: Allocator.cpp tlsf
	g++ -c Allocator.cpp -o alloc.o

tlsf: tlsf.cpp
	g++ -c tlsf.cpp -o tlsf.o
