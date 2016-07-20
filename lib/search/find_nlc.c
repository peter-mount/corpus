
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/json.h>
#include <area51/rest.h>
#include <networkrail/corpus.h>
#include <string.h>
#include <ctype.h>

#include <area51/list.h>

void corpus_find_nlc(struct charbuffer *b, int nlc) {
    struct List *l = (struct List *) hashmapGet(corpusIndex.nlc, &nlc);
    json_append_list(b,l,corpus_append);
}