#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Music {
    int id;
    char judul[100];
    char penyanyi[100];
    char link[100];
} Music;

void Tambah() {
    Music m;
    FILE *database = fopen("database.txt", "a");
    if (!database) {
        printf("Tidak dapat membuka file!\n");
        return;
    }
    printf("ID\t\t: ");
    scanf("%d", &m.id);
    getchar();
    printf("Judul Lagu\t: ");
    fgets(m.judul, sizeof(m.judul), stdin);
    m.judul[strcspn(m.judul, "\n")] = '\0';
    printf("Penyanyi/Band\t: ");
    fgets(m.penyanyi, sizeof(m.penyanyi), stdin);
    m.penyanyi[strcspn(m.penyanyi, "\n")] = '\0';
    printf("Link Lagu\t: ");
    fgets(m.link, sizeof(m.link), stdin);
    m.link[strcspn(m.link, "\n")] = '\0';

    fprintf(database, "%d,%s,%s,%s\n", m.id, m.judul, m.penyanyi, m.link);
    fclose(database);
    printf("\nData berhasil ditambahkan!\n");
}

void Edit() {
    int id, found = 0;
    Music m;
    FILE *database = fopen("database.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!database || !temp) {
        printf("Tidak dapat membuka file!\n");
        return;
    }

    printf("Masukkan ID Musik yang ingin diedit: ");
    scanf("%d", &id);
    
    while (fscanf(database, "%d,%99[^,],%99[^,],%99[^\n]\n", &m.id, m.judul, m.penyanyi, m.link) != EOF) {
        if (m.id == id) {
            found = 1;
            getchar();
            printf("Edit Judul Lagu\t: ");
            fgets(m.judul, sizeof(m.judul), stdin);
            m.judul[strcspn(m.judul, "\n")] = '\0';
            printf("Edit Penyanyi/Band\t: ");
            fgets(m.penyanyi, sizeof(m.penyanyi), stdin);
            m.penyanyi[strcspn(m.penyanyi, "\n")] = '\0';
            printf("Edit Link Lagu\t: ");
            fgets(m.link, sizeof(m.link), stdin);
            m.link[strcspn(m.link, "\n")] = '\0';
        }
        fprintf(temp, "%d,%s,%s,%s\n", m.id, m.judul, m.penyanyi, m.link);
    }

    fclose(database);
    fclose(temp);

    if (found) {
        remove("database.txt");
        rename("temp.txt", "database.txt");
        printf("Data berhasil diedit!\n");
    } else {
        remove("temp.txt");
        printf("ID tidak ditemukan!\n");
    }
}

void List() {
    Music m[100];
    FILE *database = fopen("database.txt", "r");
    if (!database) {
        printf("Tidak dapat membuka file!\n");
        return;
    }
    int count = 0;
    while (fscanf(database, "%d,%99[^,],%99[^,],%99[^\n]\n", &m[count].id, m[count].judul, m[count].penyanyi, m[count].link) != EOF) {
        count++;
    }
    printf("%-6s   %-20s   %-20s   %-40s\n", "ID", "Judul Lagu", "Penyanyi/Band", "Link Lagu");
    printf("----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-6d   %-20s   %-20s   %-40s\n", m[i].id, m[i].judul, m[i].penyanyi, m[i].link);
    }
    printf("----------------------------------------------------------------------------------------------------------\n\n");
    fclose(database);
}

void Hapus() {
    int id, found = 0;
    Music m;
    FILE *database = fopen("database.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!database || !temp) {
        printf("Tidak dapat membuka file!\n");
        return;
    }

    printf("Masukkan ID Musik yang ingin dihapus: ");
    scanf("%d", &id);
    
    while (fscanf(database, "%d,%99[^,],%99[^,],%99[^\n]\n", &m.id, m.judul, m.penyanyi, m.link) != EOF) {
        if (m.id == id) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d,%s,%s,%s\n", m.id, m.judul, m.penyanyi, m.link);
    }

    fclose(database);
    fclose(temp);

    if (found) {
        remove("database.txt");
        rename("temp.txt", "database.txt");
        printf("Data berhasil dihapus!\n");
    } else {
        remove("temp.txt");
        printf("ID tidak ditemukan!\n");
    }
}

