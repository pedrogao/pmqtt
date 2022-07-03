#ifndef PACK_H
#define PACK_H

#include <stdio.h>
#include <stdint.h>

/*
 * bytestring structure, provides a convenient way of handling byte string data.
 * It is essentially an unsigned char pointer that track the position of the
 * last written byte and the total size of the bystestring
 */
typedef struct _bytestring
{
    size_t size;
    size_t last;
    unsigned char *data;
} bytestring;

/*
 * struct bytestring constructor, it require a size cause we use a bounded
 * bytestring, e.g. no resize over a defined size
 */
bytestring *bytestring_create(size_t);

void bytestring_init(bytestring *, size_t);

void bytestring_release(bytestring *);

void bytestring_reset(bytestring *);

void htonll(uint8_t *, uint_least64_t);

uint_least64_t ntohll(const uint8_t *);

/* Reading data on struct bytestring pointer */
// bytes -> uint8_t
uint8_t unpack_u8(bytestring *);

// bytes -> uint16_t
uint16_t unpack_u16(bytestring *);

// bytes -> uint32_t
uint32_t unpack_u32(bytestring *);

// bytes -> uint64_t
uint64_t unpack_u64(bytestring *);

// read a defined len of bytes
uint8_t *unpack_bytes(bytestring *, size_t, uint8_t *);

/* Write data on struct bytestring pointer */
// append a uint8_t -> bytes into the bytestring
void pack_u8(bytestring *, uint8_t);

// append a uint16_t -> bytes into the bytestring
void pack_u16(bytestring *, uint16_t);

// append a uint32_t -> bytes into the bytestring
void pack_u32(bytestring *, uint32_t);

// append a uint64_t -> bytes into the bytestring
void pack_u64(bytestring *, uint64_t);

// append len bytes into the bytestring
void pack_bytes(bytestring *, uint8_t *);

#endif // PACK_H