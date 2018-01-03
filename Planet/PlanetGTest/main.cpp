#include <googlemock\include\gmock\gmock.h>
#include <googletest\include\gtest\gtest.h>

#include <QPointF>

#include <functions.h>

TEST (test001, test_Distance)
{
    QPointF point1(0, 1);
    QPointF point2(0, 11);

    qreal actual = distance(point1, point2);
    qreal expected = 10.0;

    ASSERT_EQ(expected, actual);
}

TEST (test002, test_Distance)
{
    QPointF point1(1, 0);
    QPointF point2(11, 0);

    qreal actual = distance(point1, point2);
    qreal expected = 10.0;

    ASSERT_EQ(expected, actual);
}

TEST (test003, test_Distance)
{
    QPointF point1(0, 7);
    QPointF point2(0, -7);

    qreal actual = distance(point1, point2);
    qreal expected = 14.0;

    ASSERT_EQ(expected, actual);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
