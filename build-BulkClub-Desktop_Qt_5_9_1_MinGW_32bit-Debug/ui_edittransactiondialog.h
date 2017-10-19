/********************************************************************************
** Form generated from reading UI file 'edittransactiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTRANSACTIONDIALOG_H
#define UI_EDITTRANSACTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditTransactionDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QSpinBox *customerIDField;
    QLineEdit *itemPurchasedField;
    QSpinBox *quantityPurchasedField;
    QLineEdit *datePurchasedField;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cancelEditTransactionButton;
    QPushButton *saveTransactionButton;

    void setupUi(QDialog *EditTransactionDialog)
    {
        if (EditTransactionDialog->objectName().isEmpty())
            EditTransactionDialog->setObjectName(QStringLiteral("EditTransactionDialog"));
        EditTransactionDialog->resize(400, 243);
        layoutWidget = new QWidget(EditTransactionDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 12, 341, 171));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        customerIDField = new QSpinBox(layoutWidget);
        customerIDField->setObjectName(QStringLiteral("customerIDField"));

        verticalLayout_2->addWidget(customerIDField);

        itemPurchasedField = new QLineEdit(layoutWidget);
        itemPurchasedField->setObjectName(QStringLiteral("itemPurchasedField"));

        verticalLayout_2->addWidget(itemPurchasedField);

        quantityPurchasedField = new QSpinBox(layoutWidget);
        quantityPurchasedField->setObjectName(QStringLiteral("quantityPurchasedField"));

        verticalLayout_2->addWidget(quantityPurchasedField);

        datePurchasedField = new QLineEdit(layoutWidget);
        datePurchasedField->setObjectName(QStringLiteral("datePurchasedField"));

        verticalLayout_2->addWidget(datePurchasedField);


        horizontalLayout->addLayout(verticalLayout_2);

        layoutWidget1 = new QWidget(EditTransactionDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(60, 200, 291, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        cancelEditTransactionButton = new QPushButton(layoutWidget1);
        cancelEditTransactionButton->setObjectName(QStringLiteral("cancelEditTransactionButton"));

        horizontalLayout_2->addWidget(cancelEditTransactionButton);

        saveTransactionButton = new QPushButton(layoutWidget1);
        saveTransactionButton->setObjectName(QStringLiteral("saveTransactionButton"));

        horizontalLayout_2->addWidget(saveTransactionButton);


        retranslateUi(EditTransactionDialog);

        QMetaObject::connectSlotsByName(EditTransactionDialog);
    } // setupUi

    void retranslateUi(QDialog *EditTransactionDialog)
    {
        EditTransactionDialog->setWindowTitle(QApplication::translate("EditTransactionDialog", "Edit Transaction", Q_NULLPTR));
        label->setText(QApplication::translate("EditTransactionDialog", "Customer ID:", Q_NULLPTR));
        label_2->setText(QApplication::translate("EditTransactionDialog", "Item Purchased:", Q_NULLPTR));
        label_3->setText(QApplication::translate("EditTransactionDialog", "Item Quantity:", Q_NULLPTR));
        label_4->setText(QApplication::translate("EditTransactionDialog", "Date Purchased:", Q_NULLPTR));
        cancelEditTransactionButton->setText(QApplication::translate("EditTransactionDialog", "Cancel", Q_NULLPTR));
        saveTransactionButton->setText(QApplication::translate("EditTransactionDialog", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EditTransactionDialog: public Ui_EditTransactionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTRANSACTIONDIALOG_H
