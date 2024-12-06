//
// Created by Eric on 6/4/2024.
//

#pragma once
#include "service.h"
#include <QAbstractListModel>
#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QAbstractListModel>
#include "painting.h"
#include "QWidget"
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QMainWindow>
#include <QDialog>
#include <QTableWidget>
#include "observer.h"
#include <utility>
#include <vector>

using std::vector;

class ListModels: public QAbstractListModel{
    vector <Activity> activity;
public:
    explicit ListModels(vector <Activity> act): activity(std::move(act)){};
    [[nodiscard]]int rowCount(const QModelIndex& parent) const override{
        return (int)activity.size();
    }

    [[nodiscard]]QVariant data(const QModelIndex& index, int role) const override{

        if (role == Qt::DisplayRole) {
            const auto& act = activity.at(index.row());
            return QString::fromStdString(act.getTitle() + " " + act.getDesc() + " " + act.getType() + " " + std::to_string(act.getLength()));
        }
        return QVariant{};
    }
    void set_acts(const vector<Activity>& act) {
        beginResetModel();
        activity = act;
        endResetModel();
    }
};


class TableModels : public QAbstractTableModel{
     vector <Activity> activity;
public:
    explicit TableModels(vector <Activity> act): activity(std::move(act)){};
    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override{
        return (int)activity.size();
    }
    [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override{
        return 4;
    }
    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override{
        if(role == Qt::DisplayRole){
            Activity act = activity.at(index.row());
            if(index.column() == 0){
                QString str = QString ::fromStdString(act.getTitle());
                return str;
            }else if(index.column() == 1){
                QString str = QString ::fromStdString(act.getDesc());
                return str;
            }else if(index.column() == 2){
                QString str = QString ::fromStdString(act.getType());
                return str;
            }else if(index.column() == 3){
                QString str = QString ::number(act.getLength());
                return str;
            }
        }
        return QVariant{};
    }

    void set_acts(vector <Activity> act){
        beginResetModel();
        this->activity = std::move(act);
        endResetModel();
    }
};

class CosWish : public QDialog, public Observer{
private:
    Service& service;

    QPushButton *adaugare_cos{}, *golire_cos{}, *cos_random{}, *export_html{}, *close_cos{};
    QLabel *exportare{}, *denumire{}, *cos_random_1{};
    QLineEdit *exp{}, *title_activity{}, *cos_random_2{};
    QListView *lista{};
    ListModels *mdl{};
    void curata_lista(const vector <Activity>& act);
    void init_componente_secund();
    void semnale_secunde();

public:
    explicit CosWish(Service& serv,QWidget *parent = nullptr) :service(serv), QDialog(parent){
        init_componente_secund();
        service.adauga_listener(this);
        mdl = new ListModels(service.cos_getAll());
        lista->setModel(mdl);
        semnale_secunde();
        curata_lista(service.cos_getAll());
    }
    void update() override{
        curata_lista(service.cos_getAll());
    }
};

class GUIModels : public QWidget{
private:
    Service& service;

    QPushButton *adaugare_activitate{}, *stergere_activitate{}, *modificare_activitate{}, *cauta{}, *close{}, *filtrare_tip{}, *filtrare_desc{}, *sortare_titlu{}, *sortare_tip_durata{},
            *sortare_descriere{}, *refresh{}, *undo{}, *coswish{}, *draw{}, *add_cos{}, *clean_cos{}, *random_cos{};

    QSlider *cos_random{};

    QFormLayout *f_layout{};
    QVBoxLayout *main_layout{};

    TableModels *models;

    QLabel *label_title{},*label_desc{},*label_type{},*label_length{};
    QLineEdit *titlu{}, *desc{}, *type{}, *durata{};

    QTableView *tabel{};
    QListWidget *lista{}, *lista_butoane{};

    void componente_init();
    void semnale();
    void curata_tabel(vector <Activity>);
    void actualizeaza_butoane();


public:
    explicit GUIModels(Service& service): service(service){
        GUIModels:: componente_init();
        GUIModels :: semnale();
        models = new TableModels{service.getAll()};
        tabel->setModel(models);
        GUIModels :: curata_tabel(service.getAll());
    };
};
