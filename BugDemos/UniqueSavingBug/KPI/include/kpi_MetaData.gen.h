/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/11/30 12:30) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _KPI_KPI_METADATA_H_
#define _KPI_KPI_METADATA_H_

namespace kpi {
class KPI;
} // namespace kpi
namespace kpi {
class MetaDataKey;
} // namespace kpi

namespace kpi {

class KPI_EXPORT MetaData
{

   QX_REGISTER_FRIEND_CLASS(kpi::MetaData)

public:

   typedef QVector<std::shared_ptr<kpi::KPI> > type_list_of_KPI;
   typedef std::shared_ptr<kpi::MetaDataKey> type_MetaKey;

protected:

   long m_MetaData_id;
   QString m_Value;
   type_list_of_KPI m_list_of_KPI;
   type_MetaKey m_MetaKey;

public:

   MetaData();
   MetaData(const long & id);
   virtual ~MetaData();

   long getMetaData_id() const;
   QString getValue() const;
   type_list_of_KPI getlist_of_KPI() const;
   type_list_of_KPI & list_of_KPI();
   const type_list_of_KPI & list_of_KPI() const;
   type_MetaKey getMetaKey() const;

   void setMetaData_id(const long & val);
   void setValue(const QString & val);
   void setlist_of_KPI(const type_list_of_KPI & val);
   void setMetaKey(const type_MetaKey & val);

   type_list_of_KPI getlist_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_KPI & list_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_MetaKey getMetaKey(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_list_of_KPI(bool key = false) { Q_UNUSED(key); return "list_of_KPI"; }
   static QString relation_MetaKey(bool key = false) { Q_UNUSED(key); return "MetaKey"; }

public:

   static QString column_MetaData_id(bool key = false) { Q_UNUSED(key); return "MetaData_id"; }
   static QString column_Value(bool key = false) { Q_UNUSED(key); return "Value"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("MetaData") : QString("t_MetaData")); }

};

typedef std::shared_ptr<MetaData> MetaData_ptr;
typedef qx::QxCollection<long, MetaData_ptr> list_of_MetaData;
typedef std::shared_ptr<list_of_MetaData> list_of_MetaData_ptr;

} // namespace kpi

QX_REGISTER_COMPLEX_CLASS_NAME_HPP_KPI(kpi::MetaData, qx::trait::no_base_class_defined, 0, kpi_MetaData)

#include "../include/kpi_KPI.gen.h"
#include "../include/kpi_MetaDataKey.gen.h"

#include "../custom/include/kpi_MetaData.h"

#endif // _KPI_KPI_METADATA_H_
