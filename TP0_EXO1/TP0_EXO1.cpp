#include <iostream>
#include <string>
using namespace std;

struct songnode {
    int id;
    string artiste;
    string title; 
    float duration; 
    songnode* next; 
    songnode* prev; 
    
    songnode(int id, const string& title, const string& artiste, float duration){
        this->id = id;
        this->title = title;
        this->artiste = artiste;
        this->duration = duration;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class playlist {
    public:
    songnode* head;
    songnode* tail;

    playlist() : head(nullptr), tail(nullptr) {}
    ~playlist() {
        
    }

    void addsong(int id, const string& title, const string& artiste, float duration){
        songnode* node = new songnode(id, title, artiste, duration);
        if (head == nullptr) {
        
            node->next = node->prev = node;
            head = tail = node;
        } else {
           
            tail->next = node;
            node->prev = tail;
            node->next = head;
            head->prev = node;
            tail = node;
        }
    }

    void Display(){
        songnode* current = head;
        if (!head) return;
        do {
            cout << "ID: " << current->id << ", Title: " << current->title << ", Artiste: " << current->artiste << ", Duration: " << current->duration << '\n';
            current = current->next;
        } while (current != head);
    }
    void remove(const string& t){
        if (head==nullptr) return;
        songnode* current = head;
        bool found;
        do {
            if (current->title == t) {
                found = true;
                break;
            }
            current = current->next;
        } while (current != head);
        if (found==false) return;

        
        if (current->next == current) {
            delete current;
            head = tail = nullptr;
            return;
        }

        
        current->prev->next = current->next;
        current->next->prev = current->prev;

        if (current == head) head = current->next;
        if (current == tail) tail = current->prev;

        delete current;
    }
    void playnext(){
        head = head->next;
        cout << "Now playing: " << head->title << " by " << head->artiste << '\n';
        head = head->next;
        cout << "Now playing: " << head->title << " by " << head->artiste << '\n';
        head = head->next;
        cout << "Now playing: " << head->title << " by " << head->artiste << '\n';
        if (!head) return;  
    }
    void playprevious(){
        head = head->prev;
        cout << "Now playing: " << head->title << " by " << head->artiste << '\n';
        head = head->prev; 
        cout << "Now playing: " << head->title << " by " << head->artiste << '\n';
        if (!head) return;
    }
    void searchSong(string title){
        if (!head) return;
        songnode* current = head;
        bool found = false;
        do {
            if (current->title == title) {
                found = true;
                break;
            }
            current = current->next;
        } while (current != head);
        if (found) {
            cout << "Song found: ID: " << current->id << ", Title: " << current->title << ", Artiste: " << current->artiste << ", Duration: " << current->duration << '\n';
        } else {
            cout << "Song not found in the playlist." << '\n';
        }

    }
   void repeatCurrent(){ 
        if (!head) return;
        cout << "Replaying: " << head->title << " by " << head->artiste << '\n';
    }
       
}; 


int main(){
    char r;
    playlist pl;
    
    pl.addsong(1,"scars", "Novulent", 1.35);
    pl.addsong(2,"NIGHT LIKE THIS", "KID Laroi", 2.32);
    pl.addsong(3,"Blinding lights ", "The weekend", 3.42);
    pl.addsong(4,"HER", "JVKE", 2.52);
    pl.addsong(5,"Sweater Weather", "The Neighbourhood", 3.56);
    pl.addsong(6,"Consume", "chase atlantic", 4.42);
     pl.Display();
    cout << "do you want to remove a song? y/n answer only" << '\n';
    cin >> r;
    if (r=='y' || r=='Y'){
        cout << "give a title of the song you want to delete" << '\n';
        string t;
        getline(cin >> ws, t);
        pl.remove(t);
    }
    pl.Display();
    cout << "playing next song" << '\n';
    pl.playnext();
    cout << "playing previous song" << '\n';
    pl.playprevious();
    cout << "search for a song by title" << '\n';
    string s;
    getline(cin >> ws, s);
    pl.searchSong(s);
    cout << "repeating current song" << '\n';
    pl.repeatCurrent();

    return 0;
}
