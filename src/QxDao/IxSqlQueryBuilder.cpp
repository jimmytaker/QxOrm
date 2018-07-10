/****************************************************************************
**
** http://www.qxorm.com/
** Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software
**
** Commercial Usage
** Licensees holding valid commercial QxOrm licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Lionel Marty
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met : http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, or
** if you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#include <QxPrecompiled.h>

#include <QxDao/IxSqlQueryBuilder.h>
#include <QxDao/QxSqlDatabase.h>
#include <QxDao/QxSqlRelationParams.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QHash<QString, QString> IxSqlQueryBuilder::m_lstSqlQuery;
QHash<QString, QHash<QString, QString> > IxSqlQueryBuilder::m_lstSqlAlias;

IxSqlQueryBuilder::~IxSqlQueryBuilder() { ; }

void IxSqlQueryBuilder::clone(const IxSqlQueryBuilder & other)
{
   this->m_lstDataMemberPtr = other.m_lstDataMemberPtr;
   this->m_lstSqlRelationPtr = other.m_lstSqlRelationPtr;
   this->m_pDataMemberId = other.m_pDataMemberId;
   this->m_sSqlQuery = other.m_sSqlQuery;
   this->m_sTableName = other.m_sTableName;
   this->m_sHashRelation = other.m_sHashRelation;
   this->m_bCartesianProduct = other.m_bCartesianProduct;
   this->m_pIdX = other.m_pIdX;
   this->m_oSoftDelete = other.m_oSoftDelete;
   this->m_lstSqlQueryAlias = other.m_lstSqlQueryAlias;
   this->m_pDaoHelper = other.m_pDaoHelper;
   this->m_pDataMemberX = other.m_pDataMemberX;
}

void IxSqlQueryBuilder::init()
{
   if (! m_pDataMemberX || m_bInitDone) { return; }
   m_pDataMemberId = m_pDataMemberX->getId_WithDaoStrategy();
   m_sTableName = m_pDataMemberX->getName();
   m_lstDataMemberPtr.reset(new QxCollection<QString, IxDataMember *>());
   m_lstSqlRelationPtr.reset(new IxSqlRelationX());
   IxDataMember * p = NULL; long lCount = m_pDataMemberX->count_WithDaoStrategy();
   for (long l = 0; l < lCount; ++l) { if ((p = isValid_DataMember(l))) { m_lstDataMemberPtr->insert(p->getKey(), p); } }
   for (long l = 0; l < lCount; ++l) { if ((p = isValid_SqlRelation(l))) { m_lstSqlRelationPtr->insert(p->getKey(), p->getSqlRelation()); } }
   m_bInitDone = true;
}

void IxSqlQueryBuilder::setSqlQuery(const QString & sql, const QString & key /* = QString() */)
{
   m_sSqlQuery = sql;
   if (! key.isEmpty()) { m_lstSqlQuery.insert(key, sql); }
}

void IxSqlQueryBuilder::displaySqlQuery(int time_ms /* = -1 */) const
{
   if (time_ms < 0)  { qDebug("[QxOrm] sql query : %s", qPrintable(m_sSqlQuery)); }
   else              { qDebug("[QxOrm] sql query (%d ms) : %s", time_ms, qPrintable(m_sSqlQuery)); }
}

void IxSqlQueryBuilder::initIdX(long lAllRelationCount)
{
   if (! m_bCartesianProduct) { qAssert(false); return; }
   m_pIdX.reset(new type_lst_ptr_by_id());
   for (long l = 0; l < (lAllRelationCount + 1); ++l)
   { type_ptr_by_id_ptr pItem = type_ptr_by_id_ptr(new type_ptr_by_id()); m_pIdX->append(pItem); }
}

