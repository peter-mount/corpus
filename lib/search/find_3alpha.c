
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/json.h>
#include <area51/rest.h>
#include <networkrail/corpus.h>
#include <string.h>
#include <ctype.h>

#include <area51/list.h>

void corpus_find_3alpha(struct charbuffer *b, const char *talpha) {
    char *s = strdup(talpha);
    for (char *p = s; *p; p++)
        *p = toupper(*p);

    struct List *l = (struct List *)hashmapGet(corpusIndex.talpha, s);
    json_append_list(b,l,corpus_append);
}