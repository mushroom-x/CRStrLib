#ifndef CRSTRLIB_H_INCLUDED
#define CRSTRLIB_H_INCLUDED

#include "common.h"

#define MAX_STR_NUM 1000


Boolean isNum(char c);

Boolean isSymbol(char c);

int CRStrLib_char2Int(char c);

int CRStrLib_strLen(char *str);

Status CRStrLib_findNextInt(char *str, int strLen, int *strIdx, int *result);

Status CRStrLib_findNextFloat(char *str, int strLen, int *strIdx, float *result);

Boolean CRStrLib_isValidData(char *str, char *head, char *tail);

Boolean CRStrLib_startWith(char *str, char *head);

Boolean CRStrLib_endWith(char *str, char *tail);

#endif // CRSTRLIB_H_INCLUDED
