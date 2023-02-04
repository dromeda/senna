#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_make_requests(void)
{
    char *address = "https://www.google.com";
    int quantity = 2;
    struct RequestData data[quantity];
    make_requests(address, quantity, data);

    CU_ASSERT_NOT_EQUAL(data[0].response_code, 0);
    CU_ASSERT_NOT_EQUAL(data[0].response_time, 0.0);
    CU_ASSERT_NOT_EQUAL(data[1].response_code, 0);
    CU_ASSERT_NOT_EQUAL(data[1].response_time, 0.0);
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Test Suite", NULL, NULL);

    CU_add_test(suite, "test_make_requests", test_make_requests);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
