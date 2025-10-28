#include <cstdlib>

#include "hw09.h"
#include "gtest/gtest.h"
#include "gtest/gtest_prod.h"

namespace cppclass
{
class BasicBinarySearchTreeTest : public ::testing::Test
{
protected:
    BasicBinarySearchTreeTest()
    {
    }

    virtual ~BasicBinarySearchTreeTest()
    {
    }

    virtual void SetUp()
    {
        auto seed_gen = testing::UnitTest::GetInstance();
        int seed = seed_gen->random_seed();
        std::srand(seed);
        printf("seed: %i\n", seed);
    }

    virtual void TearDown()
    {
    }
};

TEST_F(BasicBinarySearchTreeTest, DefaultConstructor)
{
    BinarySearchTree<int> bst;
    EXPECT_EQ(bst.m_root, nullptr);
    EXPECT_EQ(bst.m_size, 0);
}

TEST_F(BasicBinarySearchTreeTest, GetSizeWithMutating)
{
    BinarySearchTree<int> bst;
    EXPECT_EQ(bst.size(), 0);

    bst.m_size = 200;
    EXPECT_EQ(bst.size(), 200);

    bst.m_size = 0;
    EXPECT_EQ(bst.size(), 0);
}

TEST_F(BasicBinarySearchTreeTest, Insert)
{
    BinarySearchTree<int> bst;
    EXPECT_TRUE(bst.insert(1));
    EXPECT_TRUE(bst.insert(2));
    EXPECT_TRUE(bst.insert(3));
    EXPECT_TRUE(bst.insert(4));
    EXPECT_TRUE(bst.insert(5));

    // inserting duplicates
    EXPECT_FALSE(bst.insert(4));
    EXPECT_FALSE(bst.insert(5));
}

TEST_F(BasicBinarySearchTreeTest, TreeValidation)
{
    int arr[] = { 2, 3, 4, 5, 6, 7, 8 };
    BinarySearchTree<int> bst(arr, sizeof(arr) / sizeof(*arr));

    EXPECT_TRUE(bst.isValid());
    ASSERT_EQ(bst.size(), 7);

    bst.m_root->left->right->data = 9;
    EXPECT_FALSE(bst.isValid());

    bst.m_root->left->right->data = 4;
    EXPECT_TRUE(bst.isValid());

    bst.m_root->right->left->data = 4;
    EXPECT_FALSE(bst.isValid());

    bst.m_root->right->left->data = 6;
    EXPECT_TRUE(bst.isValid());

    BinarySearchTree<int> empty_bst;
    EXPECT_TRUE(empty_bst.size() == 0);
    EXPECT_TRUE(empty_bst.isValid());
}

TEST_F(BasicBinarySearchTreeTest, Contains)
{
    BinarySearchTree<int> bst;
    for (int i = 0; i < 5; i++)
    {
        bst.insert(i + 1);
    }

    EXPECT_TRUE(bst.contains(5));
    EXPECT_TRUE(bst.contains(4));
    EXPECT_TRUE(bst.contains(3));
    EXPECT_TRUE(bst.contains(2));
    EXPECT_TRUE(bst.contains(1));

    EXPECT_FALSE(bst.contains(0));
    EXPECT_FALSE(bst.contains(6));
}

TEST_F(BasicBinarySearchTreeTest, ArrayConstructor)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    BinarySearchTree<int> bst(arr, sizeof(arr) / sizeof(*arr));
    EXPECT_EQ(bst.size(), 5);
    EXPECT_EQ(bst.m_root->data, 3);

    EXPECT_TRUE(bst.contains(1));
    EXPECT_TRUE(bst.contains(2));
    EXPECT_TRUE(bst.contains(3));
    EXPECT_TRUE(bst.contains(4));
    EXPECT_TRUE(bst.contains(5));
    EXPECT_TRUE(bst.isValid());
}

TEST_F(BasicBinarySearchTreeTest, CopyConstructor)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    BinarySearchTree<int> src(arr, sizeof(arr) / sizeof(*arr));

    BinarySearchTree<int> bst(src);
    EXPECT_EQ(bst.size(), src.size());
    EXPECT_TRUE(bst.m_root->data == src.m_root->data);
    EXPECT_TRUE(bst.isValid());
    EXPECT_TRUE(src.isValid());
}

TEST_F(BasicBinarySearchTreeTest, MoveConstructor)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    BinarySearchTree<int> src(arr, sizeof(arr) / sizeof(*arr));
    EXPECT_EQ(src.size(), 5);
    EXPECT_EQ(src.m_root->data, 3);
    EXPECT_TRUE(src.isValid());
    auto p_src_root = src.m_root;

    BinarySearchTree<int> bst(std::move(src));
    EXPECT_EQ(bst.size(), 5);
    EXPECT_EQ(bst.m_root->data, 3);
    EXPECT_EQ(src.size(), 0);
    EXPECT_EQ(src.m_root, nullptr);
    EXPECT_EQ(p_src_root, bst.m_root);
    EXPECT_TRUE(bst.isValid());
}

