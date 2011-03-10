/*
    cppcheck plugin for kdevelop4
    Copyright (C) 2011  Lambert CLARA <lambert.clara@yahoo.fr>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ccppcheckexecutor.h"
#include "cppcheck.h"
#include <QDebug>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckExecutor::CCppcheckExecutor() :
    m_pCppCheck(new CppCheck(*this))
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckExecutor::~CCppcheckExecutor()
{
    delete m_pCppCheck; m_pCppCheck = 0;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckExecutor::reportOut(const std::string &inOutputMsg)
{
    qDebug() << "Cppcheck plugin" << __FILE__ << ":" << __LINE__ << __FUNCTION__ << inOutputMsg.c_str();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckExecutor::reportErr(const ErrorLogger::ErrorMessage &inErrorMsg)
{
    emit signalCppcheckError(inErrorMsg);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckExecutor::reportStatus(unsigned int inIndex, unsigned int inMax)
{
    qDebug() << "Cppcheck plugin" << __FILE__ << ":" << __LINE__ << __FUNCTION__ << inIndex << inMax;
}
