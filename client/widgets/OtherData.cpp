#include "OtherData.h"
#include "ui_OtherData.h"
#include "Styles.h"

OtherData::OtherData(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::OtherData)
{
	ui->setupUi(this);

	connect(ui->inputEMail, &QLineEdit::textChanged, this, [this](){ update(true); });

	QFont font = Styles::font( Styles::Regular, 13 );
	QFont condensed = Styles::font( Styles::Condensed, 14 );
	
	ui->label->setFont( Styles::font( Styles::Regular, 13, QFont::DemiBold ) );
	ui->lblEMail->setFont( font );
	ui->lblNoForwarding->setFont( font );
	ui->labelEestiEe->setFont( Styles::font( Styles::Regular, 12 ) );
	ui->activate->setFont( condensed );
	ui->btnCheckEMail->setFont( condensed );
}

OtherData::~OtherData()
{
	delete ui;
}

void OtherData::update(bool activate, const QString &eMail)
{
	if(!eMail.isEmpty())
	{
		ui->btnCheckEMail->setVisible(false);
		ui->lblEMail->setVisible(true);
		ui->activateEMail->setVisible(false);

		ui->lblEMail->setText(QString("Teie @eesti.ee posti aadressid on suunatud e-postile <b>") + eMail + QString("</b>"));
	}
	else if(activate)
	{
		ui->btnCheckEMail->setVisible(false);
		ui->lblEMail->setVisible(false);
		ui->activateEMail->setVisible(true);

		if(ui->inputEMail->text().isEmpty())
		{
			ui->activate->setStyleSheet(
						"padding: 6px 9px;"
						"border: 1px;"
						"border-style: solid;"
						"border-radius: 2px;"
						"border-color: #50a7d2;"
						"background-color: #ffffff;"
						"color: #50a7d2;"
						"text-align: center;"
						);
			ui->activate->setCursor( Qt::ArrowCursor );
		}
		else
		{
			ui->activate->setStyleSheet(
						"padding: 6px 9px;"
						"border: 1px;"
						"border-style: solid;"
						"border-radius: 2px;"
						"border-color: #006eb5;"
						"background-color: #ffffff;"
						"color: #006eb5;"
						"text-align: center;"
						);
			ui->activate->setCursor( Qt::PointingHandCursor );
		}
	}
	else
	{
		ui->btnCheckEMail->setVisible(true);
		ui->lblEMail->setVisible(false);
		ui->activateEMail->setVisible(false);
	}
}

void OtherData::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}