#include <sys/types.h>
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GET             0
#define POST            1

unsigned int particles_per_row;
unsigned int particles_per_col;

struct connection_info_struct
{
  int connectiontype;
  char *answerstring;
  struct MHD_PostProcessor *postprocessor;
};


int response(struct MHD_Connection *connection, int code, char *page) {
    int ret;
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, code, response);
    MHD_destroy_response(response);
    return ret;
}

static int
null_iterator (void *coninfo_cls, enum MHD_ValueKind kind, const char *key,
              const char *filename, const char *content_type,
              const char *transfer_encoding, const char *data, uint64_t off,
              size_t size)
{
    return MHD_YES;
}

int request(void *cls,
            struct MHD_Connection *connection,
            const char *url,
            const char *method,
            const char *version,
            const char *upload_data,
            size_t *upload_data_size,
            void **con_cls) {

    if (NULL == *con_cls) {
        struct connection_info_struct *con_info = malloc(sizeof(struct connection_info_struct));

        if (NULL == con_info) return MHD_NO;

        con_info->answerstring = NULL;

        if (0 == strcmp(method, "POST")) {
            con_info->postprocessor =
              MHD_create_post_processor(connection, 1024, null_iterator, (void *) con_info);

            if (NULL == con_info->postprocessor) {
                free (con_info);
                return MHD_NO;
             }

            con_info->connectiontype = POST;
        } else {
            con_info->connectiontype = GET;
        }

        *con_cls = (void *) con_info;

        return MHD_YES;
    }

    if (0 == strcmp (method, "GET")) {
        char page[64];
        snprintf(page, sizeof page, "{rows:%d, cols:%d}", particles_per_row,  particles_per_col);
        return response(connection, MHD_HTTP_OK, page);
    }
    if (0 == strcmp (method, "POST")) {
        struct connection_info_struct *con_info = *con_cls;

        if (*upload_data_size != 0) {
            fprintf(stderr, "got data with size %zu '%s'\n", *upload_data_size, upload_data);
            // MHD_post_process(con_info->postprocessor, upload_data, *upload_data_size);
            *upload_data_size = 0;

            return MHD_YES;
          }
        else if (NULL != con_info->answerstring) {
            return response(connection, MHD_HTTP_OK, "");
        }
    }
    return response(connection, 404, "");
}

static void completed (void *cls, struct MHD_Connection *connection,
                       void **con_cls, enum MHD_RequestTerminationCode toe)
{
    struct connection_info_struct *con_info = *con_cls;

    if (NULL == con_info) return;

    if (con_info->connectiontype == POST) {
        MHD_destroy_post_processor(con_info->postprocessor);
        if (con_info->answerstring) free (con_info->answerstring);
    }

    free(con_info);
    *con_cls = NULL;
}
