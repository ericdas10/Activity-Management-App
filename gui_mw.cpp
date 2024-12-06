//
// Created by Eric on 6/4/2024.
//

#include "gui_mw.h"
#include <utility>
#include <QApplication>

void GUIModels::componente_init() {
    auto *forms_widget = new QWidget;
    f_layout = new QFormLayout;

    label_title = new QLabel("Titlul este:");
    titlu = new QLineEdit;
    label_desc = new QLabel("Descrierea este:");
    desc = new QLineEdit;
    type = new QLineEdit;
    label_type = new QLabel("Tipul este:");
    durata = new QLineEdit;
    label_length = new QLabel("Durata este:");


    f_layout->addRow(label_title,titlu);
    f_layout->addRow(label_desc, desc);
    f_layout->addRow(label_type, type);
    f_layout->addRow(label_length, durata);

    auto slider_range_layout = new QHBoxLayout;
    auto random_label = new QLabel("Random range:");
    cos_random = new QSlider(Qt :: Horizontal);
    cos_random->setMinimum(1);
    slider_range_layout->addWidget(random_label);
    slider_range_layout->addWidget(cos_random);
    f_layout->addRow(slider_range_layout);

    adaugare_activitate = new QPushButton("Adauga");
    stergere_activitate = new QPushButton("Sterge");
    modificare_activitate = new QPushButton("Modifica");
    cauta = new QPushButton("Cauta");
    filtrare_desc = new QPushButton("Filtrare dupa descriere");
    filtrare_tip = new QPushButton("Filtrare dupa tip");

    sortare_titlu = new QPushButton("Sortare dupa titlu");
    sortare_descriere = new QPushButton("Sortare dupa descriere");
    sortare_tip_durata = new QPushButton("Sortare dupa tip si durata");

    undo = new QPushButton("Undo");
    refresh = new QPushButton("Refresh");
    close = new QPushButton("Inchide");

    coswish = new QPushButton("Lista de activitati");
    draw = new QPushButton("Desen Cos");

    add_cos = new QPushButton("Adauga Cos");
    clean_cos = new QPushButton("Golire Cos");
    random_cos = new QPushButton("Adauga random Cos");

    auto *button_layout_1 = new QHBoxLayout;
    button_layout_1->addWidget(adaugare_activitate);
    button_layout_1->addWidget(stergere_activitate);
    button_layout_1->addWidget(modificare_activitate);

    auto *button_layout_2 = new QHBoxLayout;
    button_layout_2->addWidget(cauta);
    button_layout_2->addWidget(filtrare_desc);
    button_layout_2->addWidget(filtrare_tip);

    auto * button_layout_3 = new QHBoxLayout;
    button_layout_3->addWidget(sortare_titlu);
    button_layout_3 ->addWidget(sortare_descriere);
    button_layout_3 ->addWidget(sortare_tip_durata);
    button_layout_3 ->setSpacing(10);

    auto *button_layout_4 = new QHBoxLayout;
    button_layout_4->addWidget(close);
    button_layout_4->addWidget(refresh);
    button_layout_4->addWidget(undo);

    auto *button_layout_5 = new QHBoxLayout;
    button_layout_5->addWidget(coswish);
    button_layout_5->addWidget(draw);

    auto *button_layout_6 = new QHBoxLayout;
    button_layout_6->addWidget(add_cos);
    button_layout_6->addWidget(clean_cos);
    button_layout_6->addWidget(random_cos);


    f_layout->addRow(button_layout_1);
    f_layout->addRow(button_layout_2);
    f_layout->addRow(button_layout_4);
    f_layout->addRow(button_layout_5);
    f_layout->addRow(button_layout_6);

    forms_widget->setLayout(f_layout);

    auto *tabel_widget = new QWidget;
    tabel = new QTableView;
    auto *lista_layout = new QVBoxLayout;
    lista_layout->addWidget(tabel);
    lista_layout->addLayout(button_layout_3);
    tabel_widget->setLayout(lista_layout);


    auto *main_layout_second = new QHBoxLayout;
    main_layout_second->addWidget(forms_widget);
    main_layout_second->addWidget(tabel_widget);

    lista_butoane = new QListWidget;

    main_layout = new QVBoxLayout;

    main_layout->addLayout(main_layout_second);
    main_layout->addWidget(lista_butoane);

    this->setLayout(main_layout);

    actualizeaza_butoane();
}

