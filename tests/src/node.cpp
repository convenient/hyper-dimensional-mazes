#include "gtest/gtest.h"
#include "graph/node.h"

TEST(nodetest, test_bi_directional_links) {
    Point aPoint;
    Point bPoint;

    Node *adam = new Node(aPoint);

    Node *betty = new Node(bPoint);

    ASSERT_FALSE(adam->isLinked(betty));
    ASSERT_FALSE(betty->isLinked(adam));

    adam->link(betty);
    ASSERT_TRUE(adam->isLinked(betty));
    ASSERT_TRUE(betty->isLinked(adam));

    betty->unlink(adam);
    ASSERT_FALSE(adam->isLinked(betty));
    ASSERT_FALSE(betty->isLinked(adam));
}
