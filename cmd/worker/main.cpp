//! Project Headers
#include "niloticus/application/worker.app.hpp"
#include "niloticus/log/logging.hpp"

int
main()
{
    niloticus::init_logging("niloticus.worker");
    niloticus::worker_application app;
    return app.start();
}
