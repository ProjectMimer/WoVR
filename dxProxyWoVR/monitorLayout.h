#pragma once
#define WIN32_LEAN_AND_MEAN
// Windows Header Files
#include <windows.h>
#include <vector>

struct stMonitorLayout
{
    std::vector<int>       iMonitors;
    std::vector<HMONITOR>  hMonitors;
    std::vector<HDC>       hdcMonitors;
    std::vector<RECT>      rcMonitors;

    static BOOL CALLBACK MonitorEnum(HMONITOR hMon, HDC hdc, LPRECT lprcMonitor, LPARAM pData)
    {
        stMonitorLayout* pThis = reinterpret_cast<stMonitorLayout*>(pData);
        pThis->hMonitors.push_back(hMon);
        pThis->hdcMonitors.push_back(hdc);
        pThis->rcMonitors.push_back(*lprcMonitor);
        pThis->iMonitors.push_back((int)pThis->hdcMonitors.size());
        return TRUE;
    }

    stMonitorLayout()
    {
        EnumDisplayMonitors(0, 0, MonitorEnum, (LPARAM)this);
    }
};
