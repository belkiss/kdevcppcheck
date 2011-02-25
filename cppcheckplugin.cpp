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
#include "ccppcheckexecutor.h"

#include <KPluginFactory>
#include <KPluginLoader>
#include <KAboutData>
#include <KLocale>
#include <KStandardDirs>

#include <interfaces/icore.h>

K_PLUGIN_FACTORY(KDevCppcheckFactory,
                 registerPlugin<CCppcheckPlugin>();)
K_EXPORT_PLUGIN(KDevCppcheckFactory(KAboutData("kdevcppcheck",
                                               "kdevcppcheck",
                                               ki18n("cppcheck static code analyzer"),
                                               "0.1",
                                               ki18n("Launch the static code analyzer cppcheck"),
                                               KAboutData::License_GPL_V3)))

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckPlugin::CCppcheckPlugin(QObject *inpParent,
                                 const QVariantList &/*inArgs*/):
    IPlugin(KDevCppcheckFactory::componentData(), inpParent),
    m_hasError(false),
    m_errorDescription(""),
    m_pFactory(new CCppcheckFactory(this))
{
    CCppcheckExecutor cppcheck;
    std::string name = "cppcheck " + cppcheck.getcppcheckVersion();
    core()->uiController()->addToolView(i18n(name.c_str()), m_pFactory);
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
