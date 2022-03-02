#include <iostream>
#include<cstring>
#include<set>
#include<vector>
#include<typeinfo>

using namespace std;


class Angajat{
   int salariu;
   char *nume;
   Angajat* manager;
   char *data_angajare;
   void set_salariu( int salariu){this -> salariu = salariu;}
   void set_nume(char *nume){
        this -> nume = new char[strlen(nume) + 1];
        strcpy(this -> nume, nume);
    }
  void set_manager(Angajat *manager){
       this -> manager = manager;
   }
  void set_data_angajare(char* data_angajare){
       this -> data_angajare = new char[strlen(data_angajare) + 1];
       strcpy(this -> data_angajare, data_angajare);
   }
 public:
    int get_salariu(){
       return this -> salariu;
   }
   char* get_nume(){
       return this -> nume;
   }
   Angajat* get_manager(){
       return this -> manager;
   }

   char* get_data_angajare(){
       return this -> data_angajare;
   }

   Angajat& operator=(const Angajat& angajat);
   friend istream &operator>>(istream &is,  Angajat& angajat);
   friend ostream &operator<<(ostream &os,  Angajat& angajat);

    Angajat(){

        this -> salariu = 0;
        this -> nume = nullptr;
        this -> manager = nullptr;
        this -> data_angajare = nullptr;
    }
   Angajat(int salariu, char* nume, Angajat* manager, char* data_angajare){
       this -> salariu = salariu;
       this -> nume = new char[strlen(nume) + 1];
       strcpy(this -> nume, nume);
       this -> manager = manager;
       this -> data_angajare = new char[strlen(data_angajare) + 1];
       strcpy(this -> data_angajare, data_angajare);
   }
   Angajat(const Angajat &angajat){
       this -> salariu = angajat.salariu;
       this -> nume = new char[strlen(angajat.nume) + 1];
       strcpy(this -> nume, angajat.nume);
       this -> manager = angajat.manager;
       this -> data_angajare = new char[strlen(angajat.data_angajare) + 1];
       strcpy(this -> data_angajare, angajat.data_angajare);
   }
   ~Angajat(){
       this -> salariu = 0;
       delete [] data_angajare;
       delete [] nume;
   }
};

