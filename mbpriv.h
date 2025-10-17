#ifndef MBPRIV_H
#define MBPRIV_H

#include "l2bit.h"
#include "bwt.h"

#ifdef __cplusplus
extern "C" {
#endif

// defined in bwtgen.c
void mb_bwtgen(const char *fn_pac, const char *fn_bwt, int block_size);

// defined in index.c
mb_bwt_t *mb_bwt_libsais(const l2b_t *l2b, int both_strand, int n_thread);

#ifdef __cplusplus
}
#endif

#endif
