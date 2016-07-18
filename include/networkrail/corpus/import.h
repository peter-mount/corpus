
/* 
 * File:   import.h
 * Author: peter
 *
 * Created on 18 July 2016, 11:12
 */

#ifndef IMPORT_H
#define IMPORT_H

#include <area51/list.h>
#include <json-c/json.h>
#include <networkrail/corpus.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct CorpusNode {
        struct Node node;
        struct CorpusEntry corpus;
    };

    extern struct CorpusNode *corpus_import_entry(struct json_object *obj);

#ifdef __cplusplus
}
#endif

#endif /* IMPORT_H */