bool IxSqlQueryBuilder::insertIdX(long lIndex, const QVariant & idOwner, const QVariant & idData, void * ptr)
{
   QString sIdOwner = idOwner.toString(); QString sIdData = idData.toString();
   if (! m_pIdX || sIdOwner.isEmpty() || sIdData.isEmpty()) { qAssert(false); return false; }
   if ((lIndex < 0) || (lIndex >= m_pIdX->count())) { qAssert(false); return false; }

   type_id idX(sIdOwner, sIdData);
   type_ptr_by_id_ptr pHash = m_pIdX->at(lIndex);
   if (! ptr || ! pHash || pHash->contains(idX)) { qAssert(false); return false; }
   pHash->insert(idX, ptr);

   return true;
}

void * IxSqlQueryBuilder::existIdX(long lIndex, const QVariant & idOwner, const QVariant & idData)
{
   QString sIdOwner = idOwner.toString(); QString sIdData = idData.toString();
   if (! m_pIdX || sIdOwner.isEmpty() || sIdData.isEmpty()) { qAssert(false); return NULL; }
   if ((lIndex < 0) || (lIndex >= m_pIdX->count())) { qAssert(false); return NULL; }

   type_id idX(sIdOwner, sIdData);
   type_ptr_by_id_ptr pHash = m_pIdX->at(lIndex);
   if (! pHash || ! pHash->contains(idX)) { return NULL; }

   return pHash->value(idX);
}

bool IxSqlQueryBuilder::getAddAutoIncrementIdToUpdateQuery() const
{
   return qx::QxSqlDatabase::getSingleton()->getAddAutoIncrementIdToUpdateQuery();
}

void IxSqlQueryBuilder::addSqlQueryAlias(const QString & sql, const QString & sqlAlias)
{
   m_lstSqlQueryAlias.insert(sql, sqlAlias);
}

void IxSqlQueryBuilder::replaceSqlQueryAlias(QString & sql) const
{
   if (! qx::QxSqlDatabase::getSingleton()->getAutoReplaceSqlAliasIntoQuery()) { return; }
   if (m_lstSqlQueryAlias.count() <= 0) { return; }
   QHashIterator<QString, QString> itr(m_lstSqlQueryAlias);
   sql = (" " + sql);
   while (itr.hasNext())
   {
      itr.next();
      QString sBefore = (" " + itr.key() + ".");
      QString sAfter = (" " + itr.value() + ".");
      sql.replace(sBefore, sAfter);
   }
   sql = sql.trimmed();
}

bool IxSqlQueryBuilder::verifyColumns(const QStringList & columns) const
{
#ifdef _QX_MODE_DEBUG
   if (! m_pDataMemberX) { qAssert(false); return false; }
   for (int i = 0; i < columns.count(); i++)
   {
      if (! m_pDataMemberX->exist_WithDaoStrategy(columns.at(i)))
      {
         QString sErrorMsg = QString("column '%1' not found in table '%2'").arg(columns.at(i), m_sTableName);
         qDebug("[QxOrm] Error in qx::IxSqlQueryBuilder::verifyColumns() : %s", qPrintable(sErrorMsg));
         qAssertMsg(false, "[QxOrm] qx::IxSqlQueryBuilder::verifyColumns()", qPrintable(sErrorMsg));
         return false;
      }
   }
   return true;
#else // _QX_MODE_DEBUG
   Q_UNUSED(columns);
   return true;
#endif // _QX_MODE_DEBUG
}

IxDataMember * IxSqlQueryBuilder::isValid_DataMember(long lIndex) const
{
   IxDataMember * p = m_pDataMemberX->get_WithDaoStrategy(lIndex);
   bool bValid = (p && p->getDao() && ! p->hasSqlRelation());
   bValid = (bValid && (p != m_pDataMemberId));
   return (bValid ? p : NULL);
}

IxDataMember * IxSqlQueryBuilder::isValid_SqlRelation(long lIndex) const
{
   IxDataMember * p = m_pDataMemberX->get_WithDaoStrategy(lIndex);
   bool bIsValid = (p && p->getDao() && p->hasSqlRelation());
   if (bIsValid) { p->getSqlRelation()->init(); }
   return (bIsValid ? p : NULL);
}

