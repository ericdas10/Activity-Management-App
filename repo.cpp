//
// Created by HP on 31.03.2024.
//

#include "repo.h"

int Repo::store(const Activity& elem){
    auto it = std::find(activities.begin(), activities.end(), elem);
    if (it != activities.end()){
        throw RepoException{"Element existent"};
    }
    activities.push_back(elem);
    return 0;
}

int Repo::recycle(const Activity& elem){
    if (activities.empty() == 1){
        throw RepoException("Lista este vida!");
    }

    auto it = std::find(activities.begin(), activities.end(), elem);
    if (it != activities.end()){
        activities.erase(it);
        return 0;
    }
    throw RepoException("Element inexistent!");
}

int Repo::modify(const Activity& elem){
    for(auto& act: activities){
        if(act.getTitle() == elem.getTitle()){
            act = elem;
            return 0;
        }
    }
    throw RepoException("Modificare invalida!");
}

Activity Repo::search(const string& title){
    auto rez = std::find_if(activities.begin(), activities.end(), [title](const Activity& elem){
        return elem.getTitle() == title;
    });
    if (rez != activities.end()){
        return *rez;
    }
    throw RepoException("Element inexistent!");
}

vector<Activity> Repo::getAll() {
    return activities;
}

int FileRepo::store(const Activity &elem) {
    Repo::store(elem);
    FileRepo::write_to_file();
    return 0;
}

int FileRepo::modify(const Activity &elem) {
    Repo::modify(elem);
    FileRepo::write_to_file();
    return 0;
}

int FileRepo::recycle(const Activity &elem) {
    Repo::recycle(elem);
    FileRepo::write_to_file();
    return 0;
}

void FileRepo::load_from_file() {
    std::ifstream in(this -> file);
    if (!in) {
        throw RepoException("Fisier inexistent!");
    }
    float length = 0;
    string title, desc, type;
    while (in >> title >> desc >> type >> length){
        Activity act{title, desc, type, length};
        Repo::store(act);
    }
}

void FileRepo::write_to_file() {
    std::ofstream out(file);
    for (auto &act: Repo::getAll()) {
        out << act.getTitle() << "\n" << act.getDesc() << "\n" << act.getType() << "\n" << act.getLength() << "\n";
    }
}
