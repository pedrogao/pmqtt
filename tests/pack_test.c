#include "minunit.h"
#include "pack.h"

MU_TEST(test_pack)
{
    bytestring *name = bytestring_create(10);
    pack_u8(name, 'p');
    mu_assert_int_eq(name->last, 1);
    pack_u16(name, (uint16_t)'e');
    mu_assert_int_eq(name->last, 3);
    pack_u32(name, (uint32_t)'o');
    mu_assert_int_eq(name->last, 7);

    name->last = 0;
    uint8_t p = unpack_u8(name);
    mu_assert_int_eq(p, 'p');
    uint16_t e = unpack_u16(name);
    mu_assert_int_eq(e, 'e');
    uint32_t o = unpack_u32(name);
    mu_assert_int_eq(o, 'o');

    bytestring_release(name);
}

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_pack);
}

int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}