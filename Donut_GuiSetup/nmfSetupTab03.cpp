
#include "nmfSetupTab03.h"
#include "nmfConstantsDonut.h"
#include "nmfUtilsQt.h"
#include "nmfUtils.h"
#include "nmfConstants.h"

#include <QCheckBox>

nmfSetup_Tab3::nmfSetup_Tab3(QTabWidget*  tabs,
                             nmfLogger*   logger,
                             std::string& projectDir)
{
    QUiLoader loader;

    Setup_Tabs               = tabs;
    m_logger                 = logger;
    m_ProjectDir             = projectDir;
    m_ProjectName.clear();
    m_smodelSpecies          = nullptr;
    m_smodelOtherPredSpecies = nullptr;
    m_colLabelsSpecies.clear();

    readSettings();

    // Load ui as a widget from disk
    QFile file(":/forms/Setup/Setup_Tab03.ui");
    file.open(QFile::ReadOnly);
    Setup_Tab3_Widget = loader.load(&file,Setup_Tabs);
    Setup_Tab3_Widget->setObjectName("Setup_Tab3_Widget");
    file.close();

    // Add the loaded widget as the new tabbed page
    Setup_Tabs->addTab(Setup_Tab3_Widget, tr("3. Species Setup"));

    Setup_Tab3_SpeciesTW          = Setup_Tabs->findChild<QTableWidget *>("Setup_Tab3_SpeciesTW");
    Setup_Tab3_InteractionTW          = Setup_Tabs->findChild<QTableWidget *>("Setup_Tab3_InteractionTW");
    Setup_Tab3_NumSpeciesSB       = Setup_Tabs->findChild<QSpinBox     *>("Setup_Tab3_NumSpeciesSB");
    Setup_Tab3_AddSpeciesPB       = Setup_Tabs->findChild<QPushButton  *>("Setup_Tab3_AddSpeciesPB");
    Setup_Tab3_DelSpeciesPB       = Setup_Tabs->findChild<QPushButton  *>("Setup_Tab3_DelSpeciesPB");
    Setup_Tab3_LoadPB             = Setup_Tabs->findChild<QPushButton  *>("Setup_Tab3_LoadPB");
    Setup_Tab3_SavePB             = Setup_Tabs->findChild<QPushButton  *>("Setup_Tab3_SavePB");
    Setup_Tab3_NextPB             = Setup_Tabs->findChild<QPushButton  *>("Setup_Tab3_NextPB");
    Setup_Tab3_GuildsSpeciesTabW  = Setup_Tabs->findChild<QTabWidget   *>("Setup_Tab3_GuildsSpeciesTabW");

    connect(Setup_Tab3_NumSpeciesSB,    SIGNAL(valueChanged(int)),
            this,                       SLOT(callback_Setup_Tab3_NumSpecies(int)));
    connect(Setup_Tab3_AddSpeciesPB,    SIGNAL(clicked()),
            this,                       SLOT(callback_Setup_Tab3_AddSpeciesPB()));
    connect(Setup_Tab3_DelSpeciesPB,    SIGNAL(clicked()),
            this,                       SLOT(callback_Setup_Tab3_DelSpeciesPB()));
    connect(Setup_Tab3_SavePB,          SIGNAL(clicked()),
            this,                       SLOT(callback_Setup_Tab3_SavePB()));
    connect(Setup_Tab3_NextPB,          SIGNAL(clicked()),
            this,                       SLOT(callback_Setup_Tab3_NextPB()));
    connect(Setup_Tab3_SpeciesTW,       SIGNAL(cellClicked(int,int)),
            this,                       SLOT(callback_Setup_Tab3_SpeciesTableChanged(int,int)));

    Setup_Tab3_LoadPB->hide();
    Setup_Tab3_NextPB->setText("--\u25B7");
    Setup_Tab3_SavePB->setEnabled(true);
    Setup_Tab3_SpeciesTW->setSelectionMode(QAbstractItemView::ContiguousSelection);

    m_colLabelsSpecies << "Taxa" << "Type";

    // RSK Temp code
//    QStandardItemModel* smodel = new QStandardItemModel();
//    int numCols = 5;
//    int numRows = 3;
//    smodel->setRowCount(numRows);
//    smodel->setColumnCount(numCols);

//    Setup_Tab3_SpeciesTW->setHorizontalHeaderLabels(m_colLabelsSpecies);

}

nmfSetup_Tab3::~nmfSetup_Tab3()
{
}


