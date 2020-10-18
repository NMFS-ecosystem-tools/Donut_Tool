/********************************************************************************
** Form generated from reading UI file 'nmfMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NMFMAINWINDOW_H
#define UI_NMFMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nmfMainWindow
{
public:
    QAction *actionConnectToDatabase;
    QAction *actionQuit;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionClear;
    QAction *actionPasteAll;
    QAction *actionSelectAll;
    QAction *actionDeselectAll;
    QAction *actionShowCurrentRun;
    QAction *actionClearOutputData2;
    QAction *actionShowAllSavedRuns;
    QAction *actionSaveCurrentRun;
    QAction *actionClearOutputData;
    QAction *actionSaveAndShowCurrentRun;
    QAction *actionCreateTables;
    QAction *actionLayoutOutput;
    QAction *actionLayoutDefault;
    QAction *actionWhatsThis;
    QAction *actionAbout;
    QAction *actionWhatsThisTB;
    QAction *actionSaveSettings;
    QAction *actionClearSpecificOutputData;
    QAction *actionPreferences;
    QAction *actionScreenShot;
    QAction *actionImportDatabase;
    QAction *actionExportDatabase;
    QAction *actionResetCursor;
    QAction *actionExportAllDatabases;
    QAction *actionLayoutMinimal;
    QAction *actionLayoutOutputEmbedded;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *SetupInputTabWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuLayouts;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *NavigatorDockWidget;
    QWidget *NavigatorWidget;
    QDockWidget *OutputDockWidget;
    QWidget *OutputWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTabWidget *OutputTabWidget;
    QWidget *OutputChartTab;
    QGroupBox *OutputControlsGB;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QComboBox *OutputControlChartTypeCMB;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QComboBox *OutputControlChartThemeCMB;
    QDockWidget *LogDockWidget;
    QWidget *LogWidget;

    void setupUi(QMainWindow *nmfMainWindow)
    {
        if (nmfMainWindow->objectName().isEmpty())
            nmfMainWindow->setObjectName(QString::fromUtf8("nmfMainWindow"));
        nmfMainWindow->resize(1040, 685);
        actionConnectToDatabase = new QAction(nmfMainWindow);
        actionConnectToDatabase->setObjectName(QString::fromUtf8("actionConnectToDatabase"));
        actionQuit = new QAction(nmfMainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionCopy = new QAction(nmfMainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(nmfMainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionClear = new QAction(nmfMainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        actionPasteAll = new QAction(nmfMainWindow);
        actionPasteAll->setObjectName(QString::fromUtf8("actionPasteAll"));
        actionSelectAll = new QAction(nmfMainWindow);
        actionSelectAll->setObjectName(QString::fromUtf8("actionSelectAll"));
        actionDeselectAll = new QAction(nmfMainWindow);
        actionDeselectAll->setObjectName(QString::fromUtf8("actionDeselectAll"));
        actionShowCurrentRun = new QAction(nmfMainWindow);
        actionShowCurrentRun->setObjectName(QString::fromUtf8("actionShowCurrentRun"));
        actionShowCurrentRun->setCheckable(false);
        actionClearOutputData2 = new QAction(nmfMainWindow);
        actionClearOutputData2->setObjectName(QString::fromUtf8("actionClearOutputData2"));
        actionShowAllSavedRuns = new QAction(nmfMainWindow);
        actionShowAllSavedRuns->setObjectName(QString::fromUtf8("actionShowAllSavedRuns"));
        actionSaveCurrentRun = new QAction(nmfMainWindow);
        actionSaveCurrentRun->setObjectName(QString::fromUtf8("actionSaveCurrentRun"));
        actionClearOutputData = new QAction(nmfMainWindow);
        actionClearOutputData->setObjectName(QString::fromUtf8("actionClearOutputData"));
        actionSaveAndShowCurrentRun = new QAction(nmfMainWindow);
        actionSaveAndShowCurrentRun->setObjectName(QString::fromUtf8("actionSaveAndShowCurrentRun"));
        actionCreateTables = new QAction(nmfMainWindow);
        actionCreateTables->setObjectName(QString::fromUtf8("actionCreateTables"));
        actionLayoutOutput = new QAction(nmfMainWindow);
        actionLayoutOutput->setObjectName(QString::fromUtf8("actionLayoutOutput"));
        actionLayoutDefault = new QAction(nmfMainWindow);
        actionLayoutDefault->setObjectName(QString::fromUtf8("actionLayoutDefault"));
        actionWhatsThis = new QAction(nmfMainWindow);
        actionWhatsThis->setObjectName(QString::fromUtf8("actionWhatsThis"));
        actionWhatsThis->setCheckable(false);
        actionWhatsThis->setChecked(false);
        actionAbout = new QAction(nmfMainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionWhatsThisTB = new QAction(nmfMainWindow);
        actionWhatsThisTB->setObjectName(QString::fromUtf8("actionWhatsThisTB"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/whatsthis.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWhatsThisTB->setIcon(icon);
        actionSaveSettings = new QAction(nmfMainWindow);
        actionSaveSettings->setObjectName(QString::fromUtf8("actionSaveSettings"));
        actionClearSpecificOutputData = new QAction(nmfMainWindow);
        actionClearSpecificOutputData->setObjectName(QString::fromUtf8("actionClearSpecificOutputData"));
        actionPreferences = new QAction(nmfMainWindow);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        actionScreenShot = new QAction(nmfMainWindow);
        actionScreenShot->setObjectName(QString::fromUtf8("actionScreenShot"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/scrgrb.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScreenShot->setIcon(icon1);
        actionImportDatabase = new QAction(nmfMainWindow);
        actionImportDatabase->setObjectName(QString::fromUtf8("actionImportDatabase"));
        actionExportDatabase = new QAction(nmfMainWindow);
        actionExportDatabase->setObjectName(QString::fromUtf8("actionExportDatabase"));
        actionResetCursor = new QAction(nmfMainWindow);
        actionResetCursor->setObjectName(QString::fromUtf8("actionResetCursor"));
        actionExportAllDatabases = new QAction(nmfMainWindow);
        actionExportAllDatabases->setObjectName(QString::fromUtf8("actionExportAllDatabases"));
        actionLayoutMinimal = new QAction(nmfMainWindow);
        actionLayoutMinimal->setObjectName(QString::fromUtf8("actionLayoutMinimal"));
        actionLayoutOutputEmbedded = new QAction(nmfMainWindow);
        actionLayoutOutputEmbedded->setObjectName(QString::fromUtf8("actionLayoutOutputEmbedded"));
        centralWidget = new QWidget(nmfMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(100, 100));
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        SetupInputTabWidget = new QTabWidget(centralWidget);
        SetupInputTabWidget->setObjectName(QString::fromUtf8("SetupInputTabWidget"));
        SetupInputTabWidget->setMinimumSize(QSize(10, 0));
        SetupInputTabWidget->setMaximumSize(QSize(16777215, 16777215));
        SetupInputTabWidget->setFocusPolicy(Qt::TabFocus);

        verticalLayout_3->addWidget(SetupInputTabWidget);

        nmfMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(nmfMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1040, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuLayouts = new QMenu(menuBar);
        menuLayouts->setObjectName(QString::fromUtf8("menuLayouts"));
        nmfMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(nmfMainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        nmfMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(nmfMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        nmfMainWindow->setStatusBar(statusBar);
        NavigatorDockWidget = new QDockWidget(nmfMainWindow);
        NavigatorDockWidget->setObjectName(QString::fromUtf8("NavigatorDockWidget"));
        NavigatorWidget = new QWidget();
        NavigatorWidget->setObjectName(QString::fromUtf8("NavigatorWidget"));
        NavigatorDockWidget->setWidget(NavigatorWidget);
        nmfMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), NavigatorDockWidget);
        OutputDockWidget = new QDockWidget(nmfMainWindow);
        OutputDockWidget->setObjectName(QString::fromUtf8("OutputDockWidget"));
        OutputWidget = new QWidget();
        OutputWidget->setObjectName(QString::fromUtf8("OutputWidget"));
        verticalLayout = new QVBoxLayout(OutputWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(OutputWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        OutputTabWidget = new QTabWidget(splitter);
        OutputTabWidget->setObjectName(QString::fromUtf8("OutputTabWidget"));
        OutputTabWidget->setMinimumSize(QSize(10, 0));
        OutputTabWidget->setMaximumSize(QSize(16777215, 16777215));
        OutputTabWidget->setUsesScrollButtons(false);
        OutputChartTab = new QWidget();
        OutputChartTab->setObjectName(QString::fromUtf8("OutputChartTab"));
        OutputTabWidget->addTab(OutputChartTab, QString());
        splitter->addWidget(OutputTabWidget);
        OutputControlsGB = new QGroupBox(splitter);
        OutputControlsGB->setObjectName(QString::fromUtf8("OutputControlsGB"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(OutputControlsGB->sizePolicy().hasHeightForWidth());
        OutputControlsGB->setSizePolicy(sizePolicy1);
        OutputControlsGB->setMinimumSize(QSize(105, 0));
        OutputControlsGB->setMaximumSize(QSize(105, 16777215));
        verticalLayout_2 = new QVBoxLayout(OutputControlsGB);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(OutputControlsGB);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        OutputControlChartTypeCMB = new QComboBox(OutputControlsGB);
        OutputControlChartTypeCMB->addItem(QString());
        OutputControlChartTypeCMB->addItem(QString());
        OutputControlChartTypeCMB->addItem(QString());
        OutputControlChartTypeCMB->setObjectName(QString::fromUtf8("OutputControlChartTypeCMB"));

        verticalLayout_2->addWidget(OutputControlChartTypeCMB);

        verticalSpacer = new QSpacerItem(20, 288, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label_2 = new QLabel(OutputControlsGB);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        OutputControlChartThemeCMB = new QComboBox(OutputControlsGB);
        OutputControlChartThemeCMB->addItem(QString());
        OutputControlChartThemeCMB->addItem(QString());
        OutputControlChartThemeCMB->addItem(QString());
        OutputControlChartThemeCMB->addItem(QString());
        OutputControlChartThemeCMB->addItem(QString());
        OutputControlChartThemeCMB->addItem(QString());
        OutputControlChartThemeCMB->addItem(QString());
        OutputControlChartThemeCMB->addItem(QString());
        OutputControlChartThemeCMB->setObjectName(QString::fromUtf8("OutputControlChartThemeCMB"));

        verticalLayout_2->addWidget(OutputControlChartThemeCMB);

        splitter->addWidget(OutputControlsGB);

        verticalLayout->addWidget(splitter);

        OutputDockWidget->setWidget(OutputWidget);
        nmfMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), OutputDockWidget);
        LogDockWidget = new QDockWidget(nmfMainWindow);
        LogDockWidget->setObjectName(QString::fromUtf8("LogDockWidget"));
        LogWidget = new QWidget();
        LogWidget->setObjectName(QString::fromUtf8("LogWidget"));
        LogDockWidget->setWidget(LogWidget);
        nmfMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), LogDockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuLayouts->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionPreferences);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuEdit->addAction(actionClear);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionPasteAll);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelectAll);
        menuEdit->addAction(actionDeselectAll);
        menuHelp->addAction(actionWhatsThis);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);
        menuLayouts->addAction(actionLayoutDefault);
        menuLayouts->addSeparator();
        menuLayouts->addAction(actionLayoutOutput);
        menuLayouts->addAction(actionLayoutOutputEmbedded);
        menuLayouts->addAction(actionLayoutMinimal);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionScreenShot);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionWhatsThisTB);

        retranslateUi(nmfMainWindow);

        SetupInputTabWidget->setCurrentIndex(-1);
        OutputTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(nmfMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *nmfMainWindow)
    {
        nmfMainWindow->setWindowTitle(QApplication::translate("nmfMainWindow", "Donut Model", nullptr));
        actionConnectToDatabase->setText(QApplication::translate("nmfMainWindow", "&Connect to Database", nullptr));
        actionQuit->setText(QApplication::translate("nmfMainWindow", "&Quit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionCopy->setText(QApplication::translate("nmfMainWindow", "&Copy", nullptr));
#ifndef QT_NO_TOOLTIP
        actionCopy->setToolTip(QApplication::translate("nmfMainWindow", "Copy", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionCopy->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionPaste->setText(QApplication::translate("nmfMainWindow", "&Paste", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPaste->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        actionClear->setText(QApplication::translate("nmfMainWindow", "C&lear", nullptr));
#ifndef QT_NO_SHORTCUT
        actionClear->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        actionPasteAll->setText(QApplication::translate("nmfMainWindow", "Paste &All", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPasteAll->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+Shift+V", nullptr));
#endif // QT_NO_SHORTCUT
        actionSelectAll->setText(QApplication::translate("nmfMainWindow", "&Select All", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSelectAll->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionDeselectAll->setText(QApplication::translate("nmfMainWindow", "&Deselect All", nullptr));
#ifndef QT_NO_SHORTCUT
        actionDeselectAll->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+Shift+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionShowCurrentRun->setText(QApplication::translate("nmfMainWindow", "Current Run", nullptr));
#ifndef QT_NO_TOOLTIP
        actionShowCurrentRun->setToolTip(QApplication::translate("nmfMainWindow", "Show chart of current run", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionShowCurrentRun->setStatusTip(QApplication::translate("nmfMainWindow", "Show chart of current run", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionShowCurrentRun->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+Shift+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionClearOutputData2->setText(QApplication::translate("nmfMainWindow", "Clear Output Data", nullptr));
#ifndef QT_NO_TOOLTIP
        actionClearOutputData2->setToolTip(QApplication::translate("nmfMainWindow", "Clears all estimated and derived output tables from database", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionClearOutputData2->setStatusTip(QApplication::translate("nmfMainWindow", "Clears all estimated and derived output tables from database", nullptr));
#endif // QT_NO_STATUSTIP
        actionShowAllSavedRuns->setText(QApplication::translate("nmfMainWindow", "All Saved Runs", nullptr));
#ifndef QT_NO_TOOLTIP
        actionShowAllSavedRuns->setToolTip(QApplication::translate("nmfMainWindow", "Show charts of all data in output tables.", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionShowAllSavedRuns->setStatusTip(QApplication::translate("nmfMainWindow", "Show charts of all data in output tables.", nullptr));
#endif // QT_NO_STATUSTIP
        actionSaveCurrentRun->setText(QApplication::translate("nmfMainWindow", "Save Current Run", nullptr));
        actionClearOutputData->setText(QApplication::translate("nmfMainWindow", "Clear All Output Data", nullptr));
#ifndef QT_NO_TOOLTIP
        actionClearOutputData->setToolTip(QApplication::translate("nmfMainWindow", "Clears all Output and Forecast tables from database", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionClearOutputData->setStatusTip(QApplication::translate("nmfMainWindow", "Clears all Output and Forecast tables from database", nullptr));
#endif // QT_NO_STATUSTIP
        actionSaveAndShowCurrentRun->setText(QApplication::translate("nmfMainWindow", "And Save Current Run", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSaveAndShowCurrentRun->setToolTip(QApplication::translate("nmfMainWindow", "Save and then show chart of current run", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSaveAndShowCurrentRun->setStatusTip(QApplication::translate("nmfMainWindow", "Save and then show chart of current run", nullptr));
#endif // QT_NO_STATUSTIP
        actionCreateTables->setText(QApplication::translate("nmfMainWindow", "Create Tables", nullptr));
#ifndef QT_NO_TOOLTIP
        actionCreateTables->setToolTip(QApplication::translate("nmfMainWindow", "Creates any database tables not yet created", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionCreateTables->setStatusTip(QApplication::translate("nmfMainWindow", "Creates any database tables not yet created", nullptr));
#endif // QT_NO_STATUSTIP
        actionLayoutOutput->setText(QApplication::translate("nmfMainWindow", "&Output", nullptr));
#ifndef QT_NO_SHORTCUT
        actionLayoutOutput->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+1", nullptr));
#endif // QT_NO_SHORTCUT
        actionLayoutDefault->setText(QApplication::translate("nmfMainWindow", "&Default", nullptr));
#ifndef QT_NO_SHORTCUT
        actionLayoutDefault->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+L", nullptr));
#endif // QT_NO_SHORTCUT
        actionWhatsThis->setText(QApplication::translate("nmfMainWindow", "&What's This?", nullptr));
        actionWhatsThis->setIconText(QApplication::translate("nmfMainWindow", "Point and Click Help Feature (called \"What's This?\") ", nullptr));
#ifndef QT_NO_TOOLTIP
        actionWhatsThis->setToolTip(QApplication::translate("nmfMainWindow", "Point and Click Help Feature (called \"What's This?\") ", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionWhatsThis->setStatusTip(QApplication::translate("nmfMainWindow", "Point and Click Help Feature (called \"What's This?\") ", nullptr));
#endif // QT_NO_STATUSTIP
        actionAbout->setText(QApplication::translate("nmfMainWindow", "About...", nullptr));
        actionWhatsThisTB->setText(QString());
#ifndef QT_NO_TOOLTIP
        actionWhatsThisTB->setToolTip(QApplication::translate("nmfMainWindow", "Point and Click Help Feature (called \"What's This?\") ", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionWhatsThisTB->setStatusTip(QApplication::translate("nmfMainWindow", "Point and Click Help Feature (called \"What's This?\") ", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionWhatsThisTB->setWhatsThis(QApplication::translate("nmfMainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">WhatsThis? Help</span></p><p>This is the WhatsThis? help functionality available in this application. Selecting this feature will transform the cursor into a WhatsThis? cursor. As the user hovers this transformed cursor over an object that has additional &quot;WhatsThis?&quot; help implemented, the cursor shape will change to a question mark with an arrow which signifies additional popup help will appear once the user clicks over the object.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        actionSaveSettings->setText(QApplication::translate("nmfMainWindow", "Save Settings", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSaveSettings->setToolTip(QApplication::translate("nmfMainWindow", "Save GUI Location and Size", nullptr));
#endif // QT_NO_TOOLTIP
        actionClearSpecificOutputData->setText(QApplication::translate("nmfMainWindow", "Clear Specific Output Data...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionClearSpecificOutputData->setToolTip(QApplication::translate("nmfMainWindow", "Clears Output and Forecast tables of a specific Algorithm from database", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionClearSpecificOutputData->setStatusTip(QApplication::translate("nmfMainWindow", "Clears Output and Forecast tables of a specific Algorithm from database", nullptr));
#endif // QT_NO_STATUSTIP
        actionPreferences->setText(QApplication::translate("nmfMainWindow", "P&references...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionPreferences->setToolTip(QApplication::translate("nmfMainWindow", "Application Preferences", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPreferences->setStatusTip(QApplication::translate("nmfMainWindow", "Application Preferences", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        actionPreferences->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+P", nullptr));
#endif // QT_NO_SHORTCUT
        actionScreenShot->setText(QApplication::translate("nmfMainWindow", "Save Current Output Chart", nullptr));
        actionScreenShot->setIconText(QApplication::translate("nmfMainWindow", "Save Current Output Chart", nullptr));
#ifndef QT_NO_TOOLTIP
        actionScreenShot->setToolTip(QApplication::translate("nmfMainWindow", "Save Current Output Chart", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        actionScreenShot->setWhatsThis(QApplication::translate("nmfMainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Snapshot</span></p><p>This function saves the current Output Chart when clicked and stores it into the outputImages directory of the current project.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        actionImportDatabase->setText(QApplication::translate("nmfMainWindow", "Import Database...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionImportDatabase->setToolTip(QApplication::translate("nmfMainWindow", "Import MySQL Database", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionImportDatabase->setStatusTip(QApplication::translate("nmfMainWindow", "Import MySQL Database", nullptr));
#endif // QT_NO_STATUSTIP
        actionExportDatabase->setText(QApplication::translate("nmfMainWindow", "Export Database...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionExportDatabase->setToolTip(QApplication::translate("nmfMainWindow", "Export MySQL Database", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionExportDatabase->setStatusTip(QApplication::translate("nmfMainWindow", "Export MySQL Database", nullptr));
#endif // QT_NO_STATUSTIP
        actionResetCursor->setText(QApplication::translate("nmfMainWindow", "Reset Cursor", nullptr));
        actionExportAllDatabases->setText(QApplication::translate("nmfMainWindow", "Export All Databases...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionExportAllDatabases->setToolTip(QApplication::translate("nmfMainWindow", "Export All MySQL Databases", nullptr));
#endif // QT_NO_TOOLTIP
        actionLayoutMinimal->setText(QApplication::translate("nmfMainWindow", "Minimal", nullptr));
#ifndef QT_NO_SHORTCUT
        actionLayoutMinimal->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+3", nullptr));
#endif // QT_NO_SHORTCUT
        actionLayoutOutputEmbedded->setText(QApplication::translate("nmfMainWindow", "Output (Embedded)", nullptr));
#ifndef QT_NO_SHORTCUT
        actionLayoutOutputEmbedded->setShortcut(QApplication::translate("nmfMainWindow", "Ctrl+2", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_WHATSTHIS
        SetupInputTabWidget->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        menuFile->setTitle(QApplication::translate("nmfMainWindow", "&File", nullptr));
        menuEdit->setTitle(QApplication::translate("nmfMainWindow", "&Edit", nullptr));
        menuHelp->setTitle(QApplication::translate("nmfMainWindow", "&Help", nullptr));
        menuLayouts->setTitle(QApplication::translate("nmfMainWindow", "&Layouts", nullptr));
        mainToolBar->setWindowTitle(QApplication::translate("nmfMainWindow", "Main Toolbar", nullptr));
#ifndef QT_NO_WHATSTHIS
        mainToolBar->setWhatsThis(QApplication::translate("nmfMainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        NavigatorDockWidget->setWindowTitle(QApplication::translate("nmfMainWindow", "Navigator", nullptr));
        OutputDockWidget->setWindowTitle(QApplication::translate("nmfMainWindow", "Output", nullptr));
        OutputTabWidget->setTabText(OutputTabWidget->indexOf(OutputChartTab), QApplication::translate("nmfMainWindow", "Chart", nullptr));
        OutputControlsGB->setTitle(QApplication::translate("nmfMainWindow", "Controls", nullptr));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("nmfMainWindow", "Chart type for Null Ambient data", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label->setStatusTip(QApplication::translate("nmfMainWindow", "Chart type for Null Ambient data", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        label->setWhatsThis(QApplication::translate("nmfMainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Chart Type</span></p><p>These are the chart types available to visualize the Null Ambient data for the current predator. Currently there are 2 types available: Bar Chart and Donut Chart. Both charts display the same data, namely, per species percentages of various quantities. As the user hovers over each chart, a label appears that describes the chart in more detail. </p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("nmfMainWindow", "Chart Type:", nullptr));
        OutputControlChartTypeCMB->setItemText(0, QApplication::translate("nmfMainWindow", "Bar", nullptr));
        OutputControlChartTypeCMB->setItemText(1, QApplication::translate("nmfMainWindow", "Bar-prey", nullptr));
        OutputControlChartTypeCMB->setItemText(2, QApplication::translate("nmfMainWindow", "Donut", nullptr));

#ifndef QT_NO_TOOLTIP
        OutputControlChartTypeCMB->setToolTip(QApplication::translate("nmfMainWindow", "Chart type for Output data", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        OutputControlChartTypeCMB->setStatusTip(QApplication::translate("nmfMainWindow", "Chart type for Output data", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        OutputControlChartTypeCMB->setWhatsThis(QApplication::translate("nmfMainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Chart Type</span></p><p>These are the chart types available to visualize the Output data for the current predator. Currently there are 2 main types available: Bar Chart and Donut Chart. Both charts display the same data, namely, percentages of various quantities. As the user hovers over each chart, a label appears that describes the chart in more detail. </p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("nmfMainWindow", "The application's color theme", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label_2->setStatusTip(QApplication::translate("nmfMainWindow", "The application's color theme", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        label_2->setWhatsThis(QApplication::translate("nmfMainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Theme</span></p><p>This is the application's color theme. Changing this pulldown will set the application's color theme to one of several pre-defined color themes. Some themes may prove better for viewing by color-impaired individuals or for printing.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        label_2->setText(QApplication::translate("nmfMainWindow", "Theme:", nullptr));
        OutputControlChartThemeCMB->setItemText(0, QApplication::translate("nmfMainWindow", "Light", nullptr));
        OutputControlChartThemeCMB->setItemText(1, QApplication::translate("nmfMainWindow", "Cerulean", nullptr));
        OutputControlChartThemeCMB->setItemText(2, QApplication::translate("nmfMainWindow", "Dark", nullptr));
        OutputControlChartThemeCMB->setItemText(3, QApplication::translate("nmfMainWindow", "Sand", nullptr));
        OutputControlChartThemeCMB->setItemText(4, QApplication::translate("nmfMainWindow", "Blue", nullptr));
        OutputControlChartThemeCMB->setItemText(5, QApplication::translate("nmfMainWindow", "Contrast", nullptr));
        OutputControlChartThemeCMB->setItemText(6, QApplication::translate("nmfMainWindow", "Icy Blue", nullptr));
        OutputControlChartThemeCMB->setItemText(7, QApplication::translate("nmfMainWindow", "Qt", nullptr));

#ifndef QT_NO_TOOLTIP
        OutputControlChartThemeCMB->setToolTip(QApplication::translate("nmfMainWindow", "The application's color theme", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        OutputControlChartThemeCMB->setStatusTip(QApplication::translate("nmfMainWindow", "The application's color theme", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        OutputControlChartThemeCMB->setWhatsThis(QApplication::translate("nmfMainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Theme</span></p><p>This is the application's color theme. Changing this pulldown will set the application's color theme to one of several pre-defined color themes. Some themes may prove better for viewing by color-impaired individuals or for printing.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        LogDockWidget->setWindowTitle(QApplication::translate("nmfMainWindow", "Log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class nmfMainWindow: public Ui_nmfMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NMFMAINWINDOW_H
