
#include "nmfMainWindow.h"
#include "ui_nmfMainWindow.h"

#include "nmfConstantsDonut.h"
#include "nmfConstants.h"


// This is needed since a signal is passing a std::string type
Q_DECLARE_METATYPE (std::string)

nmfMainWindow::nmfMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_UI(new Ui::nmfMainWindow)
{
    QVBoxLayout* vlayt = new QVBoxLayout();

    if (! okSplashScreen()) {
        close();
    }

    m_UI->setupUi(this);

    m_UI->OutputDockWidget->hide();
    m_ChartWidget = nullptr;
    m_ChartView2d = nullptr;
    m_ProjectDir.clear();
    m_ProjectName.clear();
    m_ProjectSettingsConfig.clear();

    m_PreferencesDlg = new QDialog(this);
    m_SplashDlg      = nullptr;
    m_ChartWidget    = new QChart();
    m_ChartView2d    = new QChartView(m_ChartWidget);
    m_UI->OutputChartTab->setLayout(vlayt);
    vlayt->addWidget(m_ChartView2d);

    // Check for and make if necessary hidden dirs for program usage: logs, data
    nmfUtilsQt::checkForAndCreateDirectories(nmfConstantsDonut::HiddenDir,
                                 nmfConstantsDonut::HiddenDataDir,
                                 nmfConstantsDonut::HiddenLogDir);

    // Check for log files
    nmfUtilsQt::checkForAndDeleteLogFiles(
                QApplication::applicationName(),
                nmfConstantsDonut::HiddenLogDir,
                nmfConstantsDonut::LogFilter);

    m_Logger = new nmfLogger();
    m_Logger->initLogger(QApplication::applicationName().toStdString());
    m_Logger->logMsg(nmfConstants::Normal,"--- Start ---");

    readSettingsGuiOrientation(nmfConstantsDonut::ResetPositionAlso);
    readSettings();

    initPreferencesDlg();

    // Setup Log Widget
    setupLogWidget();

    // Load GUIs and Connections
    initGUIs();

    initConnections();

    this->addDockWidget(Qt::BottomDockWidgetArea, m_UI->LogDockWidget);
    m_UI->LogDockWidget->hide();

    initPostGuiConnections();

    callback_ReloadWidgets();

    m_UI->OutputDockWidget->hide();
}

nmfMainWindow::~nmfMainWindow()
{
    delete m_UI;
}

void
nmfMainWindow::closeEvent(QCloseEvent *event)
{
    m_Logger->logMsg(nmfConstants::Normal,"--- End ---");
    saveSettings();
}

QTableView*
nmfMainWindow::findTableInFocus()
{
    QTableView *retv = nullptr;

    if (m_UI->SetupInputTabWidget->findChild<QTableView *>("Setup_Tab4_DataTV")->hasFocus()) {
        return m_UI->SetupInputTabWidget->findChild<QTableView *>("Setup_Tab4_DataTV");
    }

    else {
        std::cout << "Error: No table found to cut, copy, or paste." << std::endl;
        return retv;
    }

}

QString
nmfMainWindow::getCurrentStyle()
{
    if (qApp->styleSheet().isEmpty())
        return "Light";
    else
        return "Dark";
}

