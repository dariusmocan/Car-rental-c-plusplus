#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;


class Masina{ //clasa masinilor ce vor fi adaugate
private:
    char nume[20];
    char model[20];
    char locuri[5];
    char disp[5];

public:

     char* getNume()  {
        return nume;
    }

     char* getModel()  {
        return model;
    }

     char* getLocuri()  {
        return locuri;
    }

     char* getDisp()  {
        return disp;
    }

    void setNume( char* newNume) {
        strcpy_s(nume, newNume);
    }

    void setModel( char* newModel) {
        strcpy_s(model, newModel);
    }

    void setLocuri( char* newLocuri) {
        strcpy_s(locuri, newLocuri);
    }

    void setDisp( char* newDisp) {
        strcpy_s(disp, newDisp);
    }

    friend int operator ==(const Masina &m1,const Masina &m2); //supraincarcarea operatorului == pentru compararea a doua masini

};

int operator ==(const Masina &m1,const Masina &m2){
    if((strcmp(m1.nume,m2.nume)==0) && (strcmp(m2.model,m2.model)==0) && (strcmp(m1.locuri,m2.locuri)==0) &&
       (strcmp(m1.disp,m2.disp)==0))
        return 1;
    else
        return 0;
}


int meniu(const char[]);

int afisare(const char path[]) {
    system("cls");
    cout << "\033[1;31m";
    cout << "    -AUTOTURISME-\n";

    ifstream filep(path);
    int nr, i = 0;
    int choice = 0;
    Masina masina[101];
        while (filep.getline(masina[i].getNume(), 20)) {
            filep.getline(masina[i].getModel(), 20);
            filep.getline(masina[i].getLocuri(), 5);
            filep.getline(masina[i].getDisp(), 5);
            i = i + 1;
        } //am retinut toate datele din fisier intr-un vector cu mai multe elemente. cu ajutorul lui i retinem indexul masinii
        nr = i;
        for (i = 0; i < nr; i++) {
                cout << i + 1 << "." << masina[i].getNume() << " " << masina[i].getModel() << " locuri:" << masina[i].getLocuri() << " disponibilitate:" << masina[i].getDisp() << endl;
        } //am afisat datele in ordine
        filep.close();
    cout << "\033[0m";
    system("pause");
    meniu(path);
}

void adaugare(const char path[]) {
    system("cls");
    cout << "\033[1;32m";
    cout << "    -ADAUGATI UN AUTOMOBIL-\n";

    ofstream filep(path, ios::app);
    char nume[20], model[20];
    int loc, disp;
    cout << "Introduceti marca masinii: ";
    cin >> nume;
    cin.ignore();
    cout << "Introduceti modelul masinii: ";
    cin.getline(model, 20);
    cout << "Introduceti locurile libere: ";
    cin >> loc;
    cout << "Introduceti disponibilitatea masinii: ";
    cin >> disp;

    //am citit de la tastatura sirurile necesare pentru completarea unei masini

    if (!filep) {
        cout << "Fisierul nu poate fi accesat\n";
    }
    else {
        filep << nume << "\n" << model << "\n" << loc << "\n" << disp << "\n";
        filep.close();
        cout << "Masina dumneavoastra a fost inregistrata\n";
    } //scriem datele retinute in fisier
    cout << "\033[0m";
    system("pause");
    meniu(path);
}

