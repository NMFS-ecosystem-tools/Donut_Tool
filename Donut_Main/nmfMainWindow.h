/**
 * @file nmfMainWindow.h
 * @brief GUI definition for the main nmfMainWindow Donut Tool Application class
 *
 * This file contains the Main Window Application class. All of the menu
 * interactions are done through this class.
 *
 * @copyright
 * Public Domain Notice\n
 *
 * National Oceanic And Atmospheric Administration\n\n
 *
 * This software is a "United States Government Work" under the terms of the
 * United States Copyright Act.  It was written as part of the author's official
 * duties as a United States Government employee/contractor and thus cannot be copyrighted.
 * This software is freely available to the public for use. The National Oceanic
 * And Atmospheric Administration and the U.S. Government have not placed any
 * restriction on its use or reproduction.  Although all reasonable efforts have
 * been taken to ensure the accuracy and reliability of the software and data,
 * the National Oceanic And Atmospheric Administration and the U.S. Government
 * do not and cannot warrant the performance or results that may be obtained
 * by using this software or data. The National Oceanic And Atmospheric
 * Administration and the U.S. Government disclaim all warranties, express
 * or implied, including warranties of performance, merchantability or fitness
 * for any particular purpose.\n\n
 *
 * Please cite the author(s) in any work or product based on this material.
 */

#ifndef NMFMAINWINDOW_H
#define NMFMAINWINDOW_H

//#include <nlopt.hpp>

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QSpinBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QTextEdit>
#include <QUiLoader>
#include <QWhatsThis>
#include <QWidget>

#include "nmfLogWidget.h"
#include "nmfUtilsStatistics.h"
#include "nmfStructsQt.h"
#include "nmfUtilsQt.h"

#include "nmfChartBar.h"
#include "nmfChartDonut.h"




#include "nmfSetupTab01.h"
#include "nmfSetupTab02.h"
#include "nmfSetupTab04.h"
#include "nmfSetupTab03.h"

#include <QtDataVisualization>
#include <QImage>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QUiLoader>


namespace Ui {
    class nmfMainWindow;
}


/**
 * @brief The Donut Tool Main Window
 *
 *
 */
class nmfMainWindow : public QMainWindow
{

    Q_OBJECT

    /*
     *  10 safe color to use: from colorbrewer2.org
     *  Red to Blue
     */
    QList<QColor> LINE_COLORS =
    {
        QColor(103,  0, 31),
        QColor(178, 24, 43),
        QColor(214, 96, 77),
        QColor(244,165,130),
        QColor(253,219,199),
        QColor(209,229,240),
        QColor(146,197,222),
        QColor( 67,147,195),
        QColor( 33,102,172),
        QColor(  5, 48, 97)
    };


private:
    Ui::nmfMainWindow* m_UI;

    QChart*        m_ChartWidget;
    QChartView*    m_ChartView2d;
    nmfLogger*     m_Logger;
    nmfLogWidget*  m_LogWidget;
    std::string    m_ProjectDir;
    std::string    m_ProjectName;
    std::string    m_ProjectSettingsConfig;
    int            m_SetupFontSize;
    QWidget*       m_NavigatorTreeWidget;
    QTreeWidget*   m_NavigatorTree;
    QDialog*       m_PreferencesDlg;
    QWidget*       m_PreferencesWidget;
    nmfSetup_Tab1* Setup_Tab1_ptr;
    nmfSetup_Tab2* Setup_Tab2_ptr;
    nmfSetup_Tab3* Setup_Tab3_ptr;
    nmfSetup_Tab4* Setup_Tab4_ptr;



    void        closeEvent(QCloseEvent *event);
    QTableView* findTableInFocus();
    QString     getCurrentStyle();
    void        initConnections();
    void        initGUIs();
//  void        initLogo();
    void        initNavigatorTree();
    void        initPostGuiConnections();
    void        initPreferencesDlg();
    void        loadGuis();
    bool        okSplashScreen();
    void        readSettings();
    void        readSettingsGuiOrientation(bool alsoResetPosition);
    bool        saveRankDataFile(QString filename);
    bool        saveScreenshot(QString &outputfile, QPixmap &pm);
    void        saveSettings();
    void        setupLogWidget();
    void        updateWindowTitle();

public:
    explicit nmfMainWindow(QWidget *parent = nullptr);
    ~nmfMainWindow();

public slots:
    void callback_LoadProject();
    void callback_NavigatorSelectionChanged();
    void callback_PreferencesSetStyleSheet(QString style);
    void callback_ProjectSaved();
    void callback_ReloadWidgets();
    void callback_SetupTabChanged(int tab);
    void callback_ShowOutputChart(
            QString Predator,
            std::vector<std::string> Species,
            std::vector<double> RPAData,
            std::vector<double> AiData,
            std::vector<double> NullSelectivityData);

    void menu_about();
    void menu_copy();
    void menu_clear();
    void menu_clearAll();
    void menu_deselectAll();
    void menu_layoutDefault();
    void menu_layoutMinimal();
    void menu_layoutOutput();
    void menu_layoutOutputEmbedded();
    void menu_paste();
    void menu_pasteAll();
    void menu_preferences();
    void menu_quit();
    void menu_screenShot();
    void menu_selectAll();
    void menu_whatsThis();
};

#endif // NMFMAINWINDOW_H
