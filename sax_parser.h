/*
 * sax_parser.h
 *
 *  Created on: 2011-07-25
 *      Author: eric
 */

#ifndef SAX_PARSER_H_
#define SAX_PARSER_H_
#include "sax.h"

#define ATTR_REGEX "(\\w+)\\s*=\\s*\"([^\"]*)\""
#define OPENTAG_REGEX "<(\\w)\\s*([^>]*)\\s*>"
#define CLOSETAG_REGEX "</(\\w+)\\s*>"
#define PROC_INST_REGEX "<\\?(\\w+)\\s+([^\\?>]*)\\?>"

void start_parse(SAX_parser *p);
attr_array * parse_attributes(const char * data);
char *trim (const char * str);
char *rtrim (const char * str);
char *ltrim (const char * str);

#endif /* SAX_PARSER_H_ */