void
nmfMainWindow::initConnections()
{
    connect(m_UI->actionAbout,                SIGNAL(triggered()),
            this,                             SLOT(menu_about()));
    connect(m_UI->actionClear,                SIGNAL(triggered()),
            this,                             SLOT(menu_clear()));
    connect(m_UI->actionCopy,                 SIGNAL(triggered()),
            this,                             SLOT(menu_copy()));
    connect(m_UI->actionDeselectAll,          SIGNAL(triggered()),
            this,                             SLOT(menu_deselectAll()));
    connect(m_UI->actionLayoutDefault,        SIGNAL(triggered()),
            this,                             SLOT(menu_layoutDefault()));
    connect(m_UI->actionLayoutMinimal,        SIGNAL(triggered()),
            this,                             SLOT(menu_layoutMinimal()));
    connect(m_UI->actionLayoutOutput,         SIGNAL(triggered()),
            this,                             SLOT(menu_layoutOutput()));
    connect(m_UI->actionLayoutOutputEmbedded, SIGNAL(triggered()),
            this,                             SLOT(menu_layoutOutputEmbedded()));
    connect(m_UI->actionPaste,                SIGNAL(triggered()),
            this,                             SLOT(menu_paste()));
    connect(m_UI->actionPasteAll,             SIGNAL(triggered()),
            this,                             SLOT(menu_pasteAll()));
    connect(m_UI->actionPreferences,          SIGNAL(triggered()),
            this,                             SLOT(menu_preferences()));
    connect(m_UI->actionQuit,                 SIGNAL(triggered()),
            this,                             SLOT(menu_quit()));
//  connect(m_UI->actionResetCursor,          SIGNAL(triggered()),
//          this,                             SLOT(menu_resetCursor()));
    connect(m_UI->actionScreenShot,           SIGNAL(triggered()),
            this,                             SLOT(menu_screenShot()));
    connect(m_UI->actionSelectAll,            SIGNAL(triggered()),
            this,                             SLOT(menu_selectAll()));
    connect(m_UI->actionWhatsThis,            SIGNAL(triggered()),
            this,                             SLOT(menu_whatsThis()));
    connect(m_UI->actionWhatsThisTB,          SIGNAL(triggered()),
            this,                             SLOT(menu_whatsThis()));
    connect(m_NavigatorTree,                  SIGNAL(itemSelectionChanged()),
            this,                             SLOT(callback_NavigatorSelectionChanged()));
    connect(Setup_Tab2_ptr,                   SIGNAL(ProjectSaved()),
            this,                             SLOT(callback_ProjectSaved()));
    connect(Setup_Tab3_ptr,                   SIGNAL(ReloadRankData()),
            Setup_Tab4_ptr,                   SLOT(callback_Reload()));
//  connect(Setup_Tab3_ptr,                   SIGNAL(ReloadWidgets()),
//          this,                             SLOT(callback_ReloadWidgets()));
//  connect(Setup_Tab4_ptr,                   SIGNAL(ReloadWidgets()),
//          this,                             SLOT(callback_ReloadWidgets()));
    connect(Setup_Tab4_ptr,                   SIGNAL(ShowOutputChart(QString,std::vector<std::string>,std::vector<double>,std::vector<double>,std::vector<double>)),
            this,                             SLOT(callback_ShowOutputChart(QString,std::vector<std::string>,std::vector<double>,std::vector<double>,std::vector<double>)));
    connect(m_UI->OutputControlChartTypeCMB,  SIGNAL(activated(QString)),
            Setup_Tab4_ptr,                   SLOT(callback_TypeCMB(QString)));
    connect(m_UI->OutputControlChartThemeCMB, SIGNAL(currentTextChanged(QString)),
            Setup_Tab4_ptr,                   SLOT(callback_TypeCMB(QString)));
    connect(m_UI->SetupInputTabWidget,        SIGNAL(currentChanged(int)),
            this,                             SLOT(callback_SetupTabChanged(int)));
}

void
nmfMainWindow::initGUIs()
{
    QUiLoader loader;

    // Initialize Navigator Tree
    QFile file(":/forms/Main/Main_NavigatorTreeWidget.ui");
    file.open(QFile::ReadOnly);
    m_NavigatorTreeWidget = loader.load(&file,this);
    file.close();
    m_UI->NavigatorDockWidget->setWidget(m_NavigatorTreeWidget);
    m_NavigatorTree = m_UI->NavigatorDockWidget->findChild<QTreeWidget *>("NavigatorTree");
    QModelIndex index = m_NavigatorTree->model()->index(0,0);
    m_NavigatorTree->setCurrentIndex(index);
    initNavigatorTree();

    // Load up Setup pages
    Setup_Tab1_ptr      = new nmfSetup_Tab1(m_UI->SetupInputTabWidget);
    Setup_Tab2_ptr      = new nmfSetup_Tab2(m_UI->SetupInputTabWidget,m_Logger);
    Setup_Tab3_ptr      = new nmfSetup_Tab3(m_UI->SetupInputTabWidget,m_Logger,m_ProjectDir);
    Setup_Tab4_ptr      = new nmfSetup_Tab4(m_UI->SetupInputTabWidget,m_Logger,m_ProjectDir);

    // Select first item in Navigator Tree
    callback_SetupTabChanged(0);
}

void
nmfMainWindow::initNavigatorTree()
{
    QTreeWidgetItem *item;

    m_NavigatorTree->clear();
    item = nmfUtilsQt::addTreeRoot(m_NavigatorTree,"Donut Model");
    nmfUtilsQt::addTreeItem(item, "1. Getting Started");
    nmfUtilsQt::addTreeItem(item, "2. Project Setup");
    nmfUtilsQt::addTreeItem(item, "3. Species Setup");
    nmfUtilsQt::addTreeItem(item, "4. Run Model");
    item->setExpanded(true);
}

void
nmfMainWindow::initPostGuiConnections()
{
    connect(Setup_Tab2_ptr, SIGNAL(LoadProject()),
            this,           SLOT(callback_LoadProject()));
}

