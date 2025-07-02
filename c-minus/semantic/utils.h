#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

/* Implementação simples de strdup para evitar problemas */
char* my_strdup(const char* s);

#define strdup my_strdup

#endif /* UTILS_H */
