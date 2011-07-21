#include <stdlib.h>
#include <stdio.h>
#include "sax.h"

SAX_parser * SAX_init(FILE * source){
    SAX_parser *p = malloc(sizeof(SAX_parser));
    p->source = source;
    return p;
}