void
nmfMainWindow::initPreferencesDlg()
{
    QUiLoader loader;
    QFile file(":/forms/Main/PreferencesDlg.ui");
    file.open(QFile::ReadOnly);
    m_PreferencesWidget = loader.load(&file,this);
    file.close();

    QComboBox*   styleCMB = m_PreferencesWidget->findChild<QComboBox*>("PrefAppStyleCMB");
    QPushButton* closePB  = m_PreferencesWidget->findChild<QPushButton*>("PrefClosePB");
    QVBoxLayout* layt = new QVBoxLayout();
    layt->addWidget(m_PreferencesWidget);
    m_PreferencesDlg->setLayout(layt);
    m_PreferencesDlg->setWindowTitle("Preferences");

    connect(styleCMB,         SIGNAL(currentTextChanged(QString)),
            this,             SLOT(callback_PreferencesSetStyleSheet(QString)));
    connect(closePB,          SIGNAL(clicked()),
            m_PreferencesDlg, SLOT(close()));
}

/*

void
nmfMainWindow::initLogo()
{
    QPixmap logoImage(":/icons/NOAA.png");
    QPixmap logoImageScaled = logoImage.scaled(m_UI->centralWidget->width()+100,
                                               m_UI->centralWidget->width()+100,
                                               Qt::KeepAspectRatio);
    QLabel *logoLBL = new QLabel();
    logoLBL->setObjectName("Logo");
    logoLBL->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    logoLBL->setPixmap(logoImageScaled);
    m_UI->centralWidget->layout()->addWidget(logoLBL);

} // end initLogo

*/

void
nmfMainWindow::loadGuis()
{
    Setup_Tab2_ptr->loadWidgets();
    Setup_Tab3_ptr->loadWidgets();
    Setup_Tab4_ptr->loadWidgets();
}

bool
nmfMainWindow::okSplashScreen()
{
   QLabel* splashLBL    = new QLabel();
   m_SplashDlg          = new QDialog();
   QPushButton* resetGUIPB      = new QPushButton("Reset GUI");
   QPushButton* startPB         = new QPushButton("Start");
   QPushButton* resetSettingsPB = new QPushButton("Reset Settings");
   QVBoxLayout* vlayt   = new QVBoxLayout();
   QHBoxLayout* hlayt   = new QHBoxLayout();
   QPixmap splashPM(":/icons/splashWithNOAAv2.jpg");
   startPB->setFixedWidth(100);
   startPB->setFixedHeight(50);
   resetGUIPB->setToolTip("Move main GUI back to (0,0). (Useful if GUI gets lost.)");
   resetGUIPB->setStatusTip("Move main GUI back to (0,0). (Useful if GUI gets lost.)");
   resetSettingsPB->setToolTip("Remove Settings file. (Useful if App won't start.)");
   resetSettingsPB->setStatusTip("Remove Settings file. (Useful if App won't start.)");

   splashLBL->setPixmap(splashPM);
   splashLBL->setMask(splashPM.mask());
   hlayt->addSpacerItem(new QSpacerItem(2,1,QSizePolicy::Expanding,QSizePolicy::Fixed));
   hlayt->addWidget(resetGUIPB);
   hlayt->addWidget(startPB);
   hlayt->addWidget(resetSettingsPB);
   hlayt->addSpacerItem(new QSpacerItem(2,1,QSizePolicy::Expanding,QSizePolicy::Fixed));
   vlayt->addWidget(splashLBL);
   vlayt->addLayout(hlayt);
   m_SplashDlg->setLayout(vlayt);
   connect(startPB,          SIGNAL(clicked()),
           m_SplashDlg,              SLOT(close()));
   connect(resetGUIPB,       SIGNAL(clicked()),
           this,             SLOT(callback_ResetGUI()));
   connect(resetSettingsPB,  SIGNAL(clicked()),
           this,             SLOT(callback_ResetSettings()));
   m_SplashDlg->setWindowTitle("Donut Tool");
   m_SplashDlg->exec();

   return true;
}

void
nmfMainWindow::readSettings()
{
    QSettings* settings = nmfUtilsQt::createSettings(
                nmfConstantsDonut::SettingsDirWindows,QApplication::applicationName());

    settings->beginGroup("Settings");
    m_ProjectSettingsConfig = settings->value("Name","").toString().toStdString();
    settings->endGroup();

    settings->beginGroup("SetupTab");
    m_ProjectName     = settings->value("ProjectName","").toString().toStdString();
    m_ProjectDir      = settings->value("ProjectDir","").toString().toStdString();
    m_SetupFontSize   = settings->value("FontSize",9).toInt();
    settings->endGroup();

    delete settings;

    updateWindowTitle();
}

