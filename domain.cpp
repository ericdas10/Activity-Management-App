//
// Created by HP on 31.03.2024.
//
#include "domain.h"
#include <assert.h>
#include <iostream>

string Activity::getTitle() const {
    return title;
}

string Activity::getDesc() const {
    return desc;
}

string Activity::getType() const {
    return type;
}

float Activity::getLength() const {
    return length;
}



void Activity::setLength(float value) {
    this->length = value;
}

void Activity::setTitle(string value) {
    this->title = std::move(value);
}

void Activity::setDesc(string value) {
    this->desc = std::move(value);
}

void Activity::setType(string value) {
    this->type = std::move(value);
}

void Activity::swap_elem(Activity& elem_to_swap, const Activity& new_elem){
    elem_to_swap.setTitle(new_elem.getTitle());
    elem_to_swap.setDesc(new_elem.getDesc());
    elem_to_swap.setType(new_elem.getType());
    elem_to_swap.setLength(new_elem.getLength());
}