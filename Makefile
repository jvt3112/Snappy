# Complete This!
snap: *.c
	gcc -o snap *.c -I -"./snap.c"
	sudo cp ./snap /bin/snappy