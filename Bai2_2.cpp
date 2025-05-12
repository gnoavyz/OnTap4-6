#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<algorithm>

const int MAX = 100;
using namespace std;
struct SinhVien
{
    string idName;
    string name;
    int namS;
    double diem1, diem2, diem3;
    SinhVien(string id="", string ten ="", int ns=0, double d1=0, double d2=0, double d3=0)
    {
        idName = id;
        name = ten;
        namS = ns;
        diem1 = d1;
        diem2 = d2;
        diem3 = d3;
    }
    static bool kiemTraSV(const string& line)
    {
        return isdigit(line[0]);
    }
    void inRa()
    {
        cout << idName << "\t" << name << "\t" << namS << "\t" << fixed << setprecision(2) << diem1 << "\t" << diem2 << "\t" << diem3 << "\t" << "DTB: " << diemTB() << endl;
    }
    double diemTB()
    {
        return (diem1 + diem2 + diem3) / 3.0;
    }
};
struct LopHoc
{
    SinhVien dsSV[MAX];
    int soSV=0;
    void docTuFile()
    {
        ifstream File("Data.txt");
        if(!File.is_open())
        {
        cout << "Khong mo duoc file!" << endl;
        return;
        }
        string line;
        while(getline(File, line))
        {
            if(SinhVien::kiemTraSV(line) && soSV<MAX)
            {
                stringstream ss(line);
                string id, ten, ns, d1, d2, d3;
                getline(ss, id, '-');
                getline(ss, ten, '-');
                getline(ss, ns, '-');
                getline(ss, d1, '-');
                getline(ss, d2, '-');
                getline(ss, d3, '-');

                dsSV[soSV]= SinhVien(id, ten, stoi(ns), stof(d1), stof(d2), stof(d3));
                soSV++;
                if(soSV >= MAX)
                {
                    cout << "Da vuot qua so luong sinh vien cho phep!" << endl;
                    break;
                }
            }
        }

    }
    void xuat()
    {
        cout << "\t DANH SACH SINH VIEN \n";
        for(int i=0; i<soSV; i++)
        {
            dsSV[i].inRa();
        }
    }
    void timTheoTen(string ten)
    {
        bool timThay = false;
        cout << "\t SINH VIEN CO TEN " << ten << ":\n";
        for(int i=0; i<soSV; i++)
        {
            if(dsSV[i].name == ten)
            {
                dsSV[i].inRa();
                timThay = true;
            }
        }
        if(!timThay)
        {
            cout << "Khong tim thay sinh vien nao." << endl;
        }
    }
    void inSVDiemTB(double d)
    {
        cout << "\t SINH VIEN CO DIEM TB > " << d << ":\n";
        for(int i=0; i<soSV; i++)
        {
            if(dsSV[i].diemTB() > d)
            {
                dsSV[i].inRa();
            }
        }
    }
    void xoaTheoMaSV(string ma)
    {
        bool daXoa = false;
        for(int i=0; i<soSV; i++)
        {
            if(dsSV[i].idName == ma)
            {
                for(int j=i; j<soSV-1; j++)
                {
                    dsSV[j] = dsSV[j+1];
                }
                soSV--;
                daXoa = true;
                cout << "\nDa xoa sinh vien co ma: " << ma << endl;
                break;
            }
        }
        if(!daXoa)
        {
            cout << "\nKhong tim thay sinh vien co ma: " << ma << endl;
        }
    }
    void sapXepTheoDTBGiamDan()
    {
        for(int i=0; i<soSV-1; i++)
        {
            for(int j=i+1; j<soSV; j++)
            {
                if(dsSV[i].diemTB() < dsSV[j].diemTB())
                {
                    swap(dsSV[i], dsSV[j]);
                }
            }
        }
    }
    void ghiRaFile()
    {
        ofstream outFile("SV.txt");
        if(!outFile.is_open())
        {
            cout << "Khong mo duoc file!" << endl;
            return;
        }
        for(int i=0; i<soSV; i++)
        {
            outFile << dsSV[i].idName << "-" << dsSV[i].name << "-" << dsSV[i].namS << "-" << dsSV[i].diem1 << "-" << dsSV[i].diem2 << "-" << dsSV[i].diem3 << endl;
        }
        outFile.close();
    }
};
int main()
{
    LopHoc lop;
    lop.docTuFile();
    system("cls");
    lop.xuat();
    string ten;
    cout << "Nhap ten sinh vien can tim: ";
    fflush(stdin);
    getline(cin, ten);
    lop.timTheoTen(ten);
    double d;
    cout << "Nhap diem trung binh: ";
    cin >> d;
    lop.inSVDiemTB(d);
    cin.ignore();
    string ma;
    cout << "Nhap ma sinh vien can xoa: ";
    getline(cin, ma);
    lop.xoaTheoMaSV(ma);
    lop.xuat();
    lop.sapXepTheoDTBGiamDan();
    cout << "\nDa sap xep sinh vien theo DTB giam dan.\n";
    lop.xuat();
    lop.ghiRaFile();
    cout << "\nDa ghi thong tin sinh vien vao file Output.txt\n";
    system("pause");
    return 0;
}