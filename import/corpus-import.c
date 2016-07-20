
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
#include <unistd.h>
#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <networkrail/corpus/version.h>

int verbose = 0;

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc != 3) {
        logconsole("Usage: corpus-import input output\n");
        return EXIT_FAILURE;
    }

    logconsole(PKGBANNER);
    logconsole(PKGBUILD);

    logconsole("Reading %s", argv[1]);

    int fsock = open(argv[1], O_RDONLY);
    if (fsock == -1) {
        logconsole("No source %s", argv[1]);
        return EXIT_FAILURE;
    }

    struct json_object *obj = json_parse_file(fsock);
    if (!obj) {
        logconsole("Failed to parse json");
        return EXIT_FAILURE;
    }

    close(fsock);

    struct List data;
    list_init(&data);

    if (import_corpus(obj, &data)) {
        logconsole("Failed to import");
        return EXIT_FAILURE;
    }

    logconsole("Writing %s", argv[2]);
    FILE *out = fopen(argv[2], "w");
    int status = write_corpus_list(&data, out);
    fclose(out);
    return status ? EXIT_FAILURE : EXIT_SUCCESS;
}