void
nmfMainWindow::readSettingsGuiOrientation(bool alsoResetPosition)
{
    QSettings* settings = nmfUtilsQt::createSettings(
                nmfConstantsDonut::SettingsDirWindows,QApplication::applicationName());

    settings->beginGroup("MainWindow");
    resize(settings->value("size", QSize(400, 400)).toSize());
    if (alsoResetPosition) {
        move(settings->value("pos", QPoint(200, 200)).toPoint());
    }

    // Resize the dock widgets
    int NavDockWidth      = settings->value("NavigatorDockWidgetWidth",200).toInt();
    int OutputDockWidth   = settings->value("OutputDockWidgetWidth",200).toInt();
    this->resizeDocks({m_UI->NavigatorDockWidget,m_UI->OutputDockWidget},
                      {NavDockWidth,OutputDockWidth},
                      Qt::Horizontal);
    settings->endGroup();

    delete settings;
}

bool
nmfMainWindow::saveScreenshot(QString &outputImageFile, QPixmap &pm)
{
    bool dataSavedOK;
    QString msg;
    QString pathImage;
    QString pathData;
    QMessageBox::StandardButton reply;
    QString outputImageFileWithPath;
    QString outputDataFileWithPath;
    QString outputDataFile = outputImageFile;

    nmfUtilsQt::switchFileExtensions(outputDataFile,".csv",{".jpg",".png"});

    pathImage = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(nmfConstantsDonut::OutputImagesDir));
    pathData  = QDir(QString::fromStdString(m_ProjectDir)).filePath(QString::fromStdString(nmfConstantsDonut::OutputDataDir));

    // If path doesn't exist make it
    for (QString path : {pathImage,pathData}) {
        QDir pathDir(path);
        if (! pathDir.exists()) {
            pathDir.mkpath(path);
        }
    }
    outputDataFileWithPath  = QDir(pathData).filePath(outputDataFile);
    outputImageFileWithPath = QDir(pathImage).filePath(outputImageFile);
    if (QFileInfo(outputImageFileWithPath).exists()) {
        msg   = "\nFile exists. OK to overwrite?\n";
        reply = QMessageBox::question(this, tr("File Exists"), tr(msg.toLatin1()),
                                      QMessageBox::No|QMessageBox::Yes,
                                      QMessageBox::Yes);
        if (reply == QMessageBox::No)
            return false;
    }

    // Save the image
    pm.save(outputImageFileWithPath);

    // Save the complete (input and output) Rank table
    dataSavedOK = saveRankDataFile(outputDataFileWithPath);

    // Notify user image has been saved
    msg  = "\nOutput image saved to file:\n\n" + outputImageFileWithPath;
    if (dataSavedOK) {
        msg += "\n\nOutput data saved to file:\n\n" + outputDataFileWithPath;
    }
    QMessageBox::information(this,
                             tr("Image and Data Saved"),
                             tr(msg.toLatin1()),
                             QMessageBox::Ok);

    m_Logger->logMsg(nmfConstants::Normal,"menu_screenshot: Image saved: "+ outputImageFile.toStdString());
    m_Logger->logMsg(nmfConstants::Normal,"menu_screenshot: Data  saved: "+ outputDataFile.toStdString());

    return true;
}

bool
nmfMainWindow::saveRankDataFile(QString filename)
{
    bool retv = false;
    int numRows = 0;
    int numCols = 0;
    QString value;
    QStandardItemModel* smodel = qobject_cast<QStandardItemModel *>(m_UI->SetupInputTabWidget->findChild<QTableView *>("Setup_Tab4_DataTV")->model());

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        numRows = smodel->rowCount();
        numCols = smodel->columnCount();
        for (int row=0; row<numRows; ++row) {
            // print out header data
            if (row == 0) {
                stream << smodel->headerData(0,Qt::Horizontal).toString();
                for (int col=1; col<numCols; ++col) {
                    stream << "," << smodel->headerData(col,Qt::Horizontal).toString();
                }
                stream << "\n";
            }

            stream << smodel->index(row,0).data().toString();
            for (int col=1; col<numCols; ++col) {
                value = smodel->index(row,col).data().toString();
                if (col >= nmfConstantsDonut::COLUMN_RPA_MODEL) {
                    value = value.replace("%","");
                }
                stream << "," << value;
            }
            stream << "\n";
        }
        file.close();
        retv = true;
    }
    return retv;
}