void IxSqlQueryBuilder::sql_CreateTable(QString & sql, IxSqlQueryBuilder & builder)
{
   long l1(0), l2(0);
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId();
   qx::IxSqlRelation * pRelation = NULL;
   qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
   qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
   QString table = builder.table();
   sql = "CREATE TABLE " + table + " (";
   int iSqlCountRef = sql.count();
   if (pId) { sql += pId->getSqlNameAndTypeAndParams(", ") + ", "; qAssert(! pId->getSqlType().isEmpty()); }
   while ((p = builder.nextData(l1))) { sql += p->getSqlNameAndTypeAndParams(", ") + ", "; qAssert(! p->getSqlType().isEmpty()); }
   if (! oSoftDelete.isEmpty()) { sql += oSoftDelete.buildSqlQueryToCreateTable() + ", "; }
   while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->createTable(params); }
   bool bAddBracket = (sql.count() != iSqlCountRef);
   sql = sql.left(sql.count() - 2); // Remove last ", "
   if (bAddBracket) { sql += ")"; }
}

void IxSqlQueryBuilder::sql_DeleteById(QString & sql, IxSqlQueryBuilder & builder, bool bSoftDelete)
{
   qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
   qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
   QString table = builder.table();
   if (bSoftDelete && ! oSoftDelete.isEmpty()) { sql = "UPDATE " + table + " SET " + oSoftDelete.buildSqlQueryToUpdate(); }
   else { sql = "DELETE FROM " + qx::IxDataMember::getSqlFromTable(table); }
   sql += IxSqlQueryBuilder::addSqlCondition(sql);
   sql += pId->getSqlNameEqualToPlaceHolder("", " AND ");
}

void IxSqlQueryBuilder::sql_Exist(QString & sql, IxSqlQueryBuilder & builder)
{
   qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
   qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
   QString table = builder.table();
   sql = "SELECT ";
   if (pId) { sql += pId->getSqlTablePointNameAsAlias(table); }
   if (! oSoftDelete.isEmpty()) { sql += ", " + oSoftDelete.buildSqlTablePointName(); }
   sql += " FROM " + qx::IxDataMember::getSqlFromTable(table);
   sql += " WHERE " + pId->getSqlAliasEqualToPlaceHolder(table, true);
   if (! oSoftDelete.isEmpty()) { sql += " AND " + oSoftDelete.buildSqlQueryToFetch(); }
}

void IxSqlQueryBuilder::sql_FetchAll(QString & sql, IxSqlQueryBuilder & builder)
{
   long l1(0), l2(0), l3(0), l4(0), l5(0);
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId();
   qx::IxSqlRelation * pRelation = NULL;
   qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
   qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
   QString table = builder.table();
   sql = "SELECT ";
   if (pId) { sql += (pId->getSqlTablePointNameAsAlias(table) + ", "); }
   while ((p = builder.nextData(l1))) { sql += (p->getSqlTablePointNameAsAlias(table) + ", "); }
   if (! oSoftDelete.isEmpty()) { l1++; sql += (oSoftDelete.buildSqlTablePointName() + ", "); }
   while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazySelect(params); }
   sql = sql.left(sql.count() - 2); // Remove last ", "
   sql += " FROM " + qx::IxDataMember::getSqlFromTable(table) + ", ";
   while ((pRelation = builder.nextRelation(l3))) { params.setIndex(l3); pRelation->lazyFrom(params); }
   sql = sql.left(sql.count() - 2); // Remove last ", "
   while ((pRelation = builder.nextRelation(l4))) { params.setIndex(l4); pRelation->lazyJoin(params); }
   if (! oSoftDelete.isEmpty()) { sql += " WHERE " + oSoftDelete.buildSqlQueryToFetch(); }
   while ((pRelation = builder.nextRelation(l5))) { params.setIndex(l5); pRelation->lazyWhereSoftDelete(params); }
}

