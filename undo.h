//
// Created by Eric on 22.04.2024.
//

#pragma once
#include "repo.h"
#include <utility>

class ActiuneUndo{
public:
    virtual void doUndo() = 0;
    ActiuneUndo() = default;
    ActiuneUndo(const ActiuneUndo& other) = delete;
    ActiuneUndo& operator=(const ActiuneUndo& other) = delete;
    ActiuneUndo(ActiuneUndo&& other) = delete;
    ActiuneUndo& operator=(ActiuneUndo&& other) = delete;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga: public ActiuneUndo{
private:
    AbsRepo& repo;
    Activity act;
public:
    UndoAdauga(AbsRepo &repo, Activity act): repo{repo}, act(std::move(act)) {};
    void doUndo() override{
        repo.recycle(act);
    }
};

class UndoModifica: public ActiuneUndo{
private:
    AbsRepo& repo;
    Activity act;
public:
    UndoModifica(AbsRepo& repo, Activity act): repo{repo}, act{std::move(act)}{};
    void doUndo() override{
        repo.modify(act);
    }
};

class UndoSterge: public ActiuneUndo{
private:
    AbsRepo& repo;
    Activity act;
public:
    UndoSterge(AbsRepo& repo, Activity act): repo{repo}, act(std::move(act)){};
    void doUndo() override{
        repo.store(act);
    }
};
