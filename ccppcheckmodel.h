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

#ifndef CCPPCHECKMODEL_H
#define CCPPCHECKMODEL_H

#include <QStandardItemModel>
#include <settings.h>

class CCppcheckPlugin;

class CCppcheckModel : public QStandardItemModel
{
    Q_OBJECT
    public:
        CCppcheckModel(CCppcheckPlugin *inpParent);
        virtual ~CCppcheckModel();

    public slots:
        void parseCurrentFile();

        void setShowErrors     (bool inShowErrors);
        void setShowWarnings   (bool inShowWarnings);
        void setShowStyle      (bool inShowStyle);
        void setShowPortability(bool inShowPortability);
        void setShowPerformance(bool inShowPerformance);
        void setShowInformation(bool inShowInformation);

    private:
        CCppcheckPlugin    *m_pCppcheckPlugin;

        // cppcheck lib members
        Settings            m_resultSettings;
};

#endif // CCPPCHECKMODEL_H
