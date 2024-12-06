#pragma once

#include "service.h"
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

class COS: public QDialog, public  Observer{
private:
    Service& service;

    QPushButton *adaugare_cos{}, *golire_cos{}, *cos_random{}, *export_html{}, *close_cos{};
    QLabel *exportare{}, *denumire{}, *cos_random_1{};
    QLineEdit *exp{}, *title_activity{}, *cos_random_2{};
    QListWidget *lista{};

    void curata_lista();
    void init_componente_secund();
    void semnale_secunde();

public:
    explicit COS(Service& serv,QWidget *parent = nullptr) :service(serv), QDialog(parent){
        init_componente_secund();
        semnale_secunde();
        service.adauga_listener(this);
        curata_lista();
    }
    void update() override{
        curata_lista();
    }
};

class GUI : public QWidget{
private:
    Service& service;

    QPushButton *adaugare_activitate{}, *stergere_activitate{}, *modificare_activitate{}, *cauta{}, *close{}, *filtrare_tip{}, *filtrare_desc{}, *sortare_titlu{}, *sortare_tip_durata{},
    *sortare_descriere{}, *refresh{}, *undo{}, *cos{}, *draw{}, *add_cos{}, *clean_cos{}, *random_cos{};

    QSlider *cos_random{};

    QFormLayout *f_layout{};
    QVBoxLayout *main_layout{};

    QLabel *label_title{},*label_desc{},*label_type{},*label_length{};
    QLineEdit *titlu{}, *desc{}, *type{}, *durata{};

    QTableWidget *tabel{};
    QListWidget *lista{}, *lista_butoane{};

    void componente_init();
    void semnale();
    void curata_tabel();
    void actualizeaza_butoane();

public:
    explicit GUI(Service& service): service(service){
        GUI :: componente_init();
        GUI :: semnale();
        GUI :: curata_tabel();
    };
    static QString to_q_string_method(const Activity& act);
};