void IxSqlQueryBuilder::sql_FetchAll(QString & sql, IxSqlQueryBuilder & builder, const QStringList & columns)
{
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId();
   qx::IxDataMemberX * pDataMemberX = builder.getDataMemberX(); qAssert(pDataMemberX);
   qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
   QString table = builder.table();
   sql = "SELECT ";
   if (pId) { sql += (pId->getSqlTablePointNameAsAlias(table) + ", "); }
   for (int i = 0; i < columns.count(); i++)
   { p = pDataMemberX->get_WithDaoStrategy(columns.at(i)); if (p && (p != pId)) { sql += (p->getSqlTablePointNameAsAlias(table) + ", "); } }
   sql = sql.left(sql.count() - 2); // Remove last ", "
   if (! oSoftDelete.isEmpty()) { sql += ", " + oSoftDelete.buildSqlTablePointName(); }
   sql += " FROM " + qx::IxDataMember::getSqlFromTable(table);
   if (! oSoftDelete.isEmpty()) { sql += " WHERE " + oSoftDelete.buildSqlQueryToFetch(); }
}

void IxSqlQueryBuilder::sql_FetchAll_WithRelation(qx::QxSqlRelationLinked * pRelationX, QString & sql, IxSqlQueryBuilder & builder)
{
   long l(0);
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId();
   qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
   qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
   QString table = builder.table();
   sql = "SELECT ";
   if (pId) { sql += (pId->getSqlTablePointNameAsAlias(table) + ", "); }
   while ((p = builder.nextData(l))) { if (pRelationX->checkRootColumns(p->getKey())) { sql += (p->getSqlTablePointNameAsAlias(table) + ", "); } }
   if (! oSoftDelete.isEmpty()) { l++; sql += (oSoftDelete.buildSqlTablePointName() + ", "); }
   pRelationX->hierarchySelect(params);
   sql = sql.left(sql.count() - 2); // Remove last ", "
   sql += " FROM " + qx::IxDataMember::getSqlFromTable(table) + ", ";
   pRelationX->hierarchyFrom(params);
   sql = sql.left(sql.count() - 2); // Remove last ", "
   pRelationX->hierarchyJoin(params);
   if (! oSoftDelete.isEmpty()) { sql += " WHERE " + oSoftDelete.buildSqlQueryToFetch(); }
   pRelationX->hierarchyWhereSoftDelete(params);
}

void IxSqlQueryBuilder::sql_FetchById(QString & sql, IxSqlQueryBuilder & builder)
{
   qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
   QString table = builder.table();
   sql = builder.buildSql().getSqlQuery();
   sql += IxSqlQueryBuilder::addSqlCondition(sql);
   sql += pId->getSqlAliasEqualToPlaceHolder(table, true);
}

void IxSqlQueryBuilder::sql_FetchById(QString & sql, IxSqlQueryBuilder & builder, const QStringList & columns)
{
   qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
   QString table = builder.table();
   sql = builder.buildSql(columns).getSqlQuery();
   sql += IxSqlQueryBuilder::addSqlCondition(sql);
   sql += pId->getSqlAliasEqualToPlaceHolder(table, true);
}

void IxSqlQueryBuilder::sql_FetchById_WithRelation(qx::QxSqlRelationLinked * pRelationX, QString & sql, IxSqlQueryBuilder & builder)
{
   qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
   QString table = builder.table(); QStringList columns;
   sql = builder.buildSql(columns, pRelationX).getSqlQuery();
   sql += IxSqlQueryBuilder::addSqlCondition(sql);
   sql += pId->getSqlAliasEqualToPlaceHolder(table, true);
}

void IxSqlQueryBuilder::sql_Insert(QString & sql, IxSqlQueryBuilder & builder)
{
   long l1(0), l2(0);
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId();
   qx::IxSqlRelation * pRelation = NULL;
   qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
   QString table = builder.table(); QString tmp;
   sql = "INSERT INTO " + table + " (";
   if (pId && ! pId->getAutoIncrement()) { tmp = pId->getSqlName(", ", "", true); if (! tmp.isEmpty()) { sql += tmp + ", "; } }
   while ((p = builder.nextData(l1))) { sql += p->getSqlName(", ") + ", "; }
   while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyInsert(params); }
   sql = sql.left(sql.count() - 2); // Remove last ", "
   sql += ") VALUES (";
   l1 = 0; l2 = 0; p = NULL; pRelation = NULL;
   if (pId && ! pId->getAutoIncrement()) { tmp = pId->getSqlPlaceHolder("", -1, ", ", "", true); if (! tmp.isEmpty()) { sql += tmp + ", "; } }
   while ((p = builder.nextData(l1))) { sql += p->getSqlPlaceHolder("", -1, ", ") + ", "; }
   while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyInsert_Values(params); }
   sql = sql.left(sql.count() - 2); // Remove last ", "
   sql += ")";
}

