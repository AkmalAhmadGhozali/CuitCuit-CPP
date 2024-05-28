#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

const int MaxGroup = 10, MaxUser = 50, MaxFollowing = 5, MaxTopic = 10;

struct UserStruct {
    int Group;
    string Name;
    string Interest[3];
    string Following[MaxFollowing];
    int NumberFollowed;
    int NumberOfFollowers;
};
UserStruct User[MaxUser];
int NumberOfGroup = 0;

static void MostGroupTopic(int NumberOfGroup, int NumberOfUsers) {
    struct GroupTopicStruct {
        int GroupId;
        int UserId;
        string name;
        string Topic;
    };
    GroupTopicStruct GroupTopic[100], TempGroupTopic;

    struct MostTopicStruct {
        int GroupId;
        string Topic;
        int NumberOfTopic;
    };
    MostTopicStruct MostTopic[100], TempMostTopic;
    string Topic, Temp;
    int GroupId, NumberOfTopic, i, j, k;

    k = 0;
    for (i = 1; i <= NumberOfGroup; i++) {
        for (j = 1; j <= NumberOfUsers; j++) {
            if (User[j].Group == i) {
                GroupTopic[k].GroupId = i;
                GroupTopic[k].UserId = j;
                GroupTopic[k].name = User[j].Name;
                GroupTopic[k].Topic = User[j].Interest[0];
                k++;
                GroupTopic[k].GroupId = i;
                GroupTopic[k].UserId = j;
                GroupTopic[k].name = User[j].Name;
                GroupTopic[k].Topic = User[j].Interest[1];
                k++;
                GroupTopic[k].GroupId = i;
                GroupTopic[k].UserId = j;
                GroupTopic[k].name = User[j].Name;
                GroupTopic[k].Topic = User[j].Interest[2];
                k++;
            }
        }
    }

    /*------------------------------------------------------
    mencetak semua topic dalam group
    for (i = 0; i < k; i++) {
        cout << GroupTopic[i].GroupId << "\t" << GroupTopic[i].UserId << "\t";
        cout << GroupTopic[i].name << "\t" << GroupTopic[i].Topic << endl;
    }
    --------------------------------------------------------*/

    /*------------------------------------------------------
    Mengurutkan topic group berdasarkan GroupId dan Topic
    --------------------------------------------------------*/
    for (i = 0; i < k; i++) {
        for (j = i; j <= k; j++) {
            if (GroupTopic[i].GroupId == GroupTopic[j].GroupId &&
                GroupTopic[i].Topic > GroupTopic[j].Topic) {
                TempGroupTopic = GroupTopic[i];
                GroupTopic[i]  = GroupTopic[j];
                GroupTopic[j]  = TempGroupTopic;
            }
        }
    }

    /*------------------------------------------------------
    mencetak semua topic dalam group
    for (i = 0; i < k; i++) {
        cout << GroupTopic[i].GroupId << "\t" << GroupTopic[i].UserId << "\t";
        cout << GroupTopic[i].name << "\t" << GroupTopic[i].Topic << endl;
    }
    --------------------------------------------------------*/

    /*------------------------------------------------------  
    merekap semua topic dalam group
    --------------------------------------------------------*/
    GroupId       = GroupTopic[0].GroupId;
    Topic         = GroupTopic[0].Topic;
    NumberOfTopic = 1;
    j = 0;
    for (i = 1; i < k; i++) {
        if (Topic != GroupTopic[i].Topic) {
            MostTopic[j].GroupId       = GroupId;
            MostTopic[j].Topic         = Topic;
            MostTopic[j].NumberOfTopic = NumberOfTopic;
            j++;
            //------------------------------------------------
            GroupId       = GroupTopic[i].GroupId;
            Topic         = GroupTopic[i].Topic;
            NumberOfTopic = 1;
        }
        else NumberOfTopic++;
    }

    /*------------------------------------------------------
    mengurutkan hasil rekap topic berdasarkan GroupId dan jumlah rekapitulasinya
    --------------------------------------------------------*/
    for (i = 0; i < j; i++) {
        for (k = i; k <= j; k++) {
            if (MostTopic[i].GroupId == MostTopic[k].GroupId &&
                MostTopic[i].NumberOfTopic < MostTopic[k].NumberOfTopic) {
                TempMostTopic = MostTopic[i];
                MostTopic[i]  = MostTopic[k];
                MostTopic[k]  = TempMostTopic;
            }
        }
    }

    /*------------------------------------------------------
    mecetak hasil rekap topic
    for (i = 0; i < j; i++) {
        cout << MostTopic[i].GroupId << "\t";
        cout << MostTopic[i].Topic << "\t";
        cout << MostTopic[i].NumberOfTopic << endl;
    }
    --------------------------------------------------------*/

    /*------------------------------------------------------
    output query grouptopic
    --------------------------------------------------------*/
    GroupId       = MostTopic[0].GroupId;
    Topic         = MostTopic[0].Topic;
    NumberOfTopic = MostTopic[0].NumberOfTopic;
    cout << Topic;
    for (i = 1; i < j; i++) {
        if (GroupId == MostTopic[i].GroupId &&  NumberOfTopic == MostTopic[i].NumberOfTopic) {
            GroupId       = MostTopic[i].GroupId;
            Topic         = MostTopic[i].Topic;
            NumberOfTopic = MostTopic[i].NumberOfTopic;
            cout << "," << Topic;
        }
        else if (GroupId != MostTopic[i].GroupId) {
            GroupId       = MostTopic[i].GroupId;
            Topic         = MostTopic[i].Topic;
            NumberOfTopic = MostTopic[i].NumberOfTopic;
            cout << endl << Topic;
        }
    }
    cout << endl;
}

