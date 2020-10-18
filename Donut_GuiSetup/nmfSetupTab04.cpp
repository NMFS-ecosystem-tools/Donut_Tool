#include "nmfSetupTab04.h"
#include "nmfConstantsDonut.h"
#include "nmfUtilsQt.h"
#include "nmfUtils.h"
#include "nmfConstants.h"


nmfSetup_Tab4::nmfSetup_Tab4(QTabWidget*  tabs,
                             nmfLogger*   logger,
                             std::string& projectDir)
{
    QUiLoader loader;

    Setup_Tabs    = tabs;
    m_logger      = logger;
    m_ProjectDir  = projectDir;
    m_ProjectSettingsConfig.clear();
    m_EstimatedParameters.clear();
    m_LastSliderValue = 50;
    m_ProjectName.clear();


    Setup_Tab4_GrowthHighlightPB = nullptr;

    // Load ui as a widget from disk
    QFile file(":/forms/Setup/Setup_Tab04.ui");
    file.open(QFile::ReadOnly);
    Setup_Tab4_Widget = loader.load(&file,Setup_Tabs);
    Setup_Tab4_Widget->setObjectName("Setup_Tab4_Widget");
    file.close();

    // Add the loaded widget as the new tabbed page
    Setup_Tabs->addTab(Setup_Tab4_Widget, tr("4. Run Model"));

    Setup_Tab4_DataTV          = Setup_Tabs->findChild<QTableView  *>("Setup_Tab4_DataTV");
    Setup_Tab4_DataSL          = Setup_Tabs->findChild<QSlider     *>("Setup_Tab4_DataSL");
    Setup_Tab4_RunPB           = Setup_Tabs->findChild<QPushButton *>("Setup_Tab4_RunPB");
    Setup_Tab4_SavePB          = Setup_Tabs->findChild<QPushButton *>("Setup_Tab4_SavePB");
    Setup_Tab4_PredatorCMB     = Setup_Tabs->findChild<QComboBox   *>("Setup_Tab4_PredatorCMB");
    Setup_Tab4_NotesTE         = Setup_Tabs->findChild<QTextEdit   *>("Setup_Tab4_NotesTE");
    Setup_Tab4_PreyLN          = Setup_Tabs->findChild<QFrame      *>("Setup_Tab4_PreyLN");
    Setup_Tab4_PreyLBL         = Setup_Tabs->findChild<QLabel      *>("Setup_Tab4_PreyLBL");
    Setup_Tab4_RankLBL         = Setup_Tabs->findChild<QLabel      *>("Setup_Tab4_RankLBL");
    Setup_Tab4_ProportionLBL   = Setup_Tabs->findChild<QLabel      *>("Setup_Tab4_ProportionLBL");
    Setup_Tab4_OutputMatrixLBL = Setup_Tabs->findChild<QLabel      *>("Setup_Tab4_OutputMatrixLBL");
    Setup_Tab4_PrevPB          = Setup_Tabs->findChild<QPushButton *>("Setup_Tab4_PrevPB");
    Setup_Tab4_LoadPB          = Setup_Tabs->findChild<QPushButton *>("Setup_Tab4_LoadPB");

    Setup_Tab4_PreyLN->setFrameShape(QFrame::HLine);
    Setup_Tab4_DataTV->horizontalScrollBar()->hide();

    connect(Setup_Tab4_RunPB,   SIGNAL(clicked()),
            this,               SLOT(callback_RunPB()));
    connect(Setup_Tab4_DataSL,  SIGNAL(sliderMoved(int)),
            this,               SLOT(callback_DataSL(int)));
    connect(Setup_Tab4_DataSL,  SIGNAL(sliderReleased()),
            this,               SLOT(callback_DataReleasedSL()));
    connect(Setup_Tab4_PredatorCMB, SIGNAL(activated(QString)),
            this,                   SLOT(callback_PredatorCMB(QString)));

    // RSK continue here....
//  connect(smodel,  SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
//          this,    SLOT(callback_TableChanged(QModelIndex,QModelIndex,QVector<int>)));

    // Set widget parameters
    Setup_Tab4_LoadPB->show();
    Setup_Tab4_LoadPB->setEnabled(true);
    Setup_Tab4_SavePB->setEnabled(true);
    Setup_Tab4_PrevPB->setText("\u25C1--");

    connect(Setup_Tab4_LoadPB,                 SIGNAL(clicked()),
            this,                              SLOT(callback_LoadPB()));
    connect(Setup_Tab4_SavePB,                 SIGNAL(clicked()),
            this,                              SLOT(callback_SavePB()));
    connect(Setup_Tab4_PrevPB,                 SIGNAL(clicked()),
            this,                              SLOT(callback_PrevPB()));
}

