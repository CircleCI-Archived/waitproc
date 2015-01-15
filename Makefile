waitproc: waitproc.c
	gcc --std=c99 -o waitproc waitproc.c

clean:
	rm waitproc
