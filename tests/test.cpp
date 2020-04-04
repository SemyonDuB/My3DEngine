#define BOOST_TEST_MODULE boost_test
#include <boost/test/unit_test.hpp>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class Import
{
public:
	void importObj(fs::path file_loc)
	{
		using namespace std;
		if(!fs::exists(file_loc))
			throw fs::filesystem_error("File doesn't exist", file_loc, 
									   make_error_code(errc::no_such_file_or_directory)); 

		std::cout<<"Fine\n";
	}
};

BOOST_AUTO_TEST_CASE(test_throw_importObj)
{
	Import imp;
	fs::path p = fs::current_path() / "some";
	imp.importObj(p);
}
