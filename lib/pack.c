#include <string.h>
#include <arpa/inet.h>
#include "pack.h"
#include "util.h"

bytestring *bytestring_create(size_t len)
{
    bytestring *bstring = sol_malloc(sizeof(bytestring));
    bytestring_init(bstring, len);
    return bstring;
}

void bytestring_init(bytestring *bstring, size_t size)
{
    if (!bstring)
        return;
    bstring->size = size;
    bstring->data = sol_malloc(sizeof(unsigned char) * size);
    bytestring_reset(bstring);
}

void bytestring_release(bytestring *bstring)
{
    if (!bstring)
        return;
    sol_free(bstring->data); // free data first
    sol_free(bstring);
}

void bytestring_reset(bytestring *bstring)
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
    return (uint_least64_t)block[0] << 56 | (uint_least64_t)block[1] << 48 |
           (uint_least64_t)block[2] << 40 | (uint_least64_t)block[3] << 32 |
           (uint_least64_t)block[4] << 24 | (uint_least64_t)block[5] << 16 |
           (uint_least64_t)block[6] << 8 | (uint_least64_t)block[7] << 0;
}

// Reading data
uint8_t unpack_u8(bytestring *bstring)
{

    if ((bstring->last + sizeof(uint8_t)) > bstring->size)
        return 0;

    uint8_t val = *(bstring->data + bstring->last);
    bstring->last += sizeof(uint8_t);

    return val;
}

uint16_t unpack_u16(bytestring *bstring)
{

    if ((bstring->last + sizeof(uint16_t)) > bstring->size)
        return 0;

    uint16_t tmp;
    memcpy(&tmp, bstring->data + bstring->last, sizeof(uint16_t));
    // uint16_t val = ntohs(*((uint16_t *)(bstring->data + bstring->last)));
    uint16_t val = ntohs(tmp);
    bstring->last += sizeof(uint16_t);

    return val;
}

uint32_t unpack_u32(bytestring *bstring)
{

    if ((bstring->last + sizeof(uint32_t)) > bstring->size)
        return 0;

    uint32_t tmp;
    memcpy(&tmp, bstring->data + bstring->last, sizeof(uint32_t));

    // uint32_t val = ntohl(*((uint32_t *)(bstring->data + bstring->last)));
    uint32_t val = ntohl(tmp);
    bstring->last += sizeof(uint32_t);

    return val;
}

uint64_t unpack_u64(bytestring *bstring)
{

    if ((bstring->last + sizeof(uint64_t)) > bstring->size)
        return 0;

    uint64_t val = ntohll(bstring->data + bstring->last);
    bstring->last += sizeof(uint64_t);

    return val;
}

uint8_t *unpack_bytes(bytestring *bstring, size_t len, uint8_t *str)
{

    if (bstring->last == bstring->size)
        return NULL;

    memcpy(str, bstring->data + bstring->last, len);
    str[len] = '\0';
    bstring->last += len;

    return str;
}

// Write data
void pack_u8(bytestring *bstring, uint8_t val)
{

    if ((bstring->last + sizeof(uint8_t)) > bstring->size)
        return;

    *(bstring->data + bstring->last) = val;
    bstring->last += sizeof(uint8_t);
}

void pack_u16(bytestring *bstring, uint16_t val)
{

    if ((bstring->last + sizeof(uint16_t)) > bstring->size)
        return;
    uint16_t tmp = htons(val);
    memcpy(bstring->data + bstring->last, &tmp, sizeof(uint16_t));
    // *((uint16_t *)(bstring->data + bstring->last)) = htons(val);
    bstring->last += sizeof(uint16_t);
}

void pack_u32(bytestring *bstring, uint32_t val)
{

    if ((bstring->last + sizeof(uint32_t)) > bstring->size)
        return;

    uint32_t tmp = htonl(val);
    memcpy(bstring->data + bstring->last, &tmp, sizeof(uint32_t));

    // *((uint32_t *)(bstring->data + bstring->last)) = htonl(val);
    bstring->last += sizeof(uint32_t);
}

void pack_u64(bytestring *bstring, uint64_t val)
{

    if ((bstring->last + sizeof(uint64_t)) > bstring->size)
        return;

    htonll(bstring->data + bstring->last, val);
    bstring->last += sizeof(uint64_t);
}

void pack_bytes(bytestring *bstring, uint8_t *str)
{

    size_t len = strlen((char *)str);
    if ((bstring->last + len) > bstring->size)
        return;

    memcpy(bstring->data + bstring->last, str, len);
    bstring->last += len;
}