void rezervare(const char path[]) {
    system("cls");
    cout << "\033[0;33m";
    cout << "    -REZERVATI UN AUTOMOBIL-\n";
    ifstream filep(path);
    int nr, i = 0;
    int choice = 0;

    if (!filep) {
        cout << "Fisierul nu poate fi accesat";
    }
    else {
        Masina masina[101];
        while (filep.getline(masina[i].getNume(), 20)) {
            filep.getline(masina[i].getModel(), 20);
            filep.getline(masina[i].getLocuri(), 5);
            filep.getline(masina[i].getDisp(), 5);
            i = i + 1;
        }
        nr = i;
        for (i = 0; i < nr; i++) {
            if (strchr(masina[i].getDisp(), '1'))
                cout << i + 1 << "." << masina[i].getNume() << " " << masina[i].getModel() << " locuri:" << masina[i].getLocuri() << " disponibilitate:" << masina[i].getDisp() << endl;
        }
        filep.close();
        //am afisat pe ecran doar masinile care sunt disponibile
        choice = getch();
        ofstream fp(path);
        for (i = 0; i < nr; i++) {
            if (i == choice - 49)
                fp << masina[i].getNume() << endl << masina[i].getModel() << endl << masina[i].getLocuri() << endl << "0" << endl;
            else
                fp << masina[i].getNume() << endl << masina[i].getModel() << endl << masina[i].getLocuri() << endl << masina[i].getDisp() << endl;
        }
        //masina din dreptul indexului apasat de la tastatura isi schimba disponibilitatea fiind rezervata
        fp.close();
        cout << "\033[0m";
        system("pause");
        meniu(path);
    }
}
void anulare(const char path[]) {
    system("cls");
    cout << "\033[1;34m";
    cout << "    -ANULATI REZERVAREA UNUI AUTOMOBIL-\n";
    ifstream filep(path);
    int nr, i = 0;
    int choice = 0;

    if (!filep) {
        cout << "Fisierul nu poate fi accesat";
    }
    else {
        Masina masina[101];
        while (filep.getline(masina[i].getNume(), 20)) {
            filep.getline(masina[i].getModel(), 20);
            filep.getline(masina[i].getLocuri(), 5);
            filep.getline(masina[i].getDisp(), 5);
            i = i + 1;
        }
        nr = i;
        for (i = 0; i < nr; i++) {
            if (strchr(masina[i].getDisp(), '0'))
                cout << i + 1 << "." << masina[i].getNume() << " " << masina[i].getModel() << " locuri:" << masina[i].getLocuri() << " disponibilitate:" << masina[i].getDisp() << endl;
        }
        filep.close();
        //am afisat pe ecran doar masinile care nu sunt disponibile
        choice = getch();
        ofstream fp(path);
        for (i = 0; i < nr; i++) {
            if (i == choice - 49)
                fp << masina[i].getNume() << endl << masina[i].getModel() << endl << masina[i].getLocuri() << endl << "1" << endl;
            else
                fp << masina[i].getNume() << endl << masina[i].getModel() << endl << masina[i].getLocuri() << endl << masina[i].getDisp() << endl;
        }
        //masina din dreptul indexului apasat de la tastatura isi schimba disponibilitatea fiind anulata rezervarea
        fp.close();
        cout << "\033[0m";
        system("pause");
        meniu(path);
    }
}

