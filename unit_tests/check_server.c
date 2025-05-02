#include <stdlib.h>
#include <check.h>

#include "server.h"

START_TEST(test_handle_method_get)
{
    const char *http_request = "GET HTTP/1.1 /";

    int method_code = handle_method(http_request);

    ck_assert_int_eq(method_code, GET_METHOD);
}
END_TEST

START_TEST(test_handle_method_head)
{
    const char *http_request = "HEAD HTTP/1.1 /";

    int method_code = handle_method(http_request);

    ck_assert_int_eq(method_code, HEAD_METHOD);
}
END_TEST

START_TEST(test_handle_method_not_allowed)
{
    const char *http_request = "POST HTTP/1.1 /";

    int method_code = handle_method(http_request);

    ck_assert_int_eq(method_code, NOT_ALLOWED_METHOD);
}
END_TEST

START_TEST(test_parse_extension_3_chars)
{
    const char *filename = "/root/assets/images/photo.png";
    char extension[5] = {'\0'};

    size_t extension_len = parse_extension(filename, extension);

    ck_assert_str_eq(extension, "png");
    ck_assert_uint_eq(extension_len, 3);
}
END_TEST

START_TEST(test_parse_extension_4_chars)
{
    const char *filename = "/page.html";
    char extension[5] = {'\0'};

    size_t extension_len = parse_extension(filename, extension);

    ck_assert_str_eq(extension, "html");
    ck_assert_uint_eq(extension_len, 4);
}
END_TEST

START_TEST(test_parse_extension_no_ext)
{
    const char *filename = "/root/assets/images/photo";
    char extension[5] = {'\0'};

    size_t extension_len = parse_extension(filename, extension);

    ck_assert_str_eq(extension, "");
    ck_assert_uint_eq(extension_len, 0);
}
END_TEST

Suite *server_suite(void)
{
    Suite *suite = suite_create("Server");
    
    TCase *tc_handle_method = tcase_create("Handle method");
    TCase *tc_parse_extension = tcase_create("Parse extension");

    tcase_add_test(tc_handle_method, test_handle_method_get);
    tcase_add_test(tc_handle_method, test_handle_method_head);
    tcase_add_test(tc_handle_method, test_handle_method_not_allowed);

    tcase_add_test(tc_parse_extension, test_parse_extension_3_chars);
    tcase_add_test(tc_parse_extension, test_parse_extension_4_chars);
    tcase_add_test(tc_parse_extension, test_parse_extension_no_ext);
    
    suite_add_tcase(suite, tc_handle_method);
    suite_add_tcase(suite, tc_parse_extension);

    return suite;
}

int main(void)
{
    int failed_tests = 0;
    Suite *suite = server_suite();
    SRunner *suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_NORMAL);
    failed_tests = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
    
    if (failed_tests == 0)
    {
        return EXIT_SUCCESS;
    }
        
    return EXIT_FAILURE;
}