void GUIModels::semnale() {
    QObject ::connect(coswish,&QPushButton :: clicked, [&](){
        auto wish = new CosWish(service, this);
        wish->show();
    });

    QObject ::connect(draw, &QPushButton :: clicked, [this](){
        auto desenare = new Painting(service,this);
        desenare->show();
    });

    QObject ::connect(add_cos, &QPushButton :: clicked, [this](){
        try {
            service.adaugare_cos(titlu->text().toStdString());
            QMessageBox ::information(this, tr("Success!"), tr("Adaugat element cu success!"));

        }catch (ServiceExceptio &error){
            QMessageBox ::warning(this, tr("Atentie"), error.what());
        }
    });

    QObject ::connect(clean_cos, &QPushButton :: clicked, [this](){
        service.golire_cos();
        QMessageBox ::information(this, tr("Success!"), tr("Adaugat element cu success!"));
    });

    QObject ::connect(random_cos, &QPushButton :: clicked, [this](){
        try{
            auto val = this->cos_random->value();
            service.cos_random(val);
            QMessageBox ::information(this, tr("Success!"), tr("Random cu success!"));
        }catch (ServiceExceptio &error){
            QMessageBox ::warning(this, tr("Atentie"), error.what());
        }
    });
    QObject ::connect(adaugare_activitate, &QPushButton ::clicked, [&](){
        try {
            Activity elem{titlu->text().toStdString(), desc->text().toStdString(), type->text().toStdString(), durata->text().toFloat()};
            service.adaugare_activitate(elem);
            curata_tabel(service.getAll());
            actualizeaza_butoane();
            QMessageBox::information(this, tr("Succes"), tr("Medicamentul a fost adaugat cu succes."));
        } catch (const ServiceExceptio& error) {
            QMessageBox::warning(this, tr("Atentie"), error.what());
        } catch(const RepoException& error){
            QMessageBox::warning(this, tr("Atentie"), error.what());
        }
    });

    QObject ::connect(stergere_activitate, &QPushButton :: clicked, [&](){
        try {
            Activity elem{titlu->text().toStdString(), desc->text().toStdString(), type->text().toStdString(), durata->text().toFloat()};
            service.stergere_activitate(elem);
            curata_tabel(service.getAll());
            actualizeaza_butoane();
            QMessageBox ::information(this, tr("Succes"), tr("Element sters cu succes!"));
        }catch (const ServiceExceptio& error) {
            QMessageBox::warning(this, tr("Atentie"), error.what());
        } catch(const RepoException& error){
            QMessageBox::warning(this, tr("Atentie"), error.what());
        }
    });

    QObject ::connect(modificare_activitate, &QPushButton :: clicked, [&](){
        try {
            Activity elem{titlu->text().toStdString(), desc->text().toStdString(), type->text().toStdString(), durata->text().toFloat()};
            service.modificare_activitate(elem);
            curata_tabel(service.getAll());
            actualizeaza_butoane();
            QMessageBox ::information(this, tr("Succes"), tr("Element modificat cu success"));
        }catch (const ServiceExceptio& error) {
            QMessageBox::warning(this, tr("Atentie"), error.what());
        } catch(const RepoException& error){
            QMessageBox::warning(this, tr("Atentie"), error.what());
        }
    });

    QObject ::connect(close, &QPushButton :: clicked, [&](){
        QApplication :: quit();
    });

    QObject ::connect(cauta, &QPushButton :: clicked, [&](){
        try{
            Activity act = service.cautare_act(titlu->text().toStdString());
            std :: vector <Activity> cauta_acts;
            cauta_acts.push_back(act);
            curata_tabel(cauta_acts);
        }catch (const ServiceExceptio& error) {
            QMessageBox::warning(this, tr("Atentie"), error.what());
        } catch(const RepoException& error){
            QMessageBox::warning(this, tr("Atentie"), error.what());
        }
    });

    QObject ::connect(refresh, &QPushButton :: clicked, [&](){
        curata_tabel(service.getAll());
    });

    QObject ::connect(filtrare_desc, &QPushButton :: clicked, [&](){
        try {
            auto filter_desc = service.filtrare_desc(desc->text().toStdString());
            curata_tabel(filter_desc);
        }catch (const ServiceExceptio& error) {
            QMessageBox::warning(this, tr("Atentie"), error.what());
        }
    });

    QObject ::connect(filtrare_tip, &QPushButton :: clicked, [&](){
        try{
            auto filter_tip = service.filtrare_type(type->text().toStdString());
            curata_tabel(filter_tip);
        }catch (ServiceExceptio &error){
            QMessageBox ::warning(this, tr("Atentie"), error.what());
        }
    });

    QObject ::connect(sortare_titlu, &QPushButton ::clicked, [&](){
        auto vector_sortat = service.sortare_titlu();
        curata_tabel(vector_sortat);
    });

    QObject ::connect(undo, &QPushButton :: clicked, [&](){
        try{
            auto undo_lista = service.undo();
            curata_tabel(service.getAll());
            if(!undo_lista){
                QMessageBox ::information(this, tr("Succes"), tr("Undo facut cu succes!"));
            }
        }catch (ServiceExceptio &error){
            QMessageBox ::warning(this, tr("Atentie"), error.what());
        }
    });

    QObject ::connect(sortare_descriere, &QPushButton :: clicked, [&](){
        auto vector_sortat = service.sortare_descriere();
        curata_tabel(vector_sortat);
    });

    QObject ::connect(sortare_tip_durata, &QPushButton :: clicked, [&](){
        auto vector_sortat = service.sortare_tip_durata();
        curata_tabel(vector_sortat);
    });
}

