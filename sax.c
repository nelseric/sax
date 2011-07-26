#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "sax.h"

SAX_parser * SAX_init(FILE * source) {
	SAX_parser *p = malloc(sizeof(SAX_parser));
	p->source = source;
	p->h_list.size = 0;
	p->h_list.cap = 10;
	p->h_list.handlers = malloc(p->h_list.cap * sizeof(handler *));
	return p;
}

void saxfree(SAX_parser *p){
	for(int i = 0; i < p->h_list.size; i ++){
		free(p->h_list.handlers[i]);
	}
	free(p->h_list.handlers);
	free(p);
}
void attrfree(attr_array *a){
	for(int i = 0; i < a->size; i++){
		free(a->attrs[i].name);
		free(a->attrs[i].value);
	}
	free(a->attrs);
	free(a);
}


int reg_characters_handler(SAX_parser *p, void event_handler(char * chars)) {
	if (p->h_list.size == p->h_list.cap) {
		p->h_list.cap = (p->h_list.cap * 3) / 2;
		p->h_list.handlers = realloc(p->h_list.handlers, sizeof(handler)
				* p->h_list.size);
	}
	int s = p->h_list.size;
	handler *new = malloc(sizeof(handler));

	new->func.characters_handler = event_handler;
	new->type = CHARACTERS;

	p->h_list.handlers[s] = new;
	p->h_list.size++;

	return 0;
}

void characters_caller(SAX_parser *p, char * chars) {
	int i;
	for (i = 0; i < p->h_list.size; i++) {
		if (p->h_list.handlers[i]->type == CHARACTERS) {
			(*p->h_list.handlers[i]->func.characters_handler)(chars);
		}
	}
}

int reg_start_document_handler(SAX_parser *p, void event_handler()) {
	if (p->h_list.size == p->h_list.cap) {
		p->h_list.cap = (p->h_list.cap * 3) / 2;
		p->h_list.handlers = realloc(p->h_list.handlers, sizeof(handler)
				* p->h_list.size);
	}
	int s = p->h_list.size;
	handler *new = malloc(sizeof(handler));

	new->func.start_document_handler = event_handler;
	new->type = START_DOCUMENT;

	p->h_list.handlers[s] = new;
	p->h_list.size++;

	return 0;
}

void start_document_caller(SAX_parser *p) {
	int i;
	for (i = 0; i < p->h_list.size; i++) {
		if (p->h_list.handlers[i]->type == START_DOCUMENT) {
			p->h_list.handlers[i]->func.start_document_handler();
		}
	}
}

int reg_end_document_handler(SAX_parser *p, void event_handler()) {
	if (p->h_list.size == p->h_list.cap) {
		p->h_list.cap = (p->h_list.cap * 3) / 2;
		p->h_list.handlers = realloc(p->h_list.handlers, sizeof(handler)
				* p->h_list.size);
	}
	int s = p->h_list.size;
	handler *new = malloc(sizeof(handler));

	new->func.end_document_handler = event_handler;
	new->type = END_DOCUMENT;

	p->h_list.handlers[s] = new;
	p->h_list.size++;

	return 0;
}

void end_document_caller(SAX_parser *p) {
	int i;
	for (i = 0; i < p->h_list.size; i++) {
		if (p->h_list.handlers[i]->type == END_DOCUMENT) {
			p->h_list.handlers[i]->func.end_document_handler();
		}
	}
}

int reg_start_element_handler(SAX_parser *p, void event_handler(char * name,
		attr_array *attrs)) {
	if (p->h_list.size == p->h_list.cap) {
		p->h_list.cap = (p->h_list.cap * 3) / 2;
		p->h_list.handlers = realloc(p->h_list.handlers, sizeof(handler)
				* p->h_list.size);
	}
	int s = p->h_list.size;
	handler *new = malloc(sizeof(handler));

	new->func.start_element_handler = event_handler;
	new->type = START_ELEMENT;

	p->h_list.handlers[s] = new;
	p->h_list.size++;

	return 0;
}

void start_element_caller(SAX_parser *p, char *name, attr_array * attrs) {
	int i;
	for (i = 0; i < p->h_list.size; i++) {
		if (p->h_list.handlers[i]->type == START_ELEMENT) {
			p->h_list.handlers[i]->func.start_document_handler(name, attrs);
		}
	}
}

int reg_end_element_handler(SAX_parser *p, void event_handler(char *name)) {
	if (p->h_list.size == p->h_list.cap) {
		p->h_list.cap = (p->h_list.cap * 3) / 2;
		p->h_list.handlers = realloc(p->h_list.handlers, sizeof(handler)
				* p->h_list.size);
	}
	int s = p->h_list.size;
	handler *new = malloc(sizeof(handler));

	new->func.end_element_handler = event_handler;
	new->type = END_ELEMENT;

	p->h_list.handlers[s] = new;
	p->h_list.size++;
	return 0;
}

void end_element_caller(SAX_parser *p, char * name) {
	int i;
	for (i = 0; i < p->h_list.size; i++) {
		if (p->h_list.handlers[i]->type == END_ELEMENT) {
			p->h_list.handlers[i]->func.end_element_handler(name);
		}
	}
}

int reg_pi_handler(SAX_parser *p, void event_handler(char * name, char * data)) {
	if (p->h_list.size == p->h_list.cap) {
		p->h_list.cap = (p->h_list.cap * 3) / 2;
		p->h_list.handlers = realloc(p->h_list.handlers, sizeof(handler)
				* p->h_list.size);
	}
	int s = p->h_list.size;
	handler *new = malloc(sizeof(handler));

	new->func.process_instruction_handler = event_handler;
	new->type = PROCESS_INSTRUCTION;

	p->h_list.handlers[s] = new;
	p->h_list.size++;

	return 0;
}

void pi_caller(SAX_parser *p, char * name, char * data) {
	int i;
	for (i = 0; i < p->h_list.size; i++) {
		if (p->h_list.handlers[i]->type == PROCESS_INSTRUCTION) {
			p->h_list.handlers[i]->func.process_instruction_handler(name, data);
		}
	}
}

int reg_error_handler(SAX_parser *p, void event_handler(int errnum)) {
	if (p->h_list.size == p->h_list.cap) {
		p->h_list.cap = (p->h_list.cap * 3) / 2;
		p->h_list.handlers = realloc(p->h_list.handlers, sizeof(handler)
				* p->h_list.size);
	}
	int s = p->h_list.size;
	handler *new = malloc(sizeof(handler));

	new->func.error_handler = event_handler;
	new->type = ERROR;

	p->h_list.handlers[s] = new;
	p->h_list.size++;

	return 0;
}

void error_caller(SAX_parser *p, int errnum) {
	int i;
	for (i = 0; i < p->h_list.size; i++) {
		if (p->h_list.handlers[i]->type == ERROR) {
			(*p->h_list.handlers[i]->func.error_handler)(errnum);
		}
	}
}

