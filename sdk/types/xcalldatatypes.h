#pragma once

// Типы для передачи данных в XCall
#include <QString>

struct XCallDataCreateWidget {
    QString in_parent_id;
    void* out_widget = nullptr;
};

