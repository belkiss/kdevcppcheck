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

#include "cppcheckplugin.h"
#include "ccppcheckfactory.h"
#include "ccppcheckoutputmodel.h"

#include "cppcheck.h"

#include <KPluginFactory>
#include <KPluginLoader>
#include <KAboutData>
#include <KLocale>
#include <KStandardDirs>

#include <interfaces/icore.h>

K_PLUGIN_FACTORY(KDevCppcheckFactory,
                 registerPlugin<CCppcheckPlugin>();)
K_EXPORT_PLUGIN(KDevCppcheckFactory(KAboutData(// The program name used internally.
                                               "kdevcppcheck",
                                               // The message catalog name
                                               // If null, program name is used instead.
                                               0,
                                               // A displayable program name string.
                                               ki18n("Cppcheck static code analyzer"),
                                               // The program version string.
                                               "0.1",
                                               // Short description of what the app does.
                                               ki18n("Shows the static code analyzer cppcheck output in source code"),
                                               // The license this code is released under
                                               KAboutData::License_GPL_V3)))

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckPlugin::CCppcheckPlugin(QObject *inpParent,
                                 const QVariantList &/*inArgs*/):
    IPlugin(KDevCppcheckFactory::componentData(), inpParent),
    m_hasError(false),
    m_errorDescription(""),
    m_pFactory(new CCppcheckFactory(this)),
    m_pCppcheckModel(new CCppcheckOutputModel(this))
{
    QString name = "Cppcheck ";
    name += CppCheck::version();
    core()->uiController()->addToolView(i18n(qPrintable(name)), m_pFactory);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckPlugin::~CCppcheckPlugin()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool CCppcheckPlugin::hasError() const
{
    return KDevelop::IPlugin::hasError();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
QString CCppcheckPlugin::errorDescription() const
{
    return KDevelop::IPlugin::errorDescription();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckOutputModel *CCppcheckPlugin::getModel() const
{
    return m_pCppcheckModel;
}

