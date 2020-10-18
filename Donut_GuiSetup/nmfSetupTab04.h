/**
 * @file nmfSetupTab04.h
 * @brief GUI definition for the Setup Model page class nmfSetup_Tab4
 *
 * This file contains the GUI definitions for the Run Model page. This
 * page contains the GUI widgets that allow the user to enter and modify
 * Rank data associated with the prey species of the currently selected predator.
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

#ifndef NMFSETUPTAB4_H
#define NMFSETUPTAB4_H

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QHeaderView>
#include <QLabel>
#include <QLine>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QTabWidget>
#include <QTableView>
#include <QTextEdit>
#include <QUiLoader>
#include <QWidget>

#include <set>

#include "nmfLogger.h"
#include "nmfDonutModelAPI.h"

/**
 * @brief The Setup Tab 4 allows the user to enter and modify general System and Model Setup data
 *
 * This tab allows the user to define a System which contains data related to the
 * current model such as run length, year range, and model form.
 */
class nmfSetup_Tab4: public QObject
{
    Q_OBJECT

    std::string  m_ProjectDir;
    std::string  m_ProjectSettingsConfig;
    std::string  m_ProjectName;
    nmfLogger*   m_logger;
    QDialog      m_loadDlg;
    QPushButton* m_cancelBtn;
    QPushButton* m_okBtn;
    std::vector<std::string> m_ModelPresetNames;
    std::map<std::string,std::vector<std::string> > m_ModelPresets;
    std::map<QString,QStringList> m_PredatorMap;
    QStringList  m_EstimatedParameters;
    QStringList  m_FieldsSpecies;
    QStringList  m_FieldsRank;
    QStringList  m_FieldsProportion;
    QStringList  m_FieldsNullAmbient;
    int          m_LastSliderValue;
    nmfDonutModelAPI m_DonutModelAPI;

    QTabWidget*  Setup_Tabs;
    QTableView*  Setup_Tab4_DataTV;
    QSlider*     Setup_Tab4_DataSL;
    QPushButton* Setup_Tab4_RunPB;
    QComboBox*   Setup_Tab4_PredatorCMB;
    QLabel*      Setup_Tab4_ModelPresetsLBL;
    QPushButton* Setup_Tab4_GrowthHighlightPB;
    QPushButton* Setup_Tab4_HarvestHighlightPB;
    QPushButton* Setup_Tab4_PredationHighlightPB;
    QPushButton* Setup_Tab4_CompetitionHighlightPB;
    QPushButton* Setup_Tab4_CalcPB;
    QComboBox*   Setup_Tab4_FontSizeCMB;
    QComboBox*   Setup_Tab4_ModelPresetsCMB;
    QComboBox*   Setup_Tab4_GrowthFormCMB;
    QComboBox*   Setup_Tab4_PredationFormCMB;
    QComboBox*   Setup_Tab4_HarvestFormCMB;
    QComboBox*   Setup_Tab4_CompetitionFormCMB;
    QTextEdit*   SetupOutputTE;
    QLineEdit*   Setup_Tab4_SystemNameLE;
    QLineEdit*   Setup_Tab4_SystemCarryingCapacityLE;
    QTextEdit*   Setup_Tab4_ModelEquationTE;
    QWidget*     Setup_Tab4_Widget;
    QPushButton* Setup_Tab4_SavePB;
    QPushButton* Setup_Tab4_LoadPB;
    QPushButton* Setup_Tab4_DelPB;
    QPushButton* Setup_Tab4_PrevPB;
    QPushButton* Setup_Tab4_NewSystemPB;
    QSpinBox*    Setup_Tab4_NumberOfRunsSB;
    QSpinBox*    Setup_Tab4_StartYearSB;
    QLineEdit*   Setup_Tab4_EndYearLE;
    QSpinBox*    Setup_Tab4_RunLengthSB;
    QScrollArea* Setup_Tab4_ScrollAreaSA;
    QTextEdit*   Setup_Tab4_NotesTE;
    QFrame*      Setup_Tab4_PreyLN;
    QLabel*      Setup_Tab4_PreyLBL;
    QLabel*      Setup_Tab4_RankLBL;
    QLabel*      Setup_Tab4_ProportionLBL;
    QLabel*      Setup_Tab4_OutputMatrixLBL;

