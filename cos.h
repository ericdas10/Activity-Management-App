//
// Created by HP on 14.04.2024.
//

#pragma once
#include <stdexcept>
#include "domain.h"
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <utility>
#include "repo.h"
using std::vector;



class CosException : public std::runtime_error {
public:
    explicit CosException(const std::string& msg) : std::runtime_error(msg){}
};

class Cos{
private:
    vector<Activity> cos;
public:

    Cos() = default;

    void add_cos(const Activity& act) noexcept;

    void recycle_cos() noexcept;

    void random_cos(size_t nr, vector<Activity> lista);

    const vector<Activity>& getAll() noexcept;
};