void
nmfSetup_Tab3::clearSpeciesWidgets()
{
    Setup_Tab3_SpeciesTW->setRowCount(0);
    Setup_Tab3_SpeciesTW->setColumnCount(0);
}

void
nmfSetup_Tab3::loadInteractionData()
{
    int index;
    QCheckBox*           cbox;
    QStringList          preyList;
    QStringList          predList;
    QString              preyName;
    QString              predName;

    int numRows = Setup_Tab3_InteractionTW->rowCount();
    int numCols = Setup_Tab3_InteractionTW->columnCount();
    for (int i=0; i<numCols; ++i) {
        preyList << Setup_Tab3_InteractionTW->horizontalHeaderItem(i)->text().trimmed();
    }

    for (int i=0; i<numRows; ++i) {
        predList << Setup_Tab3_InteractionTW->verticalHeaderItem(i)->text().trimmed();
    }

    // Read project file and load
    QString filename = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(m_ProjectName));
    if (QFileInfo(filename).suffix().isEmpty()) {
        filename += ".inter";
    }
    QFile file(filename);
    QStringList parts;
    if ( file.open(QIODevice::ReadOnly|QIODevice::Text) )
    {
        QTextStream stream(&file);
        QString line = stream.readLine();
        while (! line.isNull())
        {
            parts    = line.split(",");
            predName = parts[0];
            for (int j=0; j<parts.size()-1; ++j) {
                preyName = parts[j+1].trimmed();
                index = preyList.indexOf(preyName);
                for (int k=0; k<numRows; ++k) {
                    if (predName == Setup_Tab3_InteractionTW->verticalHeaderItem(k)->text().trimmed()) {
                        cbox = Setup_Tab3_InteractionTW->cellWidget(k,index)->findChild<QCheckBox *>("CheckBoxItem");
                        cbox->setChecked(true);
                        break;
                    }
                }
            }

            line = stream.readLine();
        }
        file.close();
    }

}

void
nmfSetup_Tab3::loadSpecies()
{
    clearSpeciesWidgets();
    loadSpeciesData();
    setupInteractionTable();
    loadInteractionData();
}

void
nmfSetup_Tab3::loadSpeciesData()
{
    int NumSpecies;
    std::vector<QString> SpeciesNames;
    std::vector<int>     SpeciesIndexes;
    QString              type;
    QComboBox*           cmbox;

    // Read project file and load
    QString filename = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(m_ProjectName));
    if (QFileInfo(filename).suffix().isEmpty()) {
        filename += ".species";
    }
    QFile file(filename);
    QStringList parts;
    if ( file.open(QIODevice::ReadOnly|QIODevice::Text) )
    {
        QTextStream stream(&file);
        QString line = stream.readLine();
        while (! line.isNull()) {
            parts = line.split(",");
            SpeciesNames.push_back(parts[0]);
            type = parts[1].trimmed();
            if (type == "Pred") {
                SpeciesIndexes.push_back(0);
            } else if (type == "Prey") {
                SpeciesIndexes.push_back(1);
            } else if (type == "Both") {
                SpeciesIndexes.push_back(2);
            }
            line = stream.readLine();
        }
        file.close();
    }
    NumSpecies = SpeciesNames.size();

    int numCols = m_colLabelsSpecies.size();
    Setup_Tab3_SpeciesTW->setRowCount(NumSpecies);
    Setup_Tab3_SpeciesTW->setColumnCount(numCols);
    for (int i=0; i<NumSpecies; ++i) {
          populateARowSpecies(i,numCols);
    }
    for (int i=0; i<NumSpecies; ++i) {
        Setup_Tab3_SpeciesTW->item(i,0)->setText(SpeciesNames[i]);
        cmbox = qobject_cast<QComboBox *>(Setup_Tab3_SpeciesTW->cellWidget(i,1));
        cmbox->setCurrentIndex(SpeciesIndexes[i]);
    }

    Setup_Tab3_SpeciesTW->setHorizontalHeaderLabels(m_colLabelsSpecies);
    Setup_Tab3_SpeciesTW->resizeColumnsToContents();
    Setup_Tab3_NumSpeciesSB->blockSignals(true);
    Setup_Tab3_NumSpeciesSB->setEnabled(NumSpecies == 0);
    Setup_Tab3_NumSpeciesSB->setValue(NumSpecies);
    Setup_Tab3_NumSpeciesSB->blockSignals(false);
}

