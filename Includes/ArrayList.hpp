#pragma once

#include <CTRPluginFramework.hpp>

#define TOPSCREEN_WIDTH 400

namespace CTRPluginFramework
{
    // Singleton Class
    class ArrayList {
        ArrayList(size_t maxSize, const Color& foreground, const Color& background, const Color& border) noexcept;
        ~ArrayList()                                                                                     noexcept;

        static bool DrawArrayListOSDCallback(const Screen& scr) noexcept;
        static u32  AlignToRightEdge(const std::string& str)    noexcept;
    public:
        template <class... Args>
        static void CreateInstance(Args&&... args) noexcept {
            if (!instance) {
                instance = new ArrayList(std::forward<Args>(args)...);
            }
        }

        static void DestroyInstance() noexcept {
            delete instance;
            instance = nullptr;
        }

        static ArrayList& Instance() noexcept {
            return *instance;
        }

        void Add(const std::string& name)    noexcept;
        void Remove(const std::string& name) noexcept;
        void Clear()                         noexcept;

        void Hide()      noexcept;
        void Show()      noexcept;
        void ShowBorder() noexcept;
        void HideBorder() noexcept;

        Color& Foreground() noexcept;
        Color& Background() noexcept;
        Color& Border()     noexcept;
    private:
        static ArrayList* instance;

        std::vector<std::string> items;
        size_t maxSize;

        Color foreground;
        Color background;
        Color border;

        bool showArrayList;
        bool showBorder;
    };
}