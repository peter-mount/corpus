
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/list.h>
#include <area51/rest.h>
#include <networkrail/corpus.h>
#include <string.h>
#include <ctype.h>

void corpus_append(struct charbuffer *b, struct Node *n) {
    struct CorpusEntry *e = (struct CorpusEntry *) n->name;

    charbuffer_append(b, "{\"stanox\":");
    json_append_int(b, e->stanox);
    charbuffer_append(b, ",\"nlc\":");
    json_append_int(b, e->nlc);
    charbuffer_append(b, ",\"uic\":");
    json_append_int(b, e->uic);
    charbuffer_append(b, ",\"talpha\":");
    json_append_str(b, e->talpha);
    charbuffer_append(b, ",\"tiploc\":");
    json_append_str(b, e->tiploc);
    charbuffer_append(b, ",\"nlcdesc\":");
    json_append_str(b, e->nlcdesc);
    charbuffer_append(b, ",\"nlcdesc16\":");
    json_append_str(b, e->nlcdesc16);
    charbuffer_add(b, '}');
}
