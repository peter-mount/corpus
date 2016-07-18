
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

#include <networkrail/corpus/version.h>

int write_corpus_list(struct List *data, FILE *file) {

    // Number of records
    int listSize = list_size(data);
    fwrite(&listSize, sizeof (listSize), 1, file);

    struct CorpusNode *node = (struct CorpusNode *) list_getHead(data);
    while (list_isNode(&node->node)) {
        fwrite((void *) &node->corpus, CORPUS_REC_LEN, 1, file);
        node = (struct CorpusNode *) list_getNext(&node->node);
    }
    return (EXIT_SUCCESS);
}

