#include <string.h>
#include <arpa/inet.h>
#include "pack.h"
#include "util.h"

struct bytestring *bytestring_create(size_t len)
{
    struct bytestring *bstring = p_malloc(sizeof(*bstring));
    bytestring_init(bstring, len);
    return bstring;
}

void bytestring_init(struct bytestring *bstring, size_t size)
{
    if (!bstring)
        return;
    bstring->size = size;
    bstring->data = p_malloc(sizeof(unsigned char) * size);
    bytestring_reset(bstring);
}

void bytestring_release(struct bytestring *bstring)
{
    if (!bstring)
        return;
    p_free(bstring->data);
    p_free(bstring);
}

void bytestring_reset(struct bytestring *bstring)
{
    if (!bstring)
        return;
    bstring->last = 0;
    memset(bstring->data, 0, bstring->size);
}

/* Host-to-network (native endian to big endian) */
void htonll(uint8_t *block, uint_least64_t num)
{
    block[0] = num >> 56 & 0xFF;
    block[1] = num >> 48 & 0xFF;
    block[2] = num >> 40 & 0xFF;
    block[3] = num >> 32 & 0xFF;
    block[4] = num >> 24 & 0xFF;
    block[5] = num >> 16 & 0xFF;
    block[6] = num >> 8 & 0xFF;
    block[7] = num >> 0 & 0xFF;
}

/* Network-to-host (big endian to native endian) */
uint_least64_t ntohll(const uint8_t *block)
{
    return (uint_least64_t)block[0] << 56 | (uint_least64_t)block[1] << 48 | (uint_least64_t)block[2] << 40 | (uint_least64_t)block[3] << 32 | (uint_least64_t)block[4] << 24 | (uint_least64_t)block[5] << 16 | (uint_least64_t)block[6] << 8 | (uint_least64_t)block[7] << 0;
}

// Reading data
uint8_t unpack_u8(const uint8_t **buf)
{
    uint8_t val = **buf;
    (*buf)++;
    return val;
}

uint16_t unpack_u16(const uint8_t **buf)
{
    uint16_t val;
    memcpy(&val, *buf, sizeof(uint16_t));
    (*buf) += sizeof(uint16_t);
    return ntohs(val);
}

uint32_t unpack_u32(const uint8_t **buf)
{
    uint32_t val;
    memcpy(&val, *buf, sizeof(uint32_t));
    (*buf) += sizeof(uint32_t);
    return ntohl(val);
}

uint64_t unpack_u64(const uint8_t **buf)
{
    uint64_t val = ntohll(*buf);
    (*buf) += sizeof(uint64_t);
    return val;
}

uint8_t *unpack_bytes(const uint8_t **buf, size_t len, uint8_t *str)
{

    memcpy(str, *buf, len);
    str[len] = '\0';
    (*buf) += len;

    return str;
}

// Write data
void pack_u8(uint8_t **buf, uint8_t val)
{
    **buf = val;
    (*buf) += sizeof(uint8_t);
}

void pack_u16(uint8_t **buf, uint16_t val)
{
    uint16_t htonsval = htons(val);
    memcpy(*buf, &htonsval, sizeof(uint16_t));
    (*buf) += sizeof(uint16_t);
}

void pack_u32(uint8_t **buf, uint32_t val)
{
    uint32_t htonlval = htonl(val);
    memcpy(*buf, &htonlval, sizeof(uint32_t));
    (*buf) += sizeof(uint32_t);
}

void pack_u64(uint8_t **buf, uint64_t val)
{
    htonll(*buf, val);
    (*buf) += sizeof(uint64_t);
}

void pack_bytes(uint8_t **buf, uint8_t *str)
{

    size_t len = strlen((char *)str);

    memcpy(*buf, str, len);
    (*buf) += len;
}
