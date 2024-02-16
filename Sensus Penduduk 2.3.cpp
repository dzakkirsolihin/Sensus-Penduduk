#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <queue>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <bits/stdc++.h>
using namespace std;

// Membuat struct
struct Penduduk
{
    string nik;
    string nama;
    string umur;
    string jenisKelamin;
    string tempatLahir;
    string tanggalLahir;
    string agama;
    string alamat;
};

// Membuat node untuk tree
struct Node {
    Penduduk data;
    Node* left;
    Node* right;
};

// Fungsi untuk membuat simpul baru pada pohon
Node* createNode(const Penduduk& data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Fungsi untuk menyisipkan data pada pohon
Node* insertNode(Node* root, const Penduduk& data) {
    if (root == nullptr) {
        root = createNode(data);
        return root;
    }

    if (data.nik < root->data.nik) {
        root->left = insertNode(root->left, data);
    } else if (data.nik > root->data.nik) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

// Fungsi rekursif untuk mencari data pada pohon
Node* searchNode(Node* root, const string& nik) {
    if (root == nullptr || root->data.nik == nik) {
        return root;
    }

    if (nik < root->data.nik) {
        return searchNode(root->left, nik);
    }

    return searchNode(root->right, nik);
}

void updateData(Node* root, const string& nik, const Penduduk& newData) {
    // Cari simpul dengan NIK yang sesuai
    Node* targetNode = searchNode(root, nik);

    if (targetNode != nullptr) {
        // Ubah data pada simpul yang ditemukan
        targetNode->data = newData;
        // cout << "Data penduduk berhasil diubah." << endl;
    }
}

// Mengubah password agar disamarkan
string ubahPassword()
{
    char password[100];
    int i = 0;
    char c;

    cout << "Password : ";

    // Loop hingga tombol "Enter" ditekan
    while ((c = _getch()) != '\r')
    {
        if (c == '\b')
        {
            if (i > 0)
            {
                --i;
                cout << "\b \b";
            }
        }
        else
        {
            // Menampilkan "*" sebagai pengganti karakter yang sebenarnya
            password[i++] = c;
            cout << '*';
        }
    }

    password[i] = '\0';

    return password;
}

// Fungsi tampilan login
int login()
{
    string username, password;
    int coba = 0;
    while (coba < 3)
    {
	    system("CLS");

	    cout << "==========================================\n";
	    cout << "         PENDATAAN SENSUS PENDUDUK        \n";
	    cout << "==========================================\n";
	    cout << "Username : ";
	    cin >> username;
	    password = ubahPassword();

	    if (username == "admin" && password == "admin")
	    {
	        return true;
	    }
	    else
	    {
	        coba++;
	        cout << "\n=================================================\n";
            cout << "Username atau password salah. Silakan coba lagi." << endl;
            cout << "Sisa percobaan: " << 3 - coba << endl;
            if (coba < 3)
			{
				cout << "=================================================\n";
				getch();
            } else
			{
                // Menunggu 15 detik sebelum mengizinkan percobaan lagi
                for (int i = 15; i > 0; i--)
                {
                    system("CLS");
                    cout << "=================================================\n";
                    cout << "Anda telah melebihi batas percobaan. \nSilakan tunggu " << i << " detik lagi untuk dapat login kembali.";
                    cout << "\n=================================================\n";
                    this_thread::sleep_for(chrono::seconds(1)); // Menunggu 1 detik
                }
//				getch();
				return login();
            }
	    }
	}
}

// Fungsi untuk menentukan apakah data bersifat integer atau tidak
bool cek_angka(string str)
{
    int cek = 0;
    char arr[str.length() + 1]; 
    strcpy(arr, str.c_str()); 
    
	// for (int i = 0; i < str.length(); i++) {
	// 	cout << arr[i]; 
    // }
    
    for (int i = 0; i < str.length(); i++){
        if (!isdigit(arr[i]))
        {
            cek++;
        }
    }

    if (cek != 0)
    {
        return false;
    }

    return true;
}

// Fungsi apakah inputan berisi NULL
bool cekNull(string isi)
{
    if (isi == "")
    {
        return 0;
    }
    return 1;
}

// Fungsi untuk mencgecek NIK
bool cekNIK(const queue<Penduduk> &daftar_penduduk, const string &nik)
{
    queue<Penduduk> temp_penduduk = daftar_penduduk;

    while (!temp_penduduk.empty())
    {
        Penduduk p = temp_penduduk.front();
        if (nik == p.nik)
        {
            return true; // NIK sudah ada
        }
        temp_penduduk.pop();
    }
    return false; // NIK belum ada
}

// Fungsi untuk mengecek kebenaran format tanggal
bool cekFormatTanggal(const string& tanggal) 
{
    // Verifikasi panjang string dan format
    if (tanggal.length() != 10)
        return false;

    if (tanggal[2] != '-' || tanggal[5] != '-')
        return false;

    // Verifikasi komponen tanggal
    string tanggalStr = tanggal.substr(0, 2);  // Mengambil substring tanggal dari indeks 0 hingga 1
    string bulanStr = tanggal.substr(3, 2);  // Mengambil substring bulan dari indeks 3 hingga 4
    string tahunStr = tanggal.substr(6, 4);  // Mengambil substring tahun dari indeks 6 hingga 9

    // Memeriksa apakah komponen tanggal, bulan, dan tahun berisi angka
    if (!isdigit(tanggalStr[0]) || !isdigit(bulanStr[0]) || !isdigit(tahunStr[0]))
        return false;

    int tanggalInt = stoi(tanggalStr);  // Mengonversi string tanggal menjadi integer
    int bulanInt = stoi(bulanStr);  // Mengonversi string bulan menjadi integer
    int tahunInt = stoi(tahunStr);  // Mengonversi string tahun menjadi integer

    // Mendapatkan waktu saat ini
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm* current_time = localtime(&now);
    int tahunSaatIni = current_time->tm_year + 1900;  // Mendapatkan tahun saat ini
    int bulanSaatIni = current_time->tm_mon + 1;  // Mendapatkan bulan saat ini (Januari memiliki nilai 0)
    int tanggalSaatIni = current_time->tm_mday;  // Mendapatkan tanggal saat ini

    // Memeriksa apakah nilai tanggal, bulan, dan tahun berada dalam rentang yang valid
    if (tanggalInt < 1 || tanggalInt > 31 || bulanInt < 1 || bulanInt > 12 || tahunInt < 1900 || tahunInt > tahunSaatIni)
        return false;

    // Memeriksa apakah tanggal lahir melebihi tanggal saat ini jika bulan lahir dan tahun lahir sama dengan bulan saat ini dan tahun saat ini
    if (tanggalInt > tanggalSaatIni  || bulanInt > bulanSaatIni || tahunInt > tahunSaatIni)
        return false;

    return true;
}

// Fungsi menambah penduduk melalui queue
void tambahPenduduk(queue<Penduduk> &daftar_penduduk)
{
    Penduduk p;
    const int nikLength = 16; // jumlah digit NIK
    int progress = 0;

    // cout << "==========================================\n";
    // cout << "           Tambah Data Penduduk           " << endl;
    // cout << "==========================================\n";

    // Verifikasi data
    while (true)
    {
        system("cls");
        cout << "==========================================\n";
        cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
        cout << "==========================================\n";
        cout << "NIK : ";
        getline(cin, p.nik);

        if (!cekNull(p.nik))
        {
            cout << "Silahkan masukan data" << endl;
            getch();
        }
        else
        {
            if (p.nik.length() != nikLength)
            {
                cout << "Jumlah Digit NIK Tidak Sesuai" << endl;
                getch();
            }
            else if (cekNIK(daftar_penduduk, p.nik))
            {
                cout << "NIK sudah terdaftar. Mohon masukkan NIK yang berbeda." << endl;
                getch();
            }
            else if (!cek_angka(p.nik))
            {
                cout << "Input NIK tidak valid. Harap masukan NIK anda." << endl;
                getch();
            }
            else
            {
                cout << "Data Berhasil Ditambahkan" << endl;
                getch();
                progress++;
                break;
            }
        }
    }

    while (true)
    {
        system("cls");
        cout << "==========================================\n";
        cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
        cout << "==========================================\n";
        cout << "Nama: ";
        getline(cin, p.nama);

        if (!cekNull(p.nama))
        {
            cout << "Silahkan masukan data" << endl;
            getch();
        }
        else
        {
            cout << "Data Berhasil Ditambahkan" << endl;
            getch();
            progress++;
            break;
        }
    }

    while (true)
    {
        system("cls");
        cout << "==========================================\n";
        cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
        cout << "==========================================\n";
        cout << "Umur: ";
        getline(cin, p.umur);

        if (!cekNull(p.umur))
        {
            cout << "Silahkan masukan data" << endl;
            getch();
        }
        else
        {
            if (!cek_angka(p.umur))
            {
                cout << "Input umur tidak valid. Harap masukan umur anda." << endl;
                getch();
            }
            else
            {
                cout << "Data Berhasil Ditambahkan" << endl;
                getch();
                progress++;
                break;
            }
        }
    }

    while (true)
    {
        system("cls");
        cout << "==========================================\n";
        cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
        cout << "==========================================\n";
        cout << "Jenis Kelamin (L/P): ";
        getline(cin, p.jenisKelamin);

        if (!cekNull(p.jenisKelamin))
        {
            cout << "Silahkan masukan data" << endl;
            getch();
        }
        else
        {
            if (p.jenisKelamin != "L" && p.jenisKelamin != "P")
            {
                cout << "Input jenis kelamin tidak valid. Harap masukkan 'L' atau 'P'." << endl;
                getch();
            }
            else
            {
                cout << "Data Berhasil Ditambahkan" << endl;
                getch();
                p.jenisKelamin = toupper(p.jenisKelamin[0]);
                progress++;
                break;
            }
        }
    }

    while (true)
	{
	    system("cls");
	    cout << "==========================================\n";
	    cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
	    cout << "==========================================\n";
	    cout << "Tempat Lahir (Kabupaten/Kota): ";
	    getline(cin, p.tempatLahir);

	    if (!cekNull(p.tempatLahir))
		{
	        cout << "Silahkan masukan data" << endl;
	        getch();
	    }
	    else
		{
	        cout << "Data Berhasil Ditambahkan" << endl;
	        getch();
	        progress++;
	        break;
	    }
	}

	while (true)
	{
	    system("cls");
	    cout << "==========================================\n";
	    cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
	    cout << "==========================================\n";
	    cout << "Tanggal Lahir (dd-mm-yyyy): ";
	    getline(cin, p.tanggalLahir);

	    if (!cekNull(p.tanggalLahir))
		{
	        cout << "Silahkan masukan data" << endl;
	        getch();
	    }
	    else
		{
	        if (!cekFormatTanggal(p.tanggalLahir))
			{
	            cout << "Format tanggal tidak valid. Harap masukkan tanggal dengan format dd-mm-yyyy." << endl;
	            getch();
	        }
	        else
			{
	            cout << "Data Berhasil Ditambahkan" << endl;
	            getch();
	            progress++;
	            break;
	        }
	    }
	}


    while (true)
    {
        system("cls");
        cout << "==========================================\n";
        cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
        cout << "==========================================\n";
        cout << "Agama : ";
        getline(cin, p.agama);

        if (!cekNull(p.agama))
        {
            cout << "Silahkan masukan data" << endl;
            getch();
        }
        else
        {
            cout << "Data Berhasil Ditambahkan" << endl;
            getch();
            progress++;
            break;
        }
    }

    while (true)
    {
        system("cls");
        cout << "==========================================\n";
        cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
        cout << "==========================================\n";
        cout << "Alamat: ";
        getline(cin, p.alamat);

        if (!cekNull(p.alamat))
        {
            cout << "Silahkan masukan data" << endl;
            getch();
        }
        else
        {
            system("cls");
            progress++;
            break;
        }
    }

    cout << endl;

    daftar_penduduk.push(p);

    cout << "Data berhasil ditambahkan." << endl;
}

//Fungsi untuk mendapatkan panjang maksimum dari sebuah field dalam daftar penduduk.
int getMaxStringLength(const queue<Penduduk> &daftar_penduduk, const string &field)
{
    // Menginisialisasi variabel maxLength dengan panjang awal dari field
    int maxLength = field.length();

    // Membuat salinan dari daftar_penduduk agar tidak merusak data asli
    queue<Penduduk> temp_penduduk = daftar_penduduk;

    // Iterasi melalui setiap elemen di dalam daftar_penduduk
    while (!temp_penduduk.empty())
    {
        // Mengambil penduduk pertama dari queue
        Penduduk p = temp_penduduk.front();
        string fieldValue;

        // Menentukan nilai fieldValue berdasarkan field yang diberikan
        if (field == "nik")
            fieldValue = p.nik;
        else if (field == "nama")
            fieldValue = p.nama;
        else if (field == "umur")
            fieldValue = p.umur;
        else if (field == "jenisKelamin")
            fieldValue = p.jenisKelamin;
        else if (field == "agama")
            fieldValue = p.agama;
        else if (field == "alamat")
            fieldValue = p.alamat;
        else if (field == "tempatLahir")
            fieldValue = p.tempatLahir;
        else if (field == "tanggalLahir")
            fieldValue = p.tanggalLahir;

        // Memperbarui nilai maxLength dengan nilai terbesar antara maxLength dan panjang fieldValue
        maxLength = max(maxLength, static_cast<int>(fieldValue.length()));

        // Menghapus penduduk pertama dari queue
        temp_penduduk.pop();
    }

    // Mengembalikan nilai maxLength yang merupakan panjang maksimum dari field di dalam daftar_penduduk
    return maxLength;
}

// Fungsi menampilkan data penduduk menyeluruh
void tampilkanPenduduk(const queue<Penduduk> &daftar_penduduk)
{
    queue<Penduduk> temp_penduduk = daftar_penduduk;
	
	// Menghitung panjang maksimum dari setiap atribut dalam daftar penduduk
    int maxNIKLength = getMaxStringLength(daftar_penduduk, "nik");
    int maxNamaLength = getMaxStringLength(daftar_penduduk, "nama");
    int maxUmurLength = getMaxStringLength(daftar_penduduk, "umur");
    int maxJenisKelaminLength = getMaxStringLength(daftar_penduduk, "jenisKelamin");
    int maxTempatLahirLength = getMaxStringLength(daftar_penduduk, "tempatLahir");
    int maxTanggalLahirLength = getMaxStringLength(daftar_penduduk, "tanggalLahir");
    int maxAgamaLength = getMaxStringLength(daftar_penduduk, "agama");
    int maxAlamatLength = getMaxStringLength(daftar_penduduk, "alamat");

	// Menampilkan judul kolom
    cout << "Daftar Penduduk" << endl;
	cout << "\n===================================================================================================================================================\n";
	cout << "| " << setw(maxNIKLength) << "NIK" << " | " << setw(maxNamaLength) << "Nama" << " | " << "Umur" << setw(maxUmurLength)  << " | "
	     << setw(maxJenisKelaminLength) << "Jenis Kelamin" << " | " << setw(maxTempatLahirLength) << "Tempat Lahir" << " | " << setw(maxTanggalLahirLength) << "Tanggal Lahir" << " | "
	     << setw(maxAgamaLength) << "Agama" << " | " << setw(maxAlamatLength) << "Alamat" << " |" << endl;
	cout << "\n===================================================================================================================================================\n";

	// Menampilkan data penduduk satu per satu
    // Menampilkan atribut dari data penduduk dengan lebar maksimum yang telah ditentukan
    while (!temp_penduduk.empty())
    {
        Penduduk p = temp_penduduk.front();
        cout << "| " << setiosflags(ios::left) << setw(maxNIKLength) << p.nik << " |";
        cout << " " << setiosflags(ios::left) << setw(maxNamaLength) << p.nama << " |";
        cout << " " << setiosflags(ios::left) << setw(maxUmurLength) << p.umur << " |";
        cout << " " << setiosflags(ios::left) << setw(maxJenisKelaminLength) << p.jenisKelamin << " |";
        cout << " " << setiosflags(ios::left) << setw(maxTempatLahirLength) << p.tempatLahir << " |";
        cout << " " << setiosflags(ios::left) << setw(maxTanggalLahirLength) << p.tanggalLahir << " |";
        cout << " " << setiosflags(ios::left) << setw(maxAgamaLength) << p.agama << " | ";
        cout << " " << setiosflags(ios::left) << setw(maxAlamatLength) << p.alamat << " |";
        cout << "\n===================================================================================================================================================\n";
        temp_penduduk.pop();
    }
}

// Fungsi untuk mengedit data penduduk
bool ubahPenduduk(queue<Penduduk> &daftar_penduduk, string nik)
{
    queue<Penduduk> temp_penduduk;
    bool data_ditemukan = false;

    // Mencari penduduk dengan NIK yang sesuai
    while (!daftar_penduduk.empty())
    {
        Penduduk p = daftar_penduduk.front();
        daftar_penduduk.pop();

        if (p.nik == nik)
        {
            data_ditemukan = true;
            Penduduk p_ubah;
            int progress = 0;
            int nikLength = 16;

            // Meminta pengguna memasukkan data yang baru
            // Verifikasi data
            while (true)
            {
                system("cls");
                cout << "==========================================\n";
                cout << "Ubah Data Penduduk | " << progress << "/8" << endl;
                cout << "==========================================\n";
                cout << "NIK : ";
                getline(cin, p_ubah.nik);

                if (!cekNull(p_ubah.nik))
                {
                    cout << "Silahkan masukan data" << endl;
                    getch();
                }
                else
                {
                    if (p_ubah.nik.length() != nikLength)
                    {
                        cout << "Jumlah Digit NIK Tidak Sesuai" << endl;
                        getch();
                    }
                    else if (cekNIK(daftar_penduduk, p_ubah.nik))
                    {
                        cout << "NIK sudah terdaftar. Mohon masukkan NIK yang berbeda." << endl;
                        getch();
                    }
                    else if (!cek_angka(p_ubah.nik))
                    {
                        cout << "Input NIK tidak valid. Harap masukan NIK anda." << endl;
                        getch();
                    }
                    else
                    {
                        cout << "Data Berhasil Diubah" << endl;
                        getch();
                        progress++;
                        break;
                    }
                }
            }

            while (true)
            {
                system("cls");
                cout << "==========================================\n";
                cout << "Ubah Data Penduduk | " << progress << "/8" << endl;
                cout << "==========================================\n";
                cout << "Nama: ";
                getline(cin, p_ubah.nama);

                if (!cekNull(p_ubah.nama))
                {
                    cout << "Silahkan masukan data" << endl;
                    getch();
                }
                else
                {
                    cout << "Data Berhasil Diubah" << endl;
                    getch();
                    progress++;
                    break;
                }
            }

            while (true)
            {
                system("cls");
                cout << "==========================================\n";
                cout << "Ubah Data Penduduk | " << progress << "/8" << endl;
                cout << "==========================================\n";
                cout << "Umur: ";
                getline(cin, p_ubah.umur);

                if (!cekNull(p_ubah.umur))
                {
                    cout << "Silahkan masukan data" << endl;
                    getch();
                }
                else
                {
                    if (!cek_angka(p_ubah.umur))
                    {
                        cout << "Input umur tidak valid. Harap masukan umur anda." << endl;
                        getch();
                    }
                    else
                    {
                        cout << "Data Berhasil Diubah" << endl;
                        getch();
                        progress++;
                        p_ubah.umur = p_ubah.umur;
                        break;
                    }
                }
            }

            while (true)
            {
                system("cls");
                cout << "==========================================\n";
                cout << "Ubah Data Penduduk | " << progress << "/8" << endl;
                cout << "==========================================\n";
                cout << "Jenis Kelamin (L/P): ";
                getline(cin, p_ubah.jenisKelamin);

                if (!cekNull(p_ubah.jenisKelamin))
                {
                    cout << "Silahkan masukan data" << endl;
                    getch();
                }
                else
                {
                    if (p_ubah.jenisKelamin != "L" && p_ubah.jenisKelamin != "P")
                    {
                        cout << "Input jenis kelamin tidak valid. Harap masukkan 'L' atau 'P'." << endl;
                        getch();
                    }
                    else
                    {
                        cout << "Data Berhasil Diubah" << endl;
                        getch();
                        progress++;
                        p_ubah.jenisKelamin = p_ubah.jenisKelamin;
                        break;
                    }
                }
            }

            while (true)
			{
			    system("cls");
			    cout << "==========================================\n";
			    cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
			    cout << "==========================================\n";
			    cout << "Tempat Lahir (Kabupaten/Kota): ";
			    getline(cin, p_ubah.tempatLahir);

			    if (!cekNull(p_ubah.tempatLahir))
				{
			        cout << "Silahkan masukan data" << endl;
			        getch();
			    }
			    else
				{
			        cout << "Data Berhasil Ditambahkan" << endl;
			        getch();
			        progress++;
			        break;
			    }
			}

			while (true)
			{
			    system("cls");
			    cout << "==========================================\n";
			    cout << "Tambah Data Penduduk | " << progress << "/8" << endl;
			    cout << "==========================================\n";
			    cout << "Tanggal Lahir (dd-mm-yyyy): ";
			    getline(cin, p_ubah.tanggalLahir);

			    if (!cekNull(p_ubah.tanggalLahir))
				{
			        cout << "Silahkan masukan data" << endl;
			        getch();
			    }
			    else
				{
			        if (!cekFormatTanggal(p_ubah.tanggalLahir))
					{
			            cout << "Format tanggal tidak valid. Harap masukkan tanggal dengan format dd-mm-yyyy." << endl;
			            getch();
			        }
			        else
					{
			            cout << "Data Berhasil Ditambahkan" << endl;
			            getch();
			            progress++;
			            break;
			        }
			    }
			}

            while (true)
            {
                system("cls");
                cout << "==========================================\n";
                cout << "Ubah Data Penduduk | " << progress << "/8" << endl;
                cout << "==========================================\n";
                cout << "Agama : ";
                getline(cin, p_ubah.agama);

                if (!cekNull(p_ubah.agama))
                {
                    cout << "Silahkan masukan data" << endl;
                    getch();
                }
                else
                {
                    cout << "Data Berhasil Diubah" << endl;
                    getch();
                    progress++;
                    break;
                }
            }

            while (true)
            {
                system("cls");
                cout << "==========================================\n";
                cout << "Ubah Data Penduduk | " << progress << "/8" << endl;
                cout << "==========================================\n";
                cout << "Alamat: ";
                getline(cin, p_ubah.alamat);

                if (!cekNull(p_ubah.alamat))
                {
                    cout << "Silahkan masukan data" << endl;
                    getch();
                }
                else
                {
                    system("cls");
                    progress++;
                    break;
                }
            }

            // Menambahkan data penduduk yang telah diubah ke antrian sementara
            temp_penduduk.push(p_ubah);

            cout << "Data penduduk berhasil diubah." << endl;
        }
        else
        {
            // Menambahkan data penduduk yang tidak diubah ke antrian sementara
            temp_penduduk.push(p);
        }
    }

    // Mengembalikan data penduduk dari antrian sementara ke antrian utama
    while (!temp_penduduk.empty())
    {
        daftar_penduduk.push(temp_penduduk.front());
        temp_penduduk.pop();
    }

    return data_ditemukan;
}

// Fungsi menghapus data penduduk
bool hapusPenduduk(queue<Penduduk> &daftar_penduduk)
{
    system("cls");
    cout << "==========================================\n";
    cout << "Hapus Data Penduduk"<< endl;
    cout << "==========================================\n";
    string nik;
    cout << "Masukkan NIK penduduk yang ingin dihapus: ";
    getline(cin, nik);

    queue<Penduduk> temp_penduduk;
    bool data_ditemukan = false;

    // Mencari penduduk dengan NIK yang sesuai
    while (!daftar_penduduk.empty())
    {
        Penduduk p = daftar_penduduk.front();
        daftar_penduduk.pop();

        if (p.nik == nik)
        {
            data_ditemukan = true;
            cout << "Data penduduk berhasil dihapus." << endl;
            getch();
        }
        else
        {
            // Menambahkan data penduduk yang tidak dihapus ke antrian sementara
            temp_penduduk.push(p);
        }
    }

    // Mengembalikan data penduduk dari antrian sementara ke antrian utama
    while (!temp_penduduk.empty())
    {
        daftar_penduduk.push(temp_penduduk.front());
        temp_penduduk.pop();
    }

    return data_ditemukan;
}


// Fungsi untuk menampilkan data penduduk dalam urutan in-order
void inorderTraversal(Node* root, queue<Penduduk>& daftar_penduduk)
{
    if (root == nullptr) {
        return;
    }
	// Melakukan traversal in-order pada subpohon kiri
    inorderTraversal(root->left, daftar_penduduk);
    
    // Menghitung panjang maksimum dari setiap atribut dalam daftar penduduk
    int maxNIKLength = getMaxStringLength(daftar_penduduk, "nik");
    int maxNamaLength = getMaxStringLength(daftar_penduduk, "nama");
    int maxUmurLength = getMaxStringLength(daftar_penduduk, "umur");
    int maxJenisKelaminLength = getMaxStringLength(daftar_penduduk, "jenisKelamin");
    int maxTempatLahirLength = getMaxStringLength(daftar_penduduk, "tempatLahir");
    int maxTanggalLahirLength = getMaxStringLength(daftar_penduduk, "tanggalLahir");
    int maxAgamaLength = getMaxStringLength(daftar_penduduk, "agama");
    int maxAlamatLength = getMaxStringLength(daftar_penduduk, "alamat");
	
	// Menampilkan data penduduk saat ini dengan format yang rata kiri dan panjang maksimum yang telah ditentukan
    cout << "| " << setiosflags(ios::left) << setw(maxNIKLength) << root->data.nik << " |";
    cout << " " << setiosflags(ios::left) << setw(maxNamaLength) << root->data.nama << " |";
    cout << " " << setiosflags(ios::left) << setw(maxUmurLength) << root->data.umur << " |";
    cout << " " << setiosflags(ios::left) << setw(maxJenisKelaminLength) << root->data.jenisKelamin << " |";
    cout << " " << setiosflags(ios::left) << setw(maxTempatLahirLength) << root->data.tempatLahir << " |";
    cout << " " << setiosflags(ios::left) << setw(maxTanggalLahirLength) << root->data.tanggalLahir << " |";
    cout << " " << setiosflags(ios::left) << setw(maxAgamaLength) << root->data.agama << " |";
    cout << " " << setiosflags(ios::left) << setw(maxAlamatLength) << root->data.alamat << " |";
    cout << "\n===================================================================================================================================================\n";
    
    // Melakukan traversal in-order pada subpohon kanan
	inorderTraversal(root->right, daftar_penduduk);
}

// Fungsi utama lets go
int main()
{
    Node* root = nullptr;

    queue<Penduduk> daftar_penduduk;
    string pilihan;
    bool login_status = login();

    do
    {
        system("CLS");
        cout << "==========================================\n";
        cout << "         PENDATAAN SENSUS PENDUDUK        \n";
        cout << "==========================================\n";
        cout << "                   Menu                   " << endl;
        cout << "==========================================\n";
        cout << "1. Tambah Data Penduduk" << endl;
        cout << "2. Tampilkan Data Penduduk" << endl;
        cout << "3. Ubah Data Penduduk" << endl;
        cout << "4. Hapus Data Penduduk" << endl;
        cout << "5. Cari Data Penduduk" << endl;
        cout << "6. Keluar" << endl;
        cout << "==========================================\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cout << "\n==========================================\n";
        cin.ignore();
        cout << endl;
        system("cls");

        // Pilihan menu
        // Disini juga ada verifikasi jika data masih kosong
        if (pilihan == "1")
        {
            tambahPenduduk(daftar_penduduk);
            // Ini untuk menambahkan data kedalam tree apabila ada data yang masuk
            root = insertNode(root, daftar_penduduk.back());
            system("pause");
        }
        else if (pilihan == "2")
        {
            if (daftar_penduduk.empty())
            {
                cout << "==========================================\n";
                cout << "Belum Ada Data Penduduk" << endl;
                cout << "==========================================\n";
            }
            else
            {
                tampilkanPenduduk(daftar_penduduk);
            }
            system("pause");
        }
        else if (pilihan == "3")
        {
            if (daftar_penduduk.empty())
            {
                cout << "==========================================\n";
                cout << "Belum Ada Data Penduduk" << endl;
                cout << "==========================================\n";
            }
            else
            {
                system("cls");
                cout << "==========================================\n";
                cout << "Ubah Data Penduduk" << endl;
                cout << "==========================================\n";
                string nik;
                cout << "Masukkan NIK penduduk yang ingin diubah: ";
                getline(cin, nik);
                bool status_ubah = ubahPenduduk(daftar_penduduk, nik);
                if (!status_ubah)
                {
                    cout << "Data penduduk tidak ditemukan." << endl;
                }
                updateData(root, nik, daftar_penduduk.back());
            }

            system("pause");
        }
        else if (pilihan == "4")
        {
            if (daftar_penduduk.empty())
            {
                cout << "==========================================\n";
                cout << "Belum Ada Data Penduduk" << endl;
                cout << "==========================================\n";
            }
            else
            {
                bool status_hapus = hapusPenduduk(daftar_penduduk);
                if (!status_hapus)
                {
                    cout << "==========================================\n";
                    cout << "Data penduduk tidak ditemukan." << endl;
                    cout << "==========================================\n";
                }
            }
            system("pause");
        }
        else if (pilihan == "5")
		{
		    if (daftar_penduduk.empty())
		    {
		        cout << "==========================================\n";
		        cout << "Belum Ada Data Penduduk" << endl;
		        cout << "==========================================\n";
		    }
		    else
		    {
		        string nik;
		        cout << "Masukkan NIK penduduk yang ingin dicari: ";
		        getline(cin, nik);
		        // Ini untuk mencari dan menyimpan hasil dari pencarian tree
		        Node *result = searchNode(root, nik);
		        if (result != nullptr)
		        {
		        	// Menghitung panjang maksimum setiap atribut dalam data hasil
		        	int maxNIKLength = result->data.nik.length();
		            int maxNamaLength = result->data.nama.length();
		            int maxUmurLength;
		            
		            // Memeriksa apakah karakter pertama dari 'umur' adalah angka
		            if (isdigit(result->data.umur[0])) {
		            	// Jika karakter pertama adalah angka, konversi 'umur' menjadi integer menggunakan 'stoi()'
					    // dan menghitung panjang string hasil menggunakan 'to_string().length()'
		                maxUmurLength = to_string(stoi(result->data.umur)).length();
		            } else {
		            	// Jika karakter pertama bukan angka, langsung menghitung panjang dari 'umur'
		                maxUmurLength = result->data.umur.length();
		            }
		            int maxJenisKelaminLength = result->data.jenisKelamin.length();
		            int maxTempatLahirLength = result->data.tempatLahir.length();
		            int maxTanggalLahirLength = result->data.tanggalLahir.length();
		            int maxAgamaLength = result->data.agama.length();
		            int maxAlamatLength = result->data.alamat.length();

		            cout << "Data ditemukan:" << endl;
		            cout << "\n===================================================================================================================================================\n";
		            cout << "| " << setw(maxNIKLength) << "NIK" << " | " << setw(maxNamaLength) << "Nama" << " | " << "Umur" << setw(maxUmurLength)  << " | "
					     << setw(maxJenisKelaminLength) << "Jenis Kelamin" << " | " << setw(maxTempatLahirLength) << "Tempat Lahir" << " | " << setw(maxTanggalLahirLength) << "Tanggal Lahir" << " | "
					     << setw(maxAgamaLength) << "Agama" << " | " << setw(maxAlamatLength) << "Alamat" << " |" << endl;
		            cout << "\n===================================================================================================================================================\n";
					
					// Menampilkan data penduduk saat ini dengan format yang rata kiri dan panjang maksimum yang telah ditentukan
		            cout << "| " << setiosflags(ios::left) << setw(maxNIKLength) << result->data.nik << " |";
		            cout << " " << setiosflags(ios::left) << setw(maxNamaLength) << result->data.nama << " |";
		            cout << " " << setiosflags(ios::left) << setw(maxUmurLength) << result->data.umur << " |";
		            cout << " " << setiosflags(ios::left) << setw(maxJenisKelaminLength) << result->data.jenisKelamin << " |";
		            cout << " " << setiosflags(ios::left) << setw(maxTempatLahirLength) << result->data.tempatLahir << " |";
		            cout << " " << setiosflags(ios::left) << setw(maxTanggalLahirLength) << result->data.tanggalLahir << " |";
		            cout << " " << setiosflags(ios::left) << setw(maxAgamaLength) << result->data.agama << " |";
		            cout << " " << setiosflags(ios::left) << setw(maxAlamatLength) << result->data.alamat << " |";
					cout << "\n===================================================================================================================================================\n";
				}
				else
				{
					cout << "==========================================\n";
					cout << "Data tidak ditemukan." << endl;
					cout << "==========================================\n";
				}
			}
			system("pause");
		}

        else if (pilihan == "6")
        {
            cout << "Program selesai." << endl;
            getch();
        }
        else
        {
            system("cls");
            cout << "==========================================\n";
            cout << "Pilihan tidak valid." << endl;
            cout << "==========================================\n";
            system("pause");
        }
        cout << endl;
    } while (pilihan != "6" && login_status == true);

    return 0;
}
