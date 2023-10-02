#include <gtest/gtest.h>

extern "C"
{
#include "trigger.h"
#include <stdlib.h>
}

void _do_nothing(void *param)
{
}

TEST(Trigger, doesnt_dump_core_with_null_parameter)
{
    Bool response = Trigger(NULL, NULL);
    ASSERT_TRUE(response == _false);
}

TEST(Trigger, successful_trigger_call)
{
    Bool response = Trigger(_do_nothing, NULL);
    ASSERT_TRUE(response == _true);
}
