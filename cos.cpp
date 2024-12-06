//
// Created by HP on 14.04.2024.
//

#include "cos.h"

void Cos::add_cos(const Activity& act) noexcept{
    cos.push_back(act);
}

void Cos::recycle_cos() noexcept{
    cos.erase(cos.begin(), cos.end());
}

void Cos::random_cos(size_t nr, vector<Activity> lista){
    std::shuffle(lista.begin(), lista.end(), std::default_random_engine(std::random_device{}()));
    while (cos.size() < nr && !lista.empty()){
        cos.push_back(lista.back());
        std::shuffle(lista.begin(), lista.end(), std::default_random_engine(std::random_device{}()));
    }
}

const vector<Activity>& Cos::getAll() noexcept{
    return cos;
}