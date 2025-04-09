heapMerge: main.cpp node.cpp node.h
	g++ -std=c++11 main.cpp node.cpp -o heapMerge
clean: 
	rm heapMerge
run: heapMerge
	./heapMerge
