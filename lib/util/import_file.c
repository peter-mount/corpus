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


/**
 * Import corpus
 * @param obj Json Object containing entire corpus database
 * @param list List to write entries into
 * @return 1 on error
 */
int import_corpus(struct json_object *obj, struct List *data) {

    struct json_object *tiplocData;
    if (!json_object_object_get_ex(obj, "TIPLOCDATA", &tiplocData)) {
        logconsole("No TIPLOCDATA");
        return 1;
    }

    logconsole("Importing corpus");

    struct array_list *list = json_object_get_array(tiplocData);
    int len = array_list_length(list);
    
    for (int i = 0; i < len; i++) {
        json_object *ent = (json_object *) array_list_get_idx(list, i);

        struct CorpusNode *node = corpus_import_entry(ent);
        
        if (node != NULL)
            list_addTail(data, &node->node);
    }
    
    return 0;
}

