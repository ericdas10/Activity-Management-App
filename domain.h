//
// Created by HP on 31.03.2024.
//

#pragma once
#include <string>
#include <functional>
#include <utility>
#include <iostream>
using std::string;
using std::cout;
using std::function;

class Activity{
    private:
        string title;
        string desc;
        string type;
        float length{0};

    public:
        [[nodiscard]] string getTitle() const;
        [[nodiscard]] string getDesc() const;
        [[nodiscard]] string getType() const;
        [[nodiscard]] float getLength() const;
        void setTitle(string value);
        void setDesc(string value);
        void setType(string value);
        void setLength(float value);
        static void swap_elem(Activity& elem_to_swap, const Activity& new_elem);

        Activity() = default;
        Activity(string title, string desc, string type, float length):title{std::move(title)},desc{std::move(desc)},type{std::move(type)},length{length}{};

    bool operator==(const Activity& other) const {
        return (this->getTitle() == other.getTitle() &&
                this->getDesc() == other.getDesc() && this->getType() == other.getType() && this->getLength() == other.getLength());
    }
};

