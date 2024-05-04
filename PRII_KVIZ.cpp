//pokusaj kviza

#include<iostream>
#include<ctime>
#include<string>
#include<vector>
#include<thread>
#include<chrono>

using namespace std;

const char* crt = "\n-----------------------------------------\n";

char* Alokator(const char* tekst)
{
	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, tekst);
	return temp;
}
int Min(int e1, int e2) { return e1 < e2 ? e1 : e2; }
int Max(int e1, int e2) { return e1 > e2 ? e1 : e2; }
 int NajvecaBrzina(int br1, int br2, int br3,int br4,int br5)
 {
	 if (br1 <= br2 && br1 <= br3&&br1<=br4&&br1<=br5)
		 return 0;
	 if (br2 <= br3 && br2 <= br1 && br2 <= br4 && br2 <= br5)
		 return 1;
	 if (br3 <= br1 && br3 <= br2 && br3 <= br4 && br3 <= br5)
		 return 2;
	 if (br4 <= br1 && br4 <= br2 && br4 <= br3 && br4 <= br5)
		 return 3;
	 if (br5 <= br1 && br5 <= br2 && br5 <= br3 && br5 <= br4)
		 return 4;
 }
 void Sacekaj()
 {
	 using namespace std::this_thread;
	 using namespace std::chrono;
	 sleep_until(system_clock::now() + 5s);
 }
 
 void OcistiEkran()
 {
	 system("CLS");
}
enum class Experience{weak=0,solid,pro};
 ostream& operator<<(ostream& cout, const Experience& obj)
{
	 switch (obj)
	 {
	 case Experience::weak:cout << "Rookie"; break;
	 case Experience::solid:cout << "Amater"; break;
	 case Experience::pro:cout << "Dosta iskusan"; break;
	 default:
		 break;
	}
	return cout;
}



class Generator {
	int _slucajniBroj;
	int GeneratorL()
	{
	    return  rand() % 3 + 1;
	}
	int GeneratorB()
	{
		return  rand() % 100 + 1;
	}
public:
	int GetLovca()
	{
		_slucajniBroj = GeneratorL();
		return _slucajniBroj;
	}
	int GetBrzinu()
	{
		_slucajniBroj = GeneratorB();
		return _slucajniBroj;
	}
};

class Osoba abstract{
	string _imePrezime;
	bool TacanOdgovor()
	{
		return rand() % 2;
	}
public:
	
	Osoba(string imePrezime=" ")
	{
		_imePrezime = imePrezime;
	}

	Osoba(const Osoba&obj)
		:_imePrezime(obj._imePrezime)
	{

	}
	Osoba& operator=(const Osoba& obj)
	{
		if (this != &obj) {
			_imePrezime = _imePrezime;
		}
		return *this;
	}
	string GetIme() { return _imePrezime; }
	friend ostream& operator<<(ostream& cout, const Osoba& obj)
	{
		cout  << obj._imePrezime << endl;
		return cout;
	}
	friend bool operator==(const Osoba& obj1, const Osoba& obj2)
	{
		return obj1._imePrezime == obj2._imePrezime;
	}
	
	virtual ~Osoba() {

	}

};

class Lovac : public Osoba,public Generator
{
	typedef int Bodovi;
	static int _broj;
	int _brojLovca;
	Bodovi _bodovi;
	bool TacanOdgovor()
	{
		return rand() % 2;
	}
public:
	Lovac(string imePrezime = " ", int brojLovca = 0)
		:Osoba(imePrezime),
		_brojLovca(++_broj)
	{
		_bodovi = 0;
	}
	Lovac(const Lovac& obj)
		:Osoba(obj)
	{
		_brojLovca = obj._brojLovca;
		_bodovi = 0;

	}
	Lovac& operator=(const Lovac& obj)
	{
		if (this != &obj)
		{
			Osoba::operator=(obj);
			_brojLovca = obj._brojLovca;
			_bodovi = obj._bodovi;
		}
		return *this;
	}
	Bodovi GetBodovi() { return _bodovi; }
	void operator()(int bodovi) //dodaje bodove
	{
		_bodovi += bodovi;
	}
	bool GetTacanOdgovor()
	{
		return TacanOdgovor();
	}
	friend ostream& operator<<(ostream& cout, const Lovac& obj)
	{
		cout << (Osoba&)obj;
		cout << "Broj lovca: " << obj._brojLovca << endl;
		return cout;
	}


	
};
int Lovac::_broj = 0;


