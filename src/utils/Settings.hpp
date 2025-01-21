#pragma once

#include <QSettings>
#include <filesystem>

inline QSettings settings = [] {
    const std::filesystem::path configDir =
#ifdef Q_OS_WINDOWS
        std::filesystem::path(std::getenv("APPDATA")) / "Local" / "NJUPT-SAST-C++" / "SAST-Gallery";
#else
        std::filesystem::path(std::getenv("HOME")) / ".config" / "NJUPT-SAST-C++" / "SAST-Gallery";
#endif

    if (!std::filesystem::exists(configDir)) {
        std::filesystem::create_directories(configDir);
    }

    return QSettings(QString::fromStdString(configDir.string() + "/settings.ini"),
                     QSettings::IniFormat);
}();