void
nmfSetup_Tab3::loadWidgets()
{
    m_logger->logMsg(nmfConstants::Normal,"nmfSetup_Tab3::loadWidgets()");

    readSettings();
    loadSpecies();
}

int
nmfSetup_Tab3::numColumnsSpecies()
{
    return m_colLabelsSpecies.size();
}

void
nmfSetup_Tab3::populateARowSpecies(int row, int ncols)
{
    QComboBox *cmbox;
    QTableWidgetItem *item;
    QStringList TypeValues = {"Pred","Prey","Both"};

    for (int j=0;j<ncols; ++j) {
        switch (j) {
            case 1:
                cmbox = new QComboBox();
                cmbox->addItems(TypeValues);
                Setup_Tab3_SpeciesTW->setCellWidget(row,j,cmbox);
                break;
            default:
                item = new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignCenter);
                Setup_Tab3_SpeciesTW->setItem(row,j,item);
                break;
            }
    }
    Setup_Tab3_SpeciesTW->resizeColumnsToContents();
}

void
nmfSetup_Tab3::readSettings()
{
    QSettings* settings = nmfUtilsQt::createSettings(nmfConstantsDonut::SettingsDirWindows,"DonutTool");

    settings->beginGroup("Settings");
    m_ProjectSettingsConfig = settings->value("Name","").toString().toStdString();
    settings->endGroup();
    settings->beginGroup("SetupTab");
    m_ProjectDir  = settings->value("ProjectDir", "").toString().toStdString();
    m_ProjectName = settings->value("ProjectName","").toString().toStdString();
    settings->endGroup();

    delete settings;
}

void
nmfSetup_Tab3::removeFromProjectFiles(QString species)
{
    std::string msg;
    QString projectName = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(m_ProjectName));
    QString filename;
    QString line;
    QStringList parts;
    QStringList newLines;

    msg = "Removing all references to: " + species.toStdString();
    m_logger->logMsg(nmfConstants::Normal,msg);

    // Remove from .species file
    filename = projectName + ".species";
    newLines.clear();
    QFile fileIn(filename);
    if (fileIn.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QTextStream stream(&fileIn);
        line = stream.readLine();
        while (! line.isNull()) {
            parts = line.split(",");
            if (species != parts[0]) {
                newLines << line;
            }
            line = stream.readLine();
        }
        fileIn.close();
    } else {
        msg = "Error: Couldn't open file for reading: " + filename.toStdString();
        m_logger->logMsg(nmfConstants::Error,msg);
        return;
    }
    QFile fileOut(filename);
    if (fileOut.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream stream(&fileOut);
        for (QString line : newLines) {
            stream << line << "\n";
        }
        fileOut.close();
    }  else {
        msg = "Error: Couldn't open file for writing: " + filename.toStdString();
        m_logger->logMsg(nmfConstants::Error,msg);
        return;
    }

    // Remove species file from [project].[pred] file
    filename = projectName + "." + species;
    QFile predFile(filename);
    if (predFile.exists()) {
        if (! predFile.remove()) {
            msg = "Error: Couldn't remove file: " + filename.toStdString();
            m_logger->logMsg(nmfConstants::Error,msg);
            return;
        }
    }

    // Remove all occurrences in .inter file and copy edited lines to newLines
    filename = projectName + ".inter";
    QFile fileInterIn(filename);
    newLines.clear();
    if (fileInterIn.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QTextStream stream(&fileInterIn);
        line = stream.readLine();
        while (! line.isNull()) {
            parts = line.split(",");
            if (species != parts[0]) {
                line = line.replace(","+species,"");
                line = line.replace(species+",","");
                newLines << line;
            }
            line = stream.readLine();
        }
        fileInterIn.close();
    } else {
        msg = "Error: Couldn't open file for reading: " + filename.toStdString();
        m_logger->logMsg(nmfConstants::Error,msg);
        return;
    }
    // Copy newLines back into the .inter file
    QFile fileInterOut(filename);
    if (fileInterOut.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream stream(&fileInterOut);
        for (QString line : newLines) {
            stream << line << "\n";
        }
        fileInterOut.close();
    } else {
        msg = "Error: Couldn't open file for writing: " + filename.toStdString();
        m_logger->logMsg(nmfConstants::Error,msg);
        return;
    }
}