void GUIModels::actualizeaza_butoane() {
    lista_butoane->clear();
    auto maps = service.add_type_freq();
    for (const auto &m : maps) {
        auto str = QString::fromStdString(m.first);
        auto *button_nou = new QPushButton(str);
        auto *item = new QListWidgetItem();
        lista_butoane->addItem(item);
        lista_butoane->setItemWidget(item, button_nou);
        QObject::connect(button_nou, &QPushButton::clicked, [this, value = m.second]() {
            QMessageBox::information(this, tr("Frecventa"), tr("Numar de aparitii: %1").arg(value));
        });
    }
}


void GUIModels::curata_tabel(vector <Activity> acts) {
    models->set_acts(std::move(acts));
    tabel->update();
    tabel->repaint();
}

void CosWish::curata_lista(const vector<Activity>& acts) {
    mdl->set_acts(acts);
    lista->update();
    lista->repaint();
}

void CosWish::init_componente_secund() {
    auto second_main_layout = new QHBoxLayout(this);

    auto cos_details = new QWidget;
    auto form_layout = new QFormLayout;

    denumire = new QLabel("Titlul activitatii este este: ");
    cos_random_1 = new QLabel("Numarul de activitati pt lista: ");
    exportare = new QLabel("Nume fisier HTML:");

    title_activity = new QLineEdit;
    cos_random_2 = new QLineEdit;
    exp = new QLineEdit;

    form_layout->addRow(denumire, title_activity);
    form_layout->addRow(cos_random_1, cos_random_2);
    form_layout->addRow(exportare,exp);

    auto button_layout = new QHBoxLayout;

    adaugare_cos = new QPushButton("Adauga activitate");
    golire_cos = new QPushButton("Goleste");
    export_html = new QPushButton("Export HTML");
    cos_random = new QPushButton("Random");
    close_cos = new QPushButton("Inchide lista");

    button_layout->addWidget(adaugare_cos);
    button_layout->addWidget(golire_cos);
    button_layout->addWidget(export_html);
    button_layout->addWidget(cos_random);

    auto button_layout_2 = new QHBoxLayout;
    button_layout_2->addWidget(close_cos);

    form_layout->addRow(button_layout);
    form_layout->addRow(button_layout_2);

    cos_details->setLayout(form_layout);

    lista = new QListView;
    lista->setUniformItemSizes(true);

    second_main_layout->addWidget(lista);
    second_main_layout->addWidget(cos_details);

    this->setLayout(second_main_layout);
}

void CosWish::semnale_secunde() {
    QObject ::connect(close_cos, &QPushButton :: clicked, [&](){
        service.sterge_listener(this);
        QDialog :: close();
    });

    QObject ::connect(adaugare_cos, &QPushButton :: clicked, [&](){
        try {
            service.adaugare_cos(title_activity->text().toStdString());
            QMessageBox ::information(this, tr("Success!"), tr("Adaugat element cu success!"));
            service.notify();

        }catch (ServiceExceptio &error){
            QMessageBox ::warning(this, tr("Atentie"), error.what());
        }
    });
    QObject ::connect(golire_cos, &QPushButton :: clicked, [&](){
        try {
            service.golire_cos();
            QMessageBox ::information(this, tr("Success!"), tr("Sterse elementele cu success!"));
            service.notify();

        } catch (ServiceExceptio &error){
            QMessageBox ::warning(this, tr("Atentie"), error.what());
        }
    });
    QObject ::connect(cos_random, &QPushButton :: clicked, [&]() {
        try{
            if(cos_random_2->text().isEmpty()){
                throw ServiceExceptio("Input invalid!");
            }
            service.cos_random(cos_random_2->text().toInt());
            QMessageBox ::information(this, tr("Success!"), tr("Random cu success!"));
            service.notify();
        }catch (ServiceExceptio &error){
            QMessageBox ::warning(this, tr("Atentie"), error.what());
        }
    });

    QObject ::connect(export_html, &QPushButton :: clicked, [&](){
        try {
            service.export_html(exp->text().toStdString());
            QMessageBox ::information(this, tr("Export succes!"), tr("Export reusit cu success!"));
        }
        catch (ServiceExceptio &error){
            QMessageBox ::warning(this, tr("Atentie"), error.what());
        }
    });
}

