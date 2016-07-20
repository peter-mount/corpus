
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/json.h>
#include <networkrail/corpus.h>
#include <string.h>
#include <ctype.h>

#include <area51/list.h>
#include <area51/log.h>
void corpus_find_tiploc(struct charbuffer *b, char *tiploc) {
    char *s = strdup(tiploc);
    for (char *p = s; *p; p++)
        *p = toupper(*p);

    logconsole("Search %s", s);
    
    struct List *l = (struct List *)hashmapGet(corpusIndex.tiploc, s);
    corpus_append_list(b,l);
}