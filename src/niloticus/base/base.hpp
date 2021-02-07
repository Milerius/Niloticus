#pragma once

#import <filesystem>

namespace fs = std::filesystem;

namespace niloticus
{
    fs::path get_generic_data_folder() noexcept;
    fs::path get_generic_logs_folder() noexcept;
} // namespace niloticus