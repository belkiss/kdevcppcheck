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

#ifndef CPPCHECKPLUGIN_H
#define CPPCHECKPLUGIN_H

#include <interfaces/iplugin.h>
#include <QVariantList>

#include "ccppcheckfactory.h"

class CCppcheckPlugin : public KDevelop::IPlugin
{
    Q_OBJECT
    public:
        CCppcheckPlugin(QObject *inpParent, const QVariantList &inArgs = QVariantList());
        virtual ~CCppcheckPlugin();

        virtual bool      hasError()         const;
        virtual QString   errorDescription() const;

    private:
        bool              m_hasError;
        QString           m_errorDescription;

        CCppcheckFactory *m_pFactory;
};

#endif // CPPCHECKPLUGIN_H