void
nmfMainWindow::saveSettings() {

    QSettings* settings = nmfUtilsQt::createSettings(
                nmfConstantsDonut::SettingsDirWindows,QApplication::applicationName());

    settings->beginGroup("MainWindow");
    settings->setValue("pos", pos());
    settings->setValue("size", size());
    settings->setValue("style",getCurrentStyle());
    settings->setValue("NavigatorDockWidgetWidth",   m_UI->NavigatorDockWidget->width());
    settings->setValue("OutputDockWidgetWidth",      m_UI->OutputDockWidget->width());
    settings->setValue("LogDockWidgetIsVisible",     m_UI->LogDockWidget->isVisible());
    settings->setValue("OutputDockWidgetIsVisible",  m_UI->OutputDockWidget->isVisible());
    settings->setValue("OutputDockWidgetIsFloating", m_UI->OutputDockWidget->isFloating());
    settings->setValue("OutputDockWidgetPos",        m_UI->OutputDockWidget->pos());
    settings->setValue("OutputDockWidgetSize",       m_UI->OutputDockWidget->size());
//  settings->setValue("CentralWidgetSize",          centralWidget()->size());
    settings->endGroup();

    delete settings;

    // Save other pages' settings
    Setup_Tab2_ptr->saveSettings();
}

void
nmfMainWindow::saveDefaultSettings()
{
    QSettings* settings = nmfUtilsQt::createSettings(
                nmfConstantsDonut::SettingsDirWindows,QApplication::applicationName());

    settings->beginGroup("MainWindow");
    settings->setValue("pos", QPoint(0,0));
    settings->endGroup();

    delete settings;
}

void
nmfMainWindow::setupLogWidget()
{
    m_LogWidget = new nmfLogWidget(m_Logger,nmfConstantsDonut::LogDir);
    m_UI->LogWidget->setLayout(m_LogWidget->vMainLayt);
}

void
nmfMainWindow::updateWindowTitle()
{
    QSettings* settings = nmfUtilsQt::createSettings(
                nmfConstantsDonut::SettingsDirWindows,QApplication::applicationName());

    settings->beginGroup("SetupTab");
    m_ProjectName     = settings->value("ProjectName","").toString().toStdString();
    m_ProjectDir      = settings->value("ProjectDir","").toString().toStdString();
    m_SetupFontSize   = settings->value("FontSize",9).toInt();
    settings->endGroup();
    std::string winTitle = "Donut Tool (" + m_ProjectName + ")";
    setWindowTitle(QString::fromStdString(winTitle));

    delete settings;
}

void
nmfMainWindow::callback_LoadProject()
{
  readSettings();

  disconnect(Setup_Tab2_ptr, SIGNAL(LoadProject()),
             this,           SLOT(callback_LoadProject()));

  loadGuis();

  connect(Setup_Tab2_ptr, SIGNAL(LoadProject()),
          this,           SLOT(callback_LoadProject()));

}

void
nmfMainWindow::callback_NavigatorSelectionChanged()
{
    QString parentStr;
    QString itemSelected;
    int pageNum;

    // Handle the case if the user hasn't selected anything yet.
    QList<QTreeWidgetItem *> selectedItems = m_NavigatorTree->selectedItems();

    if (selectedItems.count() > 0) {
        itemSelected = selectedItems[0]->text(0);
        pageNum = itemSelected.at(0).digitValue();
        if (pageNum < 1)
            pageNum = 1;

        parentStr.clear();
        if (selectedItems[0]->parent()) {
            parentStr = selectedItems[0]->parent()->text(0);
        }

        if ((itemSelected == "Donut Model") || (parentStr == "Donut Model")) {
            if (pageNum > 0) {
                m_UI->SetupInputTabWidget->blockSignals(true);
                m_UI->SetupInputTabWidget->setCurrentIndex(pageNum-1);
                m_UI->SetupInputTabWidget->blockSignals(false);
            }
        }
    }
}

void
nmfMainWindow::callback_PreferencesSetStyleSheet(QString style)
{
    // Update GUI widget colors for the Light or Dark theme
    if (style == "Dark") {
        QFile fileStyle(":qdarkstyle/style.qss");
        if (! fileStyle.exists()) {
            std::cout << "Error: Unable to set stylesheet, file not found: qdarkstyle/style.qss\n" << std::endl;;
        } else {
            fileStyle.open(QFile::ReadOnly | QFile::Text);
            QTextStream stream(&fileStyle);
            qApp->setStyleSheet(stream.readAll());
        }
    } else {
        qApp->setStyleSheet("");
    }

    // Necessary to redraw the chart with either the Light or Dark theme
    m_UI->OutputControlChartThemeCMB->setCurrentText(style);

    // Necessary to change the cell background colors for the Light or Dark theme
    if (Setup_Tab4_ptr != nullptr) {
        Setup_Tab4_ptr->resetTableBackgroundColors();
    }

}

