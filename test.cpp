#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<algorithm>

const int MAX=100;

using namespace std;

struct SinhVien
{
  string idName;
  string name;
  int namS;
  double diem1, diem2, diem3;
  SinhVien(string id="", string ten="", int ns=0, double d1=0, double d2=0, double d3=0)
  {
      idName= id;
      name=ten;
      namS=ns;
      diem1=d1;
      diem2=d2;
      diem3=d3;
  }
  static bool kiemTraSinhVien(const string &line)
  {
    return isdigit(line[0]);
  }
  void inRa()
  {
      cout << idName <<"\t"<< name << "\t"<< namS << "\t"<< fixed << setprecision(2)<< diem1 <<"\t"<< diem2 << "\t"<< diem3<< "\t"<< "DTB:" << diemTB() << endl;
  }
  double diemTB()
  {
        return (diem1 + diem2 + diem3) / 3;
  }
};
int main()
{
    ifstream File("Data.txt");
    if(!File.is_open())
    {
        cout << "Khong the mo file. \n";
        return 1;
    }
    SinhVien dsSV[MAX];
    int soSV=0;
    string line;
    while(getline(File,line)&&soSV<MAX)
    {
        if(SinhVien::kiemTraSinhVien(line))
    {       
        stringstream ss(line);
        string id, ten, ns, d1, d2, d3;
        getline(ss,id, '-');
        getline(ss,ten,'-');
        getline(ss,ns, '-');
        getline(ss,d1, '-');
        getline(ss,d2, '-');
        getline(ss,d3, '-');
        
        dsSV[soSV]=SinhVien(id, ten, stoi(ns), stof(d1), stof(d2), stof(d3));
        soSV++;
    }
        if(soSV>MAX)
        {
            cout << "Vuot qua so luong Sinh Vien.\n";
        }
    }
    for(int i=0; i<soSV; i++)
    {
        dsSV[i].inRa();
    }
    system("pause");
    return 0;
}
