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

#include "ccppcheckwidget.h"

#include <KIcon>
#include <KAction>
#include <KActionMenu>
#include <KLocale>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckWidget::CCppcheckWidget(QWidget* inpParent) :
    QTreeView(inpParent)
{
    setObjectName("cppcheck plugin report");
    setWindowTitle("cppcheck");
    setWindowIcon(KIcon("cppcheck"));
    setRootIsDecorated(true);
    setWhatsThis("cppcheck");

    KAction *pActionShowErrors = new KAction(this);
    addAction(pActionShowErrors);
    pActionShowErrors->setCheckable(true);
    pActionShowErrors->setChecked(false);
    pActionShowErrors->setText(i18n("Show errors"));
    pActionShowErrors->setToolTip(i18n("Show errors"));
    pActionShowErrors->setIcon(KIcon("user-busy"));

    KAction *pActionShowWarnings = new KAction(this);
    addAction(pActionShowWarnings);
    pActionShowWarnings->setCheckable(true);
    pActionShowWarnings->setChecked(false);
    pActionShowWarnings->setText(i18n("Show warnings"));
    pActionShowWarnings->setToolTip(i18n("Show warnings"));
    pActionShowWarnings->setIcon(KIcon("dialog-warning"));

    KAction *pActionShowStyle = new KAction(this);
    addAction(pActionShowStyle);
    pActionShowStyle->setCheckable(true);
    pActionShowStyle->setChecked(false);
    pActionShowStyle->setText(i18n("Show style warnings"));
    pActionShowStyle->setToolTip(i18n("Show style warnings"));
    pActionShowStyle->setIcon(KIcon("help-hint"));

    KAction *pActionShowPortability = new KAction(this);
    addAction(pActionShowPortability);
    pActionShowPortability->setCheckable(true);
    pActionShowPortability->setChecked(false);
    pActionShowPortability->setText(i18n("Show portability warnings"));
    pActionShowPortability->setToolTip(i18n("Show portability warnings"));
    pActionShowPortability->setIcon(KIcon("office-chart-ring"));

    KAction *pActionShowPerformance = new KAction(this);
    addAction(pActionShowPerformance);
    pActionShowPerformance->setCheckable(true);
    pActionShowPerformance->setChecked(false);
    pActionShowPerformance->setText(i18n("Show performance warnings"));
    pActionShowPerformance->setToolTip(i18n("Show performance warnings"));
    pActionShowPerformance->setIcon(KIcon("fork"));

    KAction *pActionShowInformation = new KAction(this);
    addAction(pActionShowInformation);
    pActionShowInformation->setCheckable(true);
    pActionShowInformation->setChecked(false);
    pActionShowInformation->setText(i18n("Show information messages"));
    pActionShowInformation->setToolTip(i18n("Show information messages"));
    pActionShowInformation->setIcon(KIcon("help-about"));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckWidget::~CCppcheckWidget()
{
}

