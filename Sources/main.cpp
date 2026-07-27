#include "ArrayList.hpp"

namespace CTRPluginFramework
{
    // ArrayList usage example
    void Test(MenuEntry* entry) {
        if (entry->WasJustActivated()) {
            ArrayList::Instance().Add(entry->Name());
        }
        else if (!entry->IsActivated()) {
            ArrayList::Instance().Remove(entry->Name());
        }
    }

    void InitMenu(PluginMenu& menu) {
        menu += new MenuEntry("Coordinate Movement", Test, "");
        menu += new MenuEntry("Map Editor", Test, "");
        menu += new MenuEntry("Moon Jump", Test, "");
        menu += new MenuEntry("Speed", Test, "");
    }

    int main() {
        auto* menu = new PluginMenu("CTRPF - ArrayList", 1, 0, 0);
        menu->SynchronizeWithFrame(true);

        ArrayList::CreateInstance(20, Color::White, Color::Black, Color::White);
        ArrayList::Instance().ShowFrame();
        ArrayList::Instance().Show();

        InitMenu(*menu);

        menu->Run();

        ArrayList::DestroyInstance();
        delete menu;
        return 0;
    }
}