nmfSetup_Tab4::~nmfSetup_Tab4()
{
}

void
nmfSetup_Tab4::adjustLine()
{
    int newWidth = nmfUtilsQt::calculateMultiColumnWidth(
                Setup_Tab4_DataTV,
                nmfConstantsDonut::COLUMN_SPECIES,
                nmfConstantsDonut::COLUMN_REL_ABUND);
    Setup_Tab4_PreyLBL->setFixedWidth(newWidth);
    Setup_Tab4_PreyLN->setFixedWidth(newWidth-20);
    Setup_Tab4_RankLBL->setFixedWidth(
                nmfUtilsQt::calculateMultiColumnWidth(Setup_Tab4_DataTV,
                                                      nmfConstantsDonut::COLUMN_OVERLAP,
                                                      nmfConstantsDonut::COLUMN_RANK_ICING));
    Setup_Tab4_ProportionLBL->setFixedWidth(
                nmfUtilsQt::calculateMultiColumnWidth(Setup_Tab4_DataTV,
                                                      nmfConstantsDonut::COLUMN_PROP_DETECTION,
                                                      nmfConstantsDonut::COLUMN_PROP_PRODUCT));
    Setup_Tab4_OutputMatrixLBL->setFixedWidth(
                nmfUtilsQt::calculateMultiColumnWidth(Setup_Tab4_DataTV,
                                                      nmfConstantsDonut::COLUMN_RPA_MODEL,
                                                      nmfConstantsDonut::COLUMN_NULL_SELECTIVITY)-30);
    // RSK Not sure why the last label isn't centered...had to put -30 here
}

void
nmfSetup_Tab4::clearWidgets()
{
}

QString
nmfSetup_Tab4::getCurrentPredator()
{
    return Setup_Tab4_PredatorCMB->currentText();
}

void
nmfSetup_Tab4::loadPredatorNamesAndMap()
{
    QString predatorName;
    QStringList preyList;

    m_PredatorMap.clear();
    Setup_Tab4_PredatorCMB->clear();

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
            preyList.clear();
            parts = line.split(",");
            predatorName = parts[0].trimmed();
            Setup_Tab4_PredatorCMB->addItem(predatorName);
            for (int i=1;i<parts.size(); ++i) {
                preyList << parts[i].trimmed();
            }
            m_PredatorMap[predatorName] = preyList;
            line = stream.readLine();
        }
        file.close();
    }

    // For current predator, load first column in table
    callback_PredatorCMB(getCurrentPredator());

    // Set default values of Rel Abund and Overlap columns to 1's instead of blanks
    loadDefaultValues();
}

void
nmfSetup_Tab4::loadDefaultValues()
{
    QStandardItemModel*  smodel = qobject_cast<QStandardItemModel*>(Setup_Tab4_DataTV->model());
    QStandardItem* item;
    int numSpecies = smodel->rowCount();

    for (int col  = nmfConstantsDonut::COLUMN_REL_ABUND;
             col <= nmfConstantsDonut::COLUMN_OVERLAP; ++col) {
        for (int row=0; row<numSpecies; ++row) {
            //if (col == nmfConstantsDonut::COLUMN_REL_ABUND) {
            item = new QStandardItem("1");
            // } else {
            //    item = new QStandardItem("1.00");
            // }
            item->setTextAlignment(Qt::AlignCenter);
            smodel->setItem(row,col,item);
        }
    }
}

