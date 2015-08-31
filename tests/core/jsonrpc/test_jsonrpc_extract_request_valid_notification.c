#include "jsonrpc.c"

#include "mock_client_buf.h"
#include "mock_proto.h"
#include "test_jsonrpc_utils.h"

int
main(void)
{
    jsmntok_t tokens[32];
    const char json[] = ("{"
        "\"jsonrpc\": \"2.0\","
        "\"method\": \"hello\","
        "\"params\": {\"on\": true}"
    "}");
    int parsed = parse_json(
        tokens, LGTD_ARRAY_SIZE(tokens), json, sizeof(json)
    );

    struct lgtd_jsonrpc_request req = TEST_REQUEST_INITIALIZER;
    bool ok = lgtd_jsonrpc_check_and_extract_request(
        &req, tokens, parsed, json
    );

    if (!ok) {
        errx(1, "return value should be true");
    }

    if (!req.method) {
        errx(1, "missing method");
    }
    if (req.method->end - req.method->start != sizeof("hello") - 1
        || memcmp(&json[req.method->start], "hello", sizeof("hello") - 1)) {
        errx(1, "wrong method name");
    }

    if (!req.params) {
        errx(1, "missing params");
    }
    const char params[] = "{\"on\": true}";
    if (req.params->end - req.params->start != sizeof(params) - 1
        || memcmp(&json[req.params->start], params, req.params->size)) {
        errx(1, "wrong params");
    }

    if (req.id) {
        errx(1, "id should be NULL");
    }

    return 0;
}
