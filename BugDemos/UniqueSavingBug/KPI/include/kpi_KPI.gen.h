/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/11/30 09:04) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _KPI_KPI_KPI_H_
#define _KPI_KPI_KPI_H_

namespace kpi {
class Type;
} // namespace kpi
namespace kpi {
class MetaData;
} // namespace kpi

namespace kpi {

class KPI_EXPORT KPI
{

   QX_REGISTER_FRIEND_CLASS(kpi::KPI)

public:

   typedef std::shared_ptr<kpi::Type> type_TypeId;
   typedef qx::QxCollection<long, std::shared_ptr<kpi::MetaData> > type_list_of_MetaData;

protected:

   long m_KPIId;
   double m_Value;
   QDateTime m_DateTime;
   type_TypeId m_TypeId;
   type_list_of_MetaData m_list_of_MetaData;

public:

   KPI();
   KPI(const long & id);
   virtual ~KPI();

   long getKPIId() const;
   double getValue() const;
   QDateTime getDateTime() const;
   type_TypeId getTypeId() const;
   type_list_of_MetaData getlist_of_MetaData() const;
   type_list_of_MetaData & list_of_MetaData();
   const type_list_of_MetaData & list_of_MetaData() const;

   void setKPIId(const long & val);
   void setValue(const double & val);
   void setDateTime(const QDateTime & val);
   void setTypeId(const type_TypeId & val);
   void setlist_of_MetaData(const type_list_of_MetaData & val);

   type_TypeId getTypeId(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_MetaData getlist_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_MetaData & list_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_TypeId(bool key = false) { return (key ? QString("TypeId") : QString("Type_id")); }
   static QString relation_list_of_MetaData(bool key = false) { Q_UNUSED(key); return "list_of_MetaData"; }

public:

   static QString column_KPIId(bool key = false) { return (key ? QString("KPIId") : QString("KPI_id")); }
   static QString column_Value(bool key = false) { Q_UNUSED(key); return "Value"; }
   static QString column_DateTime(bool key = false) { Q_UNUSED(key); return "DateTime"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("KPI") : QString("t_KPI")); }

};

typedef std::shared_ptr<KPI> KPI_ptr;
typedef qx::QxCollection<long, KPI_ptr> list_of_KPI;
typedef std::shared_ptr<list_of_KPI> list_of_KPI_ptr;

} // namespace kpi

QX_REGISTER_COMPLEX_CLASS_NAME_HPP_KPI(kpi::KPI, qx::trait::no_base_class_defined, 0, kpi_KPI)

#include "../include/kpi_Type.gen.h"
#include "../include/kpi_MetaData.gen.h"

#include "../custom/include/kpi_KPI.h"

#endif // _KPI_KPI_KPI_H_
