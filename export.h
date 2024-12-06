//
// Created by Eric on 22.04.2024.
//

#pragma once

#include <fstream>
#include "cos.h"
#include "service.h"

class Export{
public:
    Export() = default;
    static void export_html(const string& name, const vector<Activity>& acts);
};

