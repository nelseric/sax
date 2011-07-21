#include <stdlib.h>
#include <stdio.h>
#include "sax.h"

int main(int argc, char **argv) {
    SAX_parser *p;
    p = SAX_init(stdin);

    puts("Yakety Sax");
    return EXIT_SUCCESS;
}
