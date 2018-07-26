build:
	gcc main.c -o main -lraylib -L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lm -lpthread -lmicrohttpd
run: build
	./main
