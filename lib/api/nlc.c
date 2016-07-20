#include <networkrail/corpus.h>
#include <area51/webserver.h>
#include <area51/log.h>
#include <string.h>

static const char *prefix = "/nlc/";
static const char *handler_prefix = "/nlc/*";

static int handler(struct MHD_Connection * connection, WEBSERVER_HANDLER *handler, const char *url) {
    logconsole("Got %s", url);

    int stanox = -1;
    if(url[strlen(prefix)])
        stanox = atoi(&url[strlen(prefix)]);
    
    logconsole("Searching for %d", stanox);

    struct charbuffer b;
    charbuffer_init(&b);

    corpus_find_nlc(&b, stanox);

    struct MHD_Response *response = MHD_create_response_from_buffer(b.pos, b.buffer, MHD_RESPMEM_MUST_FREE);
    return queueResponse(connection, &response);
}

void register_corpus_api_nlc() {
    webserver_add_handler(handler_prefix, handler);
}