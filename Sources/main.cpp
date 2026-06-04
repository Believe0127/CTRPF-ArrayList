#include "ArrayList.hpp"

namespace CTRPluginFramework {

    // ArrayList usage example
    void Test(MenuEntry* entry) {
        if (entry->WasJustActivated()) {
            ArrayList::Add(entry->Name());
        }
        else if (!entry->IsActivated()) {
            ArrayList::Remove(entry->Name());
        }
    }
    
    void InitMenu(PluginMenu& menu) {     
        menu += new MenuEntry("Test", Test, "");
    }
    
    int main() {
        const std::unique_ptr<PluginMenu> menu(new PluginMenu("CTRPF - ArrayList", 1, 0, 0, ""));
        const std::unique_ptr<ArrayList> arraylist(new ArrayList(20, Color::White, Color::Black));

        menu->SynchronizeWithFrame(true);
        
        InitMenu(*menu);

        arraylist->Run();
        
        menu->Run();

        return 0;
    }

} // namespace CTRPluginFramework