void stergere(const char path[]) {
    system("cls");
    cout << "\033[1;35m";
    cout << "    -STERGETI UN AUTOMOBIL-\n";

    ifstream filep(path);
    int nr, i = 0;

    if (!filep) {
        cout << "Fisierul nu poate fi accesat";
    }
    else {
        Masina masina[101];
        while (filep.getline(masina[i].getNume(), 20)) {
            filep.getline(masina[i].getModel(), 20);
            filep.getline(masina[i].getLocuri(), 5);
            filep.getline(masina[i].getDisp(), 5);
            i = i + 1;
        }
        nr = i;
        for (i = 0; i < nr; i++) {
            cout << i + 1 << "." << masina[i].getNume() << " " << masina[i].getModel() << " locuri:" << masina[i].getLocuri() << " disponibilitate:" << masina[i].getDisp() << endl;
        }
        //afisam pe ecran toate masinile din fisier
        filep.close();
        ofstream fp(path);
        int choice = 0;
        choice = getch();
        for (i = 0; i < nr; i++) {
            if (i != choice - 49)
                fp << masina[i].getNume() << endl << masina[i].getModel() << endl << masina[i].getLocuri() << endl << masina[i].getDisp() << endl;
        }
        //masina din dreptul indexului apasat de la tastatura este stearsa
        fp.close();
        cout << "\033[0m";
        system("pause");
        meniu(path);
    }
}
void actualizare(const char path[]) {
    system("cls");
    cout << "\033[1;36m";
    cout << "    -ACTUALIZATI DETALII AUTOMOBIL-\n";

    ifstream filep(path);
    int nr, i = 0;

    if (!filep) {
        cout << "Fisierul nu poate fi accesat";
    }
    else {
        Masina masina[101];
        while (filep.getline(masina[i].getNume(), 20)) {
            filep.getline(masina[i].getModel(), 20);
            filep.getline(masina[i].getLocuri(), 5);
            filep.getline(masina[i].getDisp(), 5);
            i = i + 1;
        }
        nr = i;
        for (i = 0; i < nr; i++) {
            cout << i + 1 << "." << masina[i].getNume() << " " << masina[i].getModel() << " locuri:" << masina[i].getLocuri() << " disponibilitate:" << masina[i].getDisp() << endl;
        }
        //afisam toate masinile pe ecran
        filep.close();
        ofstream fp(path);
        int choice = 0;
        choice = getch();
        for (i = 0; i < nr; i++) {
            if (i == choice - 49) {
                cout << "Introduceti noile detalii pentru masina " << endl;
                cout << "Nume: ";
                cin.get();
                cin.getline(masina[i].getNume(), 20);
                cout << "Model: ";
                cin.getline(masina[i].getModel(), 20);
                cout << "Numar de locuri: ";
                cin.getline(masina[i].getLocuri(), 5);
                cout << "Disponibilitate (0 - indisponibil, 1 - disponibil): ";
                cin.getline(masina[i].getDisp(), 5);
            }
            fp << masina[i].getNume() << endl << masina[i].getModel() << endl << masina[i].getLocuri() << endl << masina[i].getDisp() << endl;
        }
        //actualizam toate datele unei masini din dreptul indexului dorit. Metoda de actualizare este similara a celei de adaugare
        fp.close();
        cout << "\033[0m";
        system("pause");
        meniu(path);
    }
}


int meniu(const char path[]) {
    int choice;

    choice = 0;

    system("cls");
    cout << "     ---------------MENIU---------------\n";
    cout << "\033[1;31m";
    cout << "    (1) Afisare autoturisme\n";
    cout << "\033[1;32m";
    cout << "    (2) Adaugare autoturism\n";
    cout << "\033[0;33m";
    cout << "    (3) Rezervare autoturisme\n";
    cout << "\033[1;34m";
    cout << "    (4) Anulare rezervare autoturisme\n";
    cout << "\033[1;35m";
    cout << "    (5) Stergere autoturism\n";
    cout << "\033[1;36m";
    cout << "    (6) Actualizare autoturism\n";
    cout << "\033[0m";
    cout << "    (esc) Iesiti din meniu\n";
    cout << "Introduceti varianta corecta\n";
    //cout-urile multiple codificate reprezinta schimbarea culorii. Afisam pe ecran toate optiunile disponibile

    while (1) {
        if (kbhit())
            choice = getch();

        if (choice == '1')
            afisare(path);
        if (choice == '2')
            adaugare(path);
        if (choice == '3')
            rezervare(path);
        if (choice == '4')
            anulare(path);
        if (choice == '5')
            stergere(path);
        if (choice == '6')
            actualizare(path);
        if (choice == 27)
            exit(0);
    }
    //apelam functia reprezentativa indexului apasat de la tastatura

}
int main(int argc, char * argv[]) {
    char path[] = "clase.TXT";
    int ok = 1;

    cout <<"Pentru vizualizarea meniului tastati: ajutor";
	for (int i = 0; i < argc; ++i)
	{
	    if(strcmp(argv[i],"ajutor")==0) //apelarea meniului din cmd
            meniu(path);

        if(strcmp(argv[i],"afisare")==0) //apelarea meniului din cmd
            afisare(path);

        if(strcmp(argv[i],"stergere")==0)
            stergere(path);
	}//deschidem programul din cmd


    //meniu(path);
    //deschidem programul din compilator
    return 0;
}

