#include "llist.h"

#include <CUnit/Basic.h>

int
init_suite() {
    return 0;
}

int
clean_suite() {
    return 0;
}

typedef struct {
    int x;
} data_t;

void
test_llist_set() {
    list_item_t* i1 = list_item_new(&(data_t){.x = 1});
    CU_ASSERT_EQUAL(((data_t*)i1->data)->x, 1);

    list_item_t* i2 = list_item_new(&(data_t){.x = 2});
    list_item_t* i3 = list_item_new(&(data_t){.x = 3});
    list_item_t* i4 = list_item_new(&(data_t){.x = 4});

    list_append(i1, i2);
    CU_ASSERT_PTR_NOT_NULL(i1->next);
    CU_ASSERT_PTR_EQUAL(i1->next, i2);

    list_append(i1, i3);
    CU_ASSERT_PTR_EQUAL(i2->next, i3);

    list_append(i1, i4);
    CU_ASSERT_PTR_EQUAL(i3->next, i4);

    list_unlist(i3);
    CU_ASSERT_PTR_NOT_NULL(i3);
    CU_ASSERT_PTR_EQUAL(i2->next, i4);

    list_delete(i2);
    CU_ASSERT_PTR_EQUAL(i1->next, i4);

    free(i1);
    free(i3);
    free(i4);
}

void
test_llist_find() {
}

int main() {
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

   /* add a suite to the registry */
    CU_pSuite pSuite = CU_add_suite("Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(pSuite, "llist_set", test_llist_set)) ||
        (NULL == CU_add_test(pSuite, "llist_find", test_llist_find))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
