#ifndef __SAX_H__
#define __SAX_H__
#include <stdio.h>

#define SYNTAX_ERROR 2
#define REGEX_ERROR 4
#define OTHER_ERROR 1

typedef struct {
	char * name;
	char * value;
} attribute;

typedef struct {
	size_t size;
	size_t cap;
	attribute *attrs;
} attr_array;

enum eventtype {
	CHARACTERS,
	START_DOCUMENT,
	END_DOCUMENT,
	START_ELEMENT,
	END_ELEMENT,
	PROCESS_INSTRUCTION,
	ERROR
};

typedef struct {
	enum eventtype type;

	union {
		void (* characters_handler)(char * chars);
		void (* start_document_handler)();
		void (* end_document_handler)();
		void (* start_element_handler)(char * name, attr_array *attrs);
		void (* end_element_handler)(char * name);
		void (* process_instruction_handler)(char *name, char *data);
		void (* error_handler)(int errnum);
	} func;
} handler;

typedef struct {
	handler **handlers;
	size_t cap;
	size_t size;
} handler_list;

typedef struct {
	FILE * source;
	handler_list h_list;
} SAX_parser;

SAX_parser * SAX_init(FILE * source);

int reg_characters_handler(SAX_parser *p, void event_handler(char * chars));
void characters_caller(SAX_parser *p, char *chars);

int reg_start_document_handler(SAX_parser *p, void event_handler());
void start_document_caller(SAX_parser *p);
int reg_end_document_handler(SAX_parser *p, void event_handler());
void end_document_caller(SAX_parser *p);

int reg_start_element_handler(SAX_parser *p, void evt(char * name,
		attr_array *attrs));
void start_element_caller(SAX_parser *p, char * name, attr_array *attrs);
int reg_end_element_handler(SAX_parser *p, void event_handler(char *name));
void end_element_caller(SAX_parser *p, char *name);

int reg_pi_handler(SAX_parser *p, void event_handler(char * name, char * data));
void pi_caller(SAX_parser *p, char * name, char * data);

int reg_error_handler(SAX_parser *p, void event_handler(int errnum));
void error_caller(SAX_parser *p, int errnum);

#endif
