
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/json.h>
#include <area51/rest.h>
#include <networkrail/corpus.h>
#include <string.h>
#include <ctype.h>

#include <area51/list.h>
#include <area51/log.h>
void corpus_find_tiploc(struct charbuffer *b, const char *tiploc) {
    char *s = strdup(tiploc);
    for (char *p = s; *p; p++)
        *p = toupper(*p);
    
    struct List *l = (struct List *)hashmapGet(corpusIndex.tiploc, s);
    json_append_list(b,l,corpus_append);
}