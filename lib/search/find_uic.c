
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/json.h>
#include <networkrail/corpus.h>
#include <string.h>
#include <ctype.h>

#include <area51/list.h>

void corpus_find_uic(struct charbuffer *b, int uic) {
    struct List *l = (struct List *)hashmapGet(corpusIndex.uic, &uic);
    corpus_append_list(b,l);
}