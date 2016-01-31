#define BOOST_TEST_MODULE function_traits_test
#include <boost/test/included/unit_test.hpp>


#include <iostream>
#include <type_traits>
#include <pre/lambda/function_traits.hpp>


BOOST_AUTO_TEST_CASE (function_traits_test_lambda) {

    auto my_lambda = [](bool arg_0, int arg_1, double arg_2, std::string arg_3) {
                            return int{23} ;
                        };

    typedef pre::lambda::function_traits<decltype(my_lambda)> my_lambda_types;

    auto is_same =  std::is_same< my_lambda_types::result_type, int>::value;

    BOOST_ASSERT_MSG(my_lambda_types::arity == 4 , " lambda arity is wrong");
    BOOST_ASSERT_MSG(is_same, " return type wrong");

    is_same =  std::is_same<my_lambda_types::arg<0>, bool>::value;
    BOOST_ASSERT_MSG(is_same, " argument ist not as expected");

    is_same =  std::is_same<my_lambda_types::arg<1>, int>::value;
    BOOST_ASSERT_MSG(is_same, " argument ist not as expected");

    is_same =  std::is_same<my_lambda_types::arg<2>, double>::value;
    BOOST_ASSERT_MSG(is_same, " argument ist not as expected");

    is_same =  std::is_same<my_lambda_types::arg<3>, std::string>::value;
    BOOST_ASSERT_MSG(is_same, " argument ist not as expected");

    typedef std::function<int(bool, int, double, std::string)> expected_function_type;
    is_same = std::is_same<my_lambda_types::function_type , expected_function_type>::value;
    BOOST_ASSERT_MSG(is_same, " function type  ist not as expected");

    auto std_function = pre::lambda::to_std_function(my_lambda);

    BOOST_ASSERT_MSG(std_function(true, int{42}, double{3.14}, std::string{"Hello World"}) == 23 , " call to std::funtion is wrong");
}


BOOST_AUTO_TEST_CASE (function_traits_test_lambda_copy_captures) {

    bool capture_bool     = true;
    int capture_int       = 42;
    double capture_double = 12.3;

    auto my_lambda_copy_capture = [=](bool arg_0, int arg_1, double arg_2, std::string arg_3) {
      return capture_int + capture_double;
    };

    typedef pre::lambda::function_traits<decltype(my_lambda_copy_capture)> my_lambda_types;

    auto is_same =  std::is_same< my_lambda_types::result_type, double>::value;

    BOOST_ASSERT_MSG(my_lambda_types::arity == 4 , " lambda arity is wrong");
    BOOST_ASSERT_MSG(is_same, " return type wrong");

    is_same =  std::is_same<my_lambda_types::arg<0>, bool>::value;
    BOOST_ASSERT_MSG(is_same, " argument 0 ist not as expected " );

    is_same =  std::is_same<my_lambda_types::arg<1>, int>::value;
    BOOST_ASSERT_MSG(is_same, " argument 1 ist not as expected");

    is_same =  std::is_same<my_lambda_types::arg<2>, double>::value;
    BOOST_ASSERT_MSG(is_same, " argument 2 ist not as expected");

    is_same =  std::is_same<my_lambda_types::arg<3>, std::string>::value;
    BOOST_ASSERT_MSG(is_same, " argument 3 ist not as expected");

    typedef std::function<int(bool, int, double, std::string)> expected_function_type;
    is_same = std::is_same<my_lambda_types::function_type , expected_function_type>::value;
    BOOST_ASSERT_MSG(!is_same, " function type  ist not as expected with capture it is different");
    auto std_function = pre::lambda::to_std_function(my_lambda_copy_capture);

    BOOST_ASSERT_MSG(std_function(true, int{42}, double{3.14}, std::string{"Hello World"}) == (42+12.3) , " call to std::funtion is wrong");
}

BOOST_AUTO_TEST_CASE (function_traits_test_lambda_ref_captures) {

    bool capture_bool     = true;
    int capture_int       = 42;
    double capture_double = 12.3;

    auto my_lambda_ref_capture = [&](bool arg_0, int arg_1, double arg_2, std::string arg_3) {
      return capture_int + capture_double;
    };

    typedef pre::lambda::function_traits<decltype(my_lambda_ref_capture)> my_lambda_types;

    auto is_same =  std::is_same< my_lambda_types::result_type, double>::value;

    BOOST_ASSERT_MSG(my_lambda_types::arity == 4 , " lambda arity is wrong");
    BOOST_ASSERT_MSG(is_same, " return type wrong");

    is_same =  std::is_same<my_lambda_types::arg<0>, bool>::value;
    BOOST_ASSERT_MSG(is_same, " argument 0 ist not as expected");

    is_same =  std::is_same<my_lambda_types::arg<1>, int>::value;
    BOOST_ASSERT_MSG(is_same, " argument 1 ist not as expected");

    is_same =  std::is_same<my_lambda_types::arg<2>, double>::value;
    BOOST_ASSERT_MSG(is_same, " argument 2 ist not as expected");

    is_same =  std::is_same<my_lambda_types::arg<3>, std::string>::value;
    BOOST_ASSERT_MSG(is_same, " argument 3 ist not as expected");

    typedef std::function<int(bool, int, double, std::string)> expected_function_type;
    is_same = std::is_same<my_lambda_types::function_type , expected_function_type>::value;
    BOOST_ASSERT_MSG(!is_same, " function type  ist not as expected with capture it is different");

    auto std_function = pre::lambda::to_std_function(my_lambda_ref_capture);

    BOOST_ASSERT_MSG(std_function(true, int{42}, double{3.14}, std::string{"Hello World"}) == (42+12.3) , " call to std::funtion is wrong");
}

