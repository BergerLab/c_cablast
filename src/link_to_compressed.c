#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "link_to_compressed.h"

//Initializes a link to a sequence in the compressed database
struct cb_link_to_compressed *
cb_link_to_compressed_init(int32_t org_seq_id, int16_t coarse_start,
                           int16_t coarse_end, uint64_t original_start,
                           uint64_t original_end, bool dir){
    struct cb_link_to_compressed *link = malloc(sizeof(*link));
    assert(link);

    link->data = cb_link_to_compressed_data_init(org_seq_id,
                                                 coarse_start, coarse_end,
                                                 original_start, original_end,
                                                 dir);
    link->next = NULL;

    return link;
}

//Freeing function for a cb_link_to_compressed
void cb_link_to_compressed_free(struct cb_link_to_compressed *link){
    if (link != NULL) {
        cb_link_to_compressed_free(link->next);
        free(link->data);
        free(link);
    }
}

//Initializes the data in a link to a sequence in the compressed database
struct cb_link_to_compressed_data *
cb_link_to_compressed_data_init(int32_t org_seq_id, int16_t coarse_start,
                                int16_t coarse_end, uint64_t original_start,
                                uint64_t original_end, bool dir){
    struct cb_link_to_compressed_data *data = malloc(sizeof(*data));
    assert(data);

    data->org_seq_id     = org_seq_id;
    data->coarse_start   = coarse_start;
    data->coarse_end     = coarse_end;
    data->original_start = original_start;
    data->original_end   = original_end;
    data->dir            = dir;

    return data;
}

