/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *transactionsTable;
    QLabel *invalidRowSelectedMsg;
    QPushButton *loadAllTransactionsButton;
    QPushButton *editTransactionRowButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *memberIDField;
    QPushButton *showSalesByMemberIDButton;
    QPushButton *showSalesButton;
    QLabel *salesDateLabel;
    QDateEdit *salesDateInputField;
    QWidget *tab_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *itemNameLabel;
    QLineEdit *itemNameField;
    QLabel *itemPriceLabel;
    QLineEdit *itemPriceField;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *deleteItemButton;
    QPushButton *addItemButton;
    QTableWidget *itemsTable;
    QLabel *itemNameLabel_3;
    QPushButton *displayAllButton;
    QLabel *itemNameLabel_4;
    QPushButton *sortItemsByButton;
    QComboBox *sortItemsByField;
    QLineEdit *searchItemBox;
    QPushButton *searchButton;
    QWidget *customersPage;
    QTableWidget *customersTable;
    QPushButton *loadAllCustomersButton;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *monthSelectBox;
    QPushButton *displayExpiringMembershipsButton;
    QPushButton *showChangeMemberStatus;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(811, 467);
        MainWindow->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"    color: #eff0f1;\n"
"    background-color: #31363b;\n"
"    selection-background-color:#3daee9;\n"
"    selection-color: #eff0f1;\n"
"    background-clip: border;\n"
"    border-image: none;\n"
"    border: 0px transparent black;\n"
"    outline: 0;\n"
"}\n"
"\n"
"QWidget:item:selected\n"
"{\n"
"    background-color: #18465d;\n"
"}\n"
"\n"
"QTableCornerButton::section {\n"
"    background-color: #31363b;\n"
"    border: 1px transparent #76797C;\n"
"    border-radius: 0px;\n"
"}\n"
"\n"
"QTableWidget {\n"
"border: 1px solid #6A6969;\n"
"}\n"
"\n"
"QComboBox\n"
"{\n"
"    selection-background-color: #3daee9;\n"
"    border-style: solid;\n"
"    border: 1px solid #76797C;\n"
"    border-radius: 2px;\n"
"    padding: 5px;\n"
"    min-width: 75px;\n"
"}\n"
"\n"
"QPushButton:checked{\n"
"    background-color: #76797C;\n"
"    border-color: #6A6969;\n"
"}\n"
"\n"
"\n"
"\n"
"QMenuBar\n"
"{\n"
"    background-color: #31363b;\n"
"    color: #eff0f1;\n"
"}\n"
"\n"
"QMenuBar::item\n"
"{\n"
"    backgr"
                        "ound: transparent;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"border: 2px solid #3daee9;\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"    background-color: #232629;\n"
"    padding: 5px;\n"
"    border-style: solid;\n"
"    border: 1px solid #76797C;\n"
"    border-radius: 2px;\n"
"    color: #eff0f1;\n"
"}\n"
"\n"
"\n"
"\n"
"QHeaderView::section\n"
"{\n"
"    background-color: #76797C;\n"
"    color: #eff0f1;\n"
"    padding: 5px;\n"
"    border: 1px solid #76797C;\n"
"}\n"
"\n"
"\n"
"QStackedWidget\n"
"{\n"
"    border: 1px transparent black;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"    color: #eff0f1;\n"
"    background-color: #31363b;\n"
"    border-width: 1px;\n"
"    border-color: #76797C;\n"
"    border-style: solid;\n"
"    padding: 5px;\n"
"    border-radius: 2px;\n"
"    outline: none;\n"
"}\n"
"\n"
"\n"
"QPushButton:focus {\n"
"    background-color: #3daee9;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: #3daee9;\n"
"    padding-top: -15px;\n"
"    padding-bottom: -17px;\n"
"}\n"
""
                        "\n"
