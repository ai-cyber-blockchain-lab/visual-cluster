build:
	gcc -o main main.c particles.c network.c json.c cJSON.c -lraylib -L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lm -lpthread -lmicrohttpd
run: build
	./main