bool
nmfSetup_Tab4::loadRankData()
{
    bool loadedOK = false;
    int col=0;
    QStandardItemModel*  smodel = qobject_cast<QStandardItemModel*>(Setup_Tab4_DataTV->model());
    QStandardItem* item;
    QModelIndex  index;
    QString      FileSpecies;
    QStringList  parts;
    QString      RankSpecies;
    QString      part;
    QString      line;
    std::vector<QString> lines;
    int          numSpecies = smodel->rowCount();

    Setup_Tab4_NotesTE->clear();

    // Read project file and load
    QString filename = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(m_ProjectName));
    if (QFileInfo(filename).suffix().isEmpty()) {
        filename += "." + getCurrentPredator();
    }

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QTextStream stream(&file);
        line = stream.readLine().trimmed();
        if (line.isEmpty()) {
            line = " ";
        }
        while (line != "# ---") {
            Setup_Tab4_NotesTE->append(line);
            line = stream.readLine().trimmed();
        }
        while (! line.isNull()) {
            line = stream.readLine();
            lines.push_back(line);
        }
        file.close();

        for (int row=0; row<numSpecies; ++row) {
            index = smodel->index(row,0,QModelIndex());
            RankSpecies = index.data().toString();
            for (QString line : lines) {
                parts = line.split(",");
                FileSpecies = parts[0].trimmed();
                if (FileSpecies == RankSpecies) {
                    col = nmfConstantsDonut::COLUMN_REL_ABUND;
                    for (int i=1; i<parts.size(); ++i) {
                        part = parts[i].trimmed();
                        item = new QStandardItem(part);
                        item->setTextAlignment(Qt::AlignCenter);
                        smodel->setItem(row,col,item);
                        ++col;
                    }
                }
            }
        }
        loadedOK = true;
    }

    Setup_Tab4_DataTV->resizeColumnsToContents();

    if (numSpecies <= 1) {
        loadedOK = false;
    }

    return loadedOK;
}

void
nmfSetup_Tab4::loadWidgets()
{
    m_logger->logMsg(nmfConstants::Normal,"nmfSetup_Tab4::loadWidgets()");

    readSettings();

    clearWidgets();
    loadPredatorNamesAndMap();
    loadRankData();
}

void
nmfSetup_Tab4::readSettings()
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
nmfSetup_Tab4::resetTableBackgroundColors()
{
    QStandardItemModel* smodel = qobject_cast<QStandardItemModel *>(Setup_Tab4_DataTV->model());
    int numRows = smodel->rowCount();
    QBrush PropBrushLight   = QBrush(QColor(0xF0F0F0)); // light gray
    QBrush PropBrushDark    = QBrush(QColor(0x404040)); // dark  gray
    QBrush PropBrush;
    QBrush OutputBrushLight = QBrush(QColor(0xFFFF00)); // light yellow
    QBrush OutputBrushDark  = QBrush(QColor(0x808000)); // dark  yellow
    QBrush OutputBrush;

    if (qApp->styleSheet().isEmpty()) { // Means it's Light
        PropBrush = PropBrushLight;
        OutputBrush = OutputBrushLight;
    } else { // Means it's Dark
        PropBrush = PropBrushDark;
        OutputBrush = OutputBrushDark;
    }

    // Shade cells accordingly
    for (int i=0;i<numRows;++i) {
        smodel->setData(smodel->index(i,nmfConstantsDonut::COLUMN_SPECIES),PropBrush,Qt::BackgroundRole);
        for (int j  = nmfConstantsDonut::COLUMN_PROP_DETECTION;
                 j <= nmfConstantsDonut::COLUMN_PROP_PRODUCT; ++j) {
            smodel->setData(smodel->index(i,j),PropBrush,Qt::BackgroundRole);
        }
        for (int j  = nmfConstantsDonut::COLUMN_RPA_MODEL;
                 j <= nmfConstantsDonut::COLUMN_NULL_SELECTIVITY; ++j) {
            smodel->setData(smodel->index(i,j),OutputBrush,Qt::BackgroundRole);
        }
    }
}

