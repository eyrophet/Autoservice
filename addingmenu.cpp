#include "addingmenu.h"
#include "ui_addingmenu.h"
#include <QRegularExpression>

// конструктор диалогового окна
addingmenu::addingmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addingmenu)
{
    ui->setupUi(this);

    // Настройка строки состояния имени автосервиса
    ui->error_provider_auto_name->hide();

    // подключение срабатывания
    //connect(ui->autoservice_name_field, &QLineEdit::editingFinished,
         // this, &addingmenu::on_autoservice_name_field_editingFinished);
}

addingmenu::~addingmenu()
{
    delete ui;
}



// функция, срабатывающая при редактировании текста пользователем
void addingmenu::on_autoservice_name_field_textEdited(const QString &arg1)
{
    // регулярное выражение для проверки названия автосервиса
    static const QRegularExpression forbidden(
        R"(^[><.,:;!?@#$%^&*()[\]{}|\\/+=_-]|[><.,:;!?@#$%^&*()[\]{}|\\/+=_-]$)"
        );

    // передача информации для вывода соответствующей строки состояния
    if (forbidden.match(arg1.trimmed()).hasMatch()) {
        validate_keyboard_input(ui->error_provider_auto_name,"YES");
    } else {
        validate_keyboard_input(ui->error_provider_auto_name,"NO");
    }

    case_empty_line(ui->error_provider_auto_name, ui->autoservice_name_field->text());

}


// скрытие строки состояния поля названия автосервиса
/*void addingmenu::on_autoservice_name_field_editingFinished()
{
    case_empty_line(ui->error_provider_auto_name, ui->autoservice_name_field->text());
}*/

// универсальная функция вывода диагностических сообщенмй
void addingmenu::validate_keyboard_input(QLabel* error_provider_line, const QString& condition)
{
    if (condition=="YES")
    {
        error_provider_line->setText("Некорретный ввод. Внимательнее смотрите критерии ввода");
        error_provider_line->setStyleSheet("color: red;");
    }
    else if (condition == "NO")
    {
        error_provider_line->setText("Критерии соблюдены");
        error_provider_line->setStyleSheet("color: green;");
    }

    error_provider_line->show();           // обязательно после setText
    error_provider_line->adjustSize();     // обновить размеры QLabel

}

// функция проверки введенной строки названия улицы в соответствие с критериями проверкм
void addingmenu::on_street_name_field_textEdited(const QString &arg1)
{
    // Регулярное выражение:
    // ^ - начало строки
    // (Ул\.|Пер\.|Пр\.|Ш\.) - обязательный тип элемента уличной сети (с точкой)
    // \s+ - один или несколько пробелов
    // [А-ЯЁ][а-яё]+ - название улицы, начинается с заглавной кириллической, далее строчные
    // (?:\s[А-ЯЁа-яё]+)* - допускаются дополнительные слова (например, "Ул. Льва Толстого")
    // $ - конец строки
    static const QRegularExpression forbidden(R"(^\s*(Ул\.|Пер\.|Пр\.|Ш\.)\s+[А-ЯЁ][а-яё]*(?:\s*-\s*[А-ЯЁа-яё]+|\s+[А-ЯЁа-яё]+)*\s*$)");

    QString trimmedInput = arg1.trimmed();
    QRegularExpressionMatch match = forbidden.match(trimmedInput);

    // провекра регулярного выражения и передача соответствующих результатов проверки
    if (match.hasMatch()) {
        validate_keyboard_input(ui->error_provider_street_name,"NO");
    } else {
        validate_keyboard_input(ui->error_provider_street_name,"YES");
    }

    case_empty_line(ui->error_provider_street_name, ui->street_name_field->text());

    // проверка на возможность активации кнопки "применить"
    if ((check_check_btns() == true) && (ui->error_provider_street_name->text() == "Критерии соблюдены")
        && (ui->error_provider_auto_name->text() == "Критерии соблюдены") && (ui->error_provider_street_number->text() == "Критерии соблюдены")
        && (ui->error_provider_building_number->text() == "Критерии соблюдены") && (ui->error_provider_working_posts->text() == "Критерии соблюдены"))
    {
        ui->apply_btn->setEnabled(true);
    }
    else
        ui->apply_btn->setEnabled(false);

}

// скрытие строки состояния, если она осталась пустая после редактирования
void addingmenu::case_empty_line(QLabel* error_provider_line, const QString& text)
{
    if (text=="")
    {
        error_provider_line->hide();
    }
}

