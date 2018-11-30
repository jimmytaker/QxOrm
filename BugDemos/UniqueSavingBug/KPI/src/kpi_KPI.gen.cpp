/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/11/30 09:04) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/KPI_precompiled_header.gen.h"

#include "../include/kpi_KPI.gen.h"
#include "../include/kpi_Type.gen.h"
#include "../include/kpi_MetaData.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_KPI(kpi::KPI, kpi_KPI)

namespace qx {

template <>
void register_class(QxClass<kpi::KPI> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("t_KPI");

   pData = t.id(& kpi::KPI::m_KPIId, "KPIId", 0);
   pData->setName("KPI_id");

   pData = t.data(& kpi::KPI::m_Value, "Value", 0, true, true);
   pData = t.data(& kpi::KPI::m_DateTime, "DateTime", 0, true, true);

   pRelation = t.relationManyToOne(& kpi::KPI::m_TypeId, "TypeId", 0);
   pRelation->getDataMember()->setName("Type_id");
   pRelation = t.relationManyToMany(& kpi::KPI::m_list_of_MetaData, "list_of_MetaData", "t_qxee_KPI_MetaData", "KPIId", "MetaData_id", 0);

   qx::QxValidatorX<kpi::KPI> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

namespace kpi {

KPI::KPI() : m_KPIId(0), m_Value(0.0) { ; }

KPI::KPI(const long & id) : m_KPIId(id), m_Value(0.0) { ; }

KPI::~KPI() { ; }

long KPI::getKPIId() const { return m_KPIId; }

double KPI::getValue() const { return m_Value; }

QDateTime KPI::getDateTime() const { return m_DateTime; }

KPI::type_TypeId KPI::getTypeId() const { return m_TypeId; }

KPI::type_list_of_MetaData KPI::getlist_of_MetaData() const { return m_list_of_MetaData; }

KPI::type_list_of_MetaData & KPI::list_of_MetaData() { return m_list_of_MetaData; }

const KPI::type_list_of_MetaData & KPI::list_of_MetaData() const { return m_list_of_MetaData; }

void KPI::setKPIId(const long & val) { m_KPIId = val; }

void KPI::setValue(const double & val) { m_Value = val; }

void KPI::setDateTime(const QDateTime & val) { m_DateTime = val; }

void KPI::setTypeId(const KPI::type_TypeId & val) { m_TypeId = val; }

void KPI::setlist_of_MetaData(const KPI::type_list_of_MetaData & val) { m_list_of_MetaData = val; }

KPI::type_TypeId KPI::getTypeId(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getTypeId(); }
   QString sRelation = "{KPIId} | TypeId";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::KPI tmp;
   tmp.m_KPIId = this->m_KPIId;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_TypeId = tmp.m_TypeId; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_TypeId;
}

KPI::type_list_of_MetaData KPI::getlist_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_MetaData(); }
   QString sRelation = "{KPIId} | list_of_MetaData";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::KPI tmp;
   tmp.m_KPIId = this->m_KPIId;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_MetaData = tmp.m_list_of_MetaData; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_MetaData;
}

KPI::type_list_of_MetaData & KPI::list_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_MetaData(); }
   QString sRelation = "{KPIId} | list_of_MetaData";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::KPI tmp;
   tmp.m_KPIId = this->m_KPIId;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_MetaData = tmp.m_list_of_MetaData; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_MetaData;
}

} // namespace kpi