class Takmicar:public Osoba,public Generator
{
	typedef int ID;
	typedef int Bodovi;
	Experience _iskustvo;
	ID _redniBroj;
	Bodovi _bodovi;
	bool TacanOdgovor()
	{
		return rand() % 2;
	}

public:
	Takmicar(string imePrezime=" ",Experience iskustvo=Experience::weak,ID redniBroj=0)
		:Osoba(imePrezime),
		_iskustvo(iskustvo),
		_redniBroj(redniBroj)
	{
		
	}
	Takmicar(const Takmicar& obj)
		:Osoba(obj),
		_iskustvo(obj._iskustvo),
		_redniBroj(obj._redniBroj)
	{

	}

	Takmicar& operator=(const Takmicar& obj)
	{
		if (this != &obj)
		{
			Osoba::operator=(obj);
			_iskustvo = obj._iskustvo;
			_redniBroj = obj._redniBroj;
		}
		return *this;
	}
	void operator()(int bodovi) //dodaje bodove
	{
		_bodovi += bodovi;
	}
	
	Bodovi GetBodovi() { return _bodovi; }
	ID GetRedniBroj() { return _redniBroj; }

	bool GetTacanOdgovor()
	{
		return TacanOdgovor();
	}

	friend ostream& operator<<(ostream& cout, const Takmicar& obj)
	{
		cout << (Osoba&)obj;
		cout << "Redni broj: " << obj._redniBroj << endl;
		return cout;

	}
	friend bool operator==(const Takmicar& obj1, const Takmicar& obj2)
	{
		return (Osoba&)obj1 == (Osoba&)obj2 && obj1._iskustvo == obj2._iskustvo &&
			obj1._bodovi == obj2._bodovi && obj1._redniBroj == obj2._redniBroj;
	}
};

 Osoba* GetBrziOdogovor(Osoba* obj1, Osoba* obj2)
 {
	 
	 auto takmicar = dynamic_cast<Takmicar*>(obj1);
	 auto lovac = dynamic_cast<Lovac*>(obj2);
	 if (takmicar != nullptr&& lovac != nullptr)
	 {
		  int brzina1 = takmicar->GetBrzinu();
		  int brzina2 = lovac->GetBrzinu();
	      if (brzina1 >= brzina2)
		       return obj1;
	      else
		       return obj2;
	 }
	 else
		 throw exception("Niste poslali adekvatne parametre");

	
 }

class Pitanje
{
	typedef int BrojPitanja;
	BrojPitanja _broj;
	string _oblast;
	string _sadrzaj;
public:
	
	Pitanje(string pitanje,BrojPitanja broj=0)
		:_sadrzaj( pitanje),
		_broj(broj)
	{

	}
	Pitanje(string pitanje,string oblast, BrojPitanja broj = 0)
		:_sadrzaj(pitanje),
		_broj(broj),
		_oblast(oblast)
	{

	}
	string& GetPitanje() { return _sadrzaj; }
	static void PrikazOblasti()
	{
		cout << "1---> Matematika" << endl
			<< "2---> Biologija" << endl
			<< "3---> Historija" << endl 
			<< "4---> Hemija" << endl 
			<< "5---> OpsteZnanje";
	
	}

	friend ostream& operator<<(ostream&cout, const Pitanje& obj)
	{
		cout << obj._sadrzaj;
		return cout;
	}
};

