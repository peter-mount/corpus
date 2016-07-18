
/* 
 * Network Rail Corpus Database
 */

#ifndef CORPUS_H
#define CORPUS_H

#ifdef __cplusplus
extern "C" {
#endif

    struct corpus_entry {
        int stanox;
        int nlc;
        int uic;
        char talpha[4];
        char tiploc[16];
        char nlcdesc[65];
        char nlcdesc16[17];
    };

    extern int corpus_import(FILE *in,FILE *out);
    
#ifdef __cplusplus
}
#endif

#endif /* CORPUS_H */

