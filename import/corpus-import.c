
/* 
 * File:   corpus-import.c
 * Author: peter
 *
 * Created on 17 July 2016, 21:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <networkrail/corpus.h>
#include <networkrail/corpus/import.h>
#include <json-c/json.h>
#include <area51/charbuffer.h>
#include <log.h>

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage:\n\tcorpus-import input output\n");
        exit(1);
    }

    loginfo("Reading %s", argv[1]);
    FILE *in = fopen(argv[1], "r");
    struct charbuffer buf;
    charbuffer_init(&buf);
    charbuffer_read(&buf, in);
    fclose(in);

    loginfo("Read %d characters", buf.pos);

    loginfo("Decoding json");
    struct json_tokener *tokener = json_tokener_new();
    struct json_object *obj = json_tokener_parse_ex(tokener, buf.buffer, buf.pos);
    json_tokener_free(tokener);

    /*
        if( json_object_get_type(obj) != json_type.json_type_object) {
            loginfo("Invalid corpus file");
            exit(1);
        }
     */

    struct json_object *tiplocData;
    if (!json_object_object_get_ex(obj, "TIPLOCDATA", &tiplocData)) {
        loginfo("No TIPLOCDATA");
        exit(1);
    }

    struct List data;
    list_init(&data);

    struct array_list *list = json_object_get_array(tiplocData);
    int len = array_list_length(list);
    for (int i = 0; i < len; i++) {
        json_object *ent = (json_object *) array_list_get_idx(list, i);

        struct CorpusNode *node = corpus_import_entry(ent);
        if (node != NULL)
            list_addTail(&data, &node->node);
    }

    loginfo("Writing %s", argv[2]);
    FILE *out = fopen(argv[2], "w");
    
    // Number of records
    int listSize = list_size(&data);
    fwrite(&listSize,sizeof(listSize),1,out);
    
    struct CorpusNode *node = (struct CorpusNode *)list_getHead(&data);
    while(list_isNode(&node->node)) {
        fwrite((void *)&node->corpus, CORPUS_REC_LEN, 1, out );
        node = (struct CorpusNode *) list_getNext(&node->node);
    }
    fclose(out);
    return (EXIT_SUCCESS);
}

