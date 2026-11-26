#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct SinhVien {
    string maSV;
    string hoTen;
    double diemCTDL;
    double diemKTLP;
    double diemTKW;
};

SinhVien khoiTaoSinhVien(string ma = "", string ten = "",
                        double ctdl = 0.0, double ktlp = 0.0, double tkw = 0.0) {
    SinhVien sv;
    sv.maSV = ma;
    sv.hoTen = ten;
    sv.diemCTDL = ctdl;
    sv.diemKTLP = ktlp;
    sv.diemTKW = tkw;
    return sv;
}

void nhapMotSinhVien(SinhVien &sv) {
    cout << "  - Ma so sinh vien: ";
    getline(cin, sv.maSV);
    cout << "  - Ho ten sinh vien: ";
    getline(cin, sv.hoTen);
    cout << "  - Diem Cau truc du lieu: ";
    cin >> sv.diemCTDL;
    cout << "  - Diem Ky thuat lap trinh: ";
    cin >> sv.diemKTLP;
    cout << "  - Diem Thiet ke web: ";
    cin >> sv.diemTKW;
    cin.ignore();
}

void nhapDanhSach(SinhVien ds[], int &siSo) {
    do {
        cout << "Nhap si so sinh vien (> 0): ";
        cin >> siSo;
    } while (siSo <= 0);
    cin.ignore();

    for (int i = 0; i < siSo; i++) {
        cout << "\nNhap thong tin sinh vien thu " << i + 1 << ":\n";
        nhapMotSinhVien(ds[i]);
    }
}

double tinhDiemTrungBinh(const SinhVien &sv) {
    return (sv.diemCTDL + sv.diemKTLP + sv.diemTKW) / 3.0;
}

void xuatDanhSach(const SinhVien ds[], int siSo) {
    if (siSo <= 0) {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << "\n==================== DANH SACH SINH VIEN ====================\n";
    cout << left
         << setw(12) << "Ma SV"
         << setw(25) << "Ho ten"
         << setw(8)  << "CTDL"
         << setw(8)  << "KTLP"
         << setw(8)  << "TKW"
         << setw(8)  << "DTB" << "\n";
    cout << "---------------------------------------------------------------\n";

    cout << fixed << setprecision(2);
    for (int i = 0; i < siSo; i++) {
        cout << left
             << setw(12) << ds[i].maSV
             << setw(25) << ds[i].hoTen
             << setw(8)  << ds[i].diemCTDL
             << setw(8)  << ds[i].diemKTLP
             << setw(8)  << ds[i].diemTKW
             << setw(8)  << tinhDiemTrungBinh(ds[i]) << "\n";
    }
    cout << "===============================================================\n";
}

void selectionSortTheoMa(SinhVien ds[], int siSo) {
    for (int i = 0; i < siSo - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < siSo; j++) {
            if (ds[j].maSV < ds[minIdx].maSV) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            SinhVien temp = ds[i];
            ds[i] = ds[minIdx];
            ds[minIdx] = temp;
        }
    }
}

int binarySearchTheoMa(const SinhVien ds[], int siSo, const string &maCanTim) {
    int left = 0;
    int right = siSo - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (ds[mid].maSV == maCanTim) {
            return mid;
        } else if (ds[mid].maSV < maCanTim) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    const int MAX = 100;
    SinhVien ds[MAX];
    int siSo = 0;

    nhapDanhSach(ds, siSo);
    xuatDanhSach(ds, siSo);

    selectionSortTheoMa(ds, siSo);
    cout << "\nDanh sach sau khi sap xep tang dan theo ma SV (Selection Sort):";
    xuatDanhSach(ds, siSo);

    string maTim;
    cout << "\nNhap ma sinh vien can tim: ";
    getline(cin, maTim);

    int viTri = binarySearchTheoMa(ds, siSo, maTim);
    if (viTri != -1) {
        cout << "Tim thay sinh vien tai vi tri " << viTri << " (sau khi sap xep):\n";
        cout << "Ma SV: " << ds[viTri].maSV
             << ", Ho ten: " << ds[viTri].hoTen
             << ", DTB: " << fixed << setprecision(2) << tinhDiemTrungBinh(ds[viTri]) << "\n";
    } else {
        cout << "Khong tim thay sinh vien co ma \"" << maTim << "\".\n";
    }

    return 0;
}