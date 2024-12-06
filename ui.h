//
// Created by HP on 31.03.2024.
//

#pragma once
#include "service.h"

class UI{
    Service& service;
    static void menu();
    static void menu_cos();
public:
    explicit UI(Service& service):service{service}{};
    int startUI();
};
