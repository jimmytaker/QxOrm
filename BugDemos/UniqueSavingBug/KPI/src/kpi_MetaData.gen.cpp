/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/11/30 12:30) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/KPI_precompiled_header.gen.h"

#include "../include/kpi_MetaData.gen.h"
#include "../include/kpi_KPI.gen.h"
#include "../include/kpi_MetaDataKey.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_KPI(kpi::MetaData, kpi_MetaData)

namespace qx {

template <>
void register_class(QxClass<kpi::MetaData> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("t_MetaData");

   pData = t.id(& kpi::MetaData::m_MetaData_id, "MetaData_id", 0);

   pData = t.data(& kpi::MetaData::m_Value, "Value", 0, true, true);

   pRelation = t.relationManyToMany(& kpi::MetaData::m_list_of_KPI, "list_of_KPI", "t_qxee_KPI_MetaData", "MetaData_id", "KPIId", 0);
   pRelation = t.relationManyToOne(& kpi::MetaData::m_MetaKey, "MetaKey", 0);

   qx::QxValidatorX<kpi::MetaData> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

namespace kpi {

MetaData::MetaData() : m_MetaData_id(0) { ; }

MetaData::MetaData(const long & id) : m_MetaData_id(id) { ; }

MetaData::~MetaData() { ; }

long MetaData::getMetaData_id() const { return m_MetaData_id; }

QString MetaData::getValue() const { return m_Value; }

MetaData::type_list_of_KPI MetaData::getlist_of_KPI() const { return m_list_of_KPI; }

MetaData::type_list_of_KPI & MetaData::list_of_KPI() { return m_list_of_KPI; }

const MetaData::type_list_of_KPI & MetaData::list_of_KPI() const { return m_list_of_KPI; }

MetaData::type_MetaKey MetaData::getMetaKey() const { return m_MetaKey; }

void MetaData::setMetaData_id(const long & val) { m_MetaData_id = val; }

void MetaData::setValue(const QString & val) { m_Value = val; }

void MetaData::setlist_of_KPI(const MetaData::type_list_of_KPI & val) { m_list_of_KPI = val; }

void MetaData::setMetaKey(const MetaData::type_MetaKey & val) { m_MetaKey = val; }

MetaData::type_list_of_KPI MetaData::getlist_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_KPI(); }
   QString sRelation = "{MetaData_id} | list_of_KPI";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::MetaData tmp;
   tmp.m_MetaData_id = this->m_MetaData_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_KPI = tmp.m_list_of_KPI; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_KPI;
}

MetaData::type_list_of_KPI & MetaData::list_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_KPI(); }
   QString sRelation = "{MetaData_id} | list_of_KPI";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::MetaData tmp;
   tmp.m_MetaData_id = this->m_MetaData_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_KPI = tmp.m_list_of_KPI; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_KPI;
}

MetaData::type_MetaKey MetaData::getMetaKey(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getMetaKey(); }
   QString sRelation = "{MetaData_id} | MetaKey";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::MetaData tmp;
   tmp.m_MetaData_id = this->m_MetaData_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_MetaKey = tmp.m_MetaKey; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_MetaKey;
}

} // namespace kpi
