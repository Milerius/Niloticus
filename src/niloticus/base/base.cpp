#if defined(_WIN32) || defined(WIN32)
#    import <cstdlib> //< std::getenv
#endif

#include "niloticus/base/base.hpp"

namespace details
{
    bool
    create_if_doesnt_exist(const fs::path& path)
    {
        if (not fs::exists(path))
        {
            fs::create_directories(path);
            return true;
        }
        return false;
    }
} // namespace details

namespace niloticus
{
    fs::path
    get_generic_data_folder() noexcept
    {
        fs::path appdata_path;
#if defined(_WIN32) || defined(WIN32)
        appdata_path = fs::path(std::getenv("APPDATA")) / ".niloticus";
#else
        appdata_path = fs::path(std::getenv("HOME")) / ".niloticus";
#endif
        return appdata_path;
    }

    fs::path
    get_generic_logs_folder() noexcept
    {
        const auto fs_logs_path = get_generic_data_folder() / "logs";
        details::create_if_doesnt_exist(fs_logs_path);
        return fs_logs_path;
    }
} // namespace niloticus