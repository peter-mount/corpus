
#include <stdio.h>
#include <stdlib.h>
#include <area51/log.h>
#include <networkrail/corpus.h>
#include <networkrail/corpus/version.h>

#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>
#include <stdbool.h>

struct Corpus *corpus = NULL;

int corpus_load_mmap(int fh) {
    struct stat sb;
    if (fh == -1 || fstat(fh, &sb) == -1) {
        return EXIT_FAILURE;
    }

    void *dbfile = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fh, 0);
    if (dbfile == MAP_FAILED) {
        return EXIT_FAILURE;
    }

    // The file is the Corpus structure, the last entry pointing to the first record
    corpus = (struct Corpus *) dbfile;
    return 0;
}