static void MostFollowed(int NumberOfUsers) {
    string Temp, MostFollowedUsers[MaxUser];
    int i, j, Index;
    /*------------------------------------------------------
    menemukan nilai pengikut tertinggi
    --------------------------------------------------------*/
    j = User[1].NumberOfFollowers;
    for (i = 2; i <= NumberOfUsers; i++) {
        if (User[i].NumberOfFollowers > j) {
            j = User[i].NumberOfFollowers;
        }
    }

    /*------------------------------------------------------
    menemukan semua pengguna dengan pengikut tertinggi
    --------------------------------------------------------*/
    Index = 0;
    for (i = 1; i <= NumberOfUsers; i++) {
        if (User[i].NumberOfFollowers == j) {
            Index++;
            MostFollowedUsers[Index] = User[i].Name;
        }
    }
    /*------------------------------------------------------
    mengurutkan semua pengguna dengan pengikut tertinggi
    --------------------------------------------------------*/
    for (i = 1; i < Index; i++) {
        for (j = i + 1; j <= Index; j++) {
            if (MostFollowedUsers[i] > MostFollowedUsers[j]) {
                Temp                 = MostFollowedUsers[i];
                MostFollowedUsers[i] = MostFollowedUsers[j];
                MostFollowedUsers[j] = Temp;
            }
        }
    }

    /*------------------------------------------------------
    Output query mostfollowed
    --------------------------------------------------------*/
    Temp = "";
    for (i = 1; i <= Index; i++) {
        if (Temp == "") Temp = MostFollowedUsers[i];
        else Temp += "," + MostFollowedUsers[i];
    }
    cout << Temp << endl;
}