bool
nmfSetup_Tab4::runDataChecks()
{
    bool ok = true;
    QStandardItemModel* smodel = qobject_cast<QStandardItemModel *>(Setup_Tab4_DataTV->model());
    int numRows = smodel->rowCount();
    double aRankTotal;
    double sum=0;
    double value;
    std::string msg = "";
    std::set<int> dupCheck;
    QModelIndex index;

    // Check #1. Each predator has > 1 prey
    if (numRows <= 1) {
        msg = "Error: Each predator species must have at least 2 prey species associated with it.";
        ok = false;
    }

    // Check #2. Sum of all rel abund must be 1 or all rel abund must be 1
    for (int i=0; i<numRows; ++i) {
        index = smodel->index(i,nmfConstantsDonut::COLUMN_REL_ABUND);
        sum += index.data().toDouble();
    }
    if (! (nmfUtils::isNearlyZero(sum-1.0) || (sum == double(numRows)))) {
        msg = "Error: Rel Abund values must sum to 1 or all be equal to 1 (found sum = " +
                std::to_string(sum) + ")";
        ok = false;
    }

    // Check #3. All numbers must be positive
    for (int row=0; row<numRows; ++row) {
        for (int col  = nmfConstantsDonut::COLUMN_REL_ABUND;
                 col <= nmfConstantsDonut::COLUMN_RANK_ICING; ++col) {
            index = smodel->index(row,col);
            value = index.data().toDouble();
            if (value < 0) {
                msg = "Error: All entered data must be > 0. Found value = " +
                        index.data().toString().toStdString() + " at (" +
                        std::to_string(row) + "," +
                        std::to_string(col) + ").";
                ok = false;
                break;
            }
        }
    }

    // Check #4. Rel Abund and Overlap must be between 0 and 1
    for (int row=0; row<numRows; ++row) {
        for (int col  = nmfConstantsDonut::COLUMN_REL_ABUND;
                 col <= nmfConstantsDonut::COLUMN_OVERLAP; ++col) {
            index = smodel->index(row,col);
            value = index.data().toDouble();
            if ((value < 0) || (value > 1)) {
                msg = "Error: Entered value must be between 0 and 1. Found value = " +
                        index.data().toString().toStdString() + " at (" +
                        std::to_string(row) + "," +
                        std::to_string(col) + ").";
                ok = false;
                break;
            }
        }
    }

    // Check #5. Total of category (i.e. column) ranks must be n(n+1)/2 where n = num species
    QString columnName;
    int correctRankTotal = int(numRows*(numRows+1.0)/2.0);
    std::vector<double> rankTotals = {0,0,0,0,0};
    for (int row=0; row<numRows; ++row) {
        for (int col  = nmfConstantsDonut::COLUMN_RANK_DETECTION;
                 col <= nmfConstantsDonut::COLUMN_RANK_ICING; ++col) {
            index = smodel->index(row,col);
            rankTotals[col-nmfConstantsDonut::COLUMN_RANK_DETECTION] += index.data().toDouble();
        }
    }
    for (int col  = nmfConstantsDonut::COLUMN_RANK_DETECTION;
             col <= nmfConstantsDonut::COLUMN_RANK_ICING; ++col) {
        aRankTotal = rankTotals[col-nmfConstantsDonut::COLUMN_RANK_DETECTION];
        if (!nmfUtils::isNearlyZero(aRankTotal-double(correctRankTotal)) &&
            (col != nmfConstantsDonut::COLUMN_RANK_ICING)) {
            columnName = smodel->headerData(col,Qt::Horizontal).toString();
            msg  = "Error in Rank table in Tab #4: Run Model\n";
            msg += "\nPredator: " + getCurrentPredator().toStdString() + "\n";
            msg += "\nFound incorrect rank total of " + QString::number(aRankTotal,'f',1).toStdString() +
                    " in the Rank column: " + columnName.toStdString();
            msg += "\n\nAll column rank totals should be " + std::to_string(correctRankTotal) +
                    " for this predator.\n\nRanks begin with 1 (highest) and proceed in consecutive numeric order to N, where N = number of prey species.";
            ok = false;
            break;
        } else if (col == nmfConstantsDonut::COLUMN_RANK_ICING) {
            if ((aRankTotal != correctRankTotal) && (aRankTotal != numRows)) {
                columnName = smodel->headerData(col,Qt::Horizontal).toString();
                msg  = "Error in Rank table in Tab #4: Run Model\n";
                msg += "\nPredator: " + getCurrentPredator().toStdString() + "\n";
                msg += "Found incorrect rank total of " + QString::number(aRankTotal,'f',1).toStdString() +
                        " in the Rank column: " + columnName.toStdString();
                msg += "\n\nThe 'Icing' column rank values should be either 1.." + std::to_string(numRows) +
                        ", where " + std::to_string(numRows) + " is the number of prey species or " +
                        "each rank value should be set to 1 if not wished to be used.";
                ok = false;
                break;
            }
        }
    }

    // Check #6. No duplicate numbers in Rank columns
    // Commented out for now, apparently ties are allowed.
    //    for (int col  = nmfConstantsDonut::COLUMN_RANK_DETECTION;
    //             col <= nmfConstantsDonut::COLUMN_RANK_ICING; ++col) {
    //        dupCheck.clear();
    //        for (int row=0; row<numRows; ++row) {
    //            dupCheck.insert(smodel->index(row,col).data().toInt());
    //        }
    //        if (dupCheck.size() != numRows) { // this means that there's a duplicate (i.e., 2,2... instead of 1,3...)
    //            columnName = smodel->headerData(col,Qt::Horizontal).toString();
    //            msg  = "Error in Rank table in Tab #4: Run Model\n";
    //            msg += "\nPredator: " + getCurrentPredator().toStdString() + "\n";
    //            msg += "\nFound duplicate value in the Rank column: " + columnName.toStdString();
    //            msg += "\n\nEach integer rank value must be unique.";
    //            ok = false;
    //            break;
    //        }
    //    }

    if (! msg.empty()) {
        QMessageBox::critical(Setup_Tabs, "Error",QString::fromStdString("\n"+msg+"\n"));
    }
    return ok;
}

