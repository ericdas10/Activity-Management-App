//
// Created by Eric on 6/4/2024.
//

#pragma once
#include <vector>
#include <algorithm>

class Observer{
public:
    virtual void update() = 0;

};

class Subject{
private:
    std::vector<Observer*> listener;
public:
    void notify(){
        for(auto elem : listener){
            elem->update();
        }
    }

    void adauga_listener(Observer *obs){
        listener.push_back(obs);
    }
    void sterge_listener(Observer *obs){
        listener.erase(std::remove(listener.begin(), listener.end(), obs), listener.end());
    }
};