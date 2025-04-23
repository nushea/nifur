all:
	rm nifur || true
	gcc -o nifur main.c

test: all
	SERVER_NAME="subdomain.example.com" REQUEST_URI="/path/to/thing" REMOTE_ADDR="127.0.0.1" ./nifur
test-simple: all
	SERVER_NAME="subdomain.example.com" REQUEST_URI="/simpl" REMOTE_ADDR="127.0.0.1" ./nifur
test-debug: all
	SERVER_NAME="subdomain.example.com" REQUEST_URI="/debug" REMOTE_ADDR="127.0.0.1" ./nifur