void
nmfSetup_Tab4::saveRankData()
{
    bool ok;
    double val;
    std::string msg;
    QModelIndex index;

    QStandardItemModel* smodel = qobject_cast<QStandardItemModel *>(Setup_Tab4_DataTV->model());
    int numRows = smodel->rowCount();

    // Check data
    for (int row=0; row<numRows; ++row) {
        for (int col  = nmfConstantsDonut::COLUMN_SPECIES;
                 col <= nmfConstantsDonut::COLUMN_RANK_ICING; ++col) {
            ok = true;
            index = smodel->index(row,col);
            if (col == nmfConstantsDonut::COLUMN_SPECIES) {
                index.data().toString();
            } else if (col <= nmfConstantsDonut::COLUMN_OVERLAP) {

                ok = index.data().toDouble();
            } else {
                ok = index.data().toDouble();
            }
            if (! ok) {
                msg  = "Error: Missing or incorrect data at cell (";
                msg += std::to_string(row) + "," + std::to_string(col);
                msg += "). Please re-check input data.";
                m_logger->logMsg(nmfConstants::Error,msg);
                QMessageBox::critical(Setup_Tabs, "Save Error",QString::fromStdString("\n"+msg+"\n"));
                return;
            }
        }
    }

    // Write out Rank data
    QString filename = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(m_ProjectName));
    if (QFileInfo(filename).suffix().isEmpty()) {
        filename += "." + getCurrentPredator();
    }

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream stream(&file);
        stream << Setup_Tab4_NotesTE->document()->toPlainText() << "\n";
        stream << "# ---" << "\n";
        for (int row=0; row<numRows; ++row) {
            index = smodel->index(row,nmfConstantsDonut::COLUMN_SPECIES);
            stream << index.data().toString();
            for (int col=nmfConstantsDonut::COLUMN_REL_ABUND;
                     col<=nmfConstantsDonut::COLUMN_REL_ABUND+1; ++col) {
                index = smodel->index(row,col);
                val = index.data().toDouble();
                if (nmfUtils::isWholeNumber(val)) {
                    stream << "," << QString::number(val,'g');
                } else {
                    stream << "," << QString::number(val,'f',2);
                }
            }
            for (int col=nmfConstantsDonut::COLUMN_REL_ABUND+2;
                     col<=nmfConstantsDonut::COLUMN_RANK_ICING; ++col) {
                index = smodel->index(row,col);
                if (nmfUtils::isWholeNumber(index.data().toDouble())) {
                    stream << "," << QString::number(index.data().toInt());
                } else {
                    stream << "," << QString::number(index.data().toDouble());
                }

            }
            stream << "\n";
        }
        file.close();
    }

    Setup_Tab4_DataTV->resizeColumnsToContents();

    QMessageBox::information(Setup_Tabs, "Save","\nRank data saved.\n");
}

