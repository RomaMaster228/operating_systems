all: child1 child2 parent

child1:
        gcc child1.c -o child1

child2:
        gcc child2.c -o child2

var13:
        gcc parent.c -o parent

clean:
        rm -rf child1 child2 parent