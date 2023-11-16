#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Audit.h"
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>
#include "connection.h"
#include <QMessageBox>

#include <QIntValidator>
#include <QValidator>

#include <QPdfWriter>
#include <QUrlQuery>
#include "QPainter"

#include<QPieSlice >
#include<QPieSeries>
#include <QFileDialog>
#include<QtCharts>

#include "qrcode.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Audit A;
    ui->TAB_AUDIT->setModel(A.afficher());
    ui->le_id->setValidator(new QIntValidator(0,99999999,this));
       ui->le_titre->setInputMask("");
       ui->le_contenu->setInputMask("");
       ui->le_statut->setInputMask("");
       ui->le_objectif->setInputMask("");
       ui->le_ID_auditeur->setValidator(new QIntValidator(0,99999999,this));
       ui->le_ID_entreprise->setValidator(new QIntValidator(0,99999999,this));
       ui->le_id_supp->setValidator(new QIntValidator(0,99999999,this));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

        int id=ui->le_id->text().toInt() ;
        QString titre=ui->le_titre->text();
        QString contenu=ui->le_contenu->text();
        QDate date_debut = ui->le_date_debut->date();
        QDate date_fin = ui->le_date_fin->date();


        QString statut=ui->le_statut->text();
        QString objectif=ui->le_objectif->text();

        int id_auditeur=ui->le_ID_auditeur->text().toInt();
        int id_entreprise=ui->le_ID_entreprise->text().toInt();



      /*  QTime Time  =QTime::currentTime() ;
        date_debut = Time.toString("H:m:s a") ;*/

        Audit A(id,titre,contenu,date_debut,date_fin,statut,objectif,id_auditeur,id_entreprise);




             if(A.ajouter())
           { ui->TAB_AUDIT_3->setModel(A.afficher());




               QMessageBox::information(nullptr, QObject::tr("database is open"),
                               QObject::tr("ajout successfully.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);}


               else
                  {
                 ui->TAB_AUDIT_3->setModel(A.afficher());

                 QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                               QObject::tr("ajout failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);}



}

void MainWindow::on_pb_supp_clicked()
{

        int id=ui->le_id_supp->text().toInt();


        QMessageBox msgBox;
        if(A.rech(id))
{
           if (A.supprimer(id))
           {     ui->TAB_AUDIT_2->setModel(A.afficher());


               QMessageBox::information(nullptr, QObject::tr("database is open"),
                               QObject::tr("Deleted successfully.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);}


               else
                  { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                               QObject::tr("Delete failed \n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);}
       }
     else{ QMessageBox::critical(nullptr, QObject::tr("Not found"),
                                   QObject::tr("Not found \n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);}



}

void MainWindow::on_modifier_clicked()
{int id=ui->le_id->text().toInt() ;
    QString titre=ui->le_titre->text();
    QString contenu=ui->le_contenu->text();
    QDate date_debut = ui->le_date_debut->date();
    QDate date_fin = ui->le_date_fin->date();
    QString statut=ui->le_statut->text();
    QString objectif=ui->le_objectif->text();

    int id_auditeur=ui->le_ID_auditeur->text().toInt();
    int id_entreprise=ui->le_ID_entreprise->text().toInt();
    QMessageBox msgBox;
    if(A.rech(id))
{
    if (A.modifier(id,titre,contenu,date_debut,date_fin,statut,objectif,id_auditeur,id_entreprise))
    {     ui->TAB_AUDIT_3->setModel(A.afficher());


        QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Update successfully.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}


        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Update failed \n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}
}
else{ QMessageBox::critical(nullptr, QObject::tr("Not found"),
                            QObject::tr("Not found \n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}



}





//  :Audit(int id,QString titre,QString contenu,QDate date_debut,QDate date_fin,QString statut,QString objectif,int id_auditeur,int id_entreprise)


// pdf

void MainWindow::on_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/wiamf/Desktop/Atelier connexion/Audit.pdf");

         QPainter painter(&pdf);
         QString strStream;

           QTextStream out(&strStream);
         int i = 4000;
                painter.setPen(Qt::red);
                painter.setFont(QFont("Impact", 30));
                painter.drawText(3200,1100,"Liste des audits");

                painter.setPen(Qt::black);
                painter.setFont(QFont("Time New Roman", 7));

                painter.drawRect(100,100,9400,1800);
                painter.drawRect(100,2500,9400,500);




                painter.drawText(300,2800,"ID");
                painter.drawText(1300,2800,"Titre");
                painter.drawText(2300,2800,"Contenu");
                painter.drawText(3300,2800,"Date debut");
                painter.drawText(4700,2800,"Date fin");
                painter.drawText(6000,2800,"Statut");
                painter.drawText(7000,2800,"Objectif");
                painter.drawText(7700,2800,"ID auditeur");
                painter.drawText(8700,2800,"ID entreprise");


                painter.drawRect(100,3000,9400,9000);


                QSqlQuery query;
                query.prepare("select * from Auditt ");
                query.exec();
                while (query.next())
                {
                    painter.drawText(300,i,query.value(0).toString());
                    painter.drawText(1300,i,query.value(1).toString());
                    painter.drawText(2300,i,query.value(2).toString());
                    painter.drawText(3300,i,query.value(3).toString());
                    painter.drawText(4700,i,query.value(4).toString());
                    painter.drawText(6000,i,query.value(5).toString());
                    painter.drawText(7000,i,query.value(6).toString());
                    painter.drawText(8000,i,query.value(7).toString());
                    painter.drawText(9000,i,query.value(8).toString());



                   i = i + 350;
                }
                QMessageBox::information(this, QObject::tr("PDF created !"),
                QObject::tr("PDF created ! \n" "Click OK to save PDF."), QMessageBox::Ok);
}








void MainWindow::on_recherche_clicked()
{

    int id=ui->le_id_supp_2->text().toInt();

            QSqlQueryModel *verif=A.recherche(id);
            if(A.rech(id))
            {
            if (verif!=nullptr)
                         {
                             ui->TAB_AUDIT_4->setModel((verif));
                             QMessageBox::information(this, QObject::tr("recherche successfully!"),
                             QObject::tr("recherche successfully!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

            }
                         else
    {
                             QMessageBox::information(this, QObject::tr("recherche failed!"),
                             QObject::tr("recherche failed!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
            }
            else{ QMessageBox::critical(nullptr, QObject::tr("Not found"),
                                        QObject::tr("Not found \n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);}



            ui->le_id_supp_2->clear();
}


void MainWindow::on_comboBox_activated()
{
    if(ui->comboBox->currentText()=="Tri par ID")
        {
            ui->TAB_AUDIT->setModel(A.tri_id());
        }
        else if(ui->comboBox->currentText()=="Tri par titre")
        {
            ui->TAB_AUDIT->setModel(A.trierAuditParTitre());

        }
        else if(ui->comboBox->currentText()=="Tri par statut")
        {
            ui->TAB_AUDIT->setModel(A.trierAuditParStatut());
        }

}








void MainWindow::on_Stat_clicked()
{

    QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery("select * from AUDITT where STATUT = 'ANNULEE' ");
       float statutA = model->rowCount();
       model->setQuery("select * from AUDITT where STATUT = 'EN COURS' ");
       float statutB = model->rowCount();
       model->setQuery("select * from AUDITT where STATUT = 'TERMINEE' ");
       float statutC = model->rowCount();
       float total = statutA + statutB + statutC;

       QString a = QString("Audits Annulés: " + QString::number((statutA * 100) / total, 'f', 2) + "%");
       QString b = QString("Audits en cours: " + QString::number((statutB * 100) / total, 'f', 2) + "%");
       QString c = QString("Audits terminés: " + QString::number((statutC * 100) / total, 'f', 2) + "%");

       // Create the pie chart series
       QPieSeries *series = new QPieSeries();

       // Append data and set custom colors for each slice
       QPieSlice *slice1 = series->append(a, statutA);
       slice1->setBrush(QColor("#3498db"));  // Set color for the first slice

       QPieSlice *slice2 = series->append(b, statutB);
       slice2->setBrush(QColor("#2ecc71"));  // Set color for the second slice

       QPieSlice *slice3 = series->append(c, statutC);
       slice3->setBrush(QColor("#e74c3c"));  // Set color for the third slice

       // Set label visibility and appearance for the first slice
       if (statutA != 0) {
           slice1->setLabelVisible();
           slice1->setPen(QPen());
       }

       if (statutB != 0) {
           // Add label, explode and define brush for 2nd slice
           QPieSlice *slice2 = series->slices().at(1);
           //slice2->setExploded();
           slice2->setLabelVisible();
       }

       if (statutC != 0) {
           // Add labels to rest of slices
           QPieSlice *slice3 = series->slices().at(2);
           //slice3->setExploded();
           slice3->setLabelVisible();
       }

       // Create the chart widget
       QChart *chart = new QChart();

       // Add the series to the chart
       chart->addSeries(series);

       // Set the chart title and hide the legend
       chart->setTitle("Statistique sur le statut des audits :: Nombre des audits: " + QString::number(total));
       chart->legend()->hide();

       // Create the chart view
       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->resize(1000, 500);
       chartView->show();



}




void MainWindow::on_TAB_AUDIT_3_activated(const QModelIndex &index)
{
    ui->le_id->setText(ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(index.row(),0)).toString());
        ui->le_titre->setText(ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(index.row(),1)).toString());
        ui->le_contenu->setText(ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(index.row(),2)).toString());
        //ui->le_date_debut->setDate(ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(index.row(),3)).toString());
        //ui->le_date_fin->setText(ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(index.row(),4)).toString());
        ui->le_statut->setText(ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(index.row(),5)).toString());
        ui->le_objectif->setText(ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(index.row(),6)).toString());
        ui->le_ID_auditeur->setText(ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(index.row(),7)).toString());
        ui->le_ID_entreprise->setText(ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(index.row(),8)).toString());



}

void MainWindow::on_QRcode_clicked()
{
    QString text ="Client details :"+ ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(ui->TAB_AUDIT_3->currentIndex().row(),0)).toString()
                               +" "+ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(ui->TAB_AUDIT_3->currentIndex().row(),1)).toString()
                               +" "+ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(ui->TAB_AUDIT_3->currentIndex().row(),2)).toString()
                               +" "+ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(ui->TAB_AUDIT_3->currentIndex().row(),3)).toString()
                               +" "+ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(ui->TAB_AUDIT_3->currentIndex().row(),4)).toString()
                               +" "+ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(ui->TAB_AUDIT_3->currentIndex().row(),5)).toString()
                               +" "+ui->TAB_AUDIT_3->model()->data(ui->TAB_AUDIT_3->model()->index(ui->TAB_AUDIT_3->currentIndex().row(),6)).toString();
                       //text="user data";
                       using namespace qrcodegen;
                         // Create the QR Code object
                         QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
                         qint32 sz = qr.getSize();
                         QImage im(sz,sz, QImage::Format_RGB32);
                           QRgb black = qRgb(  0,  0,  0);
                           QRgb white = qRgb(255,255,255);
                         for (int y = 0; y < sz; y++)
                           for (int x = 0; x < sz; x++)
                             im.setPixel(x,y,qr.getModule(x, y) ? black : white );
                         ui->qr_code->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );

}
