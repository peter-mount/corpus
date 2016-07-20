
#include <stdio.h>
#include <stdlib.h>
#include <area51/log.h>
#include <networkrail/corpus.h>
#include <networkrail/corpus/version.h>

#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>
#include <stdbool.h>

#include <area51/list.h>

struct CorpusIndex corpusIndex;

static void add(Hashmap *m, void *k, struct CorpusEntry *e) {
    struct List *l = (struct List *) hashmapGet(m, k);
    if (!l) {
        l = (struct List *) malloc(sizeof (struct List));
        list_init(l);
        hashmapPut(m, k, l);
    }

    struct Node *n = node_alloc((char *) e);
    list_addTail(l, n);
}

void corpus_index() {
    if (!corpus) return;

    corpusIndex.talpha = hashmapCreate(100, hashmapStringHash, hashmapStringEquals);
    corpusIndex.tiploc = hashmapCreate(100, hashmapStringHash, hashmapStringEquals);
    corpusIndex.stanox = hashmapCreate(100, hashmapIntHash, hashmapIntEquals);
    corpusIndex.nlc = hashmapCreate(100, hashmapIntHash, hashmapIntEquals);
    corpusIndex.uic = hashmapCreate(100, hashmapIntHash, hashmapIntEquals);

    struct CorpusEntry *e = &corpus->data;
    for (int i = 0; i < corpus->numrecs; i++, e++) {
        if (e->talpha)
            add(corpusIndex.talpha, e->talpha, e);

        if (e->tiploc)
            add(corpusIndex.tiploc, e->tiploc, e);
        
        if(e->stanox>0)
            add(corpusIndex.stanox, &e->stanox, e);
        
        if(e->uic>0)
            add(corpusIndex.uic, &e->uic, e);
        
        if(e->nlc>0)
            add(corpusIndex.nlc, &e->nlc, e);
    }
}
