
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
#include <log.h>

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

    loginfo("Reading %s", argv[1]);

    int fsock = open(argv[1], O_RDONLY);
    if (fsock == -1) {
        loginfo("No source %s", argv[1]);
        exit(1);
    }

    struct stat sb;
    if (fstat(fsock, &sb) == -1) {
        loginfo("No stat %s", argv[1]);
        exit(1);
    }

    void *fmap = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fsock, 0);
    if (fmap == MAP_FAILED) {
        loginfo("No mmap %s", argv[1]);
        exit(1);
    }
    
    loginfo("Parsing %s", argv[1]);
    struct json_object *obj = json_tokener_parse(fmap);
    
    munmap(fmap,sb.st_size);
    close(fsock);

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

    loginfo("Importing corpus");
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
    fwrite(&listSize, sizeof (listSize), 1, out);

    struct CorpusNode *node = (struct CorpusNode *) list_getHead(&data);
    while (list_isNode(&node->node)) {
        fwrite((void *) &node->corpus, CORPUS_REC_LEN, 1, out);
        node = (struct CorpusNode *) list_getNext(&node->node);
    }
    fclose(out);
    return (EXIT_SUCCESS);
}