    void   adjustLine();
    void   clearWidgets();
    QString getCurrentPredator();
    void   getHighlightColors(QString& growthHighlightColor,
                            QString& harvestHighlightColor,
                            QString& competitionHighlightColor,
                            QString& predationHighlightColor,
                            QString& growthColorName,
                            QString& harvestColorName,
                            QString& competitionColorName,
                            QString& predationColorName);
    void loadDefaultValues();
    void loadPredatorNamesAndMap();
    bool loadRankData();
    void loadSystem();
    void readSettings();
    bool runDataChecks();
    void saveRankData();
    void saveSettings();
    bool saveSettingsConfiguration(bool verbose,
                                   std::string CurrentSettingsName);
    void setEstimatedParameterNames();
    void setModelName(std::string modelName);
    void setCurrentPredator(QString species);
    void shadeTable(QStandardItemModel* smodel);
    bool systemFileExists(QString SystemName);
    void updateOutputWidget();

public:
    /**
     * @brief nmfSetup_Tab4 : class constructor
     * @param tabs : the tab widget into which this Setup tab will be placed
     * @param logger : pointer to the application logger
     * @param projectDir : the project directory
     */
    nmfSetup_Tab4(QTabWidget*  tabs,
                  nmfLogger*   logger,
                  std::string& projectDir);
    virtual ~nmfSetup_Tab4();

    /**
     * @brief Load all widgets for this Setup GUI page
     */
    void loadWidgets();
    /**
     * @brief Sets the Rank table background colors appropriately if the user changes
     * the light/dark style preference.
     */
    void resetTableBackgroundColors();

signals:
    /**
     * @brief Signal emitted when the user wants to generate a plot of the current output data
     * @param Predator : current predator name
     * @param Species : list of all prey species associated with the current predator
     * @param RPAData : vector of RPA Model percentage values
     * @param AiData : vector of Relative Abundance (Null Ambient) percentage values
     * @param NullSelectivityData : vector of Null Selectivity percentage values
     */
    void ShowOutputChart(
            QString Predator,
            std::vector<std::string> Species,
            std::vector<double> RPAData,
            std::vector<double> AiData,
            std::vector<double> NullSelectivityData);

public Q_SLOTS:
    /**
     * @brief Callback invoked when the user modifies the table slider used
     * to both change an overlap field and then to update the corresponding chart.
     * @param value : current value of the slider being moved
     */
    void callback_DataSL(int value);
    /**
     * @brief Callback invoked when the user releases the table slider used
     * to both change an overlap field and then to update the corresponding chart.
     */
    void callback_DataReleasedSL();
    /**
     * @brief Callback invoked when the user clicks the Load Settings button
     */
    void callback_LoadPB();
    /**
     * @brief Callback invoked when the user changes the predator combo box
     * @param predatorName : name of the currently displayed predator
     */
    void callback_PredatorCMB(QString predatorName);
    /**
     * @brief Callback invoked when the user clicks the Previous Page button
     */
    void callback_PrevPB();
    /**
     * @brief Callback invoked when the user needs to reload the rank matrix. This
     * may happen when the user modifies some species attribute or interaction.
     */
    void callback_Reload();
    /**
     * @brief Callback invoked when the user clicks the Run button
     */
    void callback_RunPB();
    /**
     * @brief Callback invoked when the user clicks the Save button
     */
    void callback_SavePB();
//  void callback_TableChanged(QModelIndex unused1, QModelIndex unused2, QVector<int> unused3);
    /**
     * @brief Redraws the chart with the type specified by the passed in argument
     * @param type : type of chart to display
     */
    void callback_TypeCMB(QString type);

};

#endif // NMFSETUPTAB3_H
