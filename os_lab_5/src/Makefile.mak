all: prog1 prog2

prog1: lib1.so
        gcc main1.c -L /home/roma/os_lab_5 -l1 -Wall -o prog1 -lm

prog2: lib1.so lib2.so
        gcc main2.c -ldl -o prog2 -lm

lib1.so: lib1.o
        gcc lib1.o -lm -shared -o lib1.so -lm

lib2.so: lib2.o
        gcc lib2.o -shared -o lib2.so -lm

lib1.o:
        gcc lib1.c -c -Wall -Werror -fpic -o lib1.o -lm

lib2.o:
        gcc lib2.c -c -Wall -Werror -fpic -o lib2.o -lm

clean:
        rm -rf *.so *.o prog1 prog2 -lm
