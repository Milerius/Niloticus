//! Project Headers
#include "niloticus/application/app.hpp"
#include "niloticus/log/logging.hpp"

int
main()
{
    niloticus::init_logging();
    niloticus::application app;
    return app.start();
}