void
nmfMainWindow::callback_ProjectSaved()
{
    updateWindowTitle();
}

void
nmfMainWindow::callback_ReloadWidgets()
{
    loadGuis();
}

void
nmfMainWindow::callback_ResetGUI()
{
    QMessageBox::StandardButton reply =
            QMessageBox::question(m_SplashDlg,
                                  tr("Reset GUI"),
                                  tr("\nOK to reset GUI position?\n"),
                                  QMessageBox::No|QMessageBox::Yes,
                                  QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        saveDefaultSettings();
    }
}

void
nmfMainWindow::callback_ResetSettings()
{
    QMessageBox::StandardButton reply =
            QMessageBox::question(m_SplashDlg,
                                  tr("Reset Settings"),
                                  tr("\nOK to reset application settings?\n"),
                                  QMessageBox::No|QMessageBox::Yes,
                                  QMessageBox::Yes);
    if (reply == QMessageBox::Yes) {
        nmfUtilsQt::removeSettingsFile();
        QMessageBox::information(m_SplashDlg,
                                 tr("Reset Settings"),
                                 tr("\nSettings reset.\n\nUser interface settings will be set again upon application exit.\n"),
                                 QMessageBox::Ok);
    }
}

void
nmfMainWindow::callback_SetupTabChanged(int tab)
{
    QModelIndex topLevelIndex = m_NavigatorTree->model()->index(0,0); // first 0 is Setup group in NavigatorTree
    QModelIndex childIndex    = topLevelIndex.model()->index(tab,0,topLevelIndex);
    m_NavigatorTree->blockSignals(true);
    m_NavigatorTree->setCurrentIndex(childIndex);
    m_NavigatorTree->blockSignals(false);
}

void
nmfMainWindow::callback_ShowOutputChart(
        QString Predator,
        std::vector<std::string> Species,
        std::vector<double> RPAData,
        std::vector<double> AiData,
        std::vector<double> NullData)
{
    int i = 0;
    std::string MainTitle;
    std::string XTitle;
    std::string YTitle;
    double MaxYVal = 100.0;

    boost::numeric::ublas::matrix<double> ChartData;
    QStringList ColumnLabels;

    for (std::string species : Species) {
        ColumnLabels << QString::fromStdString(species);
    }

    m_UI->OutputDockWidget->show();

    m_ChartWidget->removeAllSeries();

    QString ChartType = m_UI->OutputControlChartTypeCMB->currentText();
    int ChartTheme    = m_UI->OutputControlChartThemeCMB->currentIndex();
    if (ChartType == "Bar") {
        nmfUtils::initialize(ChartData,3,RPAData.size());
        QStringList RowLabels = {"RPA Model","Null Ambient (Ai)","Null Selectivity"};
        for (std::vector<double> data : {RPAData,AiData,NullData}) {
            for (int j=0; j<data.size(); ++j) {
                ChartData(i,j) = data[j];
            }
            ++i;
        }
        nmfChartBar* barChart = new nmfChartBar();
        MainTitle = "Rank Data for Predator: " + Predator.toStdString();
        XTitle    = "Outputs";
        YTitle    = "Diet Composition (%)";
        barChart->populateChart(m_ChartWidget, ChartType.toStdString(), MaxYVal,
                                ChartData, RowLabels, ColumnLabels,
                                MainTitle, XTitle, YTitle,
                                {true,true}, ChartTheme);

    } else if (ChartType == "Bar-prey") {
        nmfUtils::initialize(ChartData,RPAData.size(),3);
        QStringList ColumnLabels = {"RPA Model","Null Ambient (Ai)","Null Selectivity"};
        QStringList RowLabels;
        for (std::string species : Species) {
            RowLabels << QString::fromStdString(species);
        }
        for (int j=0; j<RPAData.size();++j) {
            ChartData(j,0) = RPAData[j];
            ChartData(j,1) = AiData[j];
            ChartData(j,2) = NullData[j];
        }
        nmfChartBar* barChart = new nmfChartBar();
        MainTitle = "Rank Data for Predator: " + Predator.toStdString();
        XTitle    = "Prey";
        YTitle    = "Diet Composition (%)";
        barChart->populateChart(m_ChartWidget, "Bar", MaxYVal,
                                ChartData, RowLabels, ColumnLabels,
                                MainTitle, XTitle, YTitle,
                                {true,true}, ChartTheme);

    } else if (ChartType == "Donut") {
        nmfUtils::initialize(ChartData,3,RPAData.size());
        QStringList RowLabels = {"Null Selectivity","Rel Abund","RPA Model"};
        for (std::vector<double> data : {NullData,AiData,RPAData}) {
            for (int j=0; j<data.size(); ++j) {
                ChartData(i,j) = data[j];
            }
            ++i;
        }
        nmfChartDonut* donutChart = new nmfChartDonut();
        MainTitle = "Rank Data for Predator: " + Predator.toStdString();
        XTitle    = "RPA Model (outer), Null Ambient (Ai) (middle), Null Selectivity (inner)";
        YTitle    = "";
        donutChart->populateChart(m_ChartWidget, ChartData,
                                  RowLabels, ColumnLabels,
                                  MainTitle, XTitle, YTitle,
                                 {false,false}, ChartTheme);
    }
}

