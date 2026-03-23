#include "HelpPanel.h"
#include "ftxui/dom/elements.hpp"

ftxui::Component HelpPanel::GetComponent() {
    return ftxui::Renderer([] {
        return ftxui::vbox({
            ftxui::text("Help") | ftxui::bold,
            ftxui::separator(),
            ftxui::text("Shortcuts:"),
            ftxui::text("  Tab - Switch focus"),
            ftxui::text("  c   - Connect/Disconnect"),
            ftxui::text("  r   - Quick read (addr 0, count 10)"),
            ftxui::text("  q   - Quit"),
            ftxui::separator(),
            ftxui::text("Parity: N=None, E=Even, O=Odd")
        }) | ftxui::border;
    });
}