// проверка корректности ввода строки номера улицы
void addingmenu::on_street_number_field_textEdited(const QString &arg1)
{
    // Регулярное выражение:
    // ^ - начало строки
    // (?:[1-9]|[1-9][0-9]|[1-6][0-9]{2}|7[0-4][0-9]|75[0-6]) - числа от 1 до 756
    // $ - конец строки
    static const QRegularExpression numberCheck(R"(^(?:[1-9]|[1-9][0-9]|[1-6][0-9]{2}|7[0-4][0-9]|75[0-6])$)");

    QString trimmedInput = arg1.trimmed();
    QRegularExpressionMatch match = numberCheck.match(trimmedInput);

    // проверка регулярного выражения и передача соответствующих результатов проверки
    if (match.hasMatch()) {
        validate_keyboard_input(ui->error_provider_street_number, "NO");
    } else {
        validate_keyboard_input(ui->error_provider_street_number, "YES");
    }

    case_empty_line(ui->error_provider_street_number, ui->street_number_field->text());

    // проверка на возможность активации кнопки "применить"
    if ((check_check_btns() == true) && (ui->error_provider_street_name->text() == "Критерии соблюдены")
        && (ui->error_provider_auto_name->text() == "Критерии соблюдены") && (ui->error_provider_street_number->text() == "Критерии соблюдены")
        && (ui->error_provider_building_number->text() == "Критерии соблюдены") && (ui->error_provider_working_posts->text() == "Критерии соблюдены"))
    {
        ui->apply_btn->setEnabled(true);
    }
    else
        ui->apply_btn->setEnabled(false);
}

// проверка корректсности ввода номера строения
void addingmenu::on_building_number_field_textEdited(const QString &arg1)
{
    // Регулярное выражение:
    // ^ - начало строки
    // \d+ - одна или более цифр
    // (?:[абвгдеёжклмнопрстуфхцчшщэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЭЮЯ])? - необязательная одна буква (будет заменена на допустимые)
    // (?:/\d+|/[абвгдеёжклмнопрстуфхцчшщэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЭЮЯ])? - необязательная косая черта с цифрой или буквой
    // $ - конец строки

    // Исключаемые буквы: ё, з, й, ъ, ы, ь
    // Разрешенные буквы: [а-ик-мн-пт-щэюя] (без ё, з, й, ъ, ы, ь)
    static const QRegularExpression buildingNumberCheck(
        R"(^(?:\d+)(?:[а-ик-мн-пт-щэюяА-ИК-МН-ПТ-ЩЭЮЯ])?(?:/(?:\d+|[а-ик-мн-пт-щэюяА-ИК-МН-ПТ-ЩЭЮЯ]))?$)"
        );

    QString trimmedInput = arg1.trimmed();
    QRegularExpressionMatch match = buildingNumberCheck.match(trimmedInput);

    // проверка регулярного выражения и передача соответствующих результатов проверки
    if (match.hasMatch()) {
        validate_keyboard_input(ui->error_provider_building_number, "NO");
    } else {
        validate_keyboard_input(ui->error_provider_building_number, "YES");
    }

    case_empty_line(ui->error_provider_building_number, ui->building_number_field->text());

    // проверка на возможность активации кнопки "применить"
    if ((check_check_btns() == true) && (ui->error_provider_street_name->text() == "Критерии соблюдены")
        && (ui->error_provider_auto_name->text() == "Критерии соблюдены") && (ui->error_provider_street_number->text() == "Критерии соблюдены")
        && (ui->error_provider_building_number->text() == "Критерии соблюдены") && (ui->error_provider_working_posts->text() == "Критерии соблюдены"))
    {
        ui->apply_btn->setEnabled(true);
    }
    else
        ui->apply_btn->setEnabled(false);
}

// проверка корректности ввода поля количества рабочих постов
void addingmenu::on_number_of_work_spaces_field_textEdited(const QString &arg1)
{
    // Регулярное выражение:
    // ^ - начало строки
    // (?:[1-9]|10) - число от 1 до 9 или 10
    // $ - конец строки
    static const QRegularExpression postCountCheck(R"(^(?:[1-9]|10)$)");

    QString trimmedInput = arg1.trimmed();
    QRegularExpressionMatch match = postCountCheck.match(trimmedInput);

    // проверка регулярного выражения и передача соответствующих результатов проверки
    if (match.hasMatch()) {
        validate_keyboard_input(ui->error_provider_working_posts, "NO");
    } else {
        validate_keyboard_input(ui->error_provider_working_posts, "YES");
    }

    case_empty_line(ui->error_provider_working_posts, ui->number_of_work_spaces_field->text());
    // проверка на возможность активации кнопки "применить"
    if ((check_check_btns() == true) && (ui->error_provider_street_name->text() == "Критерии соблюдены")
        && (ui->error_provider_auto_name->text() == "Критерии соблюдены") && (ui->error_provider_street_number->text() == "Критерии соблюдены")
        && (ui->error_provider_building_number->text() == "Критерии соблюдены") && (ui->error_provider_working_posts->text() == "Критерии соблюдены"))
    {
        ui->apply_btn->setEnabled(true);
    }
    else
        ui->apply_btn->setEnabled(false);
}

