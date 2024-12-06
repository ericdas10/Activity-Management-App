#include "service.h"
#include "repo.h"
#include "gui.h"
#include "teste.h"
#include "gui_mw.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
    test_all();
    QApplication a(argc, argv);

    FileRepo repo("../saves/activity.txt");
    Service service{repo};

  //  GUI gui(service);
  //  gui.setWindowTitle("Activitati");
    //gui.show();

    GUIModels gui{service};
    gui.show();

    return QApplication::exec();
}
