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

enum eventtype {
    CHARACTERS,
    START_DOCUMENT,
    END_DOCUMENT,
    START_ELEMENT,
    END_ELEMENT,
    PROC_INST,
    ERROR
};

typedef struct {
    enum eventtype type;
    
    union {
        void (* characters_handler) (char * chars);
        void (* start_document_handler)();
        void (* end_document_handler)();
    } func;
} handler;


typedef struct {
    handler *handlers;
    int cap;
    int size;
} handler_list;

typedef struct {
    FILE * source;
    handler_list h_list;
} SAX_parser;


SAX_parser * SAX_init(FILE * source);

void start_parse(SAX_parser *p);

int reg_characters_handler(SAX_parser *p, void event_handler(char * chars));

int reg_start_document_handler(SAX_parser *p, void event_handler());
int reg_end_document_handler(SAX_parser *p, void event_handler());

int reg_start_element_handler(
        SAX_parser *p, void evt(char * name, attr_array *attrs));
int reg_end_element_handler(SAX_parser *p, void event_handler(char *name));

int reg_pi_handler(SAX_parser *p, void event_handler(char * name, char * data));

int reg_error_handler(SAX_parser *p, void event_handler(int errnum));



#endif
