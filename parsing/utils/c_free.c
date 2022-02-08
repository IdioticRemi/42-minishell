#include "../include/header.h"

void corr_free(char *str)
{
    free(str);
    str = NULL;
}