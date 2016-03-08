#include "gtest/gtest.h"
#include "node.h"

using namespace std;

TEST(nodetest, test_double_linked) {

    /**
     * Initial node status
     *
     * null <- adam -> null
     * null <- betty -> null
     */
    Node adam;
    Node betty;

    ASSERT_EQ(nullptr, adam.getRightPtr());
    ASSERT_EQ(nullptr, adam.getLeftPtr());
    ASSERT_EQ(nullptr, betty.getRightPtr());
    ASSERT_EQ(nullptr, betty.getLeftPtr());

    /**
     * New node status
     *
     * null <- adam <-> betty -> null
     *
     * By setting betty to the right of adam,
     * we implicitly set adam to the left of betty
     *
     */
    Node*bettyPtr = &betty;
    Node*adamPtr = &adam;
    adam.setRightPtr(bettyPtr);

    ASSERT_EQ(nullptr, adam.getLeftPtr());
    ASSERT_EQ(bettyPtr, adam.getRightPtr());

    ASSERT_EQ(adamPtr, betty.getLeftPtr());
    ASSERT_EQ(nullptr, betty.getRightPtr());
}
