#include "Audit.h"
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
#include <QObject>
#include <QDialog>
#include <QSqlRecord>
#include <QDebug>

Audit::Audit()
{
    id=0;
    titre="";
    contenu="";
    date_debut=QDate();
    date_fin=QDate();
    statut="";
    objectif="";
    id_auditeur=0;
    id_entreprise=0;


}


Audit::Audit(int id,QString titre,QString contenu,QDate date_debut,QDate date_fin,QString statut,QString objectif,int id_auditeur,int id_entreprise)
{
    this->id=id;
    this->titre=titre;
    this->contenu=contenu;
    this->date_debut=date_debut;
    this->date_fin=date_fin;
    this->statut=statut;
    this->objectif=objectif;
    this->id_auditeur=id_auditeur;
    this->id_entreprise=id_entreprise;

}


int Audit::getid(){return id;}
QString Audit::gettitre(){return  titre;}
QString Audit::getcontenu(){return contenu;}
QDate Audit::getdate_debut(){return date_debut;}
QDate Audit::getdate_fin(){return date_fin;};
QString Audit::getstatut(){return  statut;}
QString Audit::getobjectif(){return  objectif;}
int Audit::getid_auditeur(){return id_auditeur;}
int Audit::getid_entreprise(){return id_entreprise;}



void Audit::setid(int id){this->id=id;}
void Audit::settitre(QString titre){this->titre=titre;}
void Audit::setcontenu(QString contenu){this->contenu=contenu;}
void Audit::setdate_debut(QDate date_debut){this->date_debut=date_debut;}
void Audit::setdate_fin(QDate date_fin){this->date_fin=date_fin;}
void Audit::setstatut(QString statut){this->statut=statut;}
void Audit::setobjectif(QString objectif){this->objectif=objectif;}
void Audit::setid_auditeur(int id_auditeur){this->id_auditeur=id_auditeur;}
void Audit::setid_entreprise(int id_entreprise){this->id_entreprise=id_entreprise;}



bool Audit::ajouter()
{
    //bool test=true;


    QSqlQuery query;


    QString id_string=QString::number(id);
    QString id_auditeur_string=QString::number(id_auditeur);
    QString id_entreprise_string=QString::number(id_entreprise);

          query.prepare("INSERT INTO Auditt (id,titre,contenu,date_debut,date_fin,statut,objectif,id_auditeur,id_entreprise) "
                        "VALUES (:id,:titre,:contenu,:date_debut,:date_fin,:statut, :objectif, :id_auditeur, :id_entreprise)");

         query.bindValue(":id",id_string);
         query.bindValue(":id_auditeur",id_auditeur_string);
         query.bindValue(":id_entreprise",id_entreprise_string);

          query.bindValue(":titre",titre);
          query.bindValue(":contenu",contenu);
          query.bindValue(":date_debut",date_debut);
          query.bindValue(":date_fin",date_fin);
          query.bindValue(":statut",statut);
          query.bindValue(":objectif", objectif);




     return query.exec();
}

bool Audit::supprimer(int id)
{


    QSqlQuery query;

        QString id_string=QString::number(id);

        query.prepare("Delete from Auditt where id= :id ");
         query.bindValue(":id", id_string);
        return query.exec();

}

QSqlQueryModel* Audit::afficher()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM Auditt");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TITRE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CONTENU"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE DEBUT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE FIN"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("OBJECTIF"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("IDENTF EMPLOYEE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("IDENTIF ENTREPRISE"));




    return model;

}

bool Audit::rech(int id)
  {
     QSqlQuery q("select * from Auditt where  id = "+QString::number(id) );
        QSqlRecord rec = q.record();

        qDebug() << "Number of columns: " << rec.count();

        int nameCol = rec.indexOf("id");
        while (q.next())
        {

            qDebug() << q.value(nameCol).toString();
            QString a= q.value(nameCol).toString();
            if(a!="")
            {

                  return true;

  }
  }
          return false;
}
bool Audit::modifier(int id,QString titre,QString contenu,QDate date_debut,QDate date_fin,QString statut,QString objectif,int id_auditeur,int id_entreprise)
{ QSqlQuery query;
    QString id_string=QString::number(id);
    QString id_auditeur_string=QString::number(id_auditeur);
    QString id_entreprise_string=QString::number(id_entreprise);
    query.prepare("UPDATE Auditt SET id=:id,titre=:titre,contenu=:contenu,date_debut=:date_debut,date_fin=:date_fin,statut=:statut,objectif=:objectif,id_auditeur=:id_auditeur,id_entreprise=:id_entreprise "
                  "WHERE id=:id");

    query.bindValue(":id", id_string);
    query.bindValue(":titre", titre);
    query.bindValue(":contenu", contenu);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);
    query.bindValue(":statut", statut);
    query.bindValue(":objectif", objectif);
    query.bindValue(":id_auditeur", id_auditeur);
    query.bindValue(":id_entreprise", id_entreprise);

    return query.exec();
}



QSqlQueryModel * Audit::recherche(int id)
     {
         QSqlQuery query;
      //   QString cin_string=QString::number(CIN);

         query.prepare("select * from Auditt where id=:id");
         query.bindValue(":id",id);
         query.exec();
         QSqlQueryModel *model= new QSqlQueryModel;
         model->setQuery(query);


        return model;
}


QSqlQueryModel *Audit::tri_id()
{
              QSqlQuery * q = new  QSqlQuery ();
                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("SELECT * FROM AUDITT order by ID ");
                     q->exec();
                     model->setQuery(*q);
                     return model;
}


QSqlQueryModel *Audit::trierAuditParTitre()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM AUDITT order by TITRE ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}


QSqlQueryModel * Audit::trierAuditParStatut()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM AUDITT order by STATUT ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

