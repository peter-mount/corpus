
#include <stdio.h>
#include <stdlib.h>
#include <networkrail/corpus/import.h>
#include <string.h>

static char *getString(struct json_object *obj, const char *key) {
    struct json_object *val;
    if (json_object_object_get_ex(obj, key, &val)) {
        const char *s = json_object_get_string(val);
        // Null, empty or " " then return null
        if (s == NULL || *s == 0 || (s[0] == ' ' && s[1] == 0))
            return NULL;
        return (char *) s;
    }
    return NULL;
}

static void copyString(struct json_object *obj, const char *key, char *dst, const int maxLen) {
    char *p = dst;
    char *s = getString(obj, key);
    if (s != NULL)
        for (int i = -0; *s && i < maxLen; i++)
            *p++ = *s++;
    *p = '\0';
}

static int getInt(struct json_object *obj, const char *key) {
    const char *s = (const char *) getString(obj, key);
    return s == NULL ? INT_MIN : atoi(s);
}

struct CorpusNode *corpus_import_entry(struct json_object *obj) {
    struct CorpusNode * node = (struct CorpusNode *) malloc(sizeof (struct CorpusNode));
    if (node) {
        memset(node, 0, sizeof (struct CorpusNode));

        node->corpus.nlc = getInt(obj, "NLC");
        node->corpus.stanox = getInt(obj, "STANOX");
        node->corpus.uic = getInt(obj, "UIC");
        copyString(obj, "3ALPHA", node->corpus.talpha, CORPUS_TALPHA);
        copyString(obj, "TIPLOC", node->corpus.tiploc, CORPUS_TIPLOC);
        copyString(obj, "3ALPHA", node->corpus.talpha, CORPUS_NLCDESC);
    }
    return node;
}