"QComboBox\n"
"{\n"
"    selection-background-color: #3daee9;\n"
"    border-style: solid;\n"
"    border: 1px solid #76797C;\n"
"    border-radius: 2px;\n"
"    padding: 5px;\n"
"    min-width: 75px;\n"
"}\n"
"\n"
"QPushButton:checked{\n"
"    background-color: #76797C;\n"
"    border-color: #6A6969;\n"
"}\n"
"\n"
"QComboBox:hover,QPushButton:hover,QAbstractSpinBox:hover,QLineEdit:hover\n"
"{\n"
"    border: 1px solid #3daee9;\n"
"    color: #eff0f1;\n"
"}\n"
"\n"
"QComboBox:on\n"
"{\n"
"    padding-top: 3px;\n"
"    padding-left: 4px;\n"
"    selection-background-color: #4a4a4a;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView\n"
"{\n"
"    background-color: #232629;\n"
"    border-radius: 2px;\n"
"    border: 1px solid #76797C;\n"
"    selection-background-color: #18465d;\n"
"}\n"
"\n"
"QComboBox::drop-down\n"
"{\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 15px;\n"
"\n"
"    border-left-width: 0px;\n"
"    border-left-color: darkgray;\n"
"    border-left-style: s"
                        "olid;\n"
"    border-top-right-radius: 3px;\n"
"    border-bottom-right-radius: 3px;\n"
"}\n"
"\n"
"\n"
"QAbstractSpinBox {\n"
"    padding: 5px;\n"
"    border: 1px solid #76797C;\n"
"    background-color: #232629;\n"
"    color: #eff0f1;\n"
"    border-radius: 2px;\n"
"    min-width: 75px;\n"
"}\n"
"\n"
"QAbstractSpinBox:up-button\n"
"{\n"
"    background-color: transparent;\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: center right;\n"
"}\n"
"\n"
"QAbstractSpinBox:down-button\n"
"{\n"
"    background-color: transparent;\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: center left;\n"
"}\n"
"\n"
"\n"
"QLabel\n"
"{\n"
"    border: 0px solid black;\n"
"}\n"
"\n"
"QTabWidget{\n"
"    border: 0px transparent black;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #76797C;\n"
"    padding: 5px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    left: 5px; /* move tab bar to the right by 5px */\n"
"}\n"
"\n"
"\n"
"\n"
"QTabBar::tab:top {\n"
"    color: #ef"
                        "f0f1;\n"
