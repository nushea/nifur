all:
	rm nifur || true
	gcc -o nifur main.c

run: all
	REQUEST_URI="subdomain.example.com/path/to/thing" ./nifur
