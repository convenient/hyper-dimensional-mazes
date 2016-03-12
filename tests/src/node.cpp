#include "gtest/gtest.h"
#include "node.h"

using namespace std;

Node getOneDimensionalTestNode()
{
    Axis* xAxis = new Axis('x');

    Dimensions dimensions;
    dimensions.addAxis(xAxis);

    Node oneDimensionalNode = Node(dimensions);

    return oneDimensionalNode;
}

Node getTwoDimensionalTestNode()
{
    Axis* xAxis = new Axis('x');
    Axis* yAxis = new Axis('y');

    Dimensions dimensions;
    dimensions.addAxis(xAxis);
    dimensions.addAxis(yAxis);

    Node twoDimensionalNode = Node(dimensions);

    return twoDimensionalNode;
}

TEST(nodetest, test_initial_state) {
    Node adam = getOneDimensionalTestNode();
    ASSERT_EQ(nullptr, adam.getPtr('x', Axis::positive));
    ASSERT_EQ(nullptr, adam.getPtr('x', Axis::negative));
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
    adam.setPtr('x', Axis::positive, bettyPtr);

    ASSERT_EQ(nullptr, adam.getPtr('x', Axis::negative));
    ASSERT_EQ(&betty, adam.getPtr('x', Axis::positive));

    ASSERT_EQ(&adam, betty.getPtr('x', Axis::negative));
    ASSERT_EQ(nullptr, betty.getPtr('x', Axis::positive));

    /**
     * Break the link
     */
    betty.setPtr('x', Axis::negative, nullptr);

    ASSERT_EQ(nullptr, adam.getPtr('x', Axis::positive));
    ASSERT_EQ(nullptr, betty.getPtr('x', Axis::negative));
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
    adam.setPtr('x', Axis::positive, bettyPtr);
    ASSERT_EQ(bettyPtr, adam.getPtr('x', Axis::positive));
    ASSERT_EQ(adamPtr, betty.getPtr('x', Axis::negative));

    /**
     * New node status
     * null <- adam -> null
     * null <- charlie <-> betty -> null
     */
    betty.setPtr('x', Axis::negative, charliePtr);

    ASSERT_EQ(nullptr, adam.getPtr('x', Axis::negative));
    ASSERT_EQ(nullptr, adam.getPtr('x', Axis::positive));

    ASSERT_EQ(charliePtr, betty.getPtr('x', Axis::negative));
    ASSERT_EQ(nullptr, betty.getPtr('x', Axis::positive));

    ASSERT_EQ(nullptr, charlie.getPtr('x', Axis::negative));
    ASSERT_EQ(bettyPtr, charlie.getPtr('x', Axis::positive));
}

TEST(nodetest, test_two_dimensions) {
    Node adam = getTwoDimensionalTestNode();
    Node betty = getTwoDimensionalTestNode();
    Node charlie = getOneDimensionalTestNode();

    Node *adamPtr = &adam;
    Node *bettyPtr = &betty;
    Node *charliePtr = &charlie;

    //set adam above betty.
    betty.setPtr('y', Axis::positive, adamPtr);
    //set charlie to the left of betty
    betty.setPtr('x', Axis::negative, charliePtr);

    //Assert the linking worked both ways
    ASSERT_EQ(bettyPtr, charlie.getPtr('x', Axis::positive));
    ASSERT_EQ(bettyPtr, adam.getPtr('y', Axis::negative));

    //Betty is now linked on two axis!
}
