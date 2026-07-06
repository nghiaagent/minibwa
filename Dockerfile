# Stage 1: Build minibwa
FROM debian:stable-slim AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc \
    make \
    libc-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy local source code and build minibwa
COPY . /src/minibwa
WORKDIR /src/minibwa
RUN make clean && make

# Stage 2: Final minimal image
FROM debian:stable-slim

# Install runtime dependencies (zlib and libgomp1)
RUN apt-get update && apt-get install -y --no-install-recommends \
    zlib1g \
    libgomp1 \
    && rm -rf /var/lib/apt/lists/*

# Copy the compiled binary from builder
COPY --from=builder /src/minibwa/minibwa /usr/local/bin/minibwa

# Set BioContainers labels
LABEL base.image="debian:stable-slim" \
      version="1" \
      software="minibwa" \
      software.version="0.3" \
      description="Minibwa aligns short reads against a reference genome, succeeding bwa-mem." \
      website="https://github.com/lh3/minibwa" \
      license="MIT"

# Set default command
ENTRYPOINT ["minibwa"]
CMD ["--help"]