void
nmfSetup_Tab4::saveSettings()
{
}

void
nmfSetup_Tab4::shadeTable(QStandardItemModel* smodel)
{
    QStandardItem* item;
    int numRows = smodel->rowCount();

    // Shade cells accordingly
    for (int row=0;row<numRows;++row) {
        smodel->setData(smodel->index(row,0),QBrush(QColor(0xF0F0F0)),Qt::BackgroundRole);
        for (int col =  nmfConstantsDonut::COLUMN_PROP_DETECTION;
                 col <= nmfConstantsDonut::COLUMN_PROP_PRODUCT; ++col) {
            smodel->setData(smodel->index(row,col),QBrush(QColor(0xF0F0F0)),Qt::BackgroundRole);
        }
        for (int col = nmfConstantsDonut::COLUMN_RPA_MODEL;
                 col <=nmfConstantsDonut::COLUMN_NULL_SELECTIVITY; ++col) {
            smodel->setData(smodel->index(row,col),QBrush(QColor(0xFFFF00)),Qt::BackgroundRole);
        }
    }

    // Set read only cells
    for (int row=0; row<numRows; ++row) {
        item = smodel->item(row,0);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        for (int col  = nmfConstantsDonut::COLUMN_PROP_DETECTION;
                 col <= nmfConstantsDonut::COLUMN_NULL_SELECTIVITY; ++col) {
            item = smodel->item(row,col);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }
}

void
nmfSetup_Tab4::setCurrentPredator(QString species)
{
    Setup_Tab4_PredatorCMB->setCurrentText(species);
}

void
nmfSetup_Tab4::callback_DataReleasedSL()
{
    Setup_Tab4_DataSL->setValue(50);
    m_LastSliderValue = 50;
}

void
nmfSetup_Tab4::callback_DataSL(int value)
{
    bool validChange = false;
    double newValue;
    double inc;
    // Modify selected cells and run
    QItemSelectionModel* sel = Setup_Tab4_DataTV->selectionModel();
    QStandardItemModel* smodel =  qobject_cast<QStandardItemModel*>(Setup_Tab4_DataTV->model());

    // Remember selection
    QModelIndexList remSelection = sel->selectedIndexes();

    if (sel->hasSelection()) {
        for (QModelIndex index : sel->selectedIndexes()) {
            if ((index.column() == nmfConstantsDonut::COLUMN_OVERLAP)) {
                validChange = true;
                if (value == m_LastSliderValue) {
                    break;
                }
                inc = (value < m_LastSliderValue) ? -0.01 : 0.01;
                newValue = index.data().toDouble() + inc;
                nmfUtils::clamp(newValue,0.0,1.0);
                smodel->setData(index,newValue);
            } else {
                validChange = false;
            }
            if (validChange) {
                callback_RunPB();
            }
        }
        m_LastSliderValue = value;
    }

    // Restore selection (because the callback_RunPB will clear the selection)
    sel->clearSelection();
    for (QModelIndex index : remSelection) {
        sel->select(index,QItemSelectionModel::Select);
    }
}

void
nmfSetup_Tab4::callback_LoadPB()
{
    loadRankData();
}

void
nmfSetup_Tab4::callback_PredatorCMB(QString predatorName)
{
    int numCols;
    QModelIndex index;
    QStringList preyList = m_PredatorMap[predatorName];
    QStandardItemModel*  smodel = new QStandardItemModel();
    QStringList columns;
    int numRows = preyList.size();

    m_FieldsSpecies.clear();
    m_FieldsRank.clear();
    m_FieldsProportion.clear();
    m_FieldsNullAmbient.clear();
    m_FieldsSpecies     << "Taxa" << "Rel Abund";
    m_FieldsRank        << "Overlap" << "Detection" << "Reaction" << "Capture" << "Ingestion" << "Icing";
    m_FieldsProportion  << "Detection" << "Reaction" << "Capture" << "Ingestion" << "Icing" << "Product (Sij)";
    m_FieldsNullAmbient << "RPA Model" << "Null Ambient (Ai)" << "Null Selectivity";
    columns = m_FieldsSpecies + m_FieldsRank + m_FieldsProportion + m_FieldsNullAmbient;
    numCols = columns.size();
    smodel->setHorizontalHeaderLabels(columns);
    smodel->setColumnCount(numCols);
    smodel->setRowCount(numRows);

    Setup_Tab4_DataTV->setModel(smodel);

    // Now load prey names
    for (int i=0; i<numRows; ++i) {
        index = smodel->index(i,0,QModelIndex());
        smodel->setData(index,preyList[i]);
    }
    loadDefaultValues();
    bool loadedOK = loadRankData();

    shadeTable(smodel);

    Setup_Tab4_DataTV->resizeColumnsToContents();
    Setup_Tab4_DataTV->verticalHeader()->hide();

    if (loadedOK) {
        callback_RunPB();
    } else {
        callback_TypeCMB("");
    }

    adjustLine();
    resetTableBackgroundColors();
}

void
nmfSetup_Tab4::callback_PrevPB()
{
    int prevPage = Setup_Tabs->currentIndex()-1;
    Setup_Tabs->setCurrentIndex(prevPage);
}

void
nmfSetup_Tab4::callback_Reload()
{
    loadWidgets();
}

void
nmfSetup_Tab4::callback_RunPB()
{
    bool calculationOK;
    QStandardItem* item;
    QStandardItemModel* smodel = qobject_cast<QStandardItemModel*>(Setup_Tab4_DataTV->model());
    double val=0;
    int numSpecies = smodel->rowCount();
    int numCols    = smodel->columnCount();
    QModelIndex index;
    std::vector<double> RPAData;
    std::vector<double> AiData;
    std::vector<double> NullSelectivityData;
    std::vector<std::string> Species;
    boost::numeric::ublas::matrix<double> DataMatrix;

    if (! runDataChecks()) {
        return;
    }

    // Set up matrix representing smodel's data so the API module can operate on it
    nmfUtils::initialize(DataMatrix,numSpecies,numCols);
    for (int row=0; row<numSpecies; ++row) {
        index = smodel->index(row,nmfConstantsDonut::COLUMN_SPECIES,QModelIndex());
        Species.push_back(smodel->data(index).toString().toStdString());
        for (int col  = nmfConstantsDonut::COLUMN_REL_ABUND;
                 col <= nmfConstantsDonut::COLUMN_NULL_SELECTIVITY; ++col) {
            index = smodel->index(row,col,QModelIndex());
            DataMatrix(row,col) = smodel->data(index).toDouble();
        }
    }

    // Calculate RPA values that will complete the matrix and smodel
    calculationOK = m_DonutModelAPI.calculateRPAModel(DataMatrix,RPAData,AiData,NullSelectivityData);
    if (! calculationOK) {
        m_logger->logMsg(nmfConstants::Error,"Error calculating RPA model. Please re-check input data.");
        return;
    }

    // Put values back into smodel
    for (int row=0; row<numSpecies; ++row) {
        for (int col  = nmfConstantsDonut::COLUMN_REL_ABUND;
                 col <= nmfConstantsDonut::COLUMN_NULL_SELECTIVITY; ++col) {
            val = DataMatrix(row,col);
            if (col <= nmfConstantsDonut::COLUMN_OVERLAP) {
                if (nmfUtils::isWholeNumber(val)) {
                    item = new QStandardItem(QString::number(val,'g'));
                } else {
                    item = new QStandardItem(QString::number(val,'f',2));
                }
            } else if ((col >= nmfConstantsDonut::COLUMN_RANK_DETECTION) &&
                       (col <= nmfConstantsDonut::COLUMN_RANK_ICING)) {
                if (nmfUtils::isWholeNumber(val)) {
                    item = new QStandardItem(QString::number(val,'g'));
                } else {
                    item = new QStandardItem(QString::number(val,'f',1));
                }
            } else if ((col >= nmfConstantsDonut::COLUMN_PROP_DETECTION) &&
                       (col <  nmfConstantsDonut::COLUMN_PROP_PRODUCT)) {
                item = new QStandardItem(QString::number(val,'f',6));
            } else if (col == nmfConstantsDonut::COLUMN_PROP_PRODUCT) {
                item  = new QStandardItem(QString::number(val,'e',4));
            } else if ((col >= nmfConstantsDonut::COLUMN_RPA_MODEL) &&
                       (col <= nmfConstantsDonut::COLUMN_NULL_SELECTIVITY)) {
                item = new QStandardItem(QString::number(val,'f',1)+"%");
            }
            item->setTextAlignment(Qt::AlignCenter);
            smodel->setItem(row,col,item);
        }
    }

    // Cleanup qtableview and draw the output chart
    Setup_Tab4_DataTV->resizeColumnsToContents();
    shadeTable(smodel);
    emit ShowOutputChart(getCurrentPredator(),Species,RPAData,AiData,NullSelectivityData);
    resetTableBackgroundColors();
}

void
nmfSetup_Tab4::callback_SavePB()
{
    bool dataChecksOK = runDataChecks();
    if (dataChecksOK) {
        saveRankData();
        callback_RunPB();
        loadRankData();
    }
}

//void
//nmfSetup_Tab4::callback_TableChanged(QModelIndex unused1, QModelIndex unused2, QVector<int> unused3)
//{
//    QStandardItemModel* smodel  = qobject_cast<QStandardItemModel*>(Setup_Tab4_DataTV->model());
//    if (smodel->rowCount() > 0) {
//        callback_RunPB();
//    }
//}

void
nmfSetup_Tab4::callback_TypeCMB(QString unused)
{
    QStandardItemModel* smodel =  qobject_cast<QStandardItemModel*>(Setup_Tab4_DataTV->model());
    int numSpecies = smodel->rowCount();
    QModelIndex index;
    std::vector<std::string> Species;
    std::vector<double> RPAData;
    std::vector<double> AiData;
    std::vector<double> NullData;

    for (int i=0; i<numSpecies; ++i) {
        index = smodel->index(i,nmfConstantsDonut::COLUMN_SPECIES,QModelIndex());
        Species.push_back(smodel->data(index).toString().toStdString());

        index = smodel->index(i,nmfConstantsDonut::COLUMN_RPA_MODEL,QModelIndex());
        RPAData.push_back(smodel->data(index).toString().remove("%").toDouble());

        index = smodel->index(i,nmfConstantsDonut::COLUMN_NULL_AMBIENT,QModelIndex());
        AiData.push_back(smodel->data(index).toString().remove("%").toDouble());

        index = smodel->index(i,nmfConstantsDonut::COLUMN_NULL_SELECTIVITY,QModelIndex());
        NullData.push_back(smodel->data(index).toString().remove("%").toDouble());
    }

    emit ShowOutputChart(getCurrentPredator(),Species,RPAData,AiData,NullData);
}

