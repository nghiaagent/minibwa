## Getting Started
```sh
git clone https://github.com/lh3/minibwa
cd minibwa && make

# with test data
./minibwa index test/chrM-human.fa.gz chrM-human              # index the genome
./minibwa map -a chrM-human test/chrM-read_?.fa.gz > aln.sam  # align and output in SAM

# other examples without test data
minibwa map -t16 ref.index long-read.fq > aln.paf             # align long reads
minibwa map -a -5P ref.index reads.interleaved.fq > aln.sam   # align Hi-C short reads
```

## Introduction

Minibwa aligns short reads against a reference genome. It is the successor of
bwa-mem with a different algorithm. Minibwa is over three times as fast as the
original bwa-mem and twice as fast as bwa-mem2 at comparable accuracy. While
minibwa works with accurate long reads, minimap2 is more robust under high
error rate.

Minibwa is a hybrid of bwa-mem and minimap2: it indexes the genome with
Burrow-Wheeler Transform (BWT), finds variable-length seeds like bwa-mem, and
performs chaining and SIMD-based nucleotide alignment with the minimap2
algorithm. Minibwa speeds up bwa-mem2 further with additional prefetch for
seeding, new heuristics to skip unnecessary mate rescue and reduced effort in
highly repetitive regions where reads would often be wrongly mapped due to
structural changes anyway.

## Users' Guide

### Installation

Minibwa requires either NEON or SSE4.2 and depends on [zlib][zlib] installed on
your system. It also includes slightly modified source code of
[mimalloc][mimalloc] and [libsais][libsais] which optionally uses OpenMP for
multi-threading. You can build minibwa with
```sh
make             # automatically detect OpenMP and arm64 vs. x86_64
make omp=0       # disable multi-threading in libsais (no effect on mapping)
make gpl=0       # disable GPL'd code for low-memory BWT construction (no effect on mapping)
make mimalloc=0  # disable mimalloc and use the system malloc+kalloc instead
```

### Usage

Like bwa-mem, minibwa requires to index the genome before read alignment.

#### Indexing

You can index the reference genome with
```sh
minibwa index -t8 ref.fa     # index with 8 CPU threads, using 18N RAM (N is the genome size)
minibwa index ref.fa prefix  # use a different index prefix instead of ref.fa
minibwa index -l ref.fa      # use less memory at the cost of performance
```
Minibwa generates two files: `ref.fa.l2b` for 2-bit encoded reference genome
sequences and `ref.fa.mbw` for BWT and sampled suffix array.

#### Mapping

By default, minibwa dynamically changes multiple internal parameters based on
individual read lengths. It works for both short and accurate long reads.
```sh
minibwa map -at8 ref.fa read1.fq read2.fq   # map paired-end reads and output SAM
minibwa map -t8 ref.fa read.fa.gz           # map single-end or long reads and output PAF
```
Note in the default adaptive mode, `-g`/`-w`/`-W`/`-N`/`-m`/`-s` only changes
the short-read setting; the long-read setting is fixed. This mode is disabled
with `--adap=no` or when `-x sr` or `-x lr` is specified.

Minibwa does not support spliced alignment and has not been tested for genome alignment.

[zlib]: https://zlib.net/
[mimalloc]: https://github.com/microsoft/mimalloc
[libsais]: https://github.com/IlyaGrebnov/libsais
