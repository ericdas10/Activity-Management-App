//
// Created by HP on 01.04.2024.
//

#include "validate.h"

bool Validator::val_float(const float &value) {
    return value > 0;
}

bool Validator::val_string(const std::string &value) {
    return value.empty();
}

/*void test_validare(){
    assert(val_string("apa") == 1);
    assert(val_string("") == 0);
    assert(val_float(120) == 1);
    assert(val_float(-1) == 0);

    Activity elem = {"sah", "tabla", "minte", 200};
    Activity elem1 = {"", "tabla", "minte", 200};
    Activity elem2 = {"sah", "", "minte", 200};
    Activity elem3 = {"sah", "tabla", "", 200};
    Activity elem4 = {"sah", "tabla", "minte", -5};
    assert(validare(elem) == 1);
    assert(validare(elem1) == 0);
    assert(validare(elem2) == 0);
    assert(validare(elem3) == 0);
    assert(validare(elem4) == 0);

}*/

