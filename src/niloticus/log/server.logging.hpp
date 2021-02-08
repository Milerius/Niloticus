#pragma once

#include "logging.hpp"

namespace niloticus
{
    class spdlog_logger
    {
      public:
        template <typename Msg_Builder>
        void
        trace(Msg_Builder&& mb)
        {
            SPDLOG_TRACE(mb());
        }

        template <typename Msg_Builder>
        void
        info(Msg_Builder&& mb)
        {
            SPDLOG_INFO(mb());
        }

        template <typename Msg_Builder>
        void
        warn(Msg_Builder&& mb)
        {
            SPDLOG_WARN(mb());
        }

        template <typename Msg_Builder>
        void
        error(Msg_Builder&& mb)
        {
            SPDLOG_ERROR(mb());
        }
    };

    using t_spdlog_logger = spdlog_logger;
} // namespace niloticus