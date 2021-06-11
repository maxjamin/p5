proc1: p5.c
		gcc -o p5 p5.c -pthread

clean:
		rm *.o p5 a.out
