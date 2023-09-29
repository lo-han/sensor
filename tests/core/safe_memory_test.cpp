#include <gtest/gtest.h>

extern "C"
{
#include <safe_memory.h>
}

#define BUFFER_SIZE 10

TEST(safe_malloc, successful_allocation)
{
    char *test_buffer = NULL;
    safe_malloc((void **)&test_buffer, BUFFER_SIZE);

    ASSERT_EQ((test_buffer != NULL), true);

    safe_free_alloc((void **)&test_buffer, BUFFER_SIZE);
}

TEST(safe_free_alloc, successful_deallocation)
{
    char *test_buffer = NULL;
    safe_malloc((void **)&test_buffer, BUFFER_SIZE);

    ASSERT_EQ((test_buffer != NULL), true);

    safe_free_alloc((void **)&test_buffer, BUFFER_SIZE);
    ASSERT_EQ((test_buffer == NULL), true);
}

TEST(safe_free_alloc, successful_deallocation_with_null_pointer)
{
    char *test_buffer = NULL;

    safe_free_alloc((void **)&test_buffer, BUFFER_SIZE);
    ASSERT_EQ((test_buffer == NULL), true);
}