void Cari(){
	Music m[100];
    FILE *database = fopen("database.txt", "r");
    if (!database) {
        printf("Tidak dapat membuka file!\n");
        return;
    }
    char cari[100];
    int count = 0;
    //cari judul
    getchar();
    printf("Cari Judul Lagu/Penyanyi : ");
    fgets(cari, sizeof(cari), stdin);
    
    while (fscanf(database, "%d,%99[^,],%99[^,],%99[^\n]\n", &m[count].id, m[count].judul, m[count].penyanyi, m[count].link) != EOF) {
        count++;
    }
    printf("\n%-6s   %-20s   %-20s   %-40s\n", "ID", "Judul Lagu", "Penyanyi/Band", "Link Lagu");
    printf("----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
    	//strcspn buat hilangkan enter diakhir , 0 kan semua \n
		cari[strcspn(cari, "\n")] = 0;
		m[i].judul[strcspn(m[i].judul, "\n")] = 0;
		m[i].penyanyi[strcspn(m[i].penyanyi, "\n")] = 0;
		//strcmp buat ngecek apakah string nya sama gak? tipe nya integer. jika nol, artinya terdapat nol perbedaan yang artinya judulny ada
		int cek1 = strcmp(cari, m[i].judul);
		int cek2 = strcmp(cari, m[i].penyanyi);
        
        if(cek1 == 0 || cek2 == 0){
			printf("%-6d   %-20s   %-20s   %-40s\n", m[i].id, m[i].judul, m[i].penyanyi, m[i].link);
		}
    }
    printf("----------------------------------------------------------------------------------------------------------\n\n");
    fclose(database);
}

void Putar() {
    Music m[100];
    FILE *database = fopen("database.txt", "r");
    if (!database) {
        printf("Tidak dapat membuka file!\n");
        return;
    }

    int count = 0;
    int putar;
    char link_putar[100] = "none";

    printf("Tulis ID lagu yang ingin anda putar : ");
    scanf("%d", &putar);

    // Membaca data dari file database
    while (fscanf(database, "%d,%99[^,],%99[^,],%99[^\n]\n", &m[count].id, m[count].judul, m[count].penyanyi, m[count].link) != EOF) {
        count++;
    }
    // Menampilkan data musik
    printf("\n%-6s   %-20s   %-20s   %-40s\n", "ID", "Judul Lagu", "Penyanyi/Band", "Link Lagu");
    printf("----------------------------------------------------------------------------------------------------------\n");

    // Mencari dan menampilkan musik berdasarkan ID
    for (int i = 0; i < count; i++) {
        if (putar == m[i].id) {
            printf("%-6d   %-20s   %-20s   %-40s\n", m[i].id, m[i].judul, m[i].penyanyi, m[i].link);
            strcpy(link_putar, m[i].link);  // Menyimpan link untuk diputar
        }
    }
    printf("----------------------------------------------------------------------------------------------------------\n\n");

    char run;
    printf("Apakah anda ingin memutar lagu ini (y/n)? ");
    scanf(" %c", &run);

    if (run == 'y' || run == 'Y') {
    	if (strcmp(link_putar, "none") != 0){
	        // Menyusun perintah dengan link yang sesuai
	        char command[256];
	        // Pastikan link dimasukkan dengan benar dalam perintah `start`
	        snprintf(command, sizeof(command), "start msedge --start-fullscreen %s", link_putar);
	        // Menjalankan perintah untuk membuka link
	        system(command);
		}
		else{
			printf("\ncan't open bos,  engga ada link nya!\n");
		}
        strcpy(link_putar, "none");
    }
    fclose(database);
}


int main() {
    while (1) {
    	system("cls");
        printf("Playlist Music\n-----------------\n");
        int opsi;
        printf("\n[1] Admin\n[2] User\n[0] Exit\n\nPilih (0-2): ");
        scanf("%d", &opsi);

        if (opsi == 1) {
            while (1) {
                int opsi1;
                printf("\n[1] Tambah Data Musik\n[2] Edit Data Musik\n[3] List Musik\n[4] Hapus Data Musik\n[0] Exit\n\nPilih (0-4) : ");
                scanf("%d", &opsi1);

                if (opsi1 == 1) {
                    printf("\nTambah Data Musik\n\n");
                    Tambah();
                } else if (opsi1 == 2) {
                    printf("\nEdit Data Musik\n\n");
                    Edit();
                } else if (opsi1 == 3) {
                    printf("\nList Data Musik\n\n");
                    List();
                } else if (opsi1 == 4) {
                    printf("\nHapus Data Musik\n\n");
                    Hapus();
                } else if (opsi1 == 0) {
                    printf("\nExit\n\n");
                    break;
                } else {
                    printf("\nWrong input!\n\n");
                }
            }
        } else if (opsi == 2) {
            while (1) {
                int opsi1;
                printf("\n[1] Putar Musik\n[2] Cari Musik\n[3] List Musik\n[0] Exit\n\nPilih (0-4): ");
                scanf("%d", &opsi1);

                if (opsi1 == 1) {
                    printf("\nPutar Musik\n\n");
                    Putar();
                } else if (opsi1 == 2) {
                    printf("\nCari Musik\n\n");
                    Cari();
                } else if (opsi1 == 3) {
                    printf("\nList Musik\n\n");
                    List();
                } else if (opsi1 == 0) {
                    printf("\nExit\n\n");
                    break;
                } else {
                    printf("\nWrong input!\n\n");
                }
            }
        } else if (opsi == 0) {
            printf("\nProgram berakhir!\n\n");
            break;
        } else {
            printf("\nWrong input!\n\n");
        }
    }
}
