#include "FibonacciHeap.h"
#include <UnitTest++/UnitTest++.h>
#include <random>
#include <iostream>

using namespace ipd;


TEST(New_is_empty) {
    FibonacciHeap<int> fh;
    CHECK(fh.empty());
}

TEST(One_elt_constructor) {
    FibonacciHeap<int> fh(1);
    CHECK_EQUAL(1, fh.size());
    CHECK_EQUAL(false, fh.empty());
}

TEST(Insert) {
    FibonacciHeap<int> fh;
    CHECK(fh.empty());
    fh.insert(5);
    CHECK_EQUAL(1, fh.size());
    CHECK_EQUAL(5, fh.minimum());
}

TEST(1_1_Union) {
    FibonacciHeap<int> fh1(1);
    FibonacciHeap<int> fh2(2);
    fh2.merge(fh1);

    CHECK_EQUAL(2, fh2.size());
    CHECK_EQUAL(1, fh2.minimum());
}

TEST(3_4_Union) {
    FibonacciHeap<int> fh1{3, 5, 8};
    FibonacciHeap<int> fh2{2, 4, 9, 13};
    fh1.merge(fh2);

    CHECK_EQUAL(4, fh2.size());
    CHECK_EQUAL(7, fh1.size());
    CHECK_EQUAL(2, fh1.minimum());
}


TEST(insert_increases_size) {
    FibonacciHeap<int> h;

    h.insert(5);
    CHECK(!h.empty());
    CHECK_EQUAL(1, h.size());

    h.insert(6);
    CHECK(!h.empty());
    CHECK_EQUAL(2, h.size());
}

TEST(insert_changes_min) {
    FibonacciHeap<int> h;

    h.insert(5);
    CHECK_EQUAL(5, h.minimum());

    h.insert(6);
    CHECK_EQUAL(5, h.minimum());

    h.insert(3);
    CHECK_EQUAL(3, h.minimum());

    h.insert(1);
    CHECK_EQUAL(1, h.minimum());

    h.insert(2);
    CHECK_EQUAL(1, h.minimum());
}

TEST(Remove_Min) {
    FibonacciHeap<int> h;

    h.insert(5);
    CHECK_EQUAL(5, h.minimum());

    h.insert(6);
    CHECK_EQUAL(5, h.minimum());

    h.insert(3);
    CHECK_EQUAL(3, h.minimum());

    h.insert(1);
    CHECK_EQUAL(1, h.minimum());

    h.insert(2);
    CHECK_EQUAL(1, h.minimum());

    h.insert(0);
    CHECK_EQUAL(0, h.minimum());


    h.remove_min();
    CHECK_EQUAL(1, h.minimum());

    h.remove_min();
    CHECK_EQUAL(2, h.minimum());

    h.remove_min();
    CHECK_EQUAL(3, h.minimum());

    CHECK_EQUAL(3, h.extract_min());

}

TEST(Remove_changes_min) {
    FibonacciHeap<int> h;

    h.insert(5);
    h.insert(6);
    h.insert(7);
    h.insert(8);
    h.insert(9);
    h.insert(10);

    CHECK_EQUAL(5, h.minimum());
    h.remove_min();
    CHECK_EQUAL(6, h.minimum());
    h.remove_min();
    CHECK_EQUAL(7, h.minimum());
    h.remove_min();
    CHECK_EQUAL(8, h.minimum());
    h.remove_min();
    CHECK_EQUAL(9, h.minimum());
    h.remove_min();
    CHECK_EQUAL(10, h.minimum());
    h.remove_min();
    CHECK(h.empty());
}


TEST(Many_insertions) {
    FibonacciHeap<size_t> h;

    for (size_t i = 1000; i >= 1; --i) {
        h.insert(i);
    }

    for (size_t i = 1; i <= 1000; ++i) {
        CHECK_EQUAL(i, h.minimum());
        h.remove_min();
    }
}

TEST(Clear) {
    FibonacciHeap<size_t> h;

    for (size_t i = 1000; i >= 1; --i) {
        h.insert(i);
    }
    CHECK_EQUAL(1000, h.size());

    h.clear();
    CHECK_EQUAL(0, h.size());
}

TEST(Merge) {
    FibonacciHeap<size_t> h1, h2;
    for (size_t i = 0; i < 1000; ++i) {
        if (i % 2 == 0)
            h2.insert(i);
        else
            h1.insert(i);
    }
    h1.merge(h2);

    CHECK_EQUAL(1000, h1.size());

    for (size_t i = 0; i < 1000; ++i) {
        CHECK_EQUAL(i, h1.minimum());
        h1.remove_min();
    }
}

TEST(Repeated) {
    FibonacciHeap<int> h;

    h.insert(1);
    h.insert(1);
    h.insert(1);

    CHECK_EQUAL(3, h.size());

    CHECK_EQUAL(1, h.minimum());
    h.remove_min();
    CHECK_EQUAL(1, h.minimum());
    h.remove_min();
    CHECK_EQUAL(1, h.minimum());
    h.remove_min();

    CHECK(h.empty());
}

TEST(Random) {
    std::mt19937_64 rng;
    rng.seed(std::random_device{}());
    std::uniform_int_distribution<size_t> dist;

    for (int trials = 0; trials < 100; trials++) {
        FibonacciHeap<size_t> h;
        size_t elements = (dist(rng) % 20) + 1;
        for (int i = 0; i < elements; i++) {
            h.insert(dist(rng) % 20);
        }
        size_t prev = h.minimum();
        h.remove_min();
        while (!h.empty()) {
            CHECK(prev <= h.minimum());
            h.remove_min();
        }
    }
}