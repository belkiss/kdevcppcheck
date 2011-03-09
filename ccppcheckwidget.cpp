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
#include "ccppcheckmodel.h"
#include "cppcheckplugin.h"

#include <KIcon>
#include <KAction>
#include <KActionMenu>
#include <KLocale>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckWidget::CCppcheckWidget(QWidget* inpParent,
                                 CCppcheckPlugin *inpCppcheckPlugin) :
    QTreeView(inpParent),
    m_pCppcheckPlugin(inpCppcheckPlugin)
{
    setObjectName("cppcheck plugin report");
    setWindowTitle("cppcheck");
    setWindowIcon(KIcon("cppcheck"));
    setRootIsDecorated(true);
    setWhatsThis("cppcheck plugin report");

    setModel(m_pCppcheckPlugin->getModel());

    KAction *pCheckCurrentFile = new KAction(this);
    pCheckCurrentFile->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    pCheckCurrentFile->setText(i18n("(Re-)launch cppcheck on the current file"));
    pCheckCurrentFile->setToolTip(i18n("(Re-)launch cppcheck on the current file"));
    pCheckCurrentFile->setIcon(KIcon("view-refresh"));
    connect(pCheckCurrentFile, SIGNAL(triggered(bool)), model(), SLOT(parseCurrentFile()));
    addAction(pCheckCurrentFile);

    KAction *pActionShowErrors = new KAction(this);
    addAction(pActionShowErrors);
    pActionShowErrors->setCheckable(true);
    pActionShowErrors->setChecked(false);
    pActionShowErrors->setText(i18n("Show errors"));
    pActionShowErrors->setToolTip(i18n("Show errors"));
    pActionShowErrors->setIcon(KIcon("user-busy"));
    model()->setShowErrors(true);
    connect(pActionShowErrors, SIGNAL(triggered(bool)), model(), SLOT(setShowErrors(bool)));

    KAction *pActionShowWarnings = new KAction(this);
    addAction(pActionShowWarnings);
    pActionShowWarnings->setCheckable(true);
    pActionShowWarnings->setChecked(false);
    pActionShowWarnings->setText(i18n("Show warnings"));
    pActionShowWarnings->setToolTip(i18n("Show warnings"));
    pActionShowWarnings->setIcon(KIcon("dialog-warning"));
    model()->setShowWarnings(true);
    connect(pActionShowWarnings, SIGNAL(triggered(bool)), model(), SLOT(setShowWarnings(bool)));

    KAction *pActionShowStyle = new KAction(this);
    addAction(pActionShowStyle);
    pActionShowStyle->setCheckable(true);
    pActionShowStyle->setChecked(false);
    pActionShowStyle->setText(i18n("Show style warnings"));
    pActionShowStyle->setToolTip(i18n("Show style warnings"));
    pActionShowStyle->setIcon(KIcon("help-hint"));
    model()->setShowStyle(true);
    connect(pActionShowStyle, SIGNAL(triggered(bool)), model(), SLOT(setShowStyle(bool)));

    KAction *pActionShowPortability = new KAction(this);
    addAction(pActionShowPortability);
    pActionShowPortability->setCheckable(true);
    pActionShowPortability->setChecked(false);
    pActionShowPortability->setText(i18n("Show portability warnings"));
    pActionShowPortability->setToolTip(i18n("Show portability warnings"));
    pActionShowPortability->setIcon(KIcon("office-chart-ring"));
    model()->setShowPortability(true);
    connect(pActionShowPortability, SIGNAL(triggered(bool)), model(), SLOT(setShowPortability(bool)));

    KAction *pActionShowPerformance = new KAction(this);
    addAction(pActionShowPerformance);
    pActionShowPerformance->setCheckable(true);
    pActionShowPerformance->setChecked(false);
    pActionShowPerformance->setText(i18n("Show performance warnings"));
    pActionShowPerformance->setToolTip(i18n("Show performance warnings"));
    pActionShowPerformance->setIcon(KIcon("fork"));
    model()->setShowPerformance(true);
    connect(pActionShowPerformance, SIGNAL(triggered(bool)), model(), SLOT(setShowPerformance(bool)));

    KAction *pActionShowInformation = new KAction(this);
    addAction(pActionShowInformation);
    pActionShowInformation->setCheckable(true);
    pActionShowInformation->setChecked(false);
    pActionShowInformation->setText(i18n("Show information messages"));
    pActionShowInformation->setToolTip(i18n("Show information messages"));
    pActionShowInformation->setIcon(KIcon("help-about"));
    model()->setShowInformation(true);
    connect(pActionShowInformation, SIGNAL(triggered(bool)), model(), SLOT(setShowInformation(bool)));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckWidget::~CCppcheckWidget()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckModel *CCppcheckWidget::model() const
{
    return static_cast<CCppcheckModel*>(QTreeView::model());
}
