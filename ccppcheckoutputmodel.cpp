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

#include "ccppcheckoutputmodel.h"
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
CCppcheckOutputModel::CCppcheckOutputModel(CCppcheckPlugin *inpParent) :
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
CCppcheckOutputModel::~CCppcheckOutputModel()
{
    qDebug() << "Cppcheck plugin" << __FILE__ << ":" << __LINE__ << __FUNCTION__;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckOutputModel::activate(const QModelIndex &inIndex)
{
    qDebug() << "Cppcheck plugin" << __FILE__ << ":" << __LINE__ << __FUNCTION__;
    if(inIndex.isValid())
    {
        QStandardItem *pCppcheckErrorItem = itemFromIndex(inIndex);
        qDebug() << "Cppcheck plugin" << "Item activated :" << pCppcheckErrorItem->text();
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckOutputModel::parseCurrentFile()
{
    // remove all "old results" from model
    clear();

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
        connect(&cppcheckEx, SIGNAL(signalCppcheckError(const ErrorLogger::ErrorMessage &)), this, SLOT(addCppcheckError(const ErrorLogger::ErrorMessage &)));
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
void CCppcheckOutputModel::setShowErrors(bool /*inShowErrors*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckOutputModel::setShowInformation(bool /*inShowInformation*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckOutputModel::setShowPerformance(bool /*inShowPerformance*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckOutputModel::setShowPortability(bool /*inShowPortability*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckOutputModel::setShowStyle(bool /*inShowStyle*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckOutputModel::setShowWarnings(bool /*inShowWarnings*/)
{

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CCppcheckOutputModel::addCppcheckError(const ErrorLogger::ErrorMessage &inCppcheckError)
{
    qDebug() << "Cppcheck plugin" << __LINE__ << __FUNCTION__ << inCppcheckError.toString(true, "{file} : {line}, {severity}, {id}, {message}").c_str();
    QStandardItem *pRootItem = invisibleRootItem();
    std::stringstream cppcheckErrorStrStr(inCppcheckError.toString(true, "{file} {line} {severity} {id}"));
    std::string  fileFullPath;
    unsigned int lineNumber;
    std::string  severity;
    std::string  id;
    std::string  shortMessage;
    std::string  longMessage;
    cppcheckErrorStrStr >> fileFullPath >> lineNumber >> severity >> id;
    shortMessage = inCppcheckError.toString(false, ":{line} {message}");
    longMessage  = inCppcheckError.toString(true, "{message}");

    QStandardItem *pCppcheckErrorItem = new QStandardItem();
    pCppcheckErrorItem->setEditable(false);
    pCppcheckErrorItem->setEnabled(true);
    pCppcheckErrorItem->setSelectable(true);

    KUrl fileUrl(fileFullPath.c_str());
    QString prettyFilePath = KDevelop::ICore::self()->projectController()->prettyFileName(fileUrl, KDevelop::IProjectController::FormatPlain);

    pCppcheckErrorItem->setText(prettyFilePath + QString::fromStdString(shortMessage));

    // sets the long description as tooltip
    pCppcheckErrorItem->setToolTip(QString::fromStdString(longMessage));
    Severity::SeverityType sev = Severity::fromString(severity);
    switch(sev)
    {
        case Severity::error:
            pCppcheckErrorItem->setIcon(KIcon("user-busy"));
            break;
        case Severity::warning:
            pCppcheckErrorItem->setIcon(KIcon("dialog-warning"));
            break;
        case Severity::style:
            pCppcheckErrorItem->setIcon(KIcon("help-hint"));
            break;
        case Severity::performance:
            pCppcheckErrorItem->setIcon(KIcon("fork"));
            break;
        case Severity::portability:
            pCppcheckErrorItem->setIcon(KIcon("office-chart-ring"));
            break;
        case Severity::information:
            pCppcheckErrorItem->setIcon(KIcon("help-about"));
            break;
        case Severity::debug:
            pCppcheckErrorItem->setIcon(KIcon("tools-report-bug"));
            break;
        case Severity::none:
        default:
            pCppcheckErrorItem->setIcon(KIcon("edit-bomb"));
    };
    if(sev != Severity::debug)
    {
        pRootItem->appendRow(pCppcheckErrorItem);
    }
}