void
nmfSetup_Tab3::saveInteractionData()
{
    QStringList preyList;
    QStringList predList;
    QCheckBox* cbox;

    // Write out Interaction data
    QString filename = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(m_ProjectName));
    if (QFileInfo(filename).suffix().isEmpty()) {
        filename += ".inter";
    }
    QFile file(filename);
    if (! file.open(QIODevice::WriteOnly|QIODevice::Text) )
    {
        return;
    }
    QTextStream stream(&file);
    int numRows = Setup_Tab3_InteractionTW->rowCount();
    int numCols = Setup_Tab3_InteractionTW->columnCount();
    for (int i=0; i<numCols; ++i) {
        preyList << Setup_Tab3_InteractionTW->horizontalHeaderItem(i)->text().trimmed();
    }
    for (int i=0; i<numRows; ++i) {
        predList << Setup_Tab3_InteractionTW->verticalHeaderItem(i)->text().trimmed();
    }

    for (int i=0; i<numRows; ++i) {
        stream << predList[i];
        for (int j=0; j<numCols; ++j) {
            cbox = Setup_Tab3_InteractionTW->cellWidget(i,j)->findChild<QCheckBox *>("CheckBoxItem");
            if (cbox->isChecked()) {
                stream << "," << preyList[j];
            }
        }
        stream << "\n";
    }

    file.close();
}

void
nmfSetup_Tab3::saveSettings()
{

}

void
nmfSetup_Tab3::saveSpeciesData()
{
    m_logger->logMsg(nmfConstants::Normal,"Saving Species Data");

    int NumSpecies = Setup_Tab3_SpeciesTW->rowCount();
    std::string msg;
    std::string errorMsg;
    std::string SpeciesName;
    std::string SpeciesType;
    QString value;
    std::vector<std::string> speciesNames;
    std::vector<std::string> speciesTypes;

    // Check each cell for missing fields
    int numCols;
    numCols = Setup_Tab3_SpeciesTW->columnCount();
    for (int i=0; i<NumSpecies; ++i) {
        for (int j=0; j<numCols; ++j) {
            if (j == 1) { // combobox
            } else {
                value = Setup_Tab3_SpeciesTW->item(i,j)->text();
                if (value.isEmpty()) {
                    msg = "Missing field(s) in Species table";
                    m_logger->logMsg(nmfConstants::Error,msg);
                    QMessageBox::warning(Setup_Tabs,"Warning",
                                         QString::fromStdString("\n"+msg+"\n"),
                                         QMessageBox::Ok);
                    return;
                } else if (value.contains(',')) {
                    msg = "Found an invalid numeric value of: " + value.toStdString();
                    msg += ". No commas or special characters allowed.";
                    m_logger->logMsg(nmfConstants::Error,msg);
                    QMessageBox::warning(Setup_Tabs,"Warning",
                                         QString::fromStdString("\n"+msg+"\n"),
                                         QMessageBox::Ok);
                    return;
                }
            }
        }
    }

    // Species Data Integrity Checks:
    // 1. Check to make sure each Species name is unique.
    // If not, display error and return.
    QStringList SpeciesList;
    for (int i=0; i<NumSpecies; ++i) {
        SpeciesName = Setup_Tab3_SpeciesTW->item(i,0)->text().toStdString();
        SpeciesType = qobject_cast<QComboBox*>(Setup_Tab3_SpeciesTW->cellWidget(i,1))->currentText().toStdString();

        if (SpeciesList.contains(QString::fromStdString(SpeciesName))) {
            errorMsg = "\nFound duplicate Species name: " + SpeciesName;
            errorMsg += "\n\nEach Species name must be unique.\n";
            QMessageBox::warning(Setup_Tabs,"Error", QString::fromStdString(errorMsg),
                                 QMessageBox::Ok);
            return;
        } else {
            speciesNames.push_back(SpeciesName);
            speciesTypes.push_back(SpeciesType);
        }

    }

    // Write out Species data
    QString filename = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(m_ProjectName));
    if (QFileInfo(filename).suffix().isEmpty()) {
        filename += ".species";
    } else {
        filename = filename.replace(".prj",".species");
    }

    QFile file(filename);
    if ( file.open(QIODevice::WriteOnly|QIODevice::Text) )
    {
        QTextStream stream(&file);
        for (int i=0; i<speciesNames.size(); ++i) {
            stream << QString::fromStdString(speciesNames[i]) << "," << QString::fromStdString(speciesTypes[i]) << "\n"; // << std::endl;
        }
        file.close();
    }
}

