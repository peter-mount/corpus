
/* 
 * Network Rail Corpus Database
 */

#ifndef CORPUS_H
#define CORPUS_H

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

#define CORPUS_REC_LEN ((size_t)sizeof(struct CorpusEntry))

    extern int corpus_import(FILE *in, FILE *out);

#ifdef __cplusplus
}
#endif

#endif /* CORPUS_H */

