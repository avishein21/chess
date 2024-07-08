#include "acutest.h"
#include "util.h"

void test_add(){
    TEST_CHECK_(add(2,2) == 4, "added %d and %d to %d", 2, 2, 4);
}

TEST_LIST = {
    {"int adding", test_add},
    {0}
};
