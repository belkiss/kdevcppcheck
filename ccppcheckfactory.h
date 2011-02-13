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


#ifndef CCPPCHECKFACTORY_H
#define CCPPCHECKFACTORY_H

#include <interfaces/iuicontroller.h>

class CCppcheckFactory : public KDevelop::IToolViewFactory
{
    public:
        CCppcheckFactory();
        virtual ~CCppcheckFactory();

        virtual QWidget            *create(QWidget *inpParent = 0);
        virtual QString             id() const;
        virtual Qt::DockWidgetArea  defaultPosition();
};

#endif // CCPPCHECKFACTORY_H
