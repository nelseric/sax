#include <stdlib.h>
#include <stdio.h>
#include "ppxml.h"
#include "sax.h"

int tabs = 0;

int main(int argc, char **argv) {
	SAX_parser *p;
	p = SAX_init(stdin);

	reg_start_document_handler(p, begin);
	reg_end_document_handler(p, end);

	start_parse(p);

	fclose(p->source);

	free(p);

	return EXIT_SUCCESS;
}

void begin() {
	puts("Begin");
}

void end() {
	puts("end");
}

void chars(char * chars){

}

void start_elem(char * name, attr_array *attrs);

void end_elem(char *name);

void proc_inst(char *name, char *data) {
	fpns()
	printf("<?%s %s >\n", name, data);
}

void error(int errnum) {
	fprintf(stderr, "Error");
}

// file print n number of string s
void fpns(FILE f, int n, char * s){
	for(int i = 0; i < n; i ++){
		fprintf(f, "%s", s);
	}
}