namespace poruke {
	void PravilaIgre(Takmicar& obj)
	{
		cout << "Dragi " << obj.GetIme() << " pravila su sljedeca" <<endl<< "Pred nama su 5 pitanja iz 5 razlicitih oblasti" << endl
			<< "Takmicar ima pravo da bira oblast koju zeli" << endl << "Ko uspjeno odgovori na pitanje i pri tome bude brzi od protivnika dobiva broj bodova ekvivalentan broju pitanja" << endl
			<< "Puno srece,neka bolji pobijedi!" << endl;

	}  
	void TacanOdgovor(int brojBodova)
	{
		cout << endl << "Tacno ste odgovorili na " << brojBodova << ". pitanje" << endl <<
			"Osvojili ste " << brojBodova <<" bodova"<<endl<< endl;
	}
	void WinPoruka(Takmicar& obj)
	{
		cout << "Cestitamo gospodine " << obj.GetIme() << " vi ste pobjednik vecerasnje emisije" << endl
			<< "Osvojili ste nagradu u iznosu od xxxKM" << endl;
	}
	void PreResultMessage()
	{
		cout << "Došli smo do kraja ove sesije" << endl << "Preostaje nam da prebrojimo bodove i proglasimo pobjednika... " << endl;
		cout << endl;
		cout << endl;

	}
	void LostPoruka(Takmicar& obj)
	{
		cout << "Zao nam je gospodine " << obj.GetIme() << endl << "Ovoga puta lovac je bio uspjesniji" <<
			"Vise srece drugi put!" << endl << "Lijep pozdrav :)" << endl;
	}
	void EndPoruka()
	{
		cout << endl << "Zao nam je,vas odgovor nije bio tacan." << endl
			<< "Hvala vam na ucescu i dodite nam opet" << endl;

	}
	void Goodbyee()
	{
		OcistiEkran();
		cout << "\nLijep pozdrav!" << endl;
		cin.get();
	}
}

