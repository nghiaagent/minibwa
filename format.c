#include "mbpriv.h"
#include "kommon.h"

void mb_fmt_paf_basic(kstring_t *s, const l2b_t *l2b, int64_t qlen, const mb_hit_t *p, const char *qname)
{
	kom_sprintf_lite(s, "%s\t%ld", qname, (long)qlen);
	if (p == 0) { // for unmapped reads
		kom_sprintf_lite(s, "\t*\t*\t*\t*\t*\t*\t*\t0\t0\t0\n");
	} else {
		kom_sprintf_lite(s, "\t%d\t%d\t%c\t%s\t%ld\t%ld\t%ld\t%d\t%d\t%d\ttp:A:%c\ts1:i:%d\tcm:i:%d",
			p->qs, p->qe, p->rev? '-' : '+', l2b->ctg[p->tid].name, (long)l2b->ctg[p->tid].len, (long)p->ts, (long)p->te,
			p->mlen, p->blen, p->mapq, p->parent == p->id? 'P' : 'S', p->score, p->cnt);
		if (p->parent == p->id) kom_sprintf_lite(s, "\ts2:i:%d", p->subsc);
		if (p->p)
			kom_sprintf_lite(s, "\tAS:i:%d\tms:i:%d", p->p->dp_score, p->p->dp_max);
		kom_sprintf_lite(s, "\n");
	}
}
