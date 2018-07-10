/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#include <QxPrecompiled.h>

#include <QxRegister/IxClass.h>
#include <QxRegister/QxClassX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxClass::~IxClass()
{
   if (QxClassX::isSingletonNull() || m_sKey.isEmpty()) { return; }
   QxClassX::getSingleton()->remove(m_sKey);
}

void IxClass::updateClassX()
{
   qAssert(! m_sKey.isEmpty() && ! QxClassX::getSingleton()->exist(m_sKey));
   QxClassX::getSingleton()->insert(m_sKey, this);
}

} // namespace qx
