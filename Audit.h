#ifndef AUDIT_H
#define AUDIT_H

#include <iostream>
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
using namespace std;

class Audit
{

public:
  Audit();
  Audit(int,QString,QString,QDate,QDate,QString,QString,int,int);
  int getid();

  QString gettitre();
  QString getcontenu();
  QString getstatut();
  QString getobjectif();

  QDate getdate_debut();
  QDate getdate_fin();

  int getid_auditeur();
  int getid_entreprise();

  void setid(int);

  void settitre(QString);
  void setcontenu(QString);
  void setstatut(QString);
  void setobjectif(QString);
  void setdate_debut(QDate);
  void setdate_fin(QDate);

  void setid_auditeur(int);
  void setid_entreprise(int);

  bool ajouter();
  QSqlQueryModel* afficher();
  bool supprimer (int);
  bool rech(int );
  bool modifier(int id,QString titre,QString contenu,QDate date_debut,QDate date_fin,QString statut,QString objectif,int id_auditeur,int id_entreprise);

  QSqlQueryModel* recherche(int id);

  QSqlQueryModel * tri_id();
  QSqlQueryModel * trierAuditParTitre();
  QSqlQueryModel * trierAuditParStatut();

private:
  int id,id_auditeur,id_entreprise;
  QString titre,contenu,statut,objectif;


  QDate date_debut,date_fin;







};

#endif // AUDIT_H
