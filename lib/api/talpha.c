#include <networkrail/corpus.h>
#include <area51/webserver.h>
#include <area51/log.h>
#include <string.h>

static const char *prefix = "/3alpha/";
static const char *handler_prefix = "/3alpha/*";

static int handler(struct MHD_Connection * connection, WEBSERVER_HANDLER *handler, const char *url) {
    logconsole("Got %s", url);

    char *talpha = (char *)&url[strlen(prefix)];
    logconsole("Searching for %s", talpha);

    struct charbuffer b;
    charbuffer_init(&b);

    corpus_find_3alpha(&b, talpha);

    struct MHD_Response *response = MHD_create_response_from_buffer(b.pos, b.buffer, MHD_RESPMEM_MUST_FREE);
    return queueResponse(connection, &response);
}

void register_corpus_api_talpha() {
    webserver_add_handler(handler_prefix, handler);
}