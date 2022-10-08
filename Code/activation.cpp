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

struct OS
{
    const int _10 = 1, _8_1 = 2, _8 = 4, _7 = 8;
    const int Pro = 1, Enterprise = 2, Education = 4, Workstation = 8;
    const int N = 1, G = 2, E = 4;
    string str;
    int sys = 0, ver = 0, ver2 = 0;
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

        if (system.find(" N") != system.npos)
            ver2 += N;
        if (system.find(" G") != system.npos)
            ver2 += G;
        if (system.find(" E") != system.npos)
            ver2 += E;
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
    if (x.sys / x._10 % 2 == 1)//10or11
    {
        if (x.ver / x.Pro % 2 == 1)//专业
        {
            if (x.ver / x.Workstation % 2 == 1)//专业工作站版
            {
                if (x.ver2 / x.N % 2 == 1)//N版
                    return 18;
                //普通版
                return 17;
            }
            if (x.ver / x.Education % 2 == 1)//专业教育版
            {
                if (x.ver2 / x.N % 2 == 1)//N版
                    return 20;
                //普通版
                return 19;
            }
            //专业版
            if (x.ver2 / x.N % 2 == 1)//N版
                return 16;
            //普通版
            return 15;
        }
        if (x.ver / x.Education % 2 == 1)//教育版 注意:必存在E
        {
            if (x.ver2 / x.N % 2 == 1)//N版
                return 22;
            //普通版
            return 21;
        }
        if (x.ver / x.Enterprise % 2 == 1)//企业版 注意:必存在E
        {
            if (x.ver2 / x.N % 2 == 1)//N版
                return 24;
            if (x.ver2 / x.G % 2 == 1)//G版
                return 25;
            if (x.ver2 / x.N % 2 == 1 && x.ver2 / x.G % 2 == 1)//N G版
                return 26;
            //普通版
            return 23;
        }
        return -1;
    }
    if (x.sys / x._8_1 % 2 == 1)//8.1
    {
        if (x.ver / x.Pro % 2 == 1)//专业
        {
            if (x.ver2 / x.N % 2 == 0)//N版
                return 12;
            //普通版
            return 11;
        }
        if (x.ver / x.Enterprise % 2 == 1)//企业 注意:必存在E
        {
            if (x.ver2 / x.N % 2 == 0)//N版
                return 14;
            //普通版
            return 13;
        }
        return -1;
    }
    if (x.sys / x._8 % 2 == 1)//8
    {
        if (x.ver / x.Pro % 2 == 1)//专业
        {
            if (x.ver2 / x.N % 2 == 0)//N版
                return 8;
            //普通版
            return 7;
        }
        if (x.ver / x.Enterprise % 2 == 1)//企业 注意:必存在E
        {
            if (x.ver2 / x.N % 2 == 0)//N版
                return 10;
            //普通版
            return 9;
        }
        return -1;
    }
    if (x.sys / x._7 % 2 == 1)//7
    {
        if (x.ver / x.Pro % 2 == 1)//专业
        {
            if (x.ver2 / x.N % 2 == 0)//N版
                return 2;
            if (x.ver2 / x.N % 2 == 0)//E版
                return 3;
            //普通版
            return 1;
        }
        if (x.ver / x.Enterprise % 2 == 1)//企业 注意:必存在E
        {
            if (x.ver2 / x.N % 2 == 0)//N版
                return 5;
            if (x.str.find("Enterprize E") != x.str.npos)//E版
                return 6;
            //普通版
            return 4;
        }
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
    QMessageBox::information(NULL, QString::fromStdWString(L"关于"), QString::fromStdWString(L"KMS-Activator\nBy HeYC\n版本：3.0/Build 2204_64bit"));
}
