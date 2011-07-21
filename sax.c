#include <stdlib.h>
#include <stdio.h>
#include "sax.h"

SAX_parser * SAX_init(FILE * source){
    SAX_parser *p = malloc(sizeof(SAX_parser));
    p->source = source;
    p->h_list.size = 0;
    p->h_list.cap = 10;
    p->h_list.handlers = calloc(10, sizeof(handler));
    return p;
}


void start_parse(SAX_parser *p);

int reg_characters_handler(SAX_parser *p, void event_handler(char *)){
    return 0;
}
    

int reg_start_document_handler(SAX_parser *p, void event_handler()){
    return 0;
}
int reg_end_document_handler(SAX_parser *p, void event_handler()){
    return 0;
}

int reg_start_element_handler(SAX_parser *p, void evt(char *, attr_array *)){
    return 0;
}
int reg_end_element_handler(SAX_parser *p, void event_handler(char *)){
    return 0;
}

int reg_error_handler(SAX_parser *p, void event_handler(int)){
    return 0;
}

