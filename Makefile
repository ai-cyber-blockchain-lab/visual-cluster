build:
	gcc -o main main.c network.c -lraylib -L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lm -lpthread -lmicrohttpd
run: build
	./main