// реализация работы кнопки "отмена"
void addingmenu::on_cancel_btn_clicked()
{
    this->close(); // Закрывает окно (подходит для QWidget)
        // или:
        // this->reject(); // Если наследуешь от QDialog и нужно вернуть результат "отменено"
}

bool addingmenu::check_check_btns()
{
    // если нажата кнопка слесарных работ
    if (ui->locksmith_work_check_box->isChecked() == true)
        types_of_work[0] = true;
    else
        types_of_work[0] = false;

    // если нажата кнопка ремонтных работ
    if (ui->repair_work_check_box->isChecked() == true)
        types_of_work[1] = true;
    else
        types_of_work[1] = false;

    // если нажата кнопка диагностических работ
    if (ui->diagnostic_work_check_box->isChecked() == true)
        types_of_work[2] = true;
    else
        types_of_work[2] = false;

    // если нажата кнопка малярных работ
    if (ui->painting_work_check_box->isChecked() == true)
        types_of_work[3] = true;
    else
        types_of_work[3] = false;

    // если нажата кнопка работы регламентного обслуживания
    if (ui->rouitine_maintenance_check_box->isChecked() == true)
        types_of_work[4] = true;
    else
        types_of_work[4] = false;

    // если хотя бы один флаг поднят, то возврашается true
    for (const bool& flag: types_of_work)
    {
        if (flag == true)
            return true;
    }

    return false;
}


void addingmenu::on_locksmith_work_check_box_clicked()
{
    // проверка на возможность активации кнопки "применить"
    if ((check_check_btns() == true) && (ui->error_provider_street_name->text() == "Критерии соблюдены")
        && (ui->error_provider_auto_name->text() == "Критерии соблюдены") && (ui->error_provider_street_number->text() == "Критерии соблюдены")
        && (ui->error_provider_building_number->text() == "Критерии соблюдены") && (ui->error_provider_working_posts->text() == "Критерии соблюдены"))
    {
        ui->apply_btn->setEnabled(true);
    }
    else
        ui->apply_btn->setEnabled(false);
}


void addingmenu::on_repair_work_check_box_clicked()
{
    // проверка на возможность активации кнопки "применить"
    if ((check_check_btns() == true) && (ui->error_provider_street_name->text() == "Критерии соблюдены")
        && (ui->error_provider_auto_name->text() == "Критерии соблюдены") && (ui->error_provider_street_number->text() == "Критерии соблюдены")
        && (ui->error_provider_building_number->text() == "Критерии соблюдены") && (ui->error_provider_working_posts->text() == "Критерии соблюдены"))
    {
        ui->apply_btn->setEnabled(true);
    }
    else
        ui->apply_btn->setEnabled(false);
}


void addingmenu::on_diagnostic_work_check_box_clicked()
{
    // проверка на возможность активации кнопки "применить"
    if ((check_check_btns() == true) && (ui->error_provider_street_name->text() == "Критерии соблюдены")
        && (ui->error_provider_auto_name->text() == "Критерии соблюдены") && (ui->error_provider_street_number->text() == "Критерии соблюдены")
        && (ui->error_provider_building_number->text() == "Критерии соблюдены") && (ui->error_provider_working_posts->text() == "Критерии соблюдены"))
    {
        ui->apply_btn->setEnabled(true);
    }
    else
        ui->apply_btn->setEnabled(false);
}


void addingmenu::on_painting_work_check_box_clicked()
{
    // проверка на возможность активации кнопки "применить"
    if ((check_check_btns() == true) && (ui->error_provider_street_name->text() == "Критерии соблюдены")
        && (ui->error_provider_auto_name->text() == "Критерии соблюдены") && (ui->error_provider_street_number->text() == "Критерии соблюдены")
        && (ui->error_provider_building_number->text() == "Критерии соблюдены") && (ui->error_provider_working_posts->text() == "Критерии соблюдены"))
    {
        ui->apply_btn->setEnabled(true);
    }
    else
        ui->apply_btn->setEnabled(false);
}


void addingmenu::on_rouitine_maintenance_check_box_clicked()
{
    // проверка на возможность активации кнопки "применить"
    if ((check_check_btns() == true) && (ui->error_provider_street_name->text() == "Критерии соблюдены")
        && (ui->error_provider_auto_name->text() == "Критерии соблюдены") && (ui->error_provider_street_number->text() == "Критерии соблюдены")
        && (ui->error_provider_building_number->text() == "Критерии соблюдены") && (ui->error_provider_working_posts->text() == "Критерии соблюдены"))
    {
        ui->apply_btn->setEnabled(true);
    }
    else
        ui->apply_btn->setEnabled(false);
}


void addingmenu::on_apply_btn_clicked()
{

}

