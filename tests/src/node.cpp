#include "gtest/gtest.h"
#include "node.h"

using namespace std;

Node getOneDimensionalTestNode()
{
    Node oneDimensionalNode = Node();
    return oneDimensionalNode;
}

TEST(nodetest, test_initial_state) {
    Node adam = getOneDimensionalTestNode();
    ASSERT_EQ(nullptr, adam.getRightPtr());
    ASSERT_EQ(nullptr, adam.getLeftPtr());
}

TEST(nodetest, test_double_linked) {
    /**
     * Initial node status
     *
     * null <- adam -> null
     * null <- betty -> null
     */
    Node adam = getOneDimensionalTestNode();
    Node betty = getOneDimensionalTestNode();

    Node *bettyPtr = &betty;

    /**
     * New node status
     *
     * null <- adam <-> betty -> null
     */
    adam.setRightPtr(bettyPtr);

    ASSERT_EQ(nullptr, adam.getLeftPtr());
    ASSERT_EQ(&betty, adam.getRightPtr());

    ASSERT_EQ(&adam, betty.getLeftPtr());
    ASSERT_EQ(nullptr, betty.getRightPtr());

    /**
     * Break the link
     */
    betty.setLeftPtr(nullptr);

    ASSERT_EQ(nullptr, adam.getRightPtr());
    ASSERT_EQ(nullptr, betty.getLeftPtr());
}

TEST(nodetest, test_replace_node) {

    /**
     * Initial node status
     *
     * null <- adam -> null
     * null <- betty -> null
     * null <- charlie -> null
     */
    Node adam = getOneDimensionalTestNode();
    Node betty = getOneDimensionalTestNode();
    Node charlie = getOneDimensionalTestNode();

    Node *adamPtr = &adam;
    Node *bettyPtr = &betty;
    Node *charliePtr = &charlie;

    /**
     * New node status
     *
     * null <- adam <-> betty -> null
     * null <- charlie -> null
     */
    adam.setRightPtr(bettyPtr);
    ASSERT_EQ(bettyPtr, adam.getRightPtr());
    ASSERT_EQ(adamPtr, betty.getLeftPtr());

    /**
     * New node status
     * null <- adam -> null
     * null <- charlie <-> betty -> null
     */
    betty.setLeftPtr(charliePtr);

    ASSERT_EQ(nullptr, adam.getLeftPtr());
    ASSERT_EQ(nullptr, adam.getRightPtr());

    ASSERT_EQ(charliePtr, betty.getLeftPtr());
    ASSERT_EQ(nullptr, betty.getRightPtr());

    ASSERT_EQ(nullptr, charlie.getLeftPtr());
    ASSERT_EQ(bettyPtr, charlie.getRightPtr());
}
