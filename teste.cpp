//
// Created by HP on 09.04.2024.
//

#include "teste.h"
#include <cassert>
#include <cstring>

void test_domain(){
    Activity act_null;
    assert(act_null.getTitle().empty());
    assert(act_null.getLength() == 0);

    const float length = 200;
    Activity act = Activity{"a", "a", "a", length};
    assert(act.getLength() == 200);
    assert(act.getTitle() == "a");
    assert(act.getDesc() == "a");
    assert(act.getType() == "a");

    const float test = 100;
    act.setTitle("b");
    act.setDesc("b");
    act.setLength(test);

    assert(act.getDesc() == "b");
    assert(act.getTitle() == "b");
    assert(act.getLength() == 100);
}

void test_repo(){
    const float length = 200;
    Activity act = Activity{"a", "a", "a", length};
    Repo repo;
    repo.store(act);
    assert(repo.getAll().size() == 1);

    vector<Activity> vect = repo.getAll();
    assert(vect.size() == 1);

    Activity verifica = repo.getAll()[0];
    assert(verifica.getLength() == 200);
    assert(verifica.getTitle() == "a");
    try{repo.store(act);}catch (RepoException& ERR){
        assert(strcmp(ERR.what(), "Element existent") == 0);
    }
    const float lng = 300;
    Activity act1 = Activity{"b", "b", "b", lng};
    repo.store(act1);
    assert(repo.getAll().size() == 2);

    /*assert(repo.search(act) == 1);
    const float l = 60;
    bool ok = false;
    try{repo.search(Activity{"c","c","c", l});}catch (const RepoException&ERR){
        ok = true;
        assert(strcmp(ERR.what(), "Element inexistent!") == 0);
    }
    assert(ok == true);
    const float lng1 = 100;
    Activity act2 = Activity{"d", "d", "d", lng1};
    assert(repo.modify(act1, act2) == 0);
    verifica = repo.getAll()[1];
    assert(verifica.getLength() == 100);
    assert(verifica.getType() == "d");

    const float lng2 = 300;
    Activity act3 = Activity{"X", "X", "X", lng2};
    ok = false;
    try {repo.modify(act3, act2);}catch (const RepoException&ERR){
        ok = true;
        assert(strcmp(ERR.what(), "Modificare invalida!") == 0);
    }
    assert(ok == true);*/
}

