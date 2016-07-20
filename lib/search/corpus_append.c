
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/list.h>
#include <networkrail/corpus.h>
#include <string.h>
#include <ctype.h>

static void append_int(struct charbuffer *b, int v) {
    if (v >= 0)
        charbuffer_append_int(b, v, 0);
    else
        charbuffer_append(b, "null");
}

static void append_str(struct charbuffer *b, char *s) {
    if (s) {
        charbuffer_add(b, '"');
        charbuffer_append(b, s);
        charbuffer_add(b, '"');
    } else
        charbuffer_append(b, "null");
}

void corpus_append(struct charbuffer *b, struct CorpusEntry *e) {
    charbuffer_append(b, "{\"stanox\":");
    append_int(b, e->stanox);
    charbuffer_append(b, ",\"nlc\":");
    append_int(b, e->nlc);
    charbuffer_append(b, ",\"uic\":");
    append_int(b, e->uic);
    charbuffer_append(b, ",\"talpha\":");
    append_str(b, e->talpha);
    charbuffer_append(b, ",\"tiploc\":");
    append_str(b, e->tiploc);
    charbuffer_append(b, ",\"nlcdesc\":");
    append_str(b, e->nlcdesc);
    charbuffer_append(b, ",\"nlcdesc16\":");
    append_str(b, e->nlcdesc16);
    charbuffer_add(b, '}');
}

void corpus_append_list(struct charbuffer *b, struct List *l) {

    charbuffer_reset(b);
    charbuffer_add(b, '[');

    if (l) {
        struct Node *n = list_getHead(l);
        while (n && list_isNode(n)) {
            if (b->pos > 1)
                charbuffer_add(b, ',');
            corpus_append(b, (struct CorpusEntry *) n->name);
            n = n->n_succ;
        }
    }

    charbuffer_add(b, ']');
}
