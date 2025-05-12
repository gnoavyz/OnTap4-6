#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct SinhVien {
    string maSV;
    string tenSV;
    int namSinh;
    float diem1, diem2, diem3;

    SinhVien(string ma = "", string ten = "", int ns = 0, float d1 = 0, float d2 = 0, float d3 = 0) {
        maSV = ma;
        tenSV = ten;
        namSinh = ns;
        diem1 = d1;
        diem2 = d2;
        diem3 = d3;
    }

    float diemTrungBinh() const {
        return (diem1 + diem2 + diem3) / 3;
    }

    void xuat() const {
        cout << setw(6) << maSV << " | "
             << setw(20) << tenSV << " | "
             << namSinh << " | "
             << fixed << setprecision(2)
             << diem1 << " | " << diem2 << " | " << diem3 << " | "
             << "DTB: " << diemTrungBinh() << endl;
    }

    static bool coMaSinhVien(const string& dong) {
        return isdigit(dong[0]);
    }
};

struct LopHoc {
    static const int MAX = 40;
    SinhVien ds[MAX];
    int soLuong = 0;

    // a. Đọc file
    void docTuFile(const string& tenFile) {
        ifstream file(tenFile);
        string dong;

        while (getline(file, dong) && soLuong < MAX) {
            if (SinhVien::coMaSinhVien(dong)) {
                stringstream ss(dong);
                string ma, ten, nsStr, d1, d2, d3;
                getline(ss, ma, '-');
                getline(ss, ten, '-');
                getline(ss, nsStr, '-');
                getline(ss, d1, '-');
                getline(ss, d2, '-');
                getline(ss, d3, '-');

                ds[soLuong++] = SinhVien(ma, ten, stoi(nsStr), stof(d1), stof(d2), stof(d3));
            }
        }
    }

    // b. Xuất danh sách
    void xuatDanhSach() const {
        cout << "\nDANH SACH SINH VIEN:\n";
        for (int i = 0; i < soLuong; ++i) {
            ds[i].xuat();
        }
    }

    // c. Tìm kiếm theo tên
    void timKiemTheoTen(const string& ten) const {
        cout << "\nSINH VIEN CO TEN \"" << ten << "\":\n";
        bool timThay = false;
        for (int i = 0; i < soLuong; ++i) {
            if (ds[i].tenSV == ten) {
                ds[i].xuat();
                timThay = true;
            }
        }
        if (!timThay) cout << "Khong tim thay sinh vien nao.\n";
    }

    // d. In SV có điểm trung bình > d
    void inSVDiemTrungBinhLonHon(float d) const {
        cout << "\nSINH VIEN CO DIEM TB > " << d << ":\n";
        for (int i = 0; i < soLuong; ++i) {
            if (ds[i].diemTrungBinh() > d) {
                ds[i].xuat();
            }
        }
    }

    // e. Xóa sinh viên theo mã
    void xoaTheoMaSV(const string& ma) {
        bool daXoa = false;
        for (int i = 0; i < soLuong; ++i) {
            if (ds[i].maSV == ma) {
                for (int j = i; j < soLuong - 1; ++j) {
                    ds[j] = ds[j + 1];
                }
                soLuong--;
                daXoa = true;
                cout << "\nDa xoa sinh vien co ma: " << ma << endl;
                break;
            }
        }
        if (!daXoa) {
            cout << "\nKhong tim thay sinh vien co ma: " << ma << endl;
        }
    }

    // f. Sắp xếp giảm dần theo điểm trung bình
    void sapXepTheoDTBGiamDan() {
        for (int i = 0; i < soLuong - 1; ++i) {
            for (int j = i + 1; j < soLuong; ++j) {
                if (ds[i].diemTrungBinh() < ds[j].diemTrungBinh()) {
                    swap(ds[i], ds[j]);
                }
            }
        }
        cout << "\nDa sap xep sinh vien theo DTB giam dan.\n";
    }

    // g. Ghi ra file
    void ghiFile(const string& tenFile) const {
        ofstream out(tenFile);
        for (int i = 0; i < soLuong; ++i) {
            out << ds[i].maSV << "-" << ds[i].tenSV << "-" << ds[i].namSinh << "-"
                << ds[i].diem1 << "-" << ds[i].diem2 << "-" << ds[i].diem3 << endl;
        }
        cout << "\nDa ghi thong tin sinh vien vao file " << tenFile << endl;
    }
};

int main() {
    LopHoc lop;
    lop.docTuFile("Data.txt");
    lop.xuatDanhSach();

    lop.timKiemTheoTen("Pham Van C");
    lop.inSVDiemTrungBinhLonHon(8.0);
    lop.xoaTheoMaSV("1003");
    lop.sapXepTheoDTBGiamDan();
    lop.xuatDanhSach();
    lop.ghiFile("SV.txt");

    return 0;
}
