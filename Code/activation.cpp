#include "activation.h"
#include "ui_activation.h"

#include <QSettings>
#include <QMessageBox>

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
#include <string>
#include <fstream>
#include <Windows.h>
#include <QMessageBox>
using namespace std;

QString keys[33] =
{
    "",
    "FJ82H-XT6CR-J8D7P-XQJJ2-GPDD4",//w7pro
    "33PXH-7Y6KF-2VJC9-XBBR8-HVTHH",//w7ent
    "NG4HW-VH26C-733KW-K6F98-J8CK4",//w8pro
    "32JNW-9KQ84-P47T8-D8GGY-CWCK7",//w8ent
    "GCRJD-8NW9H-F2CDX-CCM8D-9D6T9",//w8.1pro
    "MHF9N-XY6XB-WVXMC-BTDCT-MKKG7",//w8.1ent
    "W269N-WFGWX-YVC9B-4J6C9-T83GX",//w10pro
    "NRG8B-VKK3Q-CXVCJ-9G2XF-6Q84J",//w10proworkstation
    "6TP4R-GNPTD-KYYHQ-7B7DP-J447Y",//w10proedu
    "NW6C2-QMPVW-D7KKK-3GKT6-VCFB2",//w10edu
    "NPPR9-FWDCX-D2C8J-H872K-2YT43",//w10ent
    "WNMTR-4C88C-JK8YV-HQ7T2-76DF9",//w10ent-ltsb2015
    "DCPHK-NFMTC-H88MJ-PFHPY-QJ4BJ",//w10ent-ltsb2016
    "M7XTQ-FN8P6-TTKYV-9D4CC-J462D",//w10ent-ltsc2019/ltsc2021
    "MRPKT-YTG23-K7D7T-X2JMM-QY7MG",//w7proN
    "W82YF-2Q76Y-63HXB-FGJG9-GF7QX",//w7proE
    "YDRBP-3D83W-TY26F-D46B2-XCKRJ",//w7entN
    "C29WB-22CC8-VJ326-GHFJW-H9DH4",//w7entE
    "XCVCF-2NXM9-723PB-MHCB7-2RYQQ",//w8proN
    "JMNMF-RHW7P-DMY6X-RF3DR-X2BQT",//w8entN
    "HMCNV-VVBFX-7HMBH-CTY9B-B4FXY",//w8.1proN
    "TT4HM-HN7YT-62K67-RGRQJ-JFFXW",//w8.1entN
    "MH37W-N47XK-V7XM9-C7227-GCQG9",//w10proN
    "9FNHH-K3HBT-3W4TD-6383H-6XYWF",//w10proworkstationN
    "YVWGF-BXNMC-HTQYQ-CPQ99-66QFC",//w10proeduN
    "2WH4N-8QGBV-H22JP-CT43Q-MDWWJ",//w10eduN
    "DPH2V-TTNVB-4X9Q3-TJR4H-KHJW4",//w10entN
    "YYVX9-NTFWV-6MDM3-9PT4T-4M68B",//w10entG
    "44RPN-FTY23-9VTTB-MP9BX-T84FV",//w10entGN
    "2F77B-TNFGY-69QQF-B8YKP-D69TJ",//w10entN-ltsb2015
    "QFFDN-GRT3P-VKWWX-X7T3R-8B639",//w10entN-ltsb2016
    "92NFX-8DJQP-P6BBQ-THF9C-7CG2H" //w10entN-ltsc2019/ltsc2021
};

struct OS
{
    const int _10 = 1, _8_1 = 2, _8 = 4, _7 = 8;
    const int Pro = 1, Enterprise = 2, Education = 4, Workstation = 8, LTSC = 16, LTSB = 32;
    string str;
    int sys = 0, ver = 0;
    OS(){};
    OS(string system)
    {
        str = system;

        if (system.find("10") != system.npos || system.find("11") != system.npos)
            sys += _10;
        if (system.find("8.1") != system.npos)
            sys += _8_1;
        if (system.find("8") != system.npos)
            sys += _8;
        if (system.find("7") != system.npos)
            sys += _7;

        if (system.find("Pro") != system.npos)
            ver += Pro;
        if (system.find("Enterprise") != system.npos)
            ver += Enterprise;
        if (system.find("Education") != system.npos)
            ver += Education;
        if (system.find("Workstations") != system.npos)
            ver += Workstation;
        if (system.find("LTSC") != system.npos)
            ver += LTSC;
        if (system.find("LTSB") != system.npos)
            ver += LTSB;
    }
};

QString Activation::getkey()
{
    if (ui->windows_check->isChecked())
        return keys[ui->windows->currentIndex()];
    else
        return ui->input->text();
}

int getindex(OS x)
{
    if (x.sys / x._10 % 2 == 1)//10/11
    {
        if (x.ver / x.Pro % 2 == 1)//专业
        {
            if (x.ver / x.Workstation % 2 == 1)//专业工作站
                return 8;
            if (x.ver / x.Education % 2 == 1)//专业教育
                return 9;
            return 7;
        }
        if (x.ver / x.Education % 2 == 1)//教育
            return 10;
        if (x.ver / x.Enterprise % 2 == 1)//企业
        {
            if (x.ver / x.LTSC % 2 == 1)//LTSC
            {
                if (x.str.find("2019") != x.str.npos || x.str.find("2021") != x.str.npos)
                    return 14;
                return -1;
            }
            if (x.ver / x.LTSB % 2 == 1)
            {
                if (x.str.find("2015") != x.str.npos)
                    return 12;
                if (x.str.find("2016") != x.str.npos)
                    return 13;
                return -1;
            }
            return 11;
        }
        return -1;
    }
    if (x.sys / x._8_1 % 2 == 1)//8.1
    {
        if (x.ver / x.Pro % 2 == 1)//专业
            return 5;
        if (x.ver / x.Enterprise % 2 == 1)//企业
            return 6;
        return -1;
    }
    if (x.sys / x._8 % 2 == 1)//8
    {
        if (x.ver / x.Pro % 2 == 1)//专业
            return 3;
        if (x.ver / x.Enterprise % 2 == 1)//企业
            return 4;
        return -1;
    }
    if (x.sys / x._7 % 2 == 1)//7
    {
        if (x.ver / x.Pro % 2 == 1)//专业
            return 1;
        if (x.ver / x.Enterprise % 2 == 1)//企业
            return 2;
        return -1;
    }
    return -1;
}

void Activation::autosystem()
{
    QSettings setting("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", QSettings::NativeFormat);
    QString ver = setting.value("ProductName").toString();
    OS os(ver.toStdString());
    int index = getindex(os);
    QString word;
    if (index == -1)
        word = QString::fromStdWString(L"，请自行选择激活版本！");
    else
    {
        ui->windows->setCurrentIndex(index);
        word = QString::fromStdWString(L"，已经自动选择对应的系统选项");
    }
    QMessageBox::information(NULL, QString::fromStdWString(L"提示"), QString::fromStdWString(L"您的系统是") + ver + word, QMessageBox::Ok, QMessageBox::Ok);
}

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
    QMessageBox::information(NULL, QString::fromStdWString(L"关于"), QString::fromStdWString(L"KMS-Activator\nBy HeYC\n版本：3.2/Build 2206_64bit"));
}
