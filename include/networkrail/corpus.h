
/* 
 * Network Rail Corpus Database
 */

#ifndef CORPUS_H
#define CORPUS_H

#include <area51/charbuffer.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CORPUS_TALPHA     3
#define CORPUS_TIPLOC     7
#define CORPUS_NLCDESC   32
#define CORPUS_NLCDESC16 16

    struct CorpusEntry {
        int stanox;
        int nlc;
        int uic;
        char talpha[CORPUS_TALPHA + 1];
        char tiploc[CORPUS_TIPLOC + 1];
        char nlcdesc[CORPUS_NLCDESC + 1];
        char nlcdesc16[CORPUS_NLCDESC16 + 1];
    };

    struct Corpus {
        int numrecs;
        struct CorpusEntry data;
    };

    struct CorpusIndex {
        Hashmap *talpha;
        Hashmap *tiploc;
        Hashmap *stanox;
        Hashmap *nlc;
        Hashmap *uic;
    };

#define CORPUS_REC_LEN ((size_t)sizeof(struct CorpusEntry))

    extern int corpus_import(FILE *in, FILE *out);

    extern struct Corpus *corpus;
    extern int corpus_load_mmap(int fh);

    extern struct CorpusIndex corpusIndex;
    extern void corpus_index();

    extern void corpus_append(struct charbuffer *b, struct CorpusEntry *e);
    extern void corpus_append_list(struct charbuffer *b, struct List *l);

    extern void corpus_find_3alpha(struct charbuffer *b, char *talpha);
    extern void corpus_find_nlc(struct charbuffer *b, int nlc);
    extern void corpus_find_stanox(struct charbuffer *b, int stanox);
    extern void corpus_find_tiploc(struct charbuffer *b, char *tiploc);
    extern void corpus_find_uic(struct charbuffer *b, int uic);

    extern void register_corpus_api_nlc();
    extern void register_corpus_api_stanox();
    extern void register_corpus_api_talpha();
    extern void register_corpus_api_tiploc();
    extern void register_corpus_api_uic();
    
#ifdef __cplusplus
}
#endif

#endif /* CORPUS_H */

