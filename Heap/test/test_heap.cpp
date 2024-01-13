#include "heap.h"
#include <gtest/gtest.h>

#include <cstdint>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <queue>


template<class T, class Compare>
void get_heap(std::vector<T>& heap_vector, const heap<T, Compare>& h)
{
    heap_vector.clear();
    heap_vector.resize(h.size());

    h.copy_heap(heap_vector.begin());
}


TEST(HeapInsertPop, MinHeap) 
{
    heap<int32_t, std::greater<int32_t>>  min_heap(std::greater<int32_t>{});
    std::vector<int32_t> heap_vector;

    min_heap.push(0);
    min_heap.push(1);
    min_heap.push(-1);
    min_heap.push(2);
    min_heap.push(-2);

    size_t h_size = min_heap.size();

    ASSERT_EQ(h_size, 5);

    get_heap(heap_vector, min_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::greater<int32_t>{}));
    EXPECT_EQ(min_heap.top(), -2);
    min_heap.pop();
    
    get_heap(heap_vector, min_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::greater<int32_t>{}));
    EXPECT_EQ(min_heap.top(), -1);
    min_heap.pop();

    get_heap(heap_vector, min_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::greater<int32_t>{}));
    EXPECT_EQ(min_heap.top(), 0);
    min_heap.pop();

    get_heap(heap_vector, min_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::greater<int32_t>{}));
    EXPECT_EQ(min_heap.top(), 1);
    min_heap.pop();

    get_heap(heap_vector, min_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::greater<int32_t>{}));
    EXPECT_EQ(min_heap.top(), 2);
    min_heap.pop();

    EXPECT_THROW(min_heap.pop(), std::underflow_error);
}
TEST(HeapInsertPop, MaxHeap) 
{
    heap<int32_t, std::less<int32_t>>  max_heap(std::less<int32_t>{});
    std::vector<int32_t> heap_vector;

    max_heap.push(0);
    max_heap.push(1);
    max_heap.push(-1);
    max_heap.push(2);
    max_heap.push(-2);

    size_t h_size = max_heap.size();

    ASSERT_EQ(h_size, 5);

    get_heap(heap_vector, max_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::less<int32_t>{}));
    EXPECT_EQ(max_heap.top(), 2);
    max_heap.pop();
    
    get_heap(heap_vector, max_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::less<int32_t>{}));
    EXPECT_EQ(max_heap.top(), 1);
    max_heap.pop();

    get_heap(heap_vector, max_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::less<int32_t>{}));
    EXPECT_EQ(max_heap.top(), 0);
    max_heap.pop();

    get_heap(heap_vector, max_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::less<int32_t>{}));
    EXPECT_EQ(max_heap.top(), -1);
    max_heap.pop();

    get_heap(heap_vector, max_heap);
    EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::less<int32_t>{}));
    EXPECT_EQ(max_heap.top(), -2);
    max_heap.pop();

    EXPECT_THROW(max_heap.pop(), std::underflow_error);
}


TEST(HeapRandomInsertPop, MinHeap)
{
    heap<int32_t, std::greater<int32_t>> min_heap(std::greater<int32_t>{});
    std::vector<int32_t> heap_vector;

    srand(time(NULL));

    const size_t N = 100;

    for (size_t i = 0; i < N; ++i)
    {
        size_t op = rand() % 2;

        switch (op)
        {
        case 0: // push
        {
            int32_t value = rand();

            min_heap.push(value);
            get_heap(heap_vector, min_heap);

            EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::greater<int32_t>{}));

            break;
        }
        case 1: // pop
        {
            if (min_heap.empty())
                EXPECT_THROW(min_heap.pop(), std::underflow_error);
            else
            {
                min_heap.pop();
                get_heap(heap_vector, min_heap);
                
                EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::greater<int32_t>{}));
            }

            break;
        }
        }
    }
}
TEST(HeapRandomInsertPop, MaxHeap)
{
    heap<int32_t, std::less<int32_t>> max_heap(std::less<int32_t>{});
    std::vector<int32_t> heap_vector;

    srand(time(NULL));

    const size_t N = 100;

    for (size_t i = 0; i < N; ++i)
    {
        size_t op = rand() % 2;

        switch (op)
        {
        case 0: // push
        {
            int32_t value = rand();

            max_heap.push(value);
            get_heap(heap_vector, max_heap);

            EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::less<int32_t>{}));

            break;
        }
        case 1: // pop
        {
            if (max_heap.empty())
                EXPECT_THROW(max_heap.pop(), std::underflow_error);
            else
            {
                max_heap.pop();
                get_heap(heap_vector, max_heap);
                
                EXPECT_TRUE(std::is_heap(heap_vector.begin(), heap_vector.end(), std::less<int32_t>{}));
            }

            break;
        }
        }
    }
}


TEST(PriorityQueueRandomInsertPop, MinHeap)
{
    heap<int32_t, std::greater<int32_t>> min_heap(std::greater<int32_t>{});
    std::priority_queue<int32_t, std::vector<int32_t>, std::greater<int32_t>> pr_queue;

    srand(time(NULL));

    const size_t N = 100;

    for (size_t i = 0; i < N; ++i)
    {
        size_t op = rand() % 2;

        switch (op)
        {
        case 0: // push
        {
            int32_t value = rand();

            min_heap.push(value);
            pr_queue.push(value);

            EXPECT_EQ(min_heap.top(), pr_queue.top());
            EXPECT_EQ(min_heap.size(), pr_queue.size());

            break;
        }
        case 1: // pop
        {
            if (min_heap.empty())
            {
                EXPECT_THROW(min_heap.pop(), std::underflow_error);
                EXPECT_TRUE(pr_queue.empty());
            }
            else
            {
                min_heap.pop();
                pr_queue.pop();

                if(!min_heap.empty())
                {
                    EXPECT_EQ(min_heap.top(), pr_queue.top());
                    EXPECT_EQ(min_heap.size(), pr_queue.size());
                }
                else
                    EXPECT_TRUE(pr_queue.empty());
            }

            break;
        }
        }
    }
}
TEST(PriorityQueueRandomInsertPop, MaxHeap)
{
    heap<int32_t, std::less<int32_t>> max_heap(std::less<int32_t>{});
    std::priority_queue<int32_t, std::vector<int32_t>, std::less<int32_t>> pr_queue;

    srand(time(NULL));

    const size_t N = 100;

    for (size_t i = 0; i < N; ++i)
    {
        size_t op = rand() % 2;

        switch (op)
        {
        case 0: // push
        {
            int32_t value = rand();

            max_heap.push(value);
            pr_queue.push(value);

            EXPECT_EQ(max_heap.top(), pr_queue.top());
            EXPECT_EQ(max_heap.size(), pr_queue.size());

            break;
        }
        case 1: // pop
        {
            if (max_heap.empty())
            {
                EXPECT_THROW(max_heap.pop(), std::underflow_error);
                EXPECT_TRUE(pr_queue.empty());
            }
            else
            {
                max_heap.pop();
                pr_queue.pop();

                if(!max_heap.empty())
                {
                    EXPECT_EQ(max_heap.top(), pr_queue.top());
                    EXPECT_EQ(max_heap.size(), pr_queue.size());
                }
                else
                    EXPECT_TRUE(pr_queue.empty());
            }

            break;
        }
        }
    }
}

TEST(Fail, TestFail)
{
    FAIL();
}