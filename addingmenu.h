#ifndef ADDINGMENU_H
#define ADDINGMENU_H

#include <QDialog>
#include <qlabel.h>
#include <qlineedit.h>
#include <qvector.h>
namespace Ui {
class addingmenu;
}

class addingmenu : public QDialog
{
    Q_OBJECT

public:
    explicit addingmenu(QWidget *parent = nullptr);
    ~addingmenu();


private slots:
    //void on_autoservice_name_field_inputRejected();

    void on_autoservice_name_field_textEdited(const QString &arg1);

    //void on_autoservice_name_field_editingFinished();

    void validate_keyboard_input(QLabel* error_provider_line, const QString& condition);

    void on_street_name_field_textEdited(const QString &arg1);

    //void on_street_name_field_editingFinished();

    void case_empty_line(QLabel* error_provider_line,const QString& text);

    void on_street_number_field_textEdited(const QString &arg1);

    void on_building_number_field_textEdited(const QString &arg1);

    void on_number_of_work_spaces_field_textEdited(const QString &arg1);

    void on_cancel_btn_clicked();

    bool check_check_btns();

    void on_locksmith_work_check_box_clicked();

    void on_repair_work_check_box_clicked();

    void on_diagnostic_work_check_box_clicked();

    void on_painting_work_check_box_clicked();

    void on_rouitine_maintenance_check_box_clicked();

    void on_apply_btn_clicked();

private:
    Ui::addingmenu *ui;
    std::vector<bool> types_of_work = std::vector<bool>(5, false);




/*// предупреждение об ошибках ввода
private:
    QLabel *autoserviceWarningLabel;
*/

};




#endif // ADDINGMENU_H
