/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/11/30 09:04) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/KPI_precompiled_header.gen.h"

#include "../include/kpi_Type.gen.h"
#include "../include/kpi_KPI.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_KPI(kpi::Type, kpi_Type)

namespace qx {

template <>
void register_class(QxClass<kpi::Type> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("t_Type");

   pData = t.id(& kpi::Type::m_TypeId, "TypeId", 0);
   pData->setName("Type_id");

   pData = t.data(& kpi::Type::m_Name, "Name", 0, true, true);
   pData = t.data(& kpi::Type::m_Def, "Def", 0, true, true);

   pRelation = t.relationOneToMany(& kpi::Type::m_list_of_KPI, "list_of_KPI", "TypeId", 0);

   qx::QxValidatorX<kpi::Type> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

namespace kpi {

Type::Type() : m_TypeId(0) { ; }

Type::Type(const long & id) : m_TypeId(id) { ; }

Type::~Type() { ; }

long Type::getTypeId() const { return m_TypeId; }

QString Type::getName() const { return m_Name; }

QByteArray Type::getDef() const { return m_Def; }

Type::type_list_of_KPI Type::getlist_of_KPI() const { return m_list_of_KPI; }

Type::type_list_of_KPI & Type::list_of_KPI() { return m_list_of_KPI; }

const Type::type_list_of_KPI & Type::list_of_KPI() const { return m_list_of_KPI; }

void Type::setTypeId(const long & val) { m_TypeId = val; }

void Type::setName(const QString & val) { m_Name = val; }

void Type::setDef(const QByteArray & val) { m_Def = val; }

void Type::setlist_of_KPI(const Type::type_list_of_KPI & val) { m_list_of_KPI = val; }

Type::type_list_of_KPI Type::getlist_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_KPI(); }
   QString sRelation = "{TypeId} | list_of_KPI";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::Type tmp;
   tmp.m_TypeId = this->m_TypeId;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_KPI = tmp.m_list_of_KPI; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_KPI;
}

Type::type_list_of_KPI & Type::list_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_KPI(); }
   QString sRelation = "{TypeId} | list_of_KPI";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::Type tmp;
   tmp.m_TypeId = this->m_TypeId;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_KPI = tmp.m_list_of_KPI; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_KPI;
}

} // namespace kpi