static void FindSuggestFriend(string UserName, int NumberOfUsers) {
    struct SuggestFriendStruct {
        int Id;
        string Name;
        bool Suggest;
    };
    SuggestFriendStruct SuggestFriend[MaxUser], TempSuggestFriend;
    int i, j, Index = 0, UserId = 0, GroupId = 0;
    string Temp;

    /*--------------------------------------------------------
    menemukan index user dan index group 
    -------------------------------------------------------- */ 
    for (i = 1; i <= NumberOfUsers; i++) {
        if (User[i].Name == UserName) {
            UserId = i;
            GroupId = User[i].Group;
            break;
        }
    }

    /*--------------------------------------------------------
    menemukan semua anggota yang satu group dengan User
    -------------------------------------------------------- */
    for (i = 1; i <= NumberOfUsers; i++) {
        if (User[i].Group == GroupId && User[i].Name != UserName) {
            Index++;
            SuggestFriend[Index].Id = i;
            SuggestFriend[Index].Name = User[i].Name;
            SuggestFriend[Index].Suggest = true;
            //Mengeliminasi semua anggota group yang sudah mem-follow User (Enable -> false)
            for (j = 0; j < MaxFollowing; j++) {
                if (User[i].Following[j] == UserName) {
                    SuggestFriend[Index].Suggest = false;
                    break;
                }
            }
        }
    }

    /*--------------------------------------------------------
    Mengeliminasi semua anggota 1 group yang sudah di-follow User (Enable -> false)
    -------------------------------------------------------- */
    for (i = 0; i < MaxFollowing; i++) {
        for (j = 1; j <= Index; j++) {
            if (SuggestFriend[j].Name == User[UserId].Following[i]) {
                SuggestFriend[j].Suggest = false;
                break;
            }
        }
    }

    /*--------------------------------------------------------
    Mengurutkan semua anggota 1 group berdasarkan nama
    -------------------------------------------------------- */
    for (i = 1; i < Index; i++) {
        for (j = i; j <= Index; j++) {
            if (SuggestFriend[i].Name > SuggestFriend[j].Name) {
                TempSuggestFriend = SuggestFriend[i];
                SuggestFriend[i]  = SuggestFriend[j];
                SuggestFriend[j]  = TempSuggestFriend;
            }
        }
    }
    /*--------------------------------------------------------
    mencetak semua anggota 1 group 
    cout << "Daftar anggota yang se-group " << User[UserId].Name << endl;
    cout << "-------------------------------------" << endl;
    cout << "UserId\tName\t\tSuggest" << endl;
    cout << "-------------------------------------" << endl;
    for (j = 1; j <= Index; j++) {
        cout << SuggestFriend[j].Id << "\t" << SuggestFriend[j].Name << "\t\t" << SuggestFriend[j].Suggest << endl;
    }
    -------------------------------------------------------- */

    /*--------------------------------------------------------
    Output query suggestfriend
    -------------------------------------------------------- */
    Temp = "";
    for (j = 1; j <= Index; j++) {
        if (SuggestFriend[j].Suggest == true) {
            if (Temp == "") Temp = SuggestFriend[j].Name;
            else Temp += "," + SuggestFriend[j].Name;
        }
    }
    cout << Temp << endl;
}

static void ConnectUser(string UserName1, string UserName2, int NumberOfUsers, bool Message) {
    int i, j;
    //Temukan pengguna untuk mendaftarkan pengguna yang diikuti dan jumlahnya
    for (i = 1; i <= NumberOfUsers; i++) {
        if (UserName1 == User[i].Name) {
            int n = User[i].NumberFollowed;
            User[i].Following[n] = UserName2;
            User[i].NumberFollowed++;
            break;
        }
    }
    //Temukan yang diikuti untuk merubah jumlah pengikutnya
    for (j = 1; j <= NumberOfUsers; j++) {
        if (UserName2 == User[j].Name) {
            if (User[i].Group == 0 && User[j].Group == 0 && NumberOfGroup == 0) {
                NumberOfGroup = 1;
                User[i].Group = 1;
                User[j].Group = 1;
            }
            else if (User[i].Group == 0 && User[j].Group == 0 && NumberOfGroup > 0) {
                NumberOfGroup++;
                User[i].Group = NumberOfGroup;
                User[j].Group = NumberOfGroup;
            }
            else if (User[i].Group == 0 && User[j].Group > 0) {
                User[i].Group = User[j].Group;
            }
            else if (User[i].Group > 0 && User[j].Group == 0) {
                User[j].Group = User[i].Group;
            }
            User[j].NumberOfFollowers++;
            if (Message == true) cout << "connect " << User[i].Name << " " << User[j].Name << " success" << endl;
            break;
        }
    }
}

static void InsertUser(int GroupId, string Name, string Interest1, string Interest2, string Interest3, int UserNumber, bool Message) {
    int i;
    bool RegisteredUser = false;

    for (i = 1; i < UserNumber; i++) {
        if (User[i].Name == Name) {
            RegisteredUser = true;
            break;
        }
    }
//    if (RegisteredUser == true) cout << "the user " << Name << " is already registered" << endl;
    if (RegisteredUser == true) cout << "WRONG FORMAT" << endl;
    else {
        User[UserNumber].Group = GroupId;
        User[UserNumber].Name = Name;
        User[UserNumber].Interest[0] = Interest1;
        User[UserNumber].Interest[1] = Interest2;
        User[UserNumber].Interest[2] = Interest3;
        for (i = 0; i < MaxFollowing; i++) {
            User[UserNumber].Following[i] = "";
        }
        User[UserNumber].NumberFollowed = 0;
        User[UserNumber].NumberOfFollowers = 0;
        if (Message == true) cout << Name << " inserted" << endl;
    }
}
                              
