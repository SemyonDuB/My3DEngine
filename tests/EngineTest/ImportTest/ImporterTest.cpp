#define BOOST_TEST_MODULE Importer_test
#include <boost/test/unit_test.hpp>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>


namespace fs = std::filesystem;

[[nodiscard]] fs::path find_file(const fs::path &file_name)
{
    for (auto &file_path : fs::recursive_directory_iterator(fs::current_path()))
        if (fs::path(file_path).filename() == file_name)
            return fs::path(file_path);

    using namespace std;
    throw fs::filesystem_error(
        "Can't find file", make_error_code(errc::no_such_file_or_directory));
}


class AImport
{
public:
    void importObj(const fs::path &file_path)
    {
        using namespace std;

        if (!fs::exists(file_path))
        {
            throw fs::filesystem_error(
                "File doesn't exist", file_path,
                make_error_code(errc::no_such_file_or_directory));
        }

		loadScene(file_path);
    }

private:
    void loadScene(const fs::path &file_path)
    {
        Assimp::Importer importer;

        using namespace std;
        // Dont use smart pointers! aiScene self-cleaning
        const aiScene *scene = importer.ReadFile(file_path.c_str(), 0);
        if (!scene)
            throw fs::filesystem_error("Can't read file", file_path,
                                       make_error_code(errc::not_supported));
    }
};


BOOST_FIXTURE_TEST_CASE(throw_if_file_doesnt_exist, AImport)
{
    fs::path wrong_path = "qwertasdf";
    BOOST_TEST_MESSAGE("This file doesn't exist: " << wrong_path);

    BOOST_CHECK_THROW(importObj(wrong_path), fs::filesystem_error);
}


BOOST_FIXTURE_TEST_CASE(nothrow_if_file_exist, AImport)
{
    fs::path cube_path = find_file("cube.obj");
    BOOST_TEST_MESSAGE("This file exist: " << cube_path);

    BOOST_CHECK_NO_THROW(importObj(cube_path));
}


BOOST_FIXTURE_TEST_CASE(throw_if_cannt_read_file, AImport)
{
    fs::path wrong_path = "idontknow";
    BOOST_CHECK_THROW(importObj(wrong_path), fs::filesystem_error);
}
