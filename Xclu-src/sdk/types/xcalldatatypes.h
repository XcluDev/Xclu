#pragma once

// Типы для передачи данных в XCall
#include <QString>

class XCallDataCreateWidget {
public:
    QString in_parent_id;
    void* out_widget = nullptr;
};

