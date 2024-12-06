//
// Created by HP on 31.03.2024.
//

#pragma once
#include "vect_dinamic.h"
#include <stdexcept>
#include "domain.h"
#include <vector>
#include <utility>
#include <fstream>
using std::vector;

class RepoException : public std::runtime_error {
public:
    explicit RepoException(const std::string& msg) : std::runtime_error(msg){}

};

class AbsRepo{
public:
    AbsRepo() = default;

    AbsRepo(const AbsRepo& other) = delete;
    AbsRepo& operator=(const AbsRepo& other) = delete;
    AbsRepo(const AbsRepo&& other) = delete;
    AbsRepo&& operator=(const AbsRepo&& other) = delete;

    virtual int store(const Activity& elem)=0;

    virtual int recycle(const Activity& elem)=0;

    virtual int modify(const Activity& elem)=0;

    virtual vector<Activity> getAll()=0;

    virtual ~AbsRepo() = default;

    virtual Activity search(const string& title)=0;
};

class Repo: public AbsRepo{
private:
    vector<Activity> activities;
public:
    Repo() = default;

    Repo(const Repo& other) = delete;
    Repo& operator=(const Repo& other) = delete;
    Repo(const Repo&& other) = delete;
    Repo&& operator=(const Repo&& other) = delete;

    ~Repo() override = default;

    int store(const Activity& elem) override;

    int recycle(const Activity& elem) override;

    int modify(const Activity& elem) override;

    Activity search(const string& title) override;

    vector<Activity> getAll() override;
};

class FileRepo: public Repo{
private:
    string file;
    void load_from_file();
    void write_to_file();

public:
    explicit FileRepo(string name): Repo(), file{std::move(name)}{
        load_from_file();
    }
    int store(const Activity& elem) override;

    int recycle(const Activity& elem) override;

    int modify(const Activity& elem) override;
};