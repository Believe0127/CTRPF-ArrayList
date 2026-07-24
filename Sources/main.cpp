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
        menu += new MenuEntry("ABCDEFGH", Test, "");
        menu += new MenuEntry("0x123456789", Test, "");
        menu += new MenuEntry("123456789", Test, "");
        menu += new MenuEntry("Hello World!!", Test, "");
    }
    
    int main() {
        auto* menu = new PluginMenu("CTRPF - ArrayList", 1, 0, 0);
        menu->SynchronizeWithFrame(true);

        ArrayList::CreateInstance(20, Color::White, Color::Black, Color::White);
        ArrayList::Instance().ShowFrame();
        ArrayList::Instance().Show();
        
        InitMenu(*menu);

        menu->Run();

        delete menu;
        return 0;
    }
}