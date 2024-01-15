#include "splay_tree.h"
#include <gtest/gtest.h>

#include <map>
#include <queue>
#include <cstdint>
#include <ctime>
#include <cstdlib>


TEST(SplayTreeRandomInsertExctract, StdMap)
{
    splay_tree<int32_t, int32_t> test_tree;
    std::map<int32_t, int32_t> std_tree;
    std::queue<std::pair<const int32_t, int32_t>> q;

    srand(time(NULL));

    const size_t N = 100;

    for (size_t i = 0; i < N; ++i)
    {
        size_t op = rand() % 2;

        switch (op)
        {
        case 0: // insert
        {
            std::pair<const int32_t, int32_t> value = std::make_pair(rand() % N/4, rand());

            EXPECT_EQ(test_tree.insert(value).second, std_tree.insert(value).second);
            q.push(value);

            break;
        }
        case 1: // exctract
        {
            if(!q.empty())
            {
                auto x = q.front(); q.pop();

                auto a1 = test_tree.extract(x.first);
                auto a2 = std_tree.extract(x.first);

                if (a1 != splay_tree<int32_t, int32_t>::value_type())
                    EXPECT_EQ(a1.second, a2.mapped());
                    
            }
        }
        }
    }
}