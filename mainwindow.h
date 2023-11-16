#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Audit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pb_supp_clicked();

    void on_modifier_clicked();

    void on_PDF_clicked();

    void on_recherche_clicked();

    void on_comboBox_activated();




    void on_Stat_clicked();

    void on_TAB_AUDIT_3_activated(const QModelIndex &index);

    void on_QRcode_clicked();

private:
    Ui::MainWindow *ui;
    Audit A;
};

#endif // MAINWINDOW_H
