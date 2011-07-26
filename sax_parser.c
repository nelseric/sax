/*
 * sax_parser.c
 *
 *  Created on: 2011-07-25
 *      Author: eric
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <ctype.h>
#include <string.h>
#include "sax_parser.h"
#include "sax.h"

void start_parse(SAX_parser *p) {
	char cur = fgetc(p->source);

	size_t charbuf_size = 100;
	size_t charbuf_i = 0;
	char * charbuf = calloc(charbuf_size, sizeof(char));

	start_document_caller(p);
	while (cur != EOF) {
		if (cur == '<') {
			if (charbuf_i > 0) {
				char * trimmed = trim(charbuf);
				if(strlen(trimmed) > 0){
				characters_caller(p, trimmed);
				}
				free(trimmed);
				for(int i = 0; i <= charbuf_i; i ++)
					charbuf[i] = '\0';
				charbuf_i = 0;
			}
			cur = fgetc(p->source);
			if (cur == '?') {

				cur = fgetc(p->source);
				int i = 0;
				size_t max = 64;
				char * namebuf;
				char * databuf;
				char * tmpbuf;
				namebuf = calloc(max, sizeof(char));
				while (isalnum(cur) || cur == '_') {
					if (i < max) {
						namebuf[i] = cur;
						i++;
						cur = fgetc(p->source);
					} else {
						max = max * 2;
						tmpbuf = calloc(max, sizeof(char));
						strcpy(tmpbuf, namebuf);
						free(namebuf);
						namebuf = tmpbuf;
					}
				}
				i = 0;
				databuf = calloc(max, sizeof(char));
				cur = fgetc(p->source);
				while (1) {
					if (cur == '?') {
						char next = fgetc(p->source);
						if (next == '>') {
							break;
						} else {
							ungetc(next, p->source);
						}
					}
					if (i < max) {
						databuf[i] = cur;
						i++;
						cur = fgetc(p->source);
					} else {
						max = max * 2;
						tmpbuf = calloc(max, sizeof(char));
						strcpy(tmpbuf, databuf);
						free(databuf);
						databuf = tmpbuf;
					}
				}
				pi_caller(p, namebuf, databuf);
				free(databuf);
				free(namebuf);
			} else if (cur == '/') {
				//end tag
				cur = fgetc(p->source);
				int i = 0;
				size_t max = 64;
				char * namebuf;
				char * tmpbuf;
				namebuf = calloc(max, sizeof(char));
				while (isalnum(cur) || cur == '_') {
					if (i < max) {
						namebuf[i] = cur;
						i++;
						cur = fgetc(p->source);
					} else {
						max = max * 2;
						tmpbuf = calloc(max, sizeof(char));
						strcpy(tmpbuf, namebuf);
						free(namebuf);
						namebuf = tmpbuf;
					}
				}
				end_element_caller(p, namebuf);
				free(namebuf);
			} else {
				//open tag

				//cur = fgetc(p->source);
				int i = 0;
				size_t max = 64;
				char * namebuf;
				char * tmpbuf;
				char * databuf;
				namebuf = calloc(max, sizeof(char));
				while (isalnum(cur) || cur == '_') {
					if (i < max) {
						namebuf[i] = cur;
						i++;
						cur = fgetc(p->source);
					} else {
						max = max * 2;
						tmpbuf = calloc(max, sizeof(char));
						strcpy(tmpbuf, namebuf);
						free(namebuf);
						namebuf = tmpbuf;
					}
				}
				i = 0;
				databuf = calloc(max, sizeof(char));
				while (1) {
					if (cur == '>') {
						break;

					}
					if (i < max) {
						databuf[i] = cur;
						i++;
						cur = fgetc(p->source);
					} else {
						max = max * 2;
						tmpbuf = calloc(max, sizeof(char));
						strcpy(tmpbuf, databuf);
						free(databuf);
						databuf = tmpbuf;
					}
				}

				attr_array * attrs = parse_attributes(databuf);

				start_element_caller(p, namebuf, attrs);

				attrfree(attrs);

				free(databuf);
				free(namebuf);
			}
		} else {
			if (charbuf_i == charbuf_size) {
				charbuf_size *= 2;
				char *tmp = calloc(charbuf_size, sizeof(char));
				strcpy(tmp, charbuf);
				free(charbuf);
				charbuf = tmp;
			}

			charbuf[charbuf_i] = cur;
			charbuf_i++;
		}
		cur = fgetc(p->source);
	}
	free(charbuf);
	end_document_caller(p);
}

attr_array * parse_attributes(const char * datai) {
	char * data = strdup(datai);

	attr_array *ret = malloc(sizeof(attr_array));
	ret->cap = 4;
	ret->size = 0;
	ret->attrs = calloc(ret->cap, sizeof(attribute));

	regex_t attr_r;

	regcomp(&attr_r, ATTR_REGEX, REG_EXTENDED);

	unsigned long offset = 0;
	while (offset < strlen(data)) {
		int result;
		regmatch_t match[3];

		result = regexec(&attr_r, (char *) (data + offset), 3, match, 0);
		if (result != 0) {
			break;
		} else {
			char *ms = strndup((char*) (data + offset + match[0].rm_so),
					match[0].rm_eo - match[0].rm_so);
			char *name = strndup((char*) (data + offset + match[1].rm_so),
					match[1].rm_eo - match[1].rm_so);
			char *value = strndup((char*) (data + offset + match[2].rm_so),
					match[2].rm_eo - match[2].rm_so);

			if (ret->size >= ret->cap) {
				ret->cap *= 2;
				ret->attrs = realloc(ret->attrs, ret->cap * sizeof(char));
			}
			ret->attrs[ret->size].name = name;
			ret->attrs[ret->size].value = value;
			ret->size++;
			offset += match[0].rm_eo;
			//			printf("Match (%s)\n", ms);

			free(ms);
		}

	}

	regfree(&attr_r);
	free(data);
	return ret;
}

char* trim(const char* str) {
	int has_graph = 0;
	for(int i = 0; i < strlen(str); i++){
		if(isgraph(str[i])){
			has_graph = 1;
			break;
		}
	}
	if(!has_graph)
		return strdup("");
	else {
		char *rt = rtrim(str);
		char *lt = ltrim(rt);
		free(rt);
		return lt;
	}
}

char *ltrim(const char * str){
	int i;
	for(i = 0; i < strlen(str); i++){
		if(isgraph(str[i]))
			break;
	}
	return strdup(str+i);
}
char *rtrim(const char * str){
	int i;
	for(i = strlen(str) - 1; i >= 0; i--){
		if(isgraph(str[i]))
			break;
	}
	return strndup(str, i+1);
}

