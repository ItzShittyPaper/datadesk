all:
	gcc main.c -o drawer -lncurses -O2
install:
	cp drawer /bin/drawer
	mkdir /etc/datadesk/
	cp demo.ds /etc/datadesk/demo.ds
	cp drawer.1 /usr/share/man/man1/drawer.1
	chmod -R 777 /etc/datadesk/
clean:
	rm -rf /bin/drawer
	rm -rf /usr/share/datadesk
	rm -rf /etc/datadesk
	rm -rf /usr/share/man/man1/drawer.1
