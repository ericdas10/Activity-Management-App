//
// Created by HP on 31.03.2024.
//

#include "service.h"

Service::Service(AbsRepo&repo) : repo(repo) {}



int Service::adaugare_activitate(const Activity &elem) {
    if (val_elem(elem) == 1){
        if(repo.store(elem) == 0){
            undo_save.push_back(std::make_unique<UndoAdauga>(repo, elem));
            return 0;
        }
    }
    throw ServiceExceptio("Element invalid! Mai incearca!");
}

int Service::stergere_activitate(const Activity &elem) {
    if (val_elem(elem) == 1){
        Activity copy = elem;
        if (repo.recycle(elem) == 0){
            undo_save.push_back(std::make_unique<UndoSterge>(repo, copy));
            return 0;
        }
    }
    throw ServiceExceptio("Element invalid! Mai incearca!");
}

int Service::modificare_activitate(const Activity &elem) {
    if (val_elem(elem) == 1){
        Activity act = cautare_act(elem.getTitle());
        repo.modify(elem);
        undo_save.push_back(std::make_unique<UndoModifica>(repo, act));
        return 0;
    }
    throw ServiceExceptio("Element invalid! Mai incearca!");
}

vector<Activity> Service::getAll() noexcept{
    return repo.getAll();
}

Activity Service::cautare_act(const string & title){
    if(!Validator::val_string(title)){
        Activity act = repo.search(title);
        return act;
    }
    throw ServiceExceptio("Element invalid! Mai incearca!");
}

vector<Activity> Service::filtrare_desc(const string& desc){
    if(!Validator::val_string(desc)){
        vector<Activity> lista;
        auto copy = repo.getAll();

        std::copy_if(copy.begin(), copy.end(), back_inserter(lista), [desc](const Activity& elem){return elem.getDesc() == desc;});

        return lista;
    }
    throw ServiceExceptio("Element invalid! Mai incearca!");

}

vector<Activity> Service::filtrare_type(const string& type){
    if(!Validator::val_string(type)){
        vector<Activity> lista;
        auto copy = repo.getAll();

        std::copy_if(copy.begin(), copy.end(), back_inserter(lista), [type](const Activity& elem){return elem.getType() == type;});

        return lista;
    }
    throw ServiceExceptio("Element invalid! Mai incearca!");

}

vector<Activity> Service::sortare_titlu() noexcept{
    auto lista = repo.getAll();

    vector<Activity> rezolvare;
    std::copy(lista.begin(), lista.end(), back_inserter(rezolvare));
    std::sort(rezolvare.begin(), rezolvare.end(), [](const Activity& elem1, const Activity& elem2){
        return elem1.getTitle() < elem2.getTitle();
    });
    return rezolvare;
}

vector<Activity> Service::sortare_descriere() noexcept{
    auto lista = repo.getAll();

    vector<Activity> rezolvare;
    std::copy(lista.begin(), lista.end(), back_inserter(rezolvare));
    std::sort(rezolvare.begin(), rezolvare.end(), [](const Activity& elem1, const Activity& elem2){
        return elem1.getDesc() < elem2.getDesc();
    });
    return rezolvare;
}

vector<Activity> Service::sortare_tip_durata() noexcept{
    auto lista = repo.getAll();

    vector<Activity> rezolvare;
    std::copy(lista.begin(), lista.end(), back_inserter(rezolvare));
    std::sort(rezolvare.begin(), rezolvare.end(), [](const Activity& elem1, const Activity& elem2){
        if (elem1.getType() == elem2.getType())
            return elem1.getLength() < elem2.getLength();
        return elem1.getType() < elem2.getType();
    });
    return rezolvare;
}

bool Service::val_elem(const Activity& elem){
    if(!Validator::val_string(elem.getTitle()) && !Validator::val_string(elem.getDesc()) && !Validator::val_string(elem.getType()) && Validator::val_float(elem.getLength())){
            return true;
    }
    return false;
}

const vector<Activity>& Service::adaugare_cos(const string& title){
    if(!Validator::val_string(title)) {
        auto vector = getAll();
        auto it = std::find_if(vector.begin(), vector.end(), [title](const Activity &act) {
            return act.getTitle() == title;
        });
        if(it == vector.end()){
            throw ServiceExceptio("Nu s-a gasit activitatea!");
        }
        cos.add_cos(*it);
        return cos.getAll();
    }
    throw ServiceExceptio("Nu s-a introdus un element valid!");
}

const vector<Activity>& Service::golire_cos() noexcept{
    cos.recycle_cos();
    return  cos.getAll();
}

const vector<Activity>& Service::cos_getAll() noexcept{
    return cos.getAll();
}

const vector<Activity>& Service::cos_random(size_t nr) {
    if(nr <= 0){
        throw ServiceExceptio("Date invalide!");
    }
    auto vect = repo.getAll();
    cos.random_cos(nr, vect);
    return cos.getAll();

}

std::map<string, int> Service::add_type_freq(){
    auto var = repo.getAll();
    std::map<string, int> var1;
    for(const auto& i: var){
        var1[i.getType()]++;
    }
    return var1;
}

int Service::undo() {
    if(undo_save.empty()) {
        throw ServiceExceptio("Nici o actiune anterioara valabila!");
    }

    undo_save.back() -> doUndo();
    undo_save.pop_back();
    return 0;
}

int Service::export_html(const std::string &name) {
    std::size_t found = name.find(".html");
    if (found != std::string::npos){
        Export::export_html(name, cos_getAll());
        return 0;
    }
    throw ServiceExceptio("Nu s-a putut exporta continutul dorit");
}

