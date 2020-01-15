#include <QApplication>
#include <gtest/gtest.h>
#include <QString>

#include "maps.h"
#include "transform.h"


// посмотреть как сделать один объект Transform на все тесты (mock тест)

class TestGerman : public ::testing::Test
{
protected:
    Transform t;
};

TEST_F(TestGerman, test1)
{
    QString word = "acht hundert";

    QString result;
    Errors::ErrorCodes error_code;
    std::tie(error_code, result) = t.ger_to_arab(word);

    ASSERT_EQ(Errors::ErrorCodes::NO_ERROR, error_code);
}

TEST_F(TestGerman, test2)
{
    QString result;
    int error_code = 0;
    QString word = "acht hundrt";
    std::tie(error_code, result) = t.ger_to_arab(word);

    int expected = Errors::ErrorCodes::NOT_FOUND;

    ASSERT_EQ(expected, error_code);
}

TEST_F(TestGerman, test3)
{
    QString result;
    int error_value = 0;
    QString word = "acht hundert achtzehn zwei";
    std::tie(error_value, result) = t.ger_to_arab(word);

    int expected = Errors::ErrorCodes::NO_ONE_AFTER_TENS_PLUS;

    ASSERT_EQ(expected, error_value);
}

TEST_F(TestGerman, test4)
{
    QString result;
    int error_value = 0;
    QString word = "";
    std::tie(error_value, result) = t.ger_to_arab(word);

    QString expected = QString("");

    ASSERT_EQ(expected, result);
}

TEST_F(TestGerman, test5)
{
    QString result;
    int error_value = 0;
    QString word = "";
    std::tie(error_value, result) = t.ger_to_arab(word);

    int expected = 2;

    ASSERT_EQ(expected, error_value);
}

TEST_F(TestGerman, test6)
{
    QString result;
    int error_value = 0;
    QString word = "";
    std::tie(error_value, result) = t.ger_to_arab(word);

    int expected = 2;

    ASSERT_EQ(expected, error_value);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
