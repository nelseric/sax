#include <stdlib.h>
#include <stdio.h>
#include "ppxml.h"
#include "sax.h"
#include "sax_parser.h"

int tabs = 0;
int main(int argc, char **argv) {

	SAX_parser *p;

	p = SAX_init(stdin);

	reg_characters_handler(p, chars);
	reg_start_document_handler(p, begin);
	reg_end_document_handler(p, end);
	reg_start_element_handler(p, start_elem);
	reg_end_element_handler(p, end_elem);
	reg_pi_handler(p, proc_inst);
	reg_error_handler(p, error);

	start_parse(p);

	fclose(p->source);

	saxfree(p);

	return EXIT_SUCCESS;
}

void begin() {
	//puts("Begin XML\n");
}

void end() {
	//puts("\nEnd XML\n");
}

void chars(char * chars) {
	fpns(tabs, "  ");
	printf("%s\n", chars);
}

void start_elem(char * name, attr_array *attrs) {
	fpns(tabs, "  ");
	tabs++;
	printf("<%s", name);
	for (int i = 0; i < attrs->size; i++) {
		printf(" %s=\"%s\"", attrs->attrs[i].name, attrs->attrs[i].value);
	}
	printf(">\n");
}

void end_elem(char *name) {
	tabs--;
	fpns(tabs, "  ");
	printf("</%s>\n", name);
}

void proc_inst(char *name, char *data) {
	fpns(tabs, "  ");
	printf("<?%s %s?>\n", name, data);
}

void error(int errnum) {
	fprintf(stderr, "Error");
}

// print n number of string s
void fpns(int n, char * s) {
	//  char * s = "--";
	//  fprintf(f, "%2d|", n);
	for (int i = 0; i < n; i++) {
		printf("%s", s);
	}
}

