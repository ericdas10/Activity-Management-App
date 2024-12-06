//
// Created by HP on 31.03.2024.
//

#include "ui.h"
#include <iostream>
#include <limits>
using std::cin;
using std::cout;

void UI::menu() {
    cout << "Meniu:" << std :: endl;
    cout << "0-> Exit\n"
            "1-> Adaugare activitate\n"
            "2-> Stergere activitate\n"
            "3-> Modificare activitate\n"
            "4-> Cautare activitate\n"
            "5-> Printare activitati\n"
            "6-> Filtrare activitati dupa desctiere\n"
            "7-> Filtrare activitati dupa tip\n"
            "8-> Sortare activitati dupa titlu\n"
            "9-> Sortare activitati dupa descriere\n"
            "10-> Sortare activitati dupa tip(durata)\n"
            "11-> Meniu cos\n"
            "12-> Frecventa tip\n"
            "13-> Undo\n"
            "14-> Export cos in .html\n"<< std :: endl;
}

void UI::menu_cos() {
    cout << "Meniu cos:" << std :: endl;
    cout << "0-> Exit\n"
            "1-> Adaugare activitate\n"
            "2-> Printare activitati\n"
            "3-> Golire cos\n"<< std :: endl;
}

int UI::startUI(){
    while(true){
        int cmd = 0;
        menu();
        cout << "Introdu comanda:";
        cin >> cmd;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (cmd) {
            case 0:
                return 0;
            case 1: {
                float length;
                string title, desc, type;
                cout << "Introduceti titlul:";
                getline(cin, title);
                cout << "Introduceti descrierea:";
                getline(cin, desc);
                cout << "Introduceti tipul:";
                getline(cin, type);
                cout << "Introduceti durata:";
                cin >> length;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Activity elem{title, desc, type, length};
                try {
                    if (service.adaugare_activitate(elem) == 0)
                        cout << "Adaugare realizata cu succes!\n";
                } catch (const ServiceExceptio &error) {
                    std::cerr << "Eroare: " << error.what() << std::endl;
                } catch (const RepoException &error) {
                    std::cerr << "Eroare: " << error.what() << std::endl;
                }
                break;
            }
            case 2: {
                float length;
                string title, desc, type;
                cout << "Introduceti titlul:";
                getline(cin, title);
                cout << "Introduceti descrierea:";
                getline(cin, desc);
                cout << "Introduceti tipul:";
                getline(cin, type);
                cout << "Introduceti durata:";
                cin >> length;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Activity elem{title, desc, type, length};
                try {
                    if (service.stergere_activitate(elem) == 0)
                        cout << "Stergere realizata cu succes!\n";
                } catch (const ServiceExceptio &error) {
                    std::cerr << "Eroare: " << error.what() << std::endl;
                } catch (const RepoException &error) {
                    std::cerr << "Eroare: " << error.what() << std::endl;
                }
                break;
            }
            /*case 3:{
                float length;
                string title, desc, type;
                cout << "Introduceti titlul:";
                getline(cin, title);
                cout << "Introduceti descrierea:";
                getline(cin, desc);
                cout << "Introduceti tipul:";
                getline(cin, type);
                cout << "Introduceti durata:";
                cin >> length;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                float length1;
                string title1, desc1, type1;
                cout << "Introduceti titlul modificat:";
                getline(cin, title1);
                cout << "Introduceti descrierea modificata:";
                getline(cin, desc1);
                cout << "Introduceti tipul modificat:";
                getline(cin, type1);
                cout << "Introduceti durata modificata:";
                cin >> length1;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Activity elem{title, desc, type, length};
                Activity elem1{title1, desc1, type1, length1};
                try {
                    if (service.modificare_activitate(elem, elem1) == 0)
                        cout << "Stergere realizata cu succes!\n";
                } catch (const ServiceExceptio &error) {
                    std::cerr << "Eroare: " << error.what() << std::endl;
                } catch (const RepoException &error) {
                    std::cerr << "Eroare: " << error.what() << std::endl;
                }
                break;
            }
            case 4:{
                float length;
                string title, desc, type;
                cout << "Introduceti titlul:";
                getline(cin, title);
                cout << "Introduceti descrierea:";
                getline(cin, desc);
                cout << "Introduceti tipul:";
                getline(cin, type);
                cout << "Introduceti durata:";
                cin >> length;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Activity elem{title, desc, type, length};
                try {
                    if(service.cautare_act(elem) == 1)
                        cout << "Elementul se afla in lista!\n";
                    else
                        cout << "Elementul nu se afla in lista!\n";

                } catch (const ServiceExceptio &error) {
                    std::cerr << "Eroare: " << error.what() << std::endl;
                } catch (const RepoException &error) {
                    std::cerr << "Eroare: " << error.what() << std::endl;
                }
                break;
            }*/
            case 5:{
                cout << "TITLU\tDESCRIERE\tTIP\tDURATA\n";
                for(const Activity& i : service.getAll()){
                    cout << i.getTitle() << "\t" <<i.getDesc()<< "\t" << i.getType() << "\t" << i.getLength() << "\n";
                }
                break;
            }
            case 6:{
                string desc;
                cout << "Introduceti descrierea cautata:";
                cin >> desc;
                try {
                    vector<Activity> vector = service.filtrare_desc(desc);
                    if (vector.empty() != 1)
                        cout << "Filtrare dupa descriere: " << "\n";
                    for (const Activity& i : vector) {
                        cout << i.getTitle() << "\t" << i.getDesc() << "\t" << i.getType() << "\t"<< i.getLength() << "\n";
                    }
                }catch (const ServiceExceptio& error) {
                    std::cerr << "Eroarea: " << error.what() << std::endl;
                }catch (const RepoException& error) {
                    std::cerr << "Eroarea: " << error.what() << std::endl;
                }
                break;
            }
            case 7:{
                string type;
                cout << "Introduceti tipul cautat:";
                cin >> type;
                try {
                    vector<Activity> vector = service.filtrare_type(type);
                    if (vector.empty() != 1)
                        cout << "Filtrare dupa tip: " << "\n";
                    for (const Activity& i : vector) {
                        cout << i.getTitle() << "\t" << i.getDesc() << "\t" << i.getType() << "\t"<< i.getLength() << "\n";
                    }
                }catch (const ServiceExceptio& error) {
                    std::cerr << "Eroarea: " << error.what() << std::endl;
                }catch (const RepoException& error) {
                    std::cerr << "Eroarea: " << error.what() << std::endl;
                }
                break;
            }
            case 8:{
                vector<Activity> vector = service.sortare_titlu();
                if (vector.empty() != 1)
                    cout << "Lista sortata dupa titlu:" << "\n";
                else{
                    cout << "Sortare indisponibila!" << "\n";
                }
                for (const Activity& i : vector) {
                    cout << i.getTitle() << "\t" << i.getDesc() << "\t" << i.getType() << "\t"<< i.getLength() << "\n";
                }
                break;
            }
            case 9:{
                vector<Activity> vector = service.sortare_descriere();
                if (vector.empty() != 1)
                    cout << "Lista sortata dupa descriere:" << "\n";
                else{
                    cout << "Sortare indisponibila!" << "\n";
                }
                for (const Activity& i : vector) {
                    cout << i.getTitle() << "\t" << i.getDesc() << "\t" << i.getType() << "\t"<< i.getLength() << "\n";
                }
                break;
            }
            case 10:{
                vector<Activity> vector = service.sortare_tip_durata();
                if (vector.empty() != 1)
                    cout << "Lista sortata dupa tip + durata:" << "\n";
                else{
                    cout << "Sortare indisponibila!" << "\n";
                }
                for (const Activity& i : vector) {
                    cout << i.getTitle() << "\t" << i.getDesc() << "\t" << i.getType() << "\t"<< i.getLength() << "\n";
                }
                break;
            }
            case 11:{
                int ok = 0;
                while(ok == 0){
                    int cmd_cos = 0;
                    menu_cos();
                    cout << "Introdu comanda:";
                    cin >> cmd_cos;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    switch (cmd_cos){
                        case 0:{
                            ok = 1;
                            break;
                        }
                        case 1:{
                            string title;
                            cout << "Introduceti titlul:";
                            getline(cin, title);
                            try {
                                service.adaugare_cos(title);
                                cout << "Adaugare realizata cu succes in cos!\n";
                            } catch (const ServiceExceptio &error) {
                                std::cerr << "Eroare: " << error.what() << std::endl;
                            } catch (const RepoException &error) {
                                std::cerr << "Eroare: " << error.what() << std::endl;
                            }
                            break;
                        }

                        case 2:{
                            cout << "Activitatile din cos:\n";
                            for(const Activity& i : service.cos_getAll()){
                                cout << i.getTitle() << "\t" <<i.getDesc()<< "\t" << i.getType() << "\t" << i.getLength() << "\n";
                            }
                            break;
                        }

                        case 3:{
                            service.golire_cos();
                            cout << "Cos golit cu succes!\n";
                            break;
                        }

                        case 4:{
                            int nr;
                            cout << "Numerul de activitati de adaugat este:\n";
                            cin >> nr;
                            service.cos_random(nr);
                            break;
                        }
                        default:
                            cout << "Introduceti o comanda valida!\n" << std::endl;
                            break;
                    }
                }

            }
            case 12:{
                std::map<string, int> var = service.add_type_freq();
                for(auto i: var){
                    cout << "Cheie: " << i.first << " Valoare: " << i.second << std::endl;
                }
            }
            case 13:{
                try{
                    if (service.undo() == 0) {
                        cout << "Operatiune efectuata cu succes\n";
                    }
                }catch (ServiceExceptio& error){
                    std::cerr << "Eroare: " << error.what() << std::endl;
                }
                break;
            }
            case 14:{
                string nume_fisier;
                cout << "Numele fisierului este (numele trebuie sa contina .html): ";
                cin >> nume_fisier;
                try {
                    if (service.export_html(nume_fisier) == 0) {
                        cout << "Fisier exportat cu succes!\n";
                    }
                }catch (ServiceExceptio& error){
                    std::cerr << "Eroarea: " << error.what() << std::endl;
                }
                break;
            }
            default:
                cout << "Introduceti o comanda valida!\n" << std::endl;
                break;
        }
    }
}
