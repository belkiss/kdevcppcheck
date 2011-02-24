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

#ifndef CCPPCHECKEXECUTOR_H
#define CCPPCHECKEXECUTOR_H

#include "errorlogger.h"

class CppCheck;
class CCppcheckExecutor : public ErrorLogger
{
    public:
        CCppcheckExecutor();
        virtual ~CCppcheckExecutor();

        std::string getcppcheckVersion();

        virtual void reportOut(const std::string &inOutputMsg);
        virtual void reportErr(const ErrorLogger::ErrorMessage &inErrorMsg);
        virtual void reportStatus(unsigned int inIndex, unsigned int inMax);

    private:
        CppCheck *m_pCppCheck;
};

#endif // CCPPCHECKEXECUTOR_H