void IxSqlQueryBuilder::sql_Update(QString & sql, IxSqlQueryBuilder & builder)
{
   long l1(0), l2(0);
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
   qx::IxSqlRelation * pRelation = NULL;
   qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
   QString table = builder.table(); QString tmp;
   sql = "UPDATE " + table + " SET ";
   if (! pId->getAutoIncrement() || (pId->getAutoIncrement() && builder.getAddAutoIncrementIdToUpdateQuery()))
   { tmp = pId->getSqlNameEqualToPlaceHolder("", ", ", true); if (! tmp.isEmpty()) { sql += tmp + ", "; } }
   while ((p = builder.nextData(l1))) { sql += p->getSqlNameEqualToPlaceHolder("", ", ") + ", "; }
   while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyUpdate(params); }
   sql = sql.left(sql.count() - 2); // Remove last ", "
   sql += " WHERE " + pId->getSqlNameEqualToPlaceHolder("_bis", " AND ");
}

void IxSqlQueryBuilder::sql_Update(QString & sql, IxSqlQueryBuilder & builder, const QStringList & columns)
{
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
   qx::IxDataMemberX * pDataMemberX = builder.getDataMemberX(); qAssert(pDataMemberX);
   QString table = builder.table();
   sql = "UPDATE " + table + " SET ";
   if (! pId->getAutoIncrement() || (pId->getAutoIncrement() && builder.getAddAutoIncrementIdToUpdateQuery()))
   { sql += pId->getSqlNameEqualToPlaceHolder("", ", ") + ", "; }
   for (int i = 0; i < columns.count(); i++)
   { p = pDataMemberX->get_WithDaoStrategy(columns.at(i)); if (p && (p != pId)) { sql += p->getSqlNameEqualToPlaceHolder("", ", ") + ", "; } }
   sql = sql.left(sql.count() - 2); // Remove last ", "
   sql += " WHERE " + pId->getSqlNameEqualToPlaceHolder("_bis", " AND ");
}

void IxSqlQueryBuilder::resolveOutput_FetchAll(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder)
{
   long l1(0), l2(0);
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId();
   qx::IxSqlRelation * pRelation = NULL;
   qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
   short iOffset = (pId ? pId->getNameCount() : 0);
   if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { pId->fromVariant(t, query.value(i), i, qx::cvt::context::e_database); } }
   while ((p = builder.nextData(l1))) { p->fromVariant(t, query.value(l1 + iOffset - 1), -1, qx::cvt::context::e_database); }
   iOffset = (builder.getDataCount() + iOffset + (oSoftDelete.isEmpty() ? 0 : 1));
   qx::QxSqlRelationParams params(0, iOffset, NULL, (& builder), (& query), t);
   while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyFetch_ResolveOutput(params); }
}

void IxSqlQueryBuilder::resolveOutput_FetchAll(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder, const QStringList & columns)
{
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId();
   qx::IxDataMemberX * pDataMemberX = builder.getDataMemberX(); qAssert(pDataMemberX);
   short iOffset = (pId ? pId->getNameCount() : 0);
   if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { pId->fromVariant(t, query.value(i), i, qx::cvt::context::e_database); } }
   for (int i = 0; i < columns.count(); i++)
   { p = pDataMemberX->get_WithDaoStrategy(columns.at(i)); if (p && (p != pId)) { p->fromVariant(t, query.value(i + iOffset), -1, qx::cvt::context::e_database); } }
}

