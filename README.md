
## 🎼 Music Playlist Management System
This is a simple C-based program designed to manage a music playlist. It allows both administrators and users to interact with a database of music. The program includes functionality to add, edit, delete, list, search, and play music tracks. The data is stored in a text file ```(database.txt)``` for simplicity.

## 🗂️ Features
**Admin Features :**
- Add Music : Admin can add new music records (ID, Title, Artist, and Link).
- Edit Music : Admin can modify existing music records based on ID.
- List Music : Admin can view the entire list of music in the database.
- Delete Music : Admin can remove music records by ID.

**User Features :**
- Play Music : Users can play music by selecting a track based on its ID. The program attempts to open the link of the track in the default web browser.
- Search Music : Users can search for music by title or artist.
- List Music : Users can view the list of all available music in the database.

**Example Interaction**
```bash
Playlist Music
-----------------
[1] Admin
[2] User
[0] Exit

Pilih (0-2): 1

[1] Tambah Data Musik
[2] Edit Data Musik
[3] List Musik
[4] Hapus Data Musik
[0] Exit

Pilih (0-4): 1
Tambah Data Musik

ID          : 1
Judul Lagu  : song title
Penyanyi    : name of singer
Link Lagu   : https://example.com/

Data berhasil ditambahkan!

```

**Data Storage**\
The music data is stored in a text file called database.txt where each music entry is saved in a CSV format:
```bash
ID,Title,Artist,Link
1,Let It Be,The Beatles,https://www.youtube.com/watch?v=K8o1-1T5S04
2,Shape of You,Ed Sheeran,https://www.youtube.com/watch?v=JGwWNGJdvx8

```

## 📟 How to Compile and Run
**Compilation :**
```bash
gcc -o music_playlist playlistmusic.c
```
**Running :**
```bash
./playlistmusic
```
**Requirements**
- A C compiler (e.g., GCC).
- The program uses basic file operations, so ensure write access to the directory where the program is run.
- For music playback, the program uses the default web browser to open the provided link.
- The music data file (database.txt) must be in the same directory as the program.

```bash
  🦫 it's only college assignment :)
```
## 🤡 Authors

- [@rafii-pii](https://github.com/rafii-pi)


