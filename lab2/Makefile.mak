all: child1 child2 var13

child1:
        gcc child1.c -o child1

child2:
        gcc child2.c -o child2

var13:
        gcc var13.c -o var13

clean:
        rm -rf child1 child2 var13