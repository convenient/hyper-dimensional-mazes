#include "gtest/gtest.h"
#include "dimensions.h"

TEST(dimensions_test, test_cloned) {

    //Create a dimension
    Dimensions universe_16;

    //Add an axis
    Axis xAxis = Axis('x');
    Axis *xAxisPtr = &xAxis;
    universe_16.addAxis(xAxisPtr);

    //Assert the axis was added correctly
    ASSERT_EQ(xAxisPtr, universe_16.getAxisPtr('x'));

    //Create a number and a pointer to it
    int number = 1337;
    int *numberPtr = &number;

    //Set the positive side of the axis to the numberPtr
    xAxis.setPositivePtr(numberPtr);

    //Get the axis back from the dimension
    Axis *xAxisPtrFromU16 = universe_16.getAxisPtr('x');

    //Double check that the numberPtr is persisted
    ASSERT_EQ(numberPtr, xAxisPtrFromU16->getPositivePtr());

    //Clone universe_16 into universe_17
    Dimensions universe_17 = universe_16.clone();

    Axis *xAxisPtrFromU17 = universe_17.getAxisPtr('x');

    //Assert we get a DIFFERENT pointer for an x axis.
    //But an x axis will exist all the same.
    ASSERT_NE(xAxisPtr, xAxisPtrFromU17);
    ASSERT_NE(nullptr, xAxisPtrFromU17);

    //Assert that even though we've a valid axis, it is now all empty pointers
    ASSERT_EQ(nullptr, xAxisPtrFromU17->getNegativePtr());
    ASSERT_EQ(nullptr, xAxisPtrFromU17->getPositivePtr());
}
