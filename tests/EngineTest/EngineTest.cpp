#define BOOST_TEST_MODULE Engine_test
#include <boost/test/unit_test.hpp>

#include "Engine.h"

#include <string>
#include <filesystem>

namespace fs = std::filesystem;


BOOST_AUTO_TEST_CASE(throw_if_file_doesnt_exist)
{
    fs::path wrong_path = "qwertyasdfgh";
    BOOST_TEST_MESSAGE("This file doesn't exist: " << wrong_path);

    BOOST_CHECK_THROW(SGE::find_file(wrong_path), fs::filesystem_error);
}


BOOST_AUTO_TEST_CASE(nothrow_if_file_exist)
{
    fs::path correct_path = "test_file.txt";
    BOOST_TEST_MESSAGE("This file exist: " << correct_path);

    BOOST_CHECK_NO_THROW(SGE::find_file(correct_path));
}


BOOST_AUTO_TEST_CASE(throw_if_found_not_regular_file)
{
    fs::path dir_path = "test_dir";
    BOOST_TEST_MESSAGE("This directory exist: " << dir_path);

    BOOST_CHECK_THROW(SGE::find_file("test_dir"), fs::filesystem_error);

	fs::path sym_path = "test_link_file.txt";
    BOOST_TEST_MESSAGE("This symlink file exist: " << sym_path);

	BOOST_CHECK_THROW(SGE::find_file(sym_path), fs::filesystem_error);
}
