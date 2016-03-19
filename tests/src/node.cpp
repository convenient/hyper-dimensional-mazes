#include "gtest/gtest.h"
#include "node.h"

TEST(nodetest, test_bi_directional_links) {
    Node* adam = new Node(new Point());

    Node* betty = new Node(new Point());

    ASSERT_FALSE(adam->isLinked(betty));
    ASSERT_FALSE(betty->isLinked(adam));

    adam->link(betty);
    ASSERT_TRUE(adam->isLinked(betty));
    ASSERT_TRUE(betty->isLinked(adam));

    betty->unlink(adam);
    ASSERT_FALSE(adam->isLinked(betty));
    ASSERT_FALSE(betty->isLinked(adam));
}
