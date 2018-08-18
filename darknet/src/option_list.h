#ifndef OPTION_LIST_H
#define OPTION_LIST_H
#include "list.h"

typedef struct{
    char *key;
    char *val;
    int used;
} kvp;


int read_option(char *s, linked_list *options);
void option_insert(linked_list *l, char *key, char *val);
char *option_find(linked_list *l, char *key);
int option_find_int_quiet(linked_list *l, char *key, int def);
float option_find_float(linked_list *linked_list, char *key, float def);
float option_find_float_quiet(linked_list *l, char *key, float def);
void option_unused(linked_list *l);

#endif
