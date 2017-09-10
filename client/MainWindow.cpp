/*
 * QDigiDoc4
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ContainerState.h"
#include "Styles.h"
#include "widgets/FadeInNotification.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    QFont openSansReg13 = Styles::instance().font(Styles::OpenSansRegular, 13);
    QFont openSansReg14 = Styles::instance().font(Styles::OpenSansRegular, 14);
    QFont openSansReg16 = Styles::instance().font(Styles::OpenSansRegular, 16);
    QFont openSansReg20 = Styles::instance().font(Styles::OpenSansRegular, 20);
    QFont openSansSBold14 = Styles::instance().font(Styles::OpenSansSemiBold, 14);

    ui->setupUi(this);
    
    ui->signature->init( "ALLKIRI", PageIcon::Style { openSansSBold14, "/images/sign_dark_38x38.png", "#ffffff", "#998B66" },
        PageIcon::Style { openSansReg14, "/images/sign_light_38x38.png", "#023664", "#ffffff" }, true );
    ui->crypto->init( "KRÜPTO", PageIcon::Style { openSansSBold14, "/images/crypto_dark_38x38.png", "#ffffff", "#998B66" },
        PageIcon::Style { openSansReg14, "/images/crypto_light_38x38.png", "#023664", "#ffffff" }, false );
    ui->myEid->init("MINU eID", PageIcon::Style { openSansSBold14, "/images/my_eid_dark_38x38.png", "#ffffff", "#998B66" },
        PageIcon::Style { openSansReg14, "/images/my_eid_light_38x38.png", "#023664", "#ffffff" }, false );

    ui->cardInfo->update("MARI MAASIKAS", "4845050123", "Lugejas on ID kaart");

    connect( ui->signature, &PageIcon::activated, this, &MainWindow::pageSelected );
    connect( ui->crypto, &PageIcon::activated, this, &MainWindow::pageSelected );
    connect( ui->myEid, &PageIcon::activated, this, &MainWindow::pageSelected );
    
    buttonGroup = new QButtonGroup( this );
   	buttonGroup->addButton( ui->help, HeadHelp );
   	buttonGroup->addButton( ui->settings, HeadSettings );

    ui->signIntroLabel->setFont(openSansReg20);
    ui->signIntroButton->setFont(openSansReg16);
    ui->cryptoIntroLabel->setFont(openSansReg20);
    ui->cryptoIntroButton->setFont(openSansReg16);
    
    ui->help->setFont(openSansReg13);
    ui->settings->setFont(openSansReg13);

    connect( ui->signIntroButton, &QPushButton::clicked, [this]() { navigateToPage(SignDetails); } );
    connect( ui->cryptoIntroButton, &QPushButton::clicked, [this]() { navigateToPage(CryptoDetails); } );
    connect( buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &MainWindow::buttonClicked );
    connect( ui->signContainerPage, &ContainerPage::action, this, &MainWindow::onAction );

    ui->infoStack->update(
                "MARI",
                "MAASIKAS",
                "48405051234",
                "EESTI",
                "IK1234567",
                "<span style='color: #37a447'>Kehtiv</span> kuni 10.10.2019",
                "Kontrolli sertifikaate"
                        );

    ui->accordion->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pageSelected( PageIcon *const page )
{
    if( page != ui->signature )
    {
        ui->signature->select(false);
    } 
    else
    {
        navigateToPage(SignIntro);
    }
    if( page != ui->crypto )
    {
        ui->crypto->select(false);
    }
    else
    {
        navigateToPage(CryptoIntro);
    }
    if( page != ui->myEid )
    {
        ui->myEid->select(false);
    }
    else
    {
        navigateToPage(MyEid);
    }
}

void MainWindow::buttonClicked( int button )
{
    switch( button )
    {
    case HeadHelp:
        //QDesktopServices::openUrl( QUrl( Common::helpUrl() ) );
        QMessageBox::warning( this, "DigiDoc4 client", "Not implemented yet");
        break;
    case HeadSettings:
        // qApp->showSettings();
        QMessageBox::warning( this, "DigiDoc4 client", "Not implemented yet");
        break;
    default: break;
    }
}

void MainWindow::navigateToPage( Pages page )
{
    ui->startScreen->setCurrentIndex(page);

    if ( page == SignDetails)
    {
        ui->signContainerPage->transition(ContainerState::UnsignedContainer);
    }
}

void MainWindow::onAction( const QString &action )
{
    if( "#mainAction" == action )
    {
        ui->signContainerPage->transition(ContainerState::SignedContainer);

        FadeInNotification* notification = new FadeInNotification(this, "#ffffff", "#53c964");
        notification->start(750, 1500, 600);
    }
    else if( action == "#remove" )
    {

    }
}