void
nmfSetup_Tab3::setupInteractionTable()
{
    QString SpeciesName;
    QString SpeciesType;
    QStringList pred;
    QStringList prey;
    QStringList both;

    int numSpecies = Setup_Tab3_SpeciesTW->rowCount();
    for (int i=0; i<numSpecies; ++i) {
        SpeciesName = Setup_Tab3_SpeciesTW->item(i,0)->text();
        SpeciesType = qobject_cast<QComboBox*>(Setup_Tab3_SpeciesTW->cellWidget(i,1))->currentText();
        if (SpeciesType == "Pred") {
            pred << SpeciesName;
        } else if (SpeciesType == "Prey") {
            prey << SpeciesName;
        } else if (SpeciesType == "Both") {
            both << SpeciesName;
        }
    }
    QStringList predCombined = pred + both;
    QStringList preyCombined = prey + both;
    predCombined.sort();
    preyCombined.sort();

    int numRows = predCombined.size();
    int numCols = preyCombined.size();
    Setup_Tab3_InteractionTW->setRowCount(numRows);
    Setup_Tab3_InteractionTW->setColumnCount(numCols);
    Setup_Tab3_InteractionTW->setHorizontalHeaderLabels(preyCombined);
    Setup_Tab3_InteractionTW->setVerticalHeaderLabels(predCombined);
    for (int i=0; i<numRows; ++i) {
        for (int j=0; j<numCols; ++j) {            
            QWidget* checkBoxW = new QWidget();
            QCheckBox* cbox    = new QCheckBox();
            cbox->setObjectName("CheckBoxItem");
            QHBoxLayout* cboxLayt = new QHBoxLayout();
            cboxLayt->addWidget(cbox);
            cboxLayt->setAlignment(Qt::AlignCenter);
            cboxLayt->setContentsMargins(0,0,0,0);
            checkBoxW->setLayout(cboxLayt);
            Setup_Tab3_InteractionTW->setCellWidget(i,j,checkBoxW);
        }
    }
}

void
nmfSetup_Tab3::setupHelp()
{
    QString msg;
    QString prefix = "<html>";
    QString suffix = "</html>";

    // set Tool tips here for column headings
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(0)->setToolTip("Species Name");
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(1)->setToolTip("Guild Name");
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(2)->setToolTip("Species Initial Biomass");
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(3)->setToolTip("Species Growth Rate");
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(4)->setToolTip("Species Carrying Capacity");

    msg  = "</html><strong><center>Species Name</center></strong><br>";
    msg += "The Species name entered must be unique.";
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(0)->setWhatsThis(prefix+msg+suffix);
    msg  = "</html><strong><center>Guild Name</center></strong><br>";
    msg += "The user must create Guilds prior to being able to select one here.";
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(1)->setWhatsThis(prefix+msg+suffix);
    msg  = "</html><strong><center>Initial Biomass</center></strong><br>";
    msg += "The initial species biomass is in units of metric tons.";
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(2)->setWhatsThis(prefix+msg+suffix);
    msg  = "</html><strong><center>Growth Rate</center></strong><br>";
    msg += "The Species growth rate (r) is a unit-less value typically between 0.0 and 1.0.";
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(3)->setWhatsThis(prefix+msg+suffix);
    msg  = "</html><strong><center>Species K</center></strong><br>";
    msg += "The Species carrying capacity (K) is the number of individuals<br>";
    msg += "in a population that can be supported by the habitat's resources.";
    Setup_Tab3_SpeciesTW->horizontalHeaderItem(4)->setWhatsThis(prefix+msg+suffix);
}

void
nmfSetup_Tab3::callback_Setup_Tab3_AddSpeciesPB()
{
    int numRows = Setup_Tab3_SpeciesTW->rowCount();
    int numCols = numColumnsSpecies();

    if (numRows == 0) {
        Setup_Tab3_SpeciesTW->setColumnCount(numCols);
        Setup_Tab3_SpeciesTW->setHorizontalHeaderLabels(m_colLabelsSpecies);
        Setup_Tab3_SpeciesTW->resizeColumnsToContents();
    }

    Setup_Tab3_SpeciesTW->insertRow(numRows);
    populateARowSpecies(numRows,numColumnsSpecies());
}

