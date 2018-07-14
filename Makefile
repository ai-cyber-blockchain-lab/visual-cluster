LIBFLAGS=-L/opt/vc/lib -lbrcmEGL -lbrcmGLESv2 -lbcm_host
INCLUDEFLAGS=-I/opt/vc/include -I/opt/vc/include/interface/vmcs_host/linux -I/opt/vc/include/interface/vcos/pthreads -fPIC

build:
	gcc $(INCLUDEFLAGS) $(LIBFLAGS) main.c shapes.c oglinit.c -o main
run: build
	./main

particles:
	gcc $(INCLUDEFLAGS) $(LIBFLAGS) particles.c shapes.c oglinit.c -o particles
	./particles