void IxSqlQueryBuilder::resolveOutput_FetchAll_WithRelation(qx::QxSqlRelationLinked * pRelationX, void * t, QSqlQuery & query, IxSqlQueryBuilder & builder)
{
   long l(0); long lCurrIndex(0); QVariant vId;
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId();
   qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
   short iOffsetId = (pId ? pId->getNameCount() : 0);
   if (pId) { QString sId; for (int i = 0; i < pId->getNameCount(); i++) { sId += query.value(i).toString() + "|"; }; vId = sId; }
   bool bComplex = builder.getCartesianProduct();
   bool bByPass = (bComplex && builder.existIdX(0, vId, vId));

   if (! bByPass)
   {
      if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { pId->fromVariant(t, query.value(i), i, qx::cvt::context::e_database); } }
      while ((p = builder.nextData(l))) { if (pRelationX->checkRootColumns(p->getKey())) { p->fromVariant(t, query.value(lCurrIndex + iOffsetId), -1, qx::cvt::context::e_database); lCurrIndex++; } }
      if (bComplex) { builder.insertIdX(0, vId, vId, t); }
   }

   short iOffset = (builder.getDataCount() + iOffsetId + (oSoftDelete.isEmpty() ? 0 : 1));
   if ((pRelationX->getRootColumnsCount() > 0) && (pRelationX->getRootColumnsOffset() > 0))
   { iOffset = (iOffset - pRelationX->getRootColumnsOffset()); }
   else if (pRelationX->getRootColumnsCount() > 0)
   {
      l = 0; p = NULL; long lRootColumnsOffset = 0;
      while ((p = builder.nextData(l))) { if (! pRelationX->checkRootColumns(p->getKey())) { iOffset = (iOffset - 1); lRootColumnsOffset++; } }
      pRelationX->setRootColumnsOffset(lRootColumnsOffset);
   }

   qx::QxSqlRelationParams params(0, iOffset, NULL, (& builder), (& query), t, vId);
   pRelationX->hierarchyResolveOutput(params);
}

void IxSqlQueryBuilder::resolveInput_Insert(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder)
{
   long l1(0), l2(0);
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId();
   qx::IxSqlRelation * pRelation = NULL;
   qx::QxSqlRelationParams params(0, 0, NULL, (& builder), (& query), t);
   if (pId && ! pId->getAutoIncrement()) { pId->setSqlPlaceHolder(query, t, "", "", true); }
   while ((p = builder.nextData(l1))) { p->setSqlPlaceHolder(query, t); }
   while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyInsert_ResolveInput(params); }
}

void IxSqlQueryBuilder::resolveInput_Update(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder)
{
   long l1(0), l2(0);
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
   qx::IxSqlRelation * pRelation = NULL;
   qx::QxSqlRelationParams params(0, 0, NULL, (& builder), (& query), t);
   if (! pId->getAutoIncrement() || (pId->getAutoIncrement() && builder.getAddAutoIncrementIdToUpdateQuery()))
   { pId->setSqlPlaceHolder(query, t, "", "", true); }
   while ((p = builder.nextData(l1))) { p->setSqlPlaceHolder(query, t); }
   while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyUpdate_ResolveInput(params); }
   pId->setSqlPlaceHolder(query, t, "_bis");
}

void IxSqlQueryBuilder::resolveInput_Update(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder, const QStringList & columns)
{
   qx::IxDataMember * p = NULL;
   qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
   qx::IxDataMemberX * pDataMemberX = builder.getDataMemberX(); qAssert(pDataMemberX);
   if (! pId->getAutoIncrement() || (pId->getAutoIncrement() && builder.getAddAutoIncrementIdToUpdateQuery()))
   { pId->setSqlPlaceHolder(query, t); }
   for (int i = 0; i < columns.count(); i++)
   { p = pDataMemberX->get_WithDaoStrategy(columns.at(i)); if (p && (p != pId)) { p->setSqlPlaceHolder(query, t); } }
   pId->setSqlPlaceHolder(query, t, "_bis");
}

} // namespace qx