void
nmfMainWindow::menu_about()
{
    QString name    = "Tool for predicting prey preference and diet composition";
    QString version = "Donut Tool v0.9.1 (beta)";
    QString specialAcknowledgement = "";
    QString cppVersion   = "C++??";
    QString boostVersion = "?";
    QString qdarkLink;
    QString paperLink;
    QString linuxDeployLink;
    QString boostLink;
    QString qtLink;
    QString msg; // = "<strong><br>Donut v"+ver+"</strong>";
    QString os = QString::fromStdString(nmfUtils::getOS());

    // Define Qt link
    qtLink = QString("<a href='https://www.qt.io'>https://www.qt.io</a>");

    // Find C++ version in case you want it later
    if (__cplusplus == 201103L)
        cppVersion = "C++11";
    else if (__cplusplus == 201402L)
        cppVersion = "C++14";
    else if (__cplusplus == 201703L)
        cppVersion = "C++17";

    // Boost version and link
    boostVersion = QString::number(BOOST_VERSION / 100000) + "." +
                   QString::number(BOOST_VERSION / 100 % 1000) + "." +
                   QString::number(BOOST_VERSION / 100);
    boostLink = QString("<a href='https://www.boost.org'>https://www.boost.org</a>");

    // QDarkStyle link
    qdarkLink = QString("<a href='https://github.com/ColinDuquesnoy/QDarkStyleSheet'>https://github.com/ColinDuquesnoy/QDarkStyleSheet</a>");

    // linuxdeployqt link
    linuxDeployLink = QString("<a href='https://github.com/probonopd/linuxdeployqt'>https://github.com/probonopd/linuxdeployqt</a>");

    // Build About message
  //msg += QString("<li>")+cppVersion+QString("</li>");
    msg += QString("<li>")+QString("Qt ")+QString::fromUtf8(qVersion())+QString("<br>")+qtLink+QString("</li>");
    msg += QString("<li>")+QString("Boost ")+boostVersion+QString("<br>")+boostLink+QString("</li>");
    msg += QString("<li>")+QString("QDarkStyleSheet 2.6.5 - Colin Duquesnoy (MIT License)<br>")+qdarkLink+QString("</li>");
    msg += QString("<li>")+QString("linuxdeployqt 6 (January 27, 2019)<br>")+linuxDeployLink+QString("</li>");
    msg += QString("</ul>");


    paperLink = QString("<a href='https://www.tandfonline.com/doi/citedby/10.1577/T02-142.1?scroll=top&needAccess=true'>link to article</a>");
    msg += QString("This work is based upon:<br><br>");
    msg += QString("Jason S. Link (2004) A General Model of Selectivity for Fish Feeding: A Rank Proportion Algorithm, Transactions of the American Fisheries Society, 133:3, 655-673, DOI: 10.1577/T02-142.1");
    msg += QString("&nbsp;") + paperLink;

    nmfUtilsQt::showAboutWidget(this,name,os,version,specialAcknowledgement,msg);
}

void
nmfMainWindow::menu_clear()
{
    QString retv = nmfUtilsQt::clear(qApp,findTableInFocus());
    if (! retv.isEmpty()) {
        QMessageBox::question(this,tr("Clear"),retv,QMessageBox::Ok);
    }
}

void
nmfMainWindow::menu_copy()
{
    try {
        findTableInFocus();
        // RSK - this causes a hard crash if user copies cells one of which has a combobox
    } catch (...) {
        std::cout << "\nError: Invalid cells found to copy." << std::endl;
        return;
    }

    QString retv = nmfUtilsQt::copy(qApp,findTableInFocus());
    if (! retv.isEmpty()) {
        QMessageBox::question(this,tr("Copy"),retv,QMessageBox::Ok);
    }
}

void
nmfMainWindow::menu_clearAll()
{
    QString retv = nmfUtilsQt::clearAll(findTableInFocus());
    if (! retv.isEmpty()) {
        QMessageBox::question(this,tr("Clear All"),retv,QMessageBox::Ok);
    }
}