"    border: 1px solid #76797C;\n"
"    border-bottom: 1px transparent black;\n"
"    background-color: #31363b;\n"
"    padding: 5px;\n"
"    min-width: 50px;\n"
"    border-top-left-radius: 2px;\n"
"    border-top-right-radius: 2px;\n"
"}\n"
"\n"
"QTabBar::tab:top:!selected\n"
"{\n"
"    color: #eff0f1;\n"
"    background-color: #54575B;\n"
"    border: 1px solid #76797C;\n"
"    border-bottom: 1px transparent black;\n"
"    border-top-left-radius: 2px;\n"
"    border-top-right-radius: 2px;    \n"
"}\n"
"\n"
"QTabBar::tab:top:!selected:hover {\n"
"    background-color: #3daee9;\n"
"}\n"
"\n"
"QHeaderView\n"
"{\n"
"    background-color: #31363b;\n"
"    border: 1px transparent;\n"
"    border-radius: 0px;\n"
"    margin: 0px;\n"
"    padding: 0px;\n"
"\n"
"}\n"
"\n"
"QHeaderView::section  {\n"
"    background-color: #31363b;\n"
"    color: #eff0f1;\n"
"    padding: 5px;\n"
"    border: 1px solid #76797C;\n"
"    border-radius: 0px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"\n"
""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 811, 431));
        tabWidget->setStyleSheet(QStringLiteral(""));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        transactionsTable = new QTableWidget(tab);
        transactionsTable->setObjectName(QStringLiteral("transactionsTable"));
        transactionsTable->setGeometry(QRect(30, 50, 741, 291));
        invalidRowSelectedMsg = new QLabel(tab);
        invalidRowSelectedMsg->setObjectName(QStringLiteral("invalidRowSelectedMsg"));
        invalidRowSelectedMsg->setGeometry(QRect(470, 360, 211, 20));
        invalidRowSelectedMsg->setStyleSheet(QLatin1String("QLabel {\n"
"color:red\n"
"};"));
        loadAllTransactionsButton = new QPushButton(tab);
        loadAllTransactionsButton->setObjectName(QStringLiteral("loadAllTransactionsButton"));
        loadAllTransactionsButton->setGeometry(QRect(51, 348, 173, 41));
        editTransactionRowButton = new QPushButton(tab);
        editTransactionRowButton->setObjectName(QStringLiteral("editTransactionRowButton"));
        editTransactionRowButton->setGeometry(QRect(270, 348, 173, 41));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 2, 291, 41));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        memberIDField = new QSpinBox(layoutWidget);
        memberIDField->setObjectName(QStringLiteral("memberIDField"));

        horizontalLayout_3->addWidget(memberIDField);

        showSalesByMemberIDButton = new QPushButton(layoutWidget);
        showSalesByMemberIDButton->setObjectName(QStringLiteral("showSalesByMemberIDButton"));

        horizontalLayout_3->addWidget(showSalesByMemberIDButton);

        showSalesButton = new QPushButton(tab);
        showSalesButton->setObjectName(QStringLiteral("showSalesButton"));
        showSalesButton->setGeometry(QRect(651, 5, 82, 28));
        salesDateLabel = new QLabel(tab);
        salesDateLabel->setObjectName(QStringLiteral("salesDateLabel"));
        salesDateLabel->setGeometry(QRect(430, 10, 64, 16));
        salesDateInputField = new QDateEdit(tab);
        salesDateInputField->setObjectName(QStringLiteral("salesDateInputField"));
        salesDateInputField->setGeometry(QRect(512, 0, 121, 30));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 10, 253, 162));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        itemNameLabel = new QLabel(layoutWidget1);
        itemNameLabel->setObjectName(QStringLiteral("itemNameLabel"));

        verticalLayout_2->addWidget(itemNameLabel);

        itemNameField = new QLineEdit(layoutWidget1);
        itemNameField->setObjectName(QStringLiteral("itemNameField"));

        verticalLayout_2->addWidget(itemNameField);

        itemPriceLabel = new QLabel(layoutWidget1);
        itemPriceLabel->setObjectName(QStringLiteral("itemPriceLabel"));

        verticalLayout_2->addWidget(itemPriceLabel);

        itemPriceField = new QLineEdit(layoutWidget1);
        itemPriceField->setObjectName(QStringLiteral("itemPriceField"));

        verticalLayout_2->addWidget(itemPriceField);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        deleteItemButton = new QPushButton(layoutWidget1);
        deleteItemButton->setObjectName(QStringLiteral("deleteItemButton"));

        horizontalLayout_2->addWidget(deleteItemButton);

        addItemButton = new QPushButton(layoutWidget1);
        addItemButton->setObjectName(QStringLiteral("addItemButton"));

        horizontalLayout_2->addWidget(addItemButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        itemsTable = new QTableWidget(tab_2);
        itemsTable->setObjectName(QStringLiteral("itemsTable"));
        itemsTable->setGeometry(QRect(290, 60, 481, 311));
        itemNameLabel_3 = new QLabel(tab_2);
        itemNameLabel_3->setObjectName(QStringLiteral("itemNameLabel_3"));
        itemNameLabel_3->setGeometry(QRect(20, 240, 247, 16));
        displayAllButton = new QPushButton(tab_2);
        displayAllButton->setObjectName(QStringLiteral("displayAllButton"));
        displayAllButton->setGeometry(QRect(150, 310, 117, 28));
        itemNameLabel_4 = new QLabel(tab_2);
        itemNameLabel_4->setObjectName(QStringLiteral("itemNameLabel_4"));
        itemNameLabel_4->setGeometry(QRect(530, 0, 51, 20));
        sortItemsByButton = new QPushButton(tab_2);
        sortItemsByButton->setObjectName(QStringLiteral("sortItemsByButton"));
        sortItemsByButton->setGeometry(QRect(690, 20, 71, 28));
        sortItemsByField = new QComboBox(tab_2);
        sortItemsByField->setObjectName(QStringLiteral("sortItemsByField"));
        sortItemsByField->setGeometry(QRect(530, 20, 148, 30));
        searchItemBox = new QLineEdit(tab_2);
        searchItemBox->setObjectName(QStringLiteral("searchItemBox"));
        searchItemBox->setGeometry(QRect(20, 270, 247, 30));
        searchButton = new QPushButton(tab_2);
        searchButton->setObjectName(QStringLiteral("searchButton"));
        searchButton->setGeometry(QRect(20, 310, 117, 28));
        tabWidget->addTab(tab_2, QString());
        customersPage = new QWidget();
        customersPage->setObjectName(QStringLiteral("customersPage"));
        customersTable = new QTableWidget(customersPage);
        customersTable->setObjectName(QStringLiteral("customersTable"));
        customersTable->setGeometry(QRect(20, 60, 751, 261));
        loadAllCustomersButton = new QPushButton(customersPage);
        loadAllCustomersButton->setObjectName(QStringLiteral("loadAllCustomersButton"));
        loadAllCustomersButton->setGeometry(QRect(60, 340, 161, 41));
        layoutWidget2 = new QWidget(customersPage);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 10, 491, 32));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        monthSelectBox = new QComboBox(layoutWidget2);
        monthSelectBox->setObjectName(QStringLiteral("monthSelectBox"));

        horizontalLayout_4->addWidget(monthSelectBox);

        displayExpiringMembershipsButton = new QPushButton(layoutWidget2);
        displayExpiringMembershipsButton->setObjectName(QStringLiteral("displayExpiringMembershipsButton"));

        horizontalLayout_4->addWidget(displayExpiringMembershipsButton);

        showChangeMemberStatus = new QPushButton(customersPage);
        showChangeMemberStatus->setObjectName(QStringLiteral("showChangeMemberStatus"));
        showChangeMemberStatus->setGeometry(QRect(520, 10, 191, 31));
        tabWidget->addTab(customersPage, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 811, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Admin CP", Q_NULLPTR));
        invalidRowSelectedMsg->setText(QString());
        loadAllTransactionsButton->setText(QApplication::translate("MainWindow", "Load All Transactions", Q_NULLPTR));
        editTransactionRowButton->setText(QApplication::translate("MainWindow", "Edit Selected Row", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Customer ID:", Q_NULLPTR));
        showSalesByMemberIDButton->setText(QApplication::translate("MainWindow", "Show Sales", Q_NULLPTR));
        showSalesButton->setText(QApplication::translate("MainWindow", "Show Sales", Q_NULLPTR));
        salesDateLabel->setText(QApplication::translate("MainWindow", "Sales Day:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Transactions", Q_NULLPTR));
        itemNameLabel->setText(QApplication::translate("MainWindow", "Item Name:", Q_NULLPTR));
        itemPriceLabel->setText(QApplication::translate("MainWindow", "Item Price:", Q_NULLPTR));
        deleteItemButton->setText(QApplication::translate("MainWindow", "Delete Item", Q_NULLPTR));
        addItemButton->setText(QApplication::translate("MainWindow", "Add Item", Q_NULLPTR));
        itemNameLabel_3->setText(QApplication::translate("MainWindow", "Item Name:", Q_NULLPTR));
        displayAllButton->setText(QApplication::translate("MainWindow", "Display All", Q_NULLPTR));
        itemNameLabel_4->setText(QApplication::translate("MainWindow", "Sort by:", Q_NULLPTR));
        sortItemsByButton->setText(QApplication::translate("MainWindow", "Show", Q_NULLPTR));
        sortItemsByField->clear();
        sortItemsByField->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", " Item Name (A - Z)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Item Name (Z - A)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Item Price (Low - High)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Item Price (High - Low)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Quantity Sold (Low - High)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Quantity Sold (High - Low)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Total Revenue (Low - High)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Total Revenue (High - Low)", Q_NULLPTR)
        );
        searchButton->setText(QApplication::translate("MainWindow", "Search for Item", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Items", Q_NULLPTR));
        loadAllCustomersButton->setText(QApplication::translate("MainWindow", "Load All Customers", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Search by Expiration Month:", Q_NULLPTR));
        monthSelectBox->clear();
        monthSelectBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "(01) January ", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(02) February", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(03) March", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(04) April", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(05) May", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(06) June", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(07) July", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(08) August", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(09) September", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(10) October", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(11) November", Q_NULLPTR)
         << QApplication::translate("MainWindow", "(12) December", Q_NULLPTR)
        );
        displayExpiringMembershipsButton->setText(QApplication::translate("MainWindow", "Show", Q_NULLPTR));
        showChangeMemberStatus->setText(QApplication::translate("MainWindow", "Show Change Member Status", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(customersPage), QApplication::translate("MainWindow", "Customers", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
