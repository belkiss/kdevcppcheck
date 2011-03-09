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

#include "ccppcheckmodel.h"
#include "cppcheckplugin.h"

#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/iprojectcontroller.h>

#include "ccppcheckexecutor.h"
#include <cppcheck.h>

// only needed for completion......
#include <interfaces/iproject.h>

#include <project/projectmodel.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/topducontext.h>
#include <language/duchain/duchainutils.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckModel::CCppcheckModel(CCppcheckPlugin *inpParent) :
    QStandardItemModel(inpParent),
    m_pCppcheckPlugin(inpParent)
{
    qDebug() << "Cppcheck plugin" << __FILE__ << ":" << __LINE__ << __FUNCTION__;

    std::string activateAll = m_resultSettings.addEnabled("all");
    qDebug() << "Cppcheck plugin" << __FILE__ << ":" << __LINE__ << __FUNCTION__ << activateAll.length() << activateAll.c_str();
    m_resultSettings.addEnabled("style");
    m_resultSettings.addEnabled("information");
    m_resultSettings.addEnabled("missingInclude");
    m_resultSettings.debug = false;
    m_resultSettings.debugwarnings = false;
    m_resultSettings._errorsOnly = false;
    m_resultSettings._verbose = true;
    m_resultSettings._force = true;
    m_resultSettings._xml = false;
    m_resultSettings._jobs = 1;
    m_resultSettings._inlineSuppressions = false;

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CCppcheckModel::~CCppcheckModel()
{
    qDebug() << "Cppcheck plugin" << __FILE__ << ":" << __LINE__ << __FUNCTION__;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckModel::parseCurrentFile()
{
    qDebug() << "Cppcheck plugin" << __FILE__ << ":" << __LINE__ << __FUNCTION__<< "Parse button clicked";
    if(KDevelop::ICore::self()->documentController()->activeDocument())
    {
        // get the currently active document url
        KUrl currentFileURL = KDevelop::ICore::self()->documentController()->activeDocument()->url();

        // Add include paths for this file : warning ! they must end with '/'
        qDebug() << "Cppcheck plugin" << "Parent dir :" << currentFileURL.directory(KUrl::AppendTrailingSlash);
        m_resultSettings._includePaths.push_back(currentFileURL.directory(KUrl::AppendTrailingSlash).toStdString());

        // check if it is part of an opened project
        KDevelop::IProject* pCurrentFileProject = KDevelop::ICore::self()->projectController()->findProjectForUrl(currentFileURL);
        if(pCurrentFileProject)
        {
            qDebug() << "Cppcheck plugin" << "Found project";
            QList<KDevelop::ProjectBaseItem*> currentFileItems = pCurrentFileProject->itemsForUrl(currentFileURL);
            if(!currentFileItems.isEmpty())
            {
                qDebug() << "Cppcheck plugin" << "Not empty";
                for(QList<KDevelop::ProjectBaseItem*>::iterator it = currentFileItems.begin(); it != currentFileItems.end(); ++it)
                {
                    KDevelop::ProjectBaseItem *pItem = *it;
                    qDebug() << "Cppcheck plugin" << "Item " << pItem->url().prettyUrl();
                }
            }
            else
            {
                qDebug() << "Cppcheck plugin" << "Empty";
            }

            qDebug() << "Cppcheck plugin" << "Project dir :" << pCurrentFileProject->folder().toLocalFile(KUrl::AddTrailingSlash);
            m_resultSettings._includePaths.push_back(pCurrentFileProject->folder().toLocalFile(KUrl::AddTrailingSlash).toStdString());
        }
        else
        {
            qDebug() << "Cppcheck plugin" << "Project NOT found";
        }

        {
            KDevelop::DUChainReadLocker lock;

            KDevelop::TopDUContext* pTopCtx = KDevelop::DUChainUtils::standardContextForUrl(currentFileURL);
            if(!pTopCtx)
            {
                qDebug() << "Cppcheck plugin" << "Empty";
                return;
            }
            else
            {
                qDebug() << "Cppcheck plugin" << "There is stuff inside :";
                foreach(const KDevelop::DUContext::Import &ctxImport, pTopCtx->importedParentContexts())
                {
                    KDevelop::DUContext *pBaseContext = ctxImport.context(pTopCtx->topContext());
                    if(pBaseContext)
                    {
                        KUrl parentURL = pBaseContext->url().toUrl();
                        if(KDevelop::ICore::self()->projectController()->findProjectForUrl(parentURL))
                        {
                            qDebug() << "Cppcheck plugin" << " `--" << parentURL << "added";
                            m_resultSettings._includePaths.push_back(parentURL.directory(KUrl::AppendTrailingSlash).toStdString());
                        }
                        else
                        {
                            qDebug() << "Cppcheck plugin" << " `--" << parentURL << "NOT in project";
                        }
                    }
                }
            }
        }

        qDebug() << "Cppcheck plugin" << "Launch cppcheck on" << currentFileURL;
        CCppcheckExecutor cppcheckEx;
        CppCheck cppcheck(cppcheckEx);
        cppcheck.settings(m_resultSettings);
        cppcheck.addFile(currentFileURL.toLocalFile().toStdString());
        unsigned int nbErrors = cppcheck.check();
        cppcheck.clearFiles();
        cppcheck.terminate();
        qDebug() << "Cppcheck plugin" << " cppcheck reported" << nbErrors << "errors on this file";
    }
    qDebug() << "Cppcheck plugin" << __FILE__ << ":" << __LINE__ << __FUNCTION__;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckModel::setShowErrors(bool /*inShowErrors*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckModel::setShowInformation(bool /*inShowInformation*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckModel::setShowPerformance(bool /*inShowPerformance*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckModel::setShowPortability(bool /*inShowPortability*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckModel::setShowStyle(bool /*inShowStyle*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckModel::setShowWarnings(bool /*inShowWarnings*/)
{

}
