
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

#include <networkrail/corpus.h>
#include <networkrail/corpus/version.h>
#include <string.h>
#include <stdbool.h>

#include <area51/webserver.h>

int verbose = 0;
char *database = NULL;
void *dbfile;

static int about() {
    logconsole("Usage: corpusd [-p{port}] database\n");
    return EXIT_FAILURE;
}

static int parseargs(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        char *s = argv[i];
        if (s[0] == '-' && s[1] != 0) {
            if (strncmp("-ip4", s, 4) == 0)
                webserver_enableIPv4();
            else if (strncmp("-ip6", s, 4) == 0)
                webserver_enableIPv6();
            else switch (s[1]) {
                    case 'p':
                        if (s[2])
                            webserver.port = atoi(&s[2]);
                        break;

                    case 'v':
                        verbose++;
                        break;

                    default:
                        logconsole("Unsupported option %s", s);
                        return about();
                }
        } else if (s[0]) {
            if (database) {
                return about();
            }
            database = s;
        }
    }

    if (webserver.port < 1 || webserver.port > 65535 || !database)
        return about();

    return 0;
}

static int opendb() {
    logconsole("Reading %s", database);

    int fsock = open(database, O_RDONLY);
    if (fsock == -1) {
        logconsole("No source %s", database);
        return EXIT_FAILURE;
    }

    int rc = corpus_load_mmap(fsock);
    if (rc) {
        logconsole("Failed to open %s %d", database, rc);
        close(fsock);
        return EXIT_FAILURE;
    }

    logconsole("Indexing");
    corpus_index();

    logconsole("Found %d records", corpus->numrecs);

    return 0;
}

int main(int argc, char** argv) {

    webserver_initialise();

    int rc = parseargs(argc, argv);
    if (rc)return rc;

    logconsole(PKGBANNER);
    logconsole(PKGBUILD);

    rc = opendb();
    if (rc)return rc;

    webserver_set_defaults();

    register_corpus_api_nlc();
    register_corpus_api_stanox();
    register_corpus_api_talpha();
    register_corpus_api_tiploc();
    register_corpus_api_uic();

    logconsole("Starting webserver on port %d", webserver.port);
    webserver_start();

    while (1) {
        sleep(60);
    }
}

