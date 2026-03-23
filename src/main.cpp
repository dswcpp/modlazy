#include "app/App.h"
#include "ui/MainView.h"

int main() {
    App app;
    MainView view(&app);
    view.Run();
    return 0;
}