static int FindMinCuit(int level, int MinimumCuit, string User1, string User2, string User3, string User4, int NumberOfUsers) {
    int i, j, n;
    string Following;

    if (User1 != "") {
        for (i = 1; i <= NumberOfUsers; i++) {
            if (User[i].Name == User1) {
                n = User[i].NumberFollowed;
                break;
            }
        }
        if (n > 0) {
            level++;
            for (j = 0; j < MaxFollowing; j++) {
                Following = User[i].Following[j];
                if (Following != "" && Following != User3) {
                    /*
                    cout << "Level     : " << level << endl;
                    cout << "UserName1 : " << User1 << endl;
                    cout << "Following : " << Following << endl;
                    cout << "UserName3 : " << User3 << endl;
                    cout << "UserName4 : " << User4 << endl;
                    cout << "-------------------" << endl;
                    */
                    if (Following == User4) {
                        if (MinimumCuit == 0 || level < MinimumCuit) MinimumCuit = level;
                    }
                    MinimumCuit = FindMinCuit(level, MinimumCuit, Following, User2, User1, User4, NumberOfUsers);
                }
            }
        }
    }
    return MinimumCuit;
}

static void MinCuit(string UserName1, string UserName2, int NumberOfUsers, bool Message) {
    int level = 0, MinimumCuit = 0;

    MinimumCuit = FindMinCuit(level, MinimumCuit, UserName1, UserName2, UserName1, UserName2, NumberOfUsers);
    cout << MinimumCuit-1 << endl;
}

static void ReadData(string FileName) {
    ifstream inputFile;
    string Data;
    int DataNumber = 0;
    int NumberOfUsers = 0;
    int NumberOfConnection = 0;
    int UserNumber = 0;

    //Membaca file text
    inputFile.open(FileName);
    if (inputFile.is_open() == true) {
        //cout << "Reading file: " << FileName << endl;
        //Membaca baris per baris perintah hingga end of file dari file text
        while (getline(inputFile, Data)) {
            DataNumber++;
            if (DataNumber == 1) NumberOfUsers = stoi(Data);
            else if (DataNumber == 2) NumberOfConnection = stoi(Data);
            else {
                string Query, Querys[5] = {"","","","",""};
                //1. Mem-parsing Query berdasarkan spasi " "
                int index = 0;
                stringstream ss(Data);
                while (getline(ss, Query, ' ')) {
                    Querys[index] = Query;
                    index++;
                }
                //2. Mendaftarkan Pengguna & Koneksinya secara otomatis
                if (DataNumber < (NumberOfUsers + NumberOfConnection + 2)) {
                //2.1. Mendaftarkan Pengguna
                    if (DataNumber < (NumberOfUsers + 3)) 
                        InsertUser(0, Querys[0], Querys[1], Querys[2], Querys[3], ++UserNumber, false);
                    else 
                //2.2. Mendaftarkan Koneksinya
                        ConnectUser(Querys[0], Querys[1], UserNumber, false);
                }
                else {
                //3. Memproses Query / Token
                    if (Querys[0] == "mostfollowed")
                        //3.1. Memproses Query mostfollowed
                        MostFollowed(UserNumber);
                    else if (Querys[0] == "insert")
                        //3.2. Memproses Query insert
                        InsertUser(0, Querys[1], Querys[2], Querys[3], Querys[4], ++UserNumber, true);
                    else if (Querys[0] == "numgrup")
                        //3.3. Memproses Query numgrup
                        cout << NumberOfGroup << endl;
                    else if (Querys[0] == "mincuit")
                        //3.4. Memproses Query mincuit
                        MinCuit(Querys[1], Querys[2], UserNumber, true);
                    else if (Querys[0] == "connect")
                        //3.5. Memproses Query connect
                        ConnectUser(Querys[1], Querys[2], UserNumber, true);
                    else if (Querys[0] == "grouptopic")
                        //3.6. Memproses Query grouptopic
                        MostGroupTopic(NumberOfGroup, UserNumber);
                    else if (Querys[0] == "suggestfriend")
                        //3.7. Memproses Query suggestfriend
                        FindSuggestFriend(Querys[1], UserNumber);
                    else cout << "WRONG FORMAT" << endl;
                }
            }
        }
        inputFile.close();
    }
    else cout << "Error opening file: " << FileName << endl;
}

int main() {
/*
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Error: Penggunaan: " << argv[0] << " <nama_file>" << endl;
        return 1;
    }
    ReadData(argv[1]);
*/
    ReadData("D:\\kuliah\\project_asd_2\\data_cuitcuit.txt");
    //D:\Kuliah\project_asd_2
}