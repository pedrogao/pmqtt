#ifndef PACK_H
#define PACK_H

#include <stdio.h>
#include <stdint.h>

/*
 * bytestring structure, provides a convenient way of handling byte string data.
 * It is essentially an unsigned char pointer that track the position of the
 * last written byte and the total size of the bystestring
 */
struct bytestring
{
    size_t size;
    size_t last;
    unsigned char *data;
};

/*
 * const struct bytestring constructor, it require a size cause we use a bounded
 * bytestring, e.g. no resize over a defined size
 */
struct bytestring *bytestring_create(size_t);

void bytestring_init(struct bytestring *, size_t);

void bytestring_release(struct bytestring *);

void bytestring_reset(struct bytestring *);

void htonll(uint8_t *, uint_least64_t);

uint_least64_t ntohll(const uint8_t *);

/* Reading data on const uint8_t pointer */
// bytes -> uint8_t
uint8_t unpack_u8(const uint8_t **);

// bytes -> uint16_t
uint16_t unpack_u16(const uint8_t **);

// bytes -> uint32_t
uint32_t unpack_u32(const uint8_t **);

// bytes -> uint64_t
uint64_t unpack_u64(const uint8_t **);

// read a defined len of bytes
uint8_t *unpack_bytes(const uint8_t **, size_t, uint8_t *);

/* Write data on const uint8_t pointer */
// append a uint8_t -> bytes into the bytestring
void pack_u8(uint8_t **, uint8_t);

// append a uint16_t -> bytes into the bytestring
void pack_u16(uint8_t **, uint16_t);

// append a uint32_t -> bytes into the bytestring
void pack_u32(uint8_t **, uint32_t);

// append a uint64_t -> bytes into the bytestring
void pack_u64(uint8_t **, uint64_t);

// append len bytes into the bytestring
void pack_bytes(uint8_t **, uint8_t *);

#endif