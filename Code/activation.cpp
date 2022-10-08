#include "activation.h"
#include "ui_activation.h"

Activation::Activation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Activation)
{
    ui->setupUi(this);
    setFixedSize(800, 550);
}

Activation::~Activation()
{
    delete ui;
}

#include <cstdlib>
#include <cctype>
#include <fstream>
#include <Windows.h>
#include <QMessageBox>

QString keys[33] =
{
    "",
    "FJ82H-XT6CR-J8D7P-XQJJ2-GPDD4",
    "MRPKT-YTG23-K7D7T-X2JMM-QY7MG",
    "W82YF-2Q76Y-63HXB-FGJG9-GF7QX",
    "33PXH-7Y6KF-2VJC9-XBBR8-HVTHH",
    "YDRBP-3D83W-TY26F-D46B2-XCKRJ",
    "C29WB-22CC8-VJ326-GHFJW-H9DH4",
    "NG4HW-VH26C-733KW-K6F98-J8CK4",
    "XCVCF-2NXM9-723PB-MHCB7-2RYQQ",
    "32JNW-9KQ84-P47T8-D8GGY-CWCK7",
    "JMNMF-RHW7P-DMY6X-RF3DR-X2BQT",
    "GCRJD-8NW9H-F2CDX-CCM8D-9D6T9",
    "HMCNV-VVBFX-7HMBH-CTY9B-B4FXY",
    "MHF9N-XY6XB-WVXMC-BTDCT-MKKG7",
    "TT4HM-HN7YT-62K67-RGRQJ-JFFXW",
    "W269N-WFGWX-YVC9B-4J6C9-T83GX",
    "MH37W-N47XK-V7XM9-C7227-GCQG9",
    "NRG8B-VKK3Q-CXVCJ-9G2XF-6Q84J",
    "9FNHH-K3HBT-3W4TD-6383H-6XYWF",
    "6TP4R-GNPTD-KYYHQ-7B7DP-J447Y",
    "YVWGF-BXNMC-HTQYQ-CPQ99-66QFC",
    "NW6C2-QMPVW-D7KKK-3GKT6-VCFB2",
    "2WH4N-8QGBV-H22JP-CT43Q-MDWWJ",
    "NPPR9-FWDCX-D2C8J-H872K-2YT43",
    "DPH2V-TTNVB-4X9Q3-TJR4H-KHJW4",
    "YYVX9-NTFWV-6MDM3-9PT4T-4M68B",
    "44RPN-FTY23-9VTTB-MP9BX-T84FV",
    "WNMTR-4C88C-JK8YV-HQ7T2-76DF9",
    "2F77B-TNFGY-69QQF-B8YKP-D69TJ",
    "DCPHK-NFMTC-H88MJ-PFHPY-QJ4BJ",
    "QFFDN-GRT3P-VKWWX-X7T3R-8B639",
    "M7XTQ-FN8P6-TTKYV-9D4CC-J462D",
    "92NFX-8DJQP-P6BBQ-THF9C-7CG2H"
};

bool chkkey(QString s)
{
    if (s.size() != 29)
        return false;
    for (int i = 0; i < s.size(); i++)
        if ((i + 1) % 6 == 0)
        {
            if (s[i] != '-')
                return false;
        }
        else
        {
            if (!isalpha(s[i].toLatin1()) && !isdigit(s[i].toLatin1()))
                return false;
        }
    return true;
}

QString Activation::getkey()
{
    if (ui->windows_check->isChecked())
        return keys[ui->windows->currentIndex()];
    else
        return ui->input->text();
}

void Activation::on_activate_clicked()
{
    if (ui->windows_check->isChecked() && ui->windows->currentIndex() == 0)
        QMessageBox::critical(NULL, QString::fromStdWString(L"错误"), QString::fromStdWString(L"请选择Windows版本！"), QMessageBox::Ok, QMessageBox::Ok);
    else if (ui->input_check->isChecked() && !chkkey(ui->input->text()))
        QMessageBox::critical(NULL, QString::fromStdWString(L"错误"), QString::fromStdWString(L"密钥错误！"), QMessageBox::Ok, QMessageBox::Ok);
    else
    {
        std::ofstream out("activate.bat", std::ios::trunc);
        out << "@echo off\nslmgr.vbs /ipk " << getkey().toStdString() << "\nslmgr.vbs /skms " << ui->kms_server->text().toStdString() << "\nslmgr.vbs /ato\nalmgr.vbs /xpr\n";
        out.close();
        ShellExecute(NULL, L"runas", L"activate.bat", NULL, NULL, SW_SHOWNORMAL);
    }
}

bool flag = false;

void Activation::on_windows_check_stateChanged(int arg1)
{
    flag = !flag;
    ui->windows->setEnabled(arg1 == 2);
    if (flag)
    {
        ui->input_check->setChecked(arg1 != 2);
    }
}

void Activation::on_input_check_stateChanged(int arg1)
{
    flag = !flag;
    ui->input->setEnabled(arg1 == 2);
    if (flag)
    {
        ui->windows_check->setChecked(arg1 != 2);
    }
}

void Activation::on_activate_bar_triggered()
{
    on_activate_clicked();
}

void Activation::on_exit_triggered()
{
    exit(0);
}

void Activation::on_contact_triggered()
{
    ShellExecute(NULL, L"open", L"tencent://message?uin=191039275", NULL, NULL, SW_SHOWNORMAL);
}

void Activation::on_about_triggered()
{
    QMessageBox::information(NULL, QString::fromStdWString(L"关于"), QString::fromStdWString(L"KMS-Activator\nBy HeYC\n版本：2.1/Build 2203"));
}
