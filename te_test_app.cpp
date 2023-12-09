#include "te_test_app.hpp"

namespace te {

void TeTestApp::run() {
    while(!te_window.should_close()) {
        glfwPollEvents();
    }
}

} // namespace te