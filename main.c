#include <stdio.h>
#include <string.h>

#define MAX_NV 50

// 1. Dinh nghia cau truc NhanVien
typedef struct {
    int maNV;
    char hoTen[50];
    int soPhutDiMuon;
    float luongCoBan;
} NhanVien;

// 2. Khai bao nguyen mau ham (Function Prototypes)
int timTheoMaNV(int maNV, NhanVien ds[], int soLuong);
int themNhanVien(NhanVien ds[], int soLuong);
void hienThiDanhSach(NhanVien ds[], int soLuong);
void capNhatPhutDiMuon(NhanVien ds[], int soLuong);
void timKiemNhanVien(NhanVien ds[], int soLuong);

// Ham ho tro xu ly chuoi va bo dem
void xoaBoDem();
void xoaXuongDong(char str[]);

// ================= HÀM MAIN =================
int main() {
    NhanVien danhSach[MAX_NV];
    int soLuong = 0;
    int luaChon;

    do {
        printf("\n===== HE THONG QUAN LY CHAM CONG HRM =====\n");
        printf("1. Them nhan vien moi\n");
        printf("2. Hien thi danh sach va tinh luong\n");
        printf("3. Cap nhat so phut di muon\n");
        printf("4. Tim kiem nhan vien theo ma\n");
        printf("0. Thoat\n");
        printf("==========================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &luaChon);
        xoaBoDem(); // Xoa phim Enter con xot lai trong bo dem

        switch (luaChon) {
            case 1:
                soLuong = themNhanVien(danhSach, soLuong);
                break;
            case 2:
                hienThiDanhSach(danhSach, soLuong);
                break;
            case 3:
                capNhatPhutDiMuon(danhSach, soLuong);
                break;
            case 4:
                timKiemNhanVien(danhSach, soLuong);
                break;
            case 0:
                printf("=> Thoat chuong trinh. Chuc ban mot ngay tot lanh!\n");
                break;
            default:
                printf("=> Lua chon khong hop le! Vui long nhap lai.\n");
        }
    } while (luaChon != 0);

    return 0;
}

// ================= CÁC HÀM CHỨC NĂNG =================

// Ham tim kiem tra ve vi tri (index), neu khong thay tra ve -1
int timTheoMaNV(int maNV, NhanVien ds[], int soLuong) {
    for (int i = 0; i < soLuong; i++) {
        if (ds[i].maNV == maNV) {
            return i; // Tim thay tai vi tri i
        }
    }
    return -1; // Khong tim thay
}

// Ham them nhan vien moi
int themNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong >= MAX_NV) {
        printf("=> Danh sach da day (Toi da %d nhan vien). Khong the them!\n", MAX_NV);
        return soLuong;
    }

    NhanVien nvMoi;
    int viTri;

    // Nhap va kiem tra ma nhan vien (khong duoc trung)
    do {
        printf("Nhap ma nhan vien: ");
        scanf("%d", &nvMoi.maNV);
        xoaBoDem();

        viTri = timTheoMaNV(nvMoi.maNV, ds, soLuong);
        if (viTri != -1) {
            printf("=> Ma nhan vien %d da ton tai! Vui long nhap ma khac.\n", nvMoi.maNV);
        }
    } while (viTri != -1);

    // Nhap ho ten
    printf("Nhap ho ten: ");
    fgets(nvMoi.hoTen, sizeof(nvMoi.hoTen), stdin);
    xoaXuongDong(nvMoi.hoTen);

    // Nhap so phut di muon (khong am)
    do {
        printf("Nhap so phut di muon: ");
        scanf("%d", &nvMoi.soPhutDiMuon);
        if (nvMoi.soPhutDiMuon < 0) {
            printf("=> So phut khong hop le! Nhap lai.\n");
        }
    } while (nvMoi.soPhutDiMuon < 0);

    // Nhap luong co ban (khong am)
    do {
        printf("Nhap luong co ban: ");
        scanf("%f", &nvMoi.luongCoBan);
        if (nvMoi.luongCoBan < 0) {
            printf("=> Luong co ban khong hop le! Nhap lai.\n");
        }
    } while (nvMoi.luongCoBan < 0);

    // Luu vao mang
    ds[soLuong] = nvMoi;
    printf("=> Them nhan vien thanh cong!\n");
    
    return soLuong + 1; // Tang so luong nhan vien len 1
}

// Ham hien thi danh sach va tinh luong thuc nhan
void hienThiDanhSach(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("=> Danh sach nhan vien hien dang trong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIEN ---\n");
    printf("%-7s | %-20s | %-9s | %-15s\n", "Ma NV", "Ho ten", "Phut muon", "Luong thuc nhan");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < soLuong; i++) {
        float tienPhat = (ds[i].soPhutDiMuon > 15) ? 50000.0 : 0.0;
        float luongThucNhan = ds[i].luongCoBan - tienPhat;

        printf("%-7d | %-20s | %-9d | %.0f\n", 
               ds[i].maNV, ds[i].hoTen, ds[i].soPhutDiMuon, luongThucNhan);
    }
}

// Ham cap nhat so phut di muon
void capNhatPhutDiMuon(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("=> Danh sach dang trong!\n");
        return;
    }

    int ma, viTri, phutMoi;
    printf("Nhap ma NV can cap nhat: ");
    scanf("%d", &ma);

    viTri = timTheoMaNV(ma, ds, soLuong);
    if (viTri == -1) {
        printf("=> Khong tim thay nhan vien!\n");
    } else {
        do {
            printf("Nhap so phut di muon moi: ");
            scanf("%d", &phutMoi);
            if (phutMoi < 0) {
                printf("=> So phut khong hop le! Vui long nhap lai.\n");
            }
        } while (phutMoi < 0);

        ds[viTri].soPhutDiMuon = phutMoi;
        printf("=> Cap nhat thanh cong!\n");
    }
}

// Ham tim kiem va hien thi 1 nhan vien
void timKiemNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("=> Danh sach dang trong!\n");
        return;
    }

    int ma, viTri;
    printf("Nhap ma NV can tim: ");
    scanf("%d", &ma);

    viTri = timTheoMaNV(ma, ds, soLuong);
    if (viTri == -1) {
        printf("=> Khong tim thay nhan vien!\n");
    } else {
        float tienPhat = (ds[viTri].soPhutDiMuon > 15) ? 50000.0 : 0.0;
        float luongThucNhan = ds[viTri].luongCoBan - tienPhat;

        printf("\n--- THONG TIN NHAN VIEN ---\n");
        printf("Ma NV           : %d\n", ds[viTri].maNV);
        printf("Ho ten          : %s\n", ds[viTri].hoTen);
        printf("So phut di muon : %d phut\n", ds[viTri].soPhutDiMuon);
        printf("Luong co ban    : %.0f VND\n", ds[viTri].luongCoBan);
        printf("Tien phat       : %.0f VND\n", tienPhat);
        printf("Luong thuc nhan : %.0f VND\n", luongThucNhan);
    }
}

// ================= CÁC HÀM HỖ TRỢ =================
// Xoa bo dem ban phim sau khi dung scanf
void xoaBoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Loai bo ky tu '\n' thua o cuoi chuoi khi dung fgets
void xoaXuongDong(char str[]) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}