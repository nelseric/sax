#ifndef __PPXML_H__
#define __PPXML_H__
#include "sax.h"

void begin();
void end();
void chars(char * chars);
void start_elem(char * name, attr_array *attrs);
void end_elem(char *name);
void proc_inst(char *name, char *data);
void error(int errnum);

void fpns(int n, char *s);

#endif
