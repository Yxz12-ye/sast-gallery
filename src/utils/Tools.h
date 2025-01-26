#pragma once

#include <QString>

struct Tools {
    Tools() = delete;
    static QString fileSizeString(QString filepath);
};