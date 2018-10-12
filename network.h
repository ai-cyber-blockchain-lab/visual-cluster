#ifndef NETWORK_H
#define NETWORK_H

struct connection_info_struct
{
  int connectiontype;
  char *answerstring;
  struct MHD_PostProcessor *postprocessor;
};

void completed(void *cls, struct MHD_Connection *connection,
               void **con_cls, enum MHD_RequestTerminationCode toe);

int request(void *cls,
            struct MHD_Connection *connection,
            const char *url,
            const char *method,
            const char *version,
            const char *upload_data,
            size_t *upload_data_size,
            void **con_cls);

#endif /* NETWORK_H */