istream &operator>>(istream &is, Angajat &angajat){
    cout << "\nNumele angajatului: ";
    int i;
    char c;
    angajat.nume = new char[40];
    is.get();
    while(is.getline(angajat.nume, 40)) {
        try{

            for(i = 1; i <= 127; i++){
                c = char(i);
                if(c == ' ' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                    continue;
                else{
                   if(strchr(angajat.nume, c))
                    throw(c);
                }
            }
            break;
        }
        catch(char c){
            cout <<"\nInput incorect, '" << c << "'nu este caracter valid";
            cout<< "\nNumele angajatului: ";
        }
        delete [] angajat.nume;
        angajat.nume = new char[40];
    }
    cout <<"\nData angajarii: ";
    angajat.data_angajare = new char[15];
    is.getline(angajat.data_angajare, 15);
    cout <<"\nSalariu :";
    while(is>>angajat.salariu) {
        try {
            if (angajat.salariu > 0) {
                break;
            }
            else {
                throw (angajat.salariu);
            }
        }
        catch(int x){
            cout<<'\n'<< x << "nu este o valoare valida\n";
            cout<<"\nSalariu: ";
        }
    }
    cout << "\nManager(se lasa necompletata daca nu are): ";
    char nume_manager[40];

    while(is.getline(nume_manager, 40)) {
        try{
            if(nume_manager[0] >= 'A' && nume_manager[0] <= 'Z')
                throw(1);
            for(i = 1; i <= 127; i++){
                c = char(i);
                if(c == ' ' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                    continue;
                else{
                    if(strchr(angajat.nume, c))
                        throw(c);
                }
            }

            break;
        }
        catch(char c){
            cout <<"\nInput incorect, '" << c << "'nu este caracter valid";
            cout<< "\nNumele managerului: ";
        }

        catch(int i){
            break;
        }

        delete [] angajat.nume;
        angajat.nume = new char[40];
    }
    return is;
}

ostream &operator<<(ostream &os, Angajat &angajat){
    os <<"\nNumele angajatului: ";
    os<<angajat.get_nume();
    os << "\nData angajarii: ";
    os <<angajat.get_data_angajare();
    os <<"\nSalariu in lei: ";
    os<<angajat.get_salariu();
    return os;
}

Angajat& Angajat :: operator=(const Angajat& angajat){
    if(this == &angajat)
        return *this;
    this -> salariu = angajat.salariu;
    if(this -> nume != nullptr)
        delete [] this -> nume;
    this -> nume = new char[strlen(angajat.nume) + 1];
    strcpy(this -> nume, angajat.nume);
    this -> data_angajare = new char[strlen(angajat.data_angajare) + 1];
    strcpy(this -> data_angajare, angajat.data_angajare);
    this -> manager = angajat.manager;
    return *this;
}

class Departament{
    char *nume;
    vector<Angajat> angajati;
    int nr_angajati;
    void set_nume(char *nume){
        this -> nume = new char[strlen(nume) + 1];
        strcpy(this -> nume, nume);
    }
    void set_nr_angajati(int nr_angajati){
        this -> nr_angajati = nr_angajati;
    }

    void set_angajati(Angajat angajati[]){
       // this -> angajati = angajati;
    }
  public:

    char* get_nume (){return nume;}
    int get_nr_angajati(){return nr_angajati;}
    vector<Angajat> get_angajati(){return angajati;}

    Departament& operator=(const Departament& departament);
    Departament& operator+(const Departament& departament);
    friend istream &operator>>(istream &is,  Departament& departament);
    friend ostream &operator<<(ostream &os,  Departament& departament);

    int get_cheltuieli_salariele();

    Departament(){
        this -> nume = nullptr;
        this -> nr_angajati = 0;
        this -> angajati.clear();
    }

    Departament(const char *nume, const int nr_angajati, vector<Angajat> angajati){
        this -> nume = new char[strlen(nume) + 1];
        strcpy(this -> nume, nume);
        this -> nr_angajati = nr_angajati;
        this -> angajati = angajati;
    }

    Departament(const Departament &departament){
        this -> nume = new char[strlen(departament.nume) + 1];
        strcpy(this -> nume, nume);
        this -> nr_angajati = departament.nr_angajati;
        this -> angajati = departament.angajati;
    }

    ~Departament(){
        delete [] nume;
        nr_angajati = 0;
        this -> angajati.clear();
    }
};


Departament& Departament :: operator=(const Departament& departament){
    if(this == &departament)
        return *this;
    if(this -> nume != nullptr)
        delete [] this -> nume;
    this -> nume = new char[strlen(departament.nume) + 1];
    strcpy(this -> nume, departament.nume);
    this -> nr_angajati = departament.nr_angajati;
    this -> angajati = departament.angajati;
    return *this;
}

Departament& Departament :: operator+(const Departament& departament){
    this -> nr_angajati += departament.nr_angajati;
    this -> angajati.insert(this->angajati.end(), departament.angajati.begin(), departament.angajati.end());
    return *this;
}

istream &operator>>(istream &is, Departament &departament){
    cout << "\nNumele departamentului: ";
    int i;
    char c;
    departament.nume = new char[40];
    is.get();
    while(is.getline(departament.nume, 40)) {
        try{

            for(i = 1; i <= 127; i++){
                c = char(i);
                if(c == ' ' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                    continue;
                else{
                   if(strchr(departament.nume , c))
                    throw(c);
                }
            }
            break;
        }
        catch(char c){
            cout <<"\nInput incorect, '" << c << "'nu este caracter valid";
            cout<< "\nNumele angajatului: ";
        }
        delete [] departament.nume;
        departament.nume = new char[40];
    }
    cout << "\nNumar de angajati: ";
    while(is>>departament.nr_angajati) {
        try {
            if (departament.nr_angajati > 0) {
                break;
            }
            else {
                throw (departament.nr_angajati);
            }
        }
        catch(int x){
            cout<<'\n'<< x << "nu este o valoare valida\n";
            cout<<"\nNumar de angajati: ";
        }
    }
    Angajat angajat;
    cout <<"\nINTRODUCETI DATELE CELOR "<<departament.nr_angajati<<" ANGAJATI:";
    for( i = 0; i < departament.nr_angajati; i++){
        is>>angajat;
        departament.angajati.push_back(angajat);
    }

    return is;
}

ostream&operator<<(ostream &os, Departament &departament){
    os<<"\nNumele departamentului: "<<departament.nume;
    os<<"\nNumarul de angajati: "<<departament.nr_angajati;
    os<<"\nANGAJATII:";
    for(int i = 0; i < departament.nr_angajati; i++){
        os << departament.angajati[i];
    }
    return os;
}

int Departament :: get_cheltuieli_salariele() {
    int s = 0,i;
    for(i = 0; i < this -> nr_angajati; i++)
        s += this -> angajati[i].get_salariu();
    return s;
}

class Companie{
   protected:
    char *nume;
    int nr_departamente;
    vector<Departament> departamente;
    void set_nume(const char *nume){
        this -> nume = new char[strlen(nume) + 1];
        strcpy(this -> nume, nume);
    }
  void set_nr_departamente(const int nr_departamente){
        this -> nr_departamente = nr_departamente;
    }
  void set_departamanete(const vector<Departament> departamente){
         this -> departamente = departamente;
    }
  public:

    Companie(){
        this -> nume = nullptr;
        this -> nr_departamente = 0;
        this -> departamente.clear();
    }

    Companie(const char *nume, const int nr_departamente, Departament departamente[]){
        this -> nume = new char[strlen(nume) + 1];
        strcpy(this -> nume , nume);
        this -> nr_departamente = nr_departamente;
        //this -> departamente = departamente;
    }

    Companie(const Companie &companie){
        this -> nume = new char[strlen(companie.nume) + 1];
        strcpy(this -> nume, companie.nume);
        this -> nr_departamente = companie.nr_departamente;
        this -> departamente = companie.departamente;
    }

    char* get_nume(){return this -> nume;}
    int get_nr_departamente (){return this -> nr_departamente;}
    vector<Departament> get_departamente(){return this -> departamente;}


    Companie& operator=(const Companie& companie);
    Companie& operator+(Companie& companie);
    friend istream &operator>>(istream &is,  Companie& companie);
    friend ostream &operator<<(ostream &os,  Companie& companie);

    double get_cheltuieli_salariale();
    vector<Departament> minim_n_dep(int n);

    ~Companie(){
        delete [] this -> nume;
        this -> nr_departamente = 0;
        this -> departamente.clear();
    }


};

  Companie& Companie :: operator=(const Companie& companie){
      if(this == &companie)
          return *this;
      if(this -> nume != nullptr)
          delete [] this -> nume;
      this -> nume = new char[strlen(companie.nume) + 1];
      strcpy(this -> nume, companie.nume);
      this -> nr_departamente = companie.nr_departamente;
      this -> departamente = companie.departamente;
      return *this;
  }

  Companie& Companie :: operator+(Companie& companie){
      int i,j;
      for(i = 0; i < this -> nr_departamente; i++){
          j = 0;
          while(j < companie.nr_departamente && strcmp(this -> departamente[i].get_nume(), companie.departamente[j].get_nume()) != 0){
              j++;
          }
          if(j != companie.nr_departamente) {
              this->departamente[i] = this->departamente[i] + companie.departamente[j];
              companie.departamente.erase(companie.departamente.begin() + j - 1);
          }
      }
      this -> departamente.insert(this -> departamente.end(), companie.departamente.begin(), companie.departamente.end());
      return *this;
  }

istream &operator>>(istream &is, Companie &companie){
    cout << "\nNumele companiei: ";
    companie.nume = new char[40];
    is.get();
    is.getline(companie.nume, 40);
    cout << "\nNumar de departamente: ";
    while(is>>companie.nr_departamente){
        try {
            if (companie.nr_departamente > 0) {
                break;
            }
            else {
                throw (companie.nr_departamente);
            }
        }
        catch(int x){
            cout<<'\n'<< x << "nu este o valoare valida\n";
            cout<<"\nNumar de departamente: ";
        }
    }
    Departament departament;
    cout <<"\nINTRODUCETI DATELE CELOR "<<companie.nr_departamente<<" DEPARTAMENTE:";
    for(int i = 0; i < companie.nr_departamente; i++){
        is>>departament;
        companie.departamente.push_back(departament);
    }
    return is;
}

ostream&operator<<(ostream &os, Companie &companie){
    os<<"\nNumele companiei: "<<companie.nume;
    os<<"\nNumarul de departamente: "<<companie.nr_departamente;
    os<<"\nDEPARTAMENTELE:";
    for(int i = 0; i < companie.nr_departamente; i++){
        os << companie.departamente[i];
    }
    return os;
}

double Companie :: get_cheltuieli_salariale() {
    double s = 0;
    int  i;
    for(i = 0; i < this -> nr_departamente; i++)
        s += this -> departamente[i].get_cheltuieli_salariele();
    return s;
  }
vector<Departament> Companie ::minim_n_dep(int n) {
  vector<Departament> n_dep;
  for(int i = 0; i < this -> nr_departamente; i++){
      if(this -> departamente[i].get_nr_angajati() >= n)
          n_dep.push_back(departamente[i]);
  }
  return n_dep;
  }

class Companie_scutita : public Companie{
  public:
      Companie_scutita(const char *nume, const int nr_departamente, Departament departamente[]) : Companie(nume, nr_departamente, departamente){

      };

      Companie_scutita() : Companie(){

      };

      Companie_scutita(const Companie &companie) : Companie(companie){

      };

      virtual double get_cheltuieli_salariale(){
          double s = 0;
          int i;
          for(i = 0; i < this -> nr_departamente; i++)
              s += this -> departamente[i].get_cheltuieli_salariele();
          return s * 84 / 100;
      }


      ~Companie_scutita(){};
  };

template<class Temp>
class GestionarHR{
    static GestionarHR* instance;
    set<pair<char*, int>> s;
    vector<Temp> v;
    GestionarHR(){
        this -> s.clear();
        this -> v.clear();
    }

    GestionarHR(set<pair<char*, int>> s, Temp v){
        this -> s = s;
        this -> v = v;
    }
    GestionarHR(GestionarHR &x){
        this -> v = x.v;
        this -> s = x.s;
    }
public:


    static GestionarHR* get_instance(){
        if(!instance)
            instance = new GestionarHR<Temp>;
        return instance;
    }

    void companie_noua(char* nume , int nr_departamente){
       if(typeid(Temp) == typeid(Companie))
        this -> s.insert(make_pair(nume, nr_departamente));
       else
           cout << "\nEroare"<< nume <<" : nu e companie.";
    }

    void adauga(Temp x){
       if(typeid(Temp) != typeid(Companie))
           return;

       if(s.count(make_pair(x.get_nume(), x.get_nr_departamente())))
             this -> v.push_back(x);
    }

    void afiseaza(){
        for(int i = 0; i < v.size(); i++)
            cout << v[i];
    }

    ~GestionarHR(){
        s.clear();
        v.clear();
    }

};

template<class Temp>
GestionarHR<Temp>* GestionarHR<Temp> :: instance = nullptr;

int main() {
      GestionarHR<Companie>* ptr;
      ptr = GestionarHR<Companie>::get_instance();
      int x;
      char prompter[] = "Comenzi :\n 1.Afiseaza companii.\n 2.Adauga o companie\n 3.Iesi.\n";
      cout << prompter;
      while(cin >> x){
           if(x == 3)
               break;
           else{
             if(x == 2) {
                 Companie comp;
                 cin >> comp;
                 ptr->adauga(comp);
              }
             else{
                 if(x == 1){
                     ptr -> afiseaza();
                 }
             }
           }
      }
     return 0;
}
