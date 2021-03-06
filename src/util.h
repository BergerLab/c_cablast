#ifndef __CABLAST_UTIL_H__
#define __CABLAST_UTIL_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

char *trim(char *s, const char *totrim);
char *trim_space(char *s);
int32_t readline(FILE *f, char **line);
int32_t num_cpus();
char *str_slice(char *str, int32_t start, int32_t end);
bool is_substring(char *sub, char *str);
char **split_char(char *line, char split);

#endif
