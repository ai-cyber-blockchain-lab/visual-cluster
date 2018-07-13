#include <stdio.h>
#include <unistd.h>

#include "VG/openvg.h"
#include "shapes.h"

int main(void) {
    int width, height;
    char s[3];

    init(&width, &height);
    printf("init with dimensions %d x %d", width, height);

    Start(width, height);
    Background(0, 0, 0);
    Fill(255, 255, 255, 1);
    Circle(width/2, height/2, width < height ? width : height);
    End();

    printf("press any key to exit");
    fgets(s, 2, stdin);
    finish();
    return 0;
}