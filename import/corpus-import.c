
/* 
 * File:   corpus-import.c
 * Author: peter
 *
 * Created on 17 July 2016, 21:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <area51/json.h>
#include <area51/log.h>
#include <networkrail/corpus.h>
#include <networkrail/corpus/import.h>

#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage:\n\tcorpus-import input output\n");
        exit(1);
    }

    logconsole("Reading %s", argv[1]);

    int fsock = open(argv[1], O_RDONLY);
    if (fsock == -1) {
        logconsole("No source %s", argv[1]);
        exit(1);
    }

    struct json_object *obj = json_parse_file(fsock);
    if (!obj) {
        logconsole("Failed to parse json");
        exit(1);
    }

    close(fsock);

    struct json_object *tiplocData;
    if (!json_object_object_get_ex(obj, "TIPLOCDATA", &tiplocData)) {
        logconsole("No TIPLOCDATA");
        exit(1);
    }

    logconsole("Importing corpus");
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

    logconsole("Writing %s", argv[2]);
    FILE *out = fopen(argv[2], "w");

    // Number of records
    int listSize = list_size(&data);
    fwrite(&listSize, sizeof (listSize), 1, out);

    struct CorpusNode *node = (struct CorpusNode *) list_getHead(&data);
    while (list_isNode(&node->node)) {
        fwrite((void *) &node->corpus, CORPUS_REC_LEN, 1, out);
        node = (struct CorpusNode *) list_getNext(&node->node);
    }
    fclose(out);
    return (EXIT_SUCCESS);
}