void
nmfMainWindow::menu_deselectAll()
{
    QString retv = nmfUtilsQt::deselectAll(findTableInFocus());
    if (! retv.isEmpty()) {
        QMessageBox::question(this,tr("Deselect All"),retv,QMessageBox::Ok);
    }
}

void
nmfMainWindow::menu_layoutOutput()
{
    m_UI->OutputDockWidget->setFloating(true);
    m_UI->OutputDockWidget->setGeometry(this->x()+this->width()*(2.0/3.0),this->y(),800,600);
    m_UI->OutputDockWidget->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    m_UI->OutputDockWidget->show();
    m_UI->OutputDockWidget->raise();
}

void
nmfMainWindow::menu_layoutOutputEmbedded()
{
    this->restoreDockWidget(m_UI->NavigatorDockWidget);
    this->restoreDockWidget(m_UI->OutputDockWidget);
    m_UI->NavigatorDockWidget->show();
    m_UI->OutputDockWidget->setFloating(false);
    m_UI->OutputDockWidget->show();
    QRect geo = m_UI->OutputDockWidget->geometry();
    geo.setWidth(600);
    m_UI->OutputDockWidget->setGeometry(geo);
    m_UI->LogDockWidget->setFloating(false);
    m_UI->LogDockWidget->hide();
    centralWidget()->show();

    readSettingsGuiOrientation(nmfConstantsDonut::DontResetPosition);
}

void
nmfMainWindow::menu_layoutMinimal()
{
    this->restoreDockWidget(m_UI->NavigatorDockWidget);
    this->restoreDockWidget(m_UI->OutputDockWidget);
    m_UI->NavigatorDockWidget->hide();
    m_UI->OutputDockWidget->setFloating(false);
    m_UI->OutputDockWidget->hide();
    m_UI->LogDockWidget->setFloating(false);
    m_UI->LogDockWidget->hide();
    centralWidget()->show();

    readSettingsGuiOrientation(nmfConstantsDonut::DontResetPosition);
}

void
nmfMainWindow::menu_layoutDefault()
{
    this->restoreDockWidget(m_UI->NavigatorDockWidget);
    this->restoreDockWidget(m_UI->OutputDockWidget);
    m_UI->NavigatorDockWidget->show();
    m_UI->OutputDockWidget->setFloating(false);
    m_UI->OutputDockWidget->hide();

    m_UI->LogDockWidget->setFloating(false);
    m_UI->LogDockWidget->hide();
    centralWidget()->show();

    readSettingsGuiOrientation(nmfConstantsDonut::DontResetPosition);
}


void
nmfMainWindow::menu_paste()
{
    QString retv = nmfUtilsQt::paste(qApp,findTableInFocus());
    if (! retv.isEmpty()) {
        QMessageBox::question(this,tr("Paste"),retv,QMessageBox::Ok);
    }
}

void
nmfMainWindow::menu_pasteAll()
{
    QString retv = nmfUtilsQt::pasteAll(qApp,findTableInFocus());
    if (! retv.isEmpty()) {
        QMessageBox::question(this,tr("Paste All"),retv,QMessageBox::Ok);
    }
}

void
nmfMainWindow::menu_preferences()
{
    m_PreferencesDlg->show();
}

void
nmfMainWindow::menu_quit()
{
    if (QMessageBox::Yes == QMessageBox::question(
                this,
                tr("Quit"),
                tr("\nAre you sure you want to quit?\n")))
    {
        saveSettings();
        close(); // emits closeEvent
    }
}

void
nmfMainWindow::menu_screenShot()
{
    QPixmap pm;
    QString outputFile;

    if (m_ChartView2d->isVisible())
    {
        nmfStructsQt::ChartSaveDlg *dlg = new nmfStructsQt::ChartSaveDlg(this);
        if (dlg->exec()) {
            outputFile = dlg->getFilename();
        }
        delete dlg;
        if (outputFile.isEmpty())
            return;

        // Grab the image and store in a pixmap
        if (m_ChartView2d->isVisible()) {
            m_ChartView2d->update();
            m_ChartView2d->repaint();
            pm = m_ChartView2d->grab();

        }

        saveScreenshot(outputFile,pm);
    }
}

void
nmfMainWindow::menu_selectAll()
{
    QString retv = nmfUtilsQt::selectAll(findTableInFocus());
    if (! retv.isEmpty()) {
        QMessageBox::question(this,tr("Select All"),retv,QMessageBox::Ok);
    }
}

void
nmfMainWindow::menu_whatsThis()
{
    QWhatsThis::enterWhatsThisMode();
}