void test_service(){
    Repo repo;
    Cos cos;
    Service service{repo};
    const float lgt1 = 1000, lgt2 = 2000, lgt3 = 3000;
    service.adaugare_activitate(Activity{"Alpha", "Alpha", "Alpha", lgt1});
    assert(service.getAll().size() == 1);
    Activity verifica = service.getAll()[0];
    assert(verifica.getLength() == 1000);
    assert(verifica.getType() == "Alpha");
    bool a = false;
    try{service.adaugare_activitate(Activity{ "Alpha", "Alpha", "Alpha", -lgt1});}catch (const ServiceExceptio& ERR){
        a = true;
        assert(strcmp(ERR.what(), "Element invalid! Mai incearca!") == 0);
    }
    assert(a == true);
    service.stergere_activitate(Activity{"Alpha", "Alpha", "Alpha", lgt1});
    assert(service.getAll().empty() == 1);
    bool s = false;
    try{service.stergere_activitate(Activity{"", "Alpha", "Alpha", lgt1});}catch (const ServiceExceptio&ERR){
        s = true;
        assert(strcmp(ERR.what(), "Element invalid! Mai incearca!") == 0);
    }
    assert(s == true);

    Activity elem1{"Alpha", "Alpha", "Alpha", lgt1};
    Activity elem2{"Beta", "Beta", "Beta", lgt2};
    Activity elem3{"Teta", "Teta", "Teta", lgt3};
    service.adaugare_activitate(elem1);
    service.adaugare_activitate(elem2);
    service.adaugare_activitate(elem3);

    assert(service.getAll().size() == 3);

    /*assert(service.cautare_act(elem1) == 1);
    bool g = false;
    try{
        service.cautare_act(Activity{"", "", "aa", -lgt1});
    } catch (const ServiceExceptio&Err){
        g = true;
        assert(strcmp(Err.what(), "Element invalid! Mai incearca!") == 0);
    }
    assert(g == true);
    const float lng = 9000;
    Activity elem_mod{"Beta", "Beta", "Omega", lng};
    service.modificare_activitate(elem2, elem_mod);
    assert(service.cautare_act(elem_mod) == 1);
    bool ok = false;
    const float lng1 = -900;
    try{
        service.modificare_activitate(Activity{"", "", "", lng1}, Activity{"", "", "", lng1});
    }catch (const ServiceExceptio& ERR){
        ok = true;
        assert(strcmp(ERR.what(), "Element invalid! Mai incearca!") == 0);
    }
    assert(ok == true);
    vector<Activity> vector1 = service.filtrare_desc("Alpha");
    assert(vector1.size() == 1);
    assert(vector1[0].getLength() == lgt1);
    int filt = false;
    try{
        vector<Activity> v = service.filtrare_desc("");}catch (const ServiceExceptio& ERR){
        filt = true;assert(strcmp(ERR.what(), "Element invalid! Mai incearca!") == 0);
    }
    assert(filt == true);*/

    vector<Activity> vector2 = service.filtrare_type("Alpha");
    assert(vector2.size() == 1);
    assert(vector2[0].getLength() == lgt1);
    int filt1 = false;
    try{vector<Activity> v = service.filtrare_type("");}catch (const ServiceExceptio& ERR){
        filt1 = true;assert(strcmp(ERR.what(), "Element invalid! Mai incearca!") == 0);
    }
    assert(filt1 == true);

    for(const auto& act : repo.getAll()){
        service.stergere_activitate(act);
    }

    service.adaugare_activitate(elem2);
    service.adaugare_activitate(elem1);
    service.adaugare_activitate(elem3);

    assert(service.getAll().size() == 3);

    vector<Activity> vector_sortat = service.sortare_titlu();
    assert(vector_sortat[0].getTitle() == "Alpha");
    assert(vector_sortat[1].getTitle() == "Beta");
    assert(vector_sortat[2].getTitle() == "Teta");

    vector_sortat = service.sortare_descriere();

    assert(vector_sortat[0].getTitle() == "Alpha");
    assert(vector_sortat[1].getTitle() == "Beta");
    assert(vector_sortat[2].getTitle() == "Teta");

    const float lgt4 = 10;
    Activity elem4{"Teta", "Teta", "Teta", lgt4};
    service.adaugare_activitate(elem4);

    vector_sortat = service.sortare_tip_durata();

    assert(vector_sortat[0].getTitle() == "Alpha");
    assert(vector_sortat[1].getTitle() == "Beta");
    assert(vector_sortat[2].getTitle() == "Teta");
    assert(vector_sortat[3].getTitle() == "Teta");
}

void test_cos(){
    Repo repo;
    Cos cos;
    Service svc{repo};
    const float lng1 = 100, lng2 = 200, lng3 = 300;
    Activity elem1{"A", "A", "A", lng1};
    Activity elem2{"B", "B", "B", lng2};
    Activity elem3{"C", "C", "C", lng3};
    assert(svc.adaugare_activitate(elem1) == 0);
    assert(svc.adaugare_activitate(elem2) == 0);
    assert(svc.adaugare_activitate(elem3) == 0);
    assert(svc.getAll().empty() == 0);
    //assert(svc.adaugare_cos(elem1.getTitle()) == 0);
    //assert(svc.cos_getAll().empty() == 0);
    int ok = false;
    try{
        svc.adaugare_cos("");
    }catch (const ServiceExceptio& ERR){
        ok = true;
        //assert(strcmp(ERR.what(), "Element invalid! Mai incearca!") == 0);
    }
    assert(ok == true);
    int nr = 2;
    svc.golire_cos();
    assert(svc.cos_getAll().empty() == 1);
    svc.cos_random(nr);
    assert(svc.cos_getAll().size() == 2);
    svc.golire_cos();
    assert(svc.cos_getAll().empty() == 1);
}

void test_stergere_repo(){
    const float length = 200;
    Activity act = Activity{"a", "a", "a", length};
    Repo repo;
    assert(repo.store(act) == 0);
    assert(repo.getAll().size() == 1);
    assert(repo.recycle(act) == 0);
    int ok = false;
    try{
        repo.recycle(act);
    }catch(const RepoException& err){
        ok = true;
        assert(strcmp(err.what(), "Lista este vida!") == 0);
    }
    assert(ok == true);
    assert(repo.store(act) == 0);
    assert(repo.getAll().size() == 1);
    int ok1 = false;
    try{
        repo.recycle(Activity{"b", "b", "b", length});
    }catch(const RepoException& err){
        ok1 = true;
        assert(strcmp(err.what(), "Element inexistent!") == 0);
    }
    assert(ok1 == true);

}

void test_all(){
    test_domain();
    test_repo();
    test_service();
    test_stergere_repo();
    test_cos();
}