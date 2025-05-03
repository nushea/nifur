all:
	rm nifur || true
	gcc -o nifur main.c printers.c

test: all
	SERVER_NAME="she-a.eu" REQUEST_URI="/path/subpath" REMOTE_ADDR="127.0.0.1" ./nifur
test-basic: all
	SERVER_NAME="she-a.eu" REQUEST_URI="/" REMOTE_ADDR="127.0.0.1" ./nifur
test-simple: all
	SERVER_NAME="she-a.eu" REQUEST_URI="/simpl" REMOTE_ADDR="127.0.0.1" ./nifur
test-about: all
	REMOTE_ADDR="local" SERVER_NAME="domain.exemple" REQUEST_URI="/nifur/about" ./nifur
test-about-simple: all
	REMOTE_ADDR="local" SERVER_NAME="domain.exemple" REQUEST_URI="/nifur/about/simple" ./nifur
test-debug: all
	SERVER_NAME="subdomain.example.com" REQUEST_URI="/debug" REMOTE_ADDR="127.0.0.1" ./nifur
