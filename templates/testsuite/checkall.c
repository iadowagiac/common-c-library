#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <console.h>

TCase *create_tcase_for_arrays(void);
TCase *create_tcase_for_tables(void);
TCase *create_tcase_for_stacks(void);
TCase *create_tcase_for_queues(void);

Suite *
create_test_suite(void)
{
    Suite *suite;
    warning(
"\n"
"\n    libcheck has a bug that causes a random segfault to occur upon doing a"
"\n    ck_assert_*. If you get a segfault message, it's mostly likely not my"
"\n    code that's the problem. On my machine, it only occurs about 1/4th of"
"\n    the time, so just rerun the tests and everything should work fine.\n"
"\n");
    suite = suite_create("testsuite");
    suite_add_tcase(suite, create_tcase_for_arrays());
    suite_add_tcase(suite, create_tcase_for_tables());
    suite_add_tcase(suite, create_tcase_for_stacks());
    suite_add_tcase(suite, create_tcase_for_queues());
    return suite;
}

int
main(int argc, char *argv[])
{
    int nfailed;
    Suite *suite;
    SRunner *srunner;

    suite = create_test_suite();

    srunner = srunner_create(suite);
    srunner_run_all(srunner, CK_NORMAL);
    nfailed = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return nfailed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