TEST_F(BasicBinarySearchTreeTest, Remove)
{
    int arr[] = { 5, 3, 7, 2, 4, 6, 8 };
    BinarySearchTree<int> bst(arr, sizeof(arr) / sizeof(*arr));
    EXPECT_EQ(bst.size(), 7);

    // leaf node deletion
    EXPECT_TRUE(bst.remove(2));
    EXPECT_EQ(bst.size(), 6);
    EXPECT_FALSE(bst.contains(2));
    EXPECT_TRUE(bst.isValid());

    // one child
    EXPECT_TRUE(bst.remove(3));
    EXPECT_EQ(bst.size(), 5);
    EXPECT_FALSE(bst.contains(3));
    EXPECT_TRUE(bst.isValid());

    // two children
    EXPECT_TRUE(bst.remove(5));
    EXPECT_EQ(bst.size(), 4);
    EXPECT_FALSE(bst.contains(5));
    EXPECT_TRUE(bst.isValid());

    EXPECT_FALSE(bst.remove(10));
    EXPECT_EQ(bst.size(), 4);
    EXPECT_TRUE(bst.isValid());

    BinarySearchTree<int> empty_bst;
    EXPECT_FALSE(empty_bst.remove(123));
}

class BinarySearchTreeTest : public BasicBinarySearchTreeTest
{
protected:
    BinarySearchTree<int> *p_bst;

    BinarySearchTreeTest()
    {
    }

    virtual ~BinarySearchTreeTest()
    {
    }

    virtual void SetUp()
    {
        BasicBinarySearchTreeTest::SetUp();
        std::srand(std::time(0));

        int arr[255];
        for (int i = 0; i < 255; i++)
        {
            arr[i] = std::rand() % 255;
        }

        p_bst = new BinarySearchTree<int>(arr, sizeof(arr) / sizeof(*arr));
    }

    virtual void TearDown()
    {
        BasicBinarySearchTreeTest::TearDown();

        delete p_bst;
    }
};

TEST_F(BinarySearchTreeTest, ACID)
{
    while (p_bst->size() != 0)
    {
        p_bst->remove(std::rand() % 255);
        EXPECT_TRUE(p_bst->isValid());
    }

    for (int i = 0; i < 255; i++)
    {
        p_bst->insert(std::rand() % 255);
        EXPECT_TRUE(p_bst->isValid());
    }

    while (p_bst->size() != 0)
    {
        p_bst->remove(std::rand() % 255);
        EXPECT_TRUE(p_bst->isValid());
    }

    for (int i = 0; i < 255; i++)
    {
        p_bst->insert(std::rand() % 255);
        EXPECT_TRUE(p_bst->isValid());
    }
}

class MultiBinarySearchTreeTest : public BasicBinarySearchTreeTest
{
protected:
    BinarySearchTree<int> *p_bst_first;
    BinarySearchTree<int> *p_bst_second;
    BinarySearchTree<int> *p_bst_first_copy;

    MultiBinarySearchTreeTest()
    {
    }

    virtual ~MultiBinarySearchTreeTest()
    {
    }

    virtual void SetUp()
    {
        int first_arr[] = { 5, 3, 7, 2, 4, 6, 8 };
        int second_arr[] = { 1, 2, 3, 4, 5, 6, 7 };

        p_bst_first = new BinarySearchTree<int>(
            first_arr, sizeof(first_arr) / sizeof(*first_arr));

        p_bst_first_copy = new BinarySearchTree<int>(*p_bst_first);

        p_bst_second = new BinarySearchTree<int>(
            second_arr, sizeof(second_arr) / sizeof(*second_arr));
    }

    virtual void TearDown()
    {
        BasicBinarySearchTreeTest::TearDown();

        delete p_bst_first;
        delete p_bst_second;
        delete p_bst_first_copy;
    }
};

TEST_F(MultiBinarySearchTreeTest, SetUp)
{
    EXPECT_EQ(p_bst_first->size(), 7);
    EXPECT_EQ(p_bst_second->size(), 7);
}

TEST_F(MultiBinarySearchTreeTest, NotEqual)
{
    EXPECT_TRUE(*p_bst_first != *p_bst_second);
}

TEST_F(MultiBinarySearchTreeTest, Equal)
{
    EXPECT_TRUE(*p_bst_first == *p_bst_first_copy);
    EXPECT_FALSE(*p_bst_first == *p_bst_second);
}
}
