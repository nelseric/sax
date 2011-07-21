#ifndef __SAX_H__
#define __SAX_H__
#include <stdio.h>

typedef struct {
    char * name;
    char * value;
} attribute;

typedef struct {
    int size;
    int cap;
    attribute *attrs;
} attr_array;

typedef struct {
    FILE * source;
    
} SAX_parser;


SAX_parser * SAX_init(FILE * source);

void start_parse(SAX_parser *p);

int register_characters_handler(SAX_parser *p, void event_handler(char *));

int register_start_document_handler(SAX_parser *p, void event_handler());
int register_end_document_handler(SAX_parser *p, void event_handler());

int register_start_element_handler(
        SAX_parser *p, void event_handler(char *, attr_array *));
int register_end_element_handler(SAX_parser *p, void event_handler(char *));

int register_error_handler(SAX_parser *p, void event_handler(int));



#endif