void Test()
{
	srand(time(NULL));

	OcistiEkran();

	vector<Lovac> lovci;
	Lovac l1("Dean Kotiga"), l2("Morana Zibar"), l3("Kresimir Sucevic");
	lovci.push_back(l1);
	lovci.push_back(l2);
	lovci.push_back(l3);

	vector<Takmicar>takmicari;	
	Takmicar t1("Adi Cefo", Experience::weak, 1),
		   t2("Nedim Cefo", Experience::weak, 2),
		   t3("Zlatan Cefo", Experience::pro, 3),
		   t4("Zeno Music", Experience::solid, 4),
		   t5("Asim Rustempasic", Experience::solid, 5);
	takmicari.push_back(t1);
	takmicari.push_back(t2);
	takmicari.push_back(t3);
	takmicari.push_back(t4);
	takmicari.push_back(t5);
	
	cout << crt;

	cout << "Generisem lovca..." << endl;
	Generator gl;
	
	switch (gl.GetLovca())
	{
	case 1:
		cout << "Vas lovac je: "; Sacekaj(); cout << "----------" << lovci.at(0).GetIme() << " ----------"; lovci.push_back(lovci.at(0));  break;
	case 2:
		cout << "Vas lovac je: "; Sacekaj();  cout << "----------" << lovci.at(1).GetIme() << "----------"; lovci.push_back(lovci.at(1)); break;  //izbor lovca
		 
	case 3:
		cout << "Vas lovac je: ";  Sacekaj(); cout << "----------" << lovci.at(2).GetIme() << "----------"; lovci.push_back(lovci.at(2));  break;
	}
	cout << endl;
	cout << endl;
	



	Pitanje test("Koji je glavni grad Indije?");
	cout << "\n------------------TestPitanje: " << test <<"------------------"<< endl
		<<"---------------------------Trebamo najbrzi odgovor------------------------------"<<endl;
	Sacekaj();

	int brzina1 = takmicari[0].GetBrzinu();    
	int brzina2 = takmicari[1].GetBrzinu();         //izbor takmicara
	int brzina3 = takmicari[2].GetBrzinu();
	int brzina4 = takmicari[3].GetBrzinu();
	int brzina5 = takmicari[4].GetBrzinu();
	int rb = NajvecaBrzina(brzina1, brzina2, brzina3, brzina4, brzina5);//vraca redni broj takmicara sa najvecom brzinom

	cout <<endl<< "Takmicar koji je bio najbrzi je ... ";
	Sacekaj();                                     //pauza 
	cout << "Redni broj "<<takmicari.at(rb).GetRedniBroj()<<"------->"<< takmicari.at(rb).GetIme()<<endl;

	cout << crt;
	
	poruke::PravilaIgre(takmicari.at(rb));
	cout << crt;
    Sacekaj();  //citanje pravila

	OcistiEkran();  //cistimo ekran za pocetak kviza

	Takmicar t = takmicari.at(rb);       //koristenje istanci izabranih takmicara i lovca
	Lovac l = lovci.at(3);
	Osoba* takmicar = new Takmicar(t);
	Osoba* lovac = new Lovac(l);
    int izborOblasti;
	vector<Pitanje>pitanja;
	Pitanje p1("Navedite 9 clan Fibonnaci niza ukoliko mu je prvi element 1", "Matematika", 1),
		p2("Koja je cvijetna formula ruza", "Biologija", 2),
		p3("Koje godine se desila bitka na Soci", "Historija", 3),                       //generisanje pitanja
		p4("Koji je simbol hemijskog elementa bakra", "Hemija", 4),
		p5("Prijevod poznate latinske izreke \"Festina lente\" glasi", "Opste znanje", 5);
	pitanja.push_back(p1);
	pitanja.push_back(p2);
	pitanja.push_back(p3);
	pitanja.push_back(p4);
	pitanja.push_back(p5);



	//glavni dio pitanja i odgovora   //nije najpreciznije implementirano,cilj je bio da zavrsim, kako-tako(zbog vremena)
	for (int i = 0; i < pitanja.size(); i++)
	{
		cout << crt;
		Pitanje::PrikazOblasti();
		cout << crt;

		do
		{
			cout <<endl<<endl<< "Izaberite oblast--->";
			cin >> izborOblasti;
		} while (izborOblasti < 1 || izborOblasti>5);
	
		


		switch (izborOblasti)
		{
		case 1:
			cout <<endl<< "Pitanje glasi..." << pitanja.at(0).GetPitanje() <<"->"<< endl; break;
		case 2:
			cout << endl << "Pitanje glasi..." << pitanja.at(1).GetPitanje() << "->" << endl; break;
		case 3:
			cout << endl << "Pitanje glasi..." << pitanja.at(2).GetPitanje() << "->" << endl; break;
		case 4:
			cout << endl << "Pitanje glasi..." << pitanja.at(3).GetPitanje() << "->" << endl; break;
		case 5:
			cout << endl << "Pitanje glasi..." << pitanja.at(4).GetPitanje() << "->" << endl; break;
		default:
			cout <<endl<< "Problem sa bazom..." << endl; break;
		}
		Sacekaj();
		if (t.GetTacanOdgovor() && l.GetTacanOdgovor()) //ukoliko je obojici tacan odgovor
		{                                               //gleda se brzina
			try {         

				if (t == *GetBrziOdogovor(takmicar, lovac))            //ukoliko parametri nisu poslani kako treba,baca se exception
				{
					poruke::TacanOdgovor(izborOblasti); //ispis poruke
					t(izborOblasti);
				}

				else 
				{
					l(izborOblasti);
					cout <<endl<< "Lovac kupi bodove" << endl;
				}
				
					
			}
			catch (exception& obj)
			{
				cout << "Greska--> " << obj.what() << endl;
			}
			
		}
		 
		else if (!t.GetTacanOdgovor())           //ukoliko nije takmicaru tacan odgovor--->gubi
		{
			poruke::EndPoruka();
			return;
		}
		else                                   //jedina preostala situacija jeste da lovcu nije tacan odgovor,tada takmicar kupi
		{                                      //bodove
			poruke::TacanOdgovor(izborOblasti);
			t(izborOblasti);
		}

	}
		cout << endl;
		cout << endl;
		cout << endl;
        
		cout << crt;
		
		poruke::PreResultMessage();
		Sacekaj();

      if (t.GetBodovi() > l.GetBodovi())
		    poruke::WinPoruka(t);
	   else if (t.GetBodovi() < l.GetBodovi())                  //ako je takmicar odgovorio tacno na sva pitanja,vrsi se
		    poruke::LostPoruka(t);                              //poredjenje bodova
	    else
		     cout << "Tesko da se desi,uz random vrijednosti..." << endl;
  
	  cout << crt;

	cin.get();



}


int main()
{
	int test;
	do
	{
		system("CLS");
		cout << "Zelite li testirati implementaciju DA-1 NE-0 ->";
		cin >> test;
	} while (test!=1&&test!=0);

	
	(test) ? Test(): poruke::Goodbyee();

	
	return 0;
	
}