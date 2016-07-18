
#include <stdio.h>
#include <stdlib.h>
#include <area51/json.h>
#include <networkrail/corpus/import.h>
#include <string.h>

struct CorpusNode *corpus_import_entry(struct json_object *obj) {
    struct CorpusNode * node = (struct CorpusNode *) malloc(sizeof (struct CorpusNode));
    if (node) {
        memset(node, 0, sizeof (struct CorpusNode));

        node->corpus.nlc = json_getInt(obj, "NLC");
        node->corpus.stanox = json_getInt(obj, "STANOX");
        node->corpus.uic = json_getInt(obj, "UIC");
        json_copyString(obj, "3ALPHA", node->corpus.talpha, CORPUS_TALPHA);
        json_copyString(obj, "TIPLOC", node->corpus.tiploc, CORPUS_TIPLOC);
        json_copyString(obj, "3ALPHA", node->corpus.talpha, CORPUS_NLCDESC);
    }
    return node;
}
