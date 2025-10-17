#include <stdlib.h>
#include "bwt.h"
#include "l2bit.h"
#include "libsais64.h"
#include "kommon.h"

mb_bwt_t *mb_bwt_libsais(const l2b_t *l2b, int both_strand, int n_thread)
{
	const int fs = 10000;
	uint8_t *seq;
	int64_t i, j, *a, primary, len;
	mb_bwt_t *bwt;

	len = both_strand? l2b->tot_len * 2 : l2b->tot_len;
	seq = kom_malloc(uint8_t, len);
	a = kom_malloc(int64_t, len + fs + 1);
	for (i = 0, j = 0; i < l2b->tot_len; ++i, ++j)
		seq[j] = l2b_get0(l2b, i);
	if (both_strand)
		for (i = l2b->tot_len - 1; i >= 0; --i, ++j)
			seq[j] = 3 - l2b_get0(l2b, i);
#ifdef LIBSAIS_OPENMP
    primary = libsais64_bwt_omp(seq, seq, a, len, fs, 0, n_thread);
#else
    primary = libsais64_bwt(seq, seq, a, len, fs, 0);
#endif
	free(a);
	bwt = mb_bwt_init_from_raw(1, seq, len, primary);
	free(seq);
	return bwt;
}
