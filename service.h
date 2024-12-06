//
// Created by HP on 31.03.2024.
//

#pragma once
#include "repo.h"
#include "validate.h"
#include "cos.h"
#include "undo.h"
#include "export.h"
#include <map>
#include <memory>
#include "observer.h"

class ServiceExceptio:public std::runtime_error{
public:
    explicit ServiceExceptio(const std::string& msg) : std::runtime_error(msg){}

};

class Service: public Subject{
private:
    AbsRepo& repo;
    Cos cos;
    vector<std::unique_ptr<ActiuneUndo>> undo_save;

public:
    explicit Service(AbsRepo& repo);

    Service(const Service& other) = delete;
    Service operator=(const Service& other) = delete;
    Service(const Service&& other) = delete;
    Service&& operator=(const Service&& other) = delete;
    ~Service() = default;

    int adaugare_activitate(const Activity& elem);
    std::map<string, int> add_type_freq();
    int stergere_activitate(const Activity& elem);
    int modificare_activitate(const Activity& elem);

    vector<Activity> getAll() noexcept;
    Activity cautare_act(const string & title);

    vector<Activity> filtrare_desc(const string& desc);
    vector<Activity> filtrare_type(const string& type);
    vector<Activity> sortare_titlu() noexcept;
    vector<Activity> sortare_descriere() noexcept;
    vector<Activity> sortare_tip_durata() noexcept;

    static bool val_elem(const Activity& elem);

    const vector<Activity>& adaugare_cos(const string& title);
    const vector<Activity>& golire_cos() noexcept;
    const vector<Activity>& cos_random(size_t nr);
    const vector<Activity>& cos_getAll() noexcept;

    int undo();
    int export_html(const string& name);
};
