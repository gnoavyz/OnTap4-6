#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>

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
    static bool kiemTraSV(const string& dong)
    {
        return isdigit(dong[0]);
    }
    static void nhapVao(SinhVien dsSV[MAX], int &soSV)
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
            if(SinhVien::kiemTraSV(line) && soSV< MAX)
            {
                stringstream ss(line);
                string id, ten, ns, d1, d2, d3;
                getline(ss, id, '-');
                getline(ss, ten, '-');
                getline(ss, ns, '-');
                getline(ss, d1, '-');
                getline(ss, d2, '-');
                getline(ss, d3, '-');

                dsSV[soSV] = SinhVien(id, ten, stoi(ns), stof(d1), stof(d2), stof(d3));
                soSV++;
                if(soSV >= MAX)
                {
                    cout << "Da vuot qua so luong sinh vien cho phep!" << endl;
                    break;
                }
            }
        }
    }
    void inRa()
    {
        cout << idName << "\t" << name << "\t" << namS << "\t" << fixed << setprecision(2) << diem1 << "\t" << diem2 << "\t" << diem3 << "\t" << "DTB: " << diemTrungBinh() << endl;
    }
    double diemTrungBinh()
    {
        return (diem1 + diem2 + diem3) / 3.0;
    }
};

int main()
{
    SinhVien dsSV[MAX];
    int soSV=0;
    ifstream File("Data.txt");
    if(!File.is_open())
    {
        cout << "Khong mo duoc file!" << endl;
        return 1;
    }
    SinhVien::nhapVao(dsSV,soSV);
    system("cls");
    cout << "\t" <<  "Danh sach sinh vien:" << endl;
    for (int i=0; i<soSV; i++)
    {
        dsSV[i].inRa();
    }
    File.close();
    system("pause");
    return 0;
}