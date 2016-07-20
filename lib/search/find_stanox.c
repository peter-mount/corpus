
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/json.h>
#include <networkrail/corpus.h>
#include <string.h>
#include <ctype.h>

#include <area51/list.h>

void corpus_find_stanox(struct charbuffer *b, int stanox) {
    struct List *l = (struct List *)hashmapGet(corpusIndex.stanox, &stanox);
    corpus_append_list(b,l);
}