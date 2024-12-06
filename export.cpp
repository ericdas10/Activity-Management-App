//
// Created by Eric on 22.04.2024.
//

#include "export.h"

void Export::export_html(const std::string &name, const vector<Activity> &acts) {
    std::ofstream out(name, std::ios::trunc);

    if (!out.is_open()) {
        throw ServiceExceptio("Nu s-a putut gasii:" + name);
    }

    out << "<html><body>" << "\n";
    out << R"(<table border="1" style="width:100%">)" << "\n";
    out << "<th>" << "Titlul activitatii"<< "</th>" <<"\n";
    out << "<th>" << "Descrierea activitatii" << "</th>" << "\n";
    out << "<th>" << "Tip activitate" << "</th>" << "\n";
    out << "<th>" << "Durata activitate"<< "</th>" << "\n";

    for(auto& act : acts){
        out << "<tr>" << "\n";
        out << "<td>" << act.getTitle() << "</td>" <<"\n";
        out << "<td>" << act.getDesc() << "</td>" << "\n";
        out << "<td>" << act.getType() << "</td>" << "\n";
        out << "<td>" << act.getLength() << "</td>" << "\n";
        out << "</tr>" << std::endl;
    }

    out << "</table>" << std::endl;
    out << "</body></html>" << std::endl;
    out.close();
}