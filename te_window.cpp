#include "te_window.hpp"

namespace te {

    TeWindow::TeWindow(int w, int h, std::string name) : width{w}, height{h}, window_name{name} {
        initWindow();
        
    }
}