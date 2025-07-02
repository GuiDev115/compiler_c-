#include "utils.h"

/* Implementação simples de strdup para evitar problemas */
char* my_strdup(const char* s) {
    if (!s) return NULL;
    
    size_t len = strlen(s) + 1;
    char* dup = malloc(len);
    if (dup) {
        memcpy(dup, s, len);
    }
    return dup;
}