void
nmfSetup_Tab3::callback_Setup_Tab3_DelSpeciesPB()
{
    std::string msg;
    QMessageBox::StandardButton reply;
    std::set<int> rowsToDelete;
    std::set<int>::reverse_iterator rowsToDeleteReverseIter;

    // Delete row(s) from table.  If the Species has been saved, this should happen automatically when
    // the Species are reloaded.  However, if the user is just entering the data and hasn't yet
    // saved and wants to delete a row, this statement is necessary.
    QList<QTableWidgetItem*> selItems = Setup_Tab3_SpeciesTW->selectedItems();
    int numSelItems = (int)selItems.size();
    if (numSelItems == 0) {
        return;
    }

    // Find row numbers to delete
    for (int i=0; i<numSelItems; ++i) {
        rowsToDelete.insert(selItems[i]->row());
    }
    int numRowsToDelete = rowsToDelete.size();

    // Query user and make sure they want to delete the species.
    msg  = "\nOK to delete the " + std::to_string(numRowsToDelete) + " selected species?\n";
    msg += "All associated data in all CSV files will also be deleted.\n";
    msg += "\nThis cannot be undone.\n";
    reply = QMessageBox::question(Setup_Tabs, tr("Delete"), tr(msg.c_str()),
                                  QMessageBox::No|QMessageBox::Yes,
                                  QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        Setup_Tabs->setCursor(Qt::WaitCursor);
        rowsToDeleteReverseIter = rowsToDelete.rbegin();
        for (int i=0; i<numRowsToDelete; ++i) {
            removeFromProjectFiles(Setup_Tab3_SpeciesTW->item(*rowsToDeleteReverseIter,0)->text());
            Setup_Tab3_SpeciesTW->removeRow(*rowsToDeleteReverseIter++);
        }
        // Enable spin box if there are 0 rows left
        Setup_Tab3_NumSpeciesSB->setEnabled(Setup_Tab3_SpeciesTW->rowCount() == 0);
        Setup_Tabs->setCursor(Qt::ArrowCursor);
    }

    callback_Setup_Tab3_SavePB();
}

void
nmfSetup_Tab3::callback_Setup_Tab3_NextPB()
{
    int nextPage = Setup_Tabs->currentIndex()+1;
    Setup_Tabs->setCurrentIndex(nextPage);
}

void
nmfSetup_Tab3::callback_Setup_Tab3_NumSpecies(int numSpecies)
{
    int ncols;
    int nrows;

    Setup_Tab3_SpeciesTW->clear();

    ncols = m_colLabelsSpecies.size();
    nrows = numSpecies;

    Setup_Tab3_SpeciesTW->setRowCount(nrows);
    Setup_Tab3_SpeciesTW->setColumnCount(ncols);

    // Put widgets items in each cell
    for (int i=0; i<nrows; ++i)  {
        populateARowSpecies(i,ncols);
    }
    Setup_Tab3_SpeciesTW->setHorizontalHeaderLabels(m_colLabelsSpecies);
    Setup_Tab3_SpeciesTW->resizeColumnsToContents();
}

void
nmfSetup_Tab3::callback_Setup_Tab3_SavePB()
{

    Setup_Tabs->setCursor(Qt::WaitCursor);

    if (Setup_Tab3_GuildsSpeciesTabW->currentIndex() == 0) {
        saveSpeciesData();
        setupInteractionTable();
        loadInteractionData();
        QMessageBox::information(Setup_Tabs, "Save","\nSpecies data saved.\n");
    } else {
        saveInteractionData();
        QMessageBox::information(Setup_Tabs, "Save","\nInteraction data saved.\n");
    }

    emit ReloadRankData();

    Setup_Tabs->setCursor(Qt::ArrowCursor);
}

void
nmfSetup_Tab3::callback_Setup_Tab3_SpeciesTableChanged(int row, int col)
{
    Setup_Tab3_NumSpeciesSB->setEnabled(false);
}

void
nmfSetup_Tab3::callback_Setup_Tab3_UpdateSpeciesPB()
{
    QComboBox* guildCMB;
    QString guildName;
    int numGuilds  = Setup_Tab3_GuildsTW->rowCount();
    int numSpecies = Setup_Tab3_SpeciesTW->rowCount();

    for (int i=0; i<numSpecies; ++i) {
        guildCMB = qobject_cast<QComboBox *>(Setup_Tab3_SpeciesTW->cellWidget(i,1));
        guildCMB->clear();
        for (int j=0; j<numGuilds; ++j) {
            guildName = Setup_Tab3_GuildsTW->item(j,0)->text();
            if (! guildName.isEmpty()) {
                guildCMB->addItem(Setup_Tab3_GuildsTW->item(j,0)->text());
            }
        }
    }
}
