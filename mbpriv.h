#ifndef MBPRIV_H
#define MBPRIV_H

#include "minibwa.h"
#include "l2bit.h"
#include "bwt.h"

#define MB_DBG_NO_KALLOC    (0x1LL)

struct mb_idx_s {
	l2b_t *l2b;
	mb_bwt_t *bwt;
};

typedef struct {
	int32_t tid, len;
	int32_t qs;
	uint16_t tocc, qocc;
	uint64_t pos;
} mb_anchor_t;

typedef struct { int64_t n, m; mb_anchor_t *a; } mb_anchor_v;

#ifdef __cplusplus
extern "C" {
#endif

// defined in bwtgen.c
void mb_bwtgen(const char *fn_pac, const char *fn_bwt, int block_size);

// defined in base-algo.c
void mb_seed_intv(void *km, const mb_bwt_t *bwt, int32_t len, const uint8_t *seq, int32_t min_len, int32_t max_sub_occ, mb_sai_v *v);
void mb_anchor(void *km, const mb_idx_t *idx, const mb_sai_v *u, int32_t max_occ, mb_anchor_v *v);

#ifdef __cplusplus
}
#endif

#endif
