#include "ArrayList.hpp"

#include <ranges>

namespace CTRPluginFramework 
{    
    ArrayList* ArrayList::instance = nullptr;

    ArrayList::ArrayList(size_t maxSize, const Color& foreground, const Color& background, const Color& frame) noexcept
        : items{}
        , maxSize(maxSize)
        , foreground(foreground) 
        , background(background) 
        , frame(frame)
        , showArrayList(false) 
        , showFrame(false) 
    {}

    ArrayList::~ArrayList() noexcept {
        Hide();
    }

    bool ArrayList::DrawArrayListOSDCallback(const Screen& scr) noexcept 
    {
        const auto& self = ArrayList::Instance(); 
        if (self.showArrayList && !self.items.empty()) {
            if (scr.IsTop) {
                u32 posY = 0;
                for (auto it = self.items.begin(), end = self.items.end(); it != end; ++it) {
                    const u32 posX = AlignToRightEdge(*it);

                    posY = scr.Draw(*it, posX, posY, self.foreground, self.background);
                    
                    // Draw Frame
                    if (self.showFrame) {
                        const u32 newPosX = posX - 1;

                        for (u32 y = posY - 10; y < posY; ++y) {
                            scr.DrawPixel(newPosX, y, self.frame);
                        }
                        
                        const auto nextIt = std::next(it);
                        for (u32 x = newPosX, endX = (nextIt == end ? TOPSCREEN_WIDTH : AlignToRightEdge(*nextIt)); x < endX; ++x) {
                            scr.DrawPixel(x, posY, self.frame);
                        }
                    }
                }
            }
        }
        return true;
    }

    void ArrayList::Add(const std::string& name) noexcept 
    {
        if (!name.empty() && items.size() < maxSize) {
            const auto insert_pos = std::ranges::find_if(
                items, 
                [len = name.length()](const std::string& str) -> bool {
                    return str.length() < len;
                }
            );
            items.insert(insert_pos, name);
        }
    }
    
    void ArrayList::Remove(const std::string& name) noexcept 
    {
        if (!name.empty() && !items.empty()) {
            std::erase_if(items, 
                [&name](const std::string& str) -> bool {
                    return str == name;
                }
            );
        }
    }

    void ArrayList::Clear() noexcept {
        items.clear();
    }

    void ArrayList::Hide() noexcept 
    {
        if (showArrayList) {
            OSD::Stop(DrawArrayListOSDCallback);
            showArrayList = false;
        }
    }
    
    void ArrayList::Show() noexcept 
    {
        if (!showArrayList) {
            OSD::Run(DrawArrayListOSDCallback);
            showArrayList = true;
        }
    }

    void ArrayList::ShowFrame() noexcept {
        showFrame = true;
    }

    void ArrayList::HideFrame() noexcept {
        showFrame = false;
    }

    Color& ArrayList::ForegroundColor() noexcept {
        return foreground;
    }
    
    Color& ArrayList::BackgroundColor() noexcept {
        return background;
    }

    Color& ArrayList::FrameColor() noexcept {
        return frame;
    }
    
    u32 ArrayList::AlignToRightEdge(const std::string& str) noexcept {
        return TOPSCREEN_WIDTH - (str.length() * 6) - 2;
    }
}