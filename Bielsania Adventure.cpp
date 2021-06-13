#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <locale.h>
#include <sstream>
#include <time.h>
using namespace std;
	
    int pl_hp = 100;   //punkty zycia
    int pl_dmg = 10;   //sila ataku
    int pl_rep = 0;    //reputacja 
    int pl_cash = 100; //w sensie zlotowki
    int pl_kev = 0;	   //zbroja gracza
    int pl_kev_health = 0; //zdrowie zbroi gracza
    int pl_weap = 0;   //bron gracza
    int pl_food = 0;   //ile jedzenia ma gracz (kebabow), 1 kebab = 20 HP
    int pl_map = 0;	   //okresla czy gracz posiada mape
    int pl_stal = 0;   //ile kawalkow stali ma gracz, przydatne przy kowalu
    
    int pass = 0;      //jezeli =1 to znaczy ze zaczyna sie gra
    int ending = 0;    //zakonczenie zalezne od rozmowy
    int wyjdz = 0;	   //zeby wyjsc z menu
    int tajm = 40;     //czas miedzy kreskami w tytule
    string HUD = "ON";  //czy HUD ma byc wyswietlany
    
	int miedz = 0; //miedziana ruda ktora ma byc dostarczona kowalowi
	int kowal = 0; //liczba wizyt u kowala    
	int ch2 = 0; //zmienna do rozdzialu 2, pomaga w petlowaniu godziburga
	int innos = 0;  //ilosc blogoslawienstw boga, zabezpieczenie
	int adanos = 0; //zabezpieczenie blogoslawienstwa ksiedza
	int bindar_cash = 0;
	int michniard_tip = 0;
	int wola_zajaslawa = 1;
	
void kreska() { 		//rysowanie kreski, element GUI
    cout<<"______________________________________________"<<endl;
}
void stats() {
	if (HUD == "ON"){
	cout<<"\n| HP "<<pl_hp<<" | KEV "<<pl_kev_health<<" | DMG "<<pl_dmg<<" | REP "<<pl_rep<<" | CASH "<<pl_cash<<" |\n";
	} else {
		cout<<"";
	}
}
int check(int odpowiedz, int ile_pytan){ //zabezpieczenie GUI i rozmow
	
	if (odpowiedz == 9){
		kreska();
		cout<<"| 1. HP\n";
		cout<<"| 2. DMG\n";
		cout<<"| 3. CASH\n";
		kreska();
		int hack1;
		cin>>hack1;
		switch (hack1){
			case 1:
				cout<<"| Add HP: ";
				int HP;
				cin>>HP;
				pl_hp = pl_hp + HP;
				break;
			case 2:
				cout<<"| Add DMG: ";
				int DMG;
				cin>>DMG;
				pl_dmg = pl_dmg + DMG;
				break;
			case 3:
				cout<<"| Add CASH: ";
				int CASH;
				cin>>CASH;
				pl_cash = pl_cash + CASH;
				break;
		}
	}
	
	if (odpowiedz > ile_pytan || odpowiedz == 0){
		kreska();
		cout<<"\n| To nie jest prawidlowa odpowiedz, napisz jeszcze raz \n";
		kreska();
		odpowiedz = 0;
		do {
			cin>>odpowiedz;
		}while(odpowiedz > ile_pytan || odpowiedz == 0);
	}
	return odpowiedz;
}
void mapa(){
	cout<<"______________________________________________\n";
	cout<<"|                                            |\n";
	cout<<"|                       CZECHIGROD           |\n";
	cout<<"|                        ___________         |\n";
	cout<<"|          ____________ / O  o o  __|        |\n";
	cout<<"| SPORDAN | ___________    o   O /           |\n";
	cout<<"|      \\ _| |          |O O O O |            |\n";
	cout<<"|       |o  |          \\_______/             |\n";
	cout<<"|       |_  |                                |\n";
	cout<<"|         | |                  ___________   |\n";
	cout<<"|         | |                 /  o o  o  o|  |\n";
	cout<<"|        _| |_               |o           |  |\n";
	cout<<"|       |o   o|_____         |  BIELOGROD |  |\n";
	cout<<"|       |O  O  ___  |        | o          |  |\n";
	cout<<"|       |_____|   | |        | O O   O O o|  |\n";
	cout<<"|      /          | |         \\  __      o|  |\n";
	cout<<"|     LITYNIA     | |         / /  \\ o   o|  |\n";
	cout<<"|           ______| |_      / /     \\  o o|  |\n";
	cout<<"|          / O  O    /     | |       \\___/   |\n";
	cout<<"|         /O   o   O/______| |               |\n";
	cout<<"|        |O  O o   ________  |     SERWENIA  |\n";
	cout<<"|        \\________/        | |           \\_  |\n";
	cout<<"|             /            | |__________|  | |\n";
	cout<<"|     GODZIBURG            |_______________| |\n";
	cout<<"______________________________________________\n\n  ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n";
}
void tytul(){			//wypisanie tytulu
	cout<<" ____________________________________________\n";
	Sleep(tajm);
	cout<<" |  ____         _                 _        |\n";
	Sleep(tajm);
	cout<<" | |  _ \\(_)    | |               (_)       |\n";
	Sleep(tajm);
	cout<<" | | |_) |_  ___| |___  __ _ _ __  _  __ _  |\n";
	Sleep(tajm);
	cout<<" | |  _ <| |/ _ \\ / __|/ _` | '_ \\| |/ _` | |\n";
	Sleep(tajm);
	cout<<" | | |_) | |  __/ \\__ \\ (_| | | | | | (_| | |\n";
	Sleep(tajm);
	cout<<" | |____/|_|\\___|_|___/\\__,_|_| |_|_|\\__,_| |\n";
	Sleep(tajm);
	cout<<" ____________________________________________\n";
	Sleep(tajm);
}
void disclaimer(){
	cout<<"\n         UWAGA, GRA WYMAGA MINIMALNIE \n            TAKIEJ SZEROKOSCI OKNA\n";
	cout<<"<____________________________________________>"<<endl;
	cout<<"\n       DOSTOSUJ SWOJE USTAWIENIA OKNA\n\n       ";
	system("pause");
}
int walka(int enemy){	//modul walki
	srand(time(NULL));
	int en_hp;			//HP wroga
	int en_dmg;			//DMG wroga
	int en_kev;			//zbroja wroga
	int en_kev_health; 	//stan zbroi wroga
	int en_weap;		//bron wroga
	string name;		//nazwa wroga
	int win = 0;		//zwyciezca (1=wrog, 2=Player)
	cout<<"|                 WALKA          \n|\n";
	if (enemy == 1){
		name = "STEBENIA";
		en_hp = 70;
		en_dmg = 6;
		en_kev = 0;
		en_weap = 0;
	} else if (enemy == 2){
		name="SPORDAN";
		en_hp = 200;
		en_dmg = 30;
		en_kev = 2;
		en_weap = 2;
	} else if (enemy == 3){
		name="BINDAR";
		en_hp = 120;
		en_dmg = 50;
		en_kev = 2;
		en_weap = 2;
	} else if (enemy == 4){
		name="ZAJ¥S£AW";
		en_hp = 240;
		en_dmg = 70;
		en_kev = 2;
		en_weap = 2;
	} else if (enemy == 5){
		name="STEFIR";
		en_hp = 180;
		en_dmg = 80;
		en_kev = 3;
		en_weap = 2;
	} else if (enemy == 6){
		name="GADZIMYS£";
		en_hp = 200;
		en_dmg = 40;
		en_kev = 2;
		en_weap = 1;
	} else if (enemy == 7){
		name="SKRETKOWY POTWÓR";
		en_hp = 100;
		en_dmg = 35;
		en_kev = 1;
		en_weap = 0;	
	} else if (enemy == 8){
		name="WOJMIR";
		en_hp = 200;
		en_dmg = 100;
		en_kev = 4;
		en_weap = 2;	
	}

	if (pl_kev == 1){pl_kev_health = 40;}
		else if (pl_kev == 2){pl_kev_health = 100;}
 		else if (pl_kev == 3){pl_kev_health = 160;}
		else if (pl_kev == 5){pl_kev_health = 500;}
	else {pl_kev_health = 0;}
		
	if (en_kev == 1){en_kev_health = 40;}
		else if (en_kev == 2){en_kev_health = 100;}
 		else if (en_kev == 3){en_kev_health = 160;}
 		else if (en_kev == 4){en_kev_health = 350;}
	else {en_kev_health = 0;}
	war:
	system("cls");
	stats();
	kreska();
	cout<<"\n PLAYER      "<<name<<"   ";
	cout<<"\n                       |";
	cout<<" TWOJE HP: "<<pl_hp<<"\n";
	cout<<"   O            O      |";
	cout<<" TWOJ KEVLAR: "<<pl_kev_health<<"\n";
	cout<<"  /";
	if (pl_kev == 1){cout<<"T";} else if (pl_kev == 2) {cout<<"H";}else if (pl_kev == 5) {cout<<"X";}else if (pl_kev == 3) {cout<<"W";}else if(pl_kev == 0){cout<<"|";}
	cout<<"\\";
 	if (pl_weap == 1 || pl_weap == 2){cout<<"/";} else {cout<<" ";}
	cout<<"        ";
	if (en_weap == 1 || en_weap == 2){cout<<"\\";} else {cout<<" ";}
	cout<<"/";
	if (en_kev == 1){cout<<"T";} else if (en_kev == 2) {cout<<"H";}else if (en_kev == 3) {cout<<"W";}else if (en_kev == 4) {cout<<"X";}else {cout<<"|";}
	cout<<"\\     |";
	cout<<" HP PRZECIWNIKA: "<<en_hp<<"\n";
	cout<<"  / \\          / \\     |";
	cout<<" KEVLAR WROGA: "<<en_kev_health<<"\n";
	kreska();
	cout<<"| 1. Atak \n";
	cout<<"| 2. Obrona \n";
	cout<<"| 3. Regeneruj HP \n";
	cout<<"| 4. Uciekaj \n";
	kreska();
	int walka;
	cin>>walka;
	switch (check(walka, 4)){
		case 1:
    		if (pl_kev == 0){
    			if ((pl_hp - en_dmg) <= 0){
					win = 2;
				} else {
    				pl_hp = pl_hp - rand() % en_dmg + 1;
				}
			}else {  
				if ((pl_kev_health - en_dmg) <= 0){
					pl_kev_health = pl_kev_health - rand() % en_dmg + 1;
					pl_hp = pl_hp + pl_kev_health;
					pl_kev = 0;
					pl_kev_health = 0;
	  	    	} else {
				  pl_kev_health = pl_kev_health - rand() % en_dmg + 1;
  	  	  	    }	
			}
			
    		if (en_kev == 0){
    			if ((en_hp - pl_dmg) <= 0){
					win = 1;
				} else {
    				en_hp = en_hp - rand() % pl_dmg + 1;
				}
			}else {  
				if ((en_kev_health - pl_dmg) <= 0){
					en_kev_health = en_kev_health - rand() % pl_dmg + 1;
					en_hp = en_hp + en_kev_health;
					en_kev = 0;
					en_kev_health = 0;
	  	    	} else {
				  en_kev_health = en_kev_health - rand() % pl_dmg + 1;
  	  	  	    }	
			}
			break;
		case 2:
			system("cls");
    		if (pl_kev == 0){
    			if ((pl_hp - (rand() % en_dmg + 1 / 10)) <= 0){
					win = 2;
				} else {
    				pl_hp = pl_hp - ((rand() % en_dmg + 1 / 10) / 10);
				}
			}else {  
				if ((pl_kev_health - (en_dmg / 10)) <= 0){
					pl_kev_health = pl_kev_health - ((rand() % en_dmg + 1 / 10) / 10);
					if ((pl_hp + pl_kev_health) <= 0){
						win = 2;
					} else {
						pl_hp = pl_hp + pl_kev_health;
						pl_kev = 0;
						pl_kev_health = 0;
					}
	  	    	} else {
				  pl_kev_health = pl_kev_health - (en_dmg / 10);
  	  	  	    }	
			}
			break;
 		case 3:
	 	 	if (pl_food >= 1){
	 	 		system("cls");
				  pl_hp = pl_hp + 20;
				  pl_food = pl_food - 1;
	  	    }
			break;
		case 4:
			win = 3;
			break;	 
	}
	if (win != 0){		
	return win;
	}else {goto war;}
}
void spordan(){
	cout<<"| Spordan: PodejdŸ tu, mam towar z najwy¿szej \n";
	cout<<"| 	   pó³ki. Wybierz sobie coœ!\n|\n";
	handel:
	cout<<"| 1. Lekka zbroja Spartanina: 70$  +40 KEV \n";
	cout<<"| 2. Miecz wyzwolenia Aten:   100$ +7  DMG \n";
	cout<<"| 3. Krzy¿ krzy¿akow:         40$  +2  REP\n";
	cout<<"| 4. Pasza (Kebab)    	      15$  +1  FOOD\n";
	if (pl_map == 0){
		cout<<"| 5. Mapa:		      60$  +1  MAPA\n";
	} else {
		cout<<"| 5. Zobacz mape\n";
	}
	cout<<"| 6. okradnij Spordana\n";
	cout<<"| 7. chyba jednak podziêkujê...\n";
	cout<<"|\n| Portfel: "<<pl_cash<<"\n";
	kreska();
	int handel;
	cin>>handel;
	switch (check(handel,7)){
		case 1:
			system("cls");
			if (pl_kev == 1){
				stats();
				kreska();
				cout<<"|\n| Spordan: Przecie¿ juz masz t¹ zbrojê! \n|\n";
				goto handel;
			}
			if (pl_cash < 60){
				stats();
				kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie staæ ciê. \n|\n";
				goto handel;
			} else {
			pl_cash = pl_cash - 60;
			pl_kev = 1;
			pl_kev_health = pl_kev_health + 40;
			stats();
			kreska();
			cout<<"|\n| Spordan: Pasuje jak ula³! Taka plandeka wytrzyma wiele.\n|          ¯yczysz sobie czegoœ jeszcze? \n|\n";
			goto handel;
			}
        case 2:
        	system("cls");
        	if (pl_weap >= 1){
        		stats();
				kreska();
				cout<<"|\n| Spordan: Przecie¿ masz lepszy miecz! \n|\n";
				goto handel;
			}
        	if (pl_weap == 1){
        		stats();
				kreska();
				cout<<"|\n| Spordan: Przecie¿ juz masz ten miecz! \n|\n";
				goto handel;
			}
			if (pl_cash < 100){
				stats();
				kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie staæ cie. \n|\n";
				goto handel;
			} else {
			pl_cash = pl_cash - 100;
        	pl_weap = 1;
        	pl_dmg = pl_dmg + 7;
			stats();
			kreska();	
        	cout<<"|\n| Spordan: Jesteœ teraz o wiele silniejszy. Chcesz coœ jeszcze?\n|\n";
        	goto handel;
			}
        case 3:
        	system("cls");
			if (pl_cash < 60){
				stats();
				kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie staæ cie. \n|\n";
				goto handel;
			} else {
			pl_cash = pl_cash - 40;
        	pl_rep = pl_rep + 2;
			stats();
			kreska();
        	cout<<"|\n| Spordan: Z nim zyskasz szacunek ludzi.\n|           Potrzebujesz czegoœ jeszcze?\n|\n";
        	goto handel;
			}
        case 4:
        	system("cls");
			if (pl_cash < 15){
				stats();
        		kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie staæ cie. \n|\n";
				goto handel;
			} else {
        	pl_cash = pl_cash - 15;
        	pl_food = pl_food + 1;
        	stats();
			kreska();
        	cout<<"|\n| Spordan: Ten kebab postawi ciê na nogi! \n|\n";
        	goto handel;
			}
		case 5:
			system("cls");
			if (pl_map == 1){
				stats();
        		mapa();
				goto handel;
			}	
			if (pl_cash < 60){
				stats();
        		kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie staæ cie. \n|\n";
				goto handel;
			}
			pl_map = 1;
			pl_cash = pl_cash - 60;
			stats();
        	kreska();
				cout<<"|\n| Spordan: Z ni¹ nigdy siê nie zgubisz\n|\n";
				goto handel;
		case 6:
			system("cls");
			stats();
			kreska();
			cout<<"|\n";
			switch (walka(2)){
				case 1:
					system("cls");
					pl_cash = pl_cash + 200;
					stats();
					kreska();
					cout<<"|\n| Spordan: bêdê ciê mia³ na oku gnojku...\n";
					cout<<"|\n| Ukradziono 200$\n";
					if(pl_kev == 0){
						pl_kev = 1;
						pl_kev_health = 40;
						cout<<"|\n| Otrzymano: Lekka zbroja spartanina\n";
					} else if (pl_weap == 0){
						pl_weap = 1;
						pl_dmg = pl_dmg + 7;
						cout<<"|\n| Otrzymano: Miecz wyzwolenia Aten\n";
					}
					break;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Spordan: Nastepnym razem ciê zabije. \n";
					break;
				case 3:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Spordan: Haha, uciekaj!\n";
					break;
			}
			break;
		case 7:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Spordan: Jeszcze siê spotkamy! \n|\n";	
			break;
	}
}
void start () {			//prolog
    stats();
	kreska();
	cout<<"\n| --- Kraina Bielsania, wiek XVI --- \n|\n";
    cout<<"| Wchodzisz do miejscowosci Czechigród \n|\n";
    cout<<"| Stebenia: Ca³e szczêœcie ze jesteœ! \n|\n";
    cout<<"| 1. Co siê sta³o? \n";
    cout<<"| 2. Nie cieszê sie z twojej obecnoœci  \n";
    cout<<"| 3. Oddawaj mi wszystko co masz kobieto! \n";
    kreska();
    int odp1;
    cin>>odp1;
    switch (check(odp1,3)){
        case 1: {
        	system("cls");
        	stats();
            kreska();
            cout<<"|\n| Stebenia: W³asnie ca³a nasza wioska \n";
			cout<<"| zosta³a obrabowana. Od czasu gdy \n";
			cout<<"| Wojmir zacz¹³ wysy³aæ do naszej wioski \n";
			cout<<"| swoje wojska, wszyscy mamy obowi¹zek sie \n";
			cout<<"| mu podporz¹dkowaæ, inaczej nas zabije \n|\n";
            cout<<"| 1. Mogê wam w jakiœ sposób pomóc? \n";
            cout<<"| 2. Nie interesuje mnie ¿e macie z nim \n";
			cout<<"|    problem. Mam wa¿niejsze sprawy \n";
            kreska();
            int odp2;
            cin>>odp2;
                switch (check(odp2,2)){
                    case 1:
                    	system("cls");
                    	stats();
                        kreska();
                        cout<<"|\n| Stebenia: Jedyna opcja to pokonaæ Wojmira,\n";
						cout<<"| a droga do jego zamku jest niebezpieczna\n|\n";
                        cout<<"| 1. Nie wa¿ne jak ciê¿ka bêdzie droga, \n|    podejmê tego wyzwania \n";
                        cout<<"| 2. Chyba jednak siê rozmyœli³em..."<<endl;
                        kreska();
                        int odp4;
                        cin>>odp4;
                            switch (check(odp4,2)){
                                case 1:
                                	system("cls");
                                	stats();
                                    kreska();
                                    cout<<"|\n| Nasz bohaterze! Muszê powiedzieæ o tym \n| wszystkim w wiosce! \n";
                                    pl_rep = pl_rep + 2;
                                    pass = 1;
                                    goto po_starcie;
                                case 2:
                                	system("cls");
                                	stats();
                                    kreska();
                                    cout<<"|\n| Stebenia: B³agam ciê, pomóz nam! Nasze plony\n";
									cout<<"|     	    zosta³y ca³kowicie zrabowane \n|\n";
                                    cout<<"| 1. No dobra, wesprê was, ale chce pieni¹dze \n";
                                    cout<<"| 2. Niech bêdzie, pomogê \n";
                                    cout<<"| 3. IdŸ precz \n";
                                    kreska();
                                    int odp5;
                                    cin>>odp5;
									switch (check(odp5,3)){
                                        case 1:
                                        	money:
                                        	system("cls");
                                        	stats();
                                            kreska();
                                            cout<<"|\n| Stebenia: Mamy jedynie 30 z³otych... \n|\n";
                                            cout<<"| 1. Wy biedaki, nie pomoge wam \n";
                                            cout<<"| 2. Przyjmê datek i zrobiê co w mojej mocy \n";
                                            cout<<"| 3. Zostawcie pieni¹dze, zrobiê to za darmo. \n";
                                            kreska();
                                            int odp6;
                                            cin>>odp6;
                                            switch (check(odp6,3)){
                                                case 1:
                                                	system("cls");
                                                	stats();
                                                    kreska();
                                                    cout<<"|\n| Stebenia: B¹dŸ przeklêty!\n";
                                                    ending = 1;
                                                    goto po_starcie;
                                                case 2:
                                                	system("cls");
                                                	stats();
                                                    kreska();
                                                    cout<<"| Stebenia: Wiêc te 30z³ jest teraz twoje, liczymy na ciebie! \n";
                                                    pl_rep = pl_rep + 1;
                                                    pl_cash = pl_cash + 30;
                                                    pass = 1;
                                                    goto po_starcie;
                                                case 3:
                                                	system("cls");
                                                	stats();
                                                    kreska();
                                                    cout<<"| Stebenia: Naprawdê? Liczymy na ciebie dzielny wojaku! \n";
                                                    pl_rep = pl_rep + 2;
                                                    pass = 1;
                                                    goto po_starcie;
                                            }
                                        case 2:
                                        	system("cls");
                                        	stats();
                                            kreska();
                                            cout<<"| Stebenia: Ca³e szczescie! Muszê powiedzieæ wszystkim w wiosce! \n";
                                            pl_rep = pl_rep + 2;
                                            pass = 1;
                                            goto po_starcie;
                                        case 3:
                                        	system("cls");
                                        	stats();
                                            kreska();
                                            cout<<"|\n| Stebenia: B¹dŸ przeklêty!\n";
                                            ending = 2;
                                            goto po_starcie;
									}
                            }      
                    case 2:
                    	system("cls");
                    	stats();
                        kreska();
                        cout<<"|\n| Stebenia: Sugerujesz ¿e jest coœ\n|           wa¿niejszego od zniszczenia\n|           Bielsanii? \n|\n";
                        cout<<"| 1. Tak, na przyk³ad ciekawsze gry \n";
                        cout<<"| 2. No, no nie. Jednak wam pomogê \n";
                        cout<<"| 3. Nie widzê w twoich rêkach sakiewki \n";
                        kreska();  
                        int odp7;
                        cin>>odp7;
                        switch (check(odp7,3)){
                            case 1:
                            	system("cls");
                            	stats();
                                kreska();
                                cout<<"| Stebenia: No to idŸ se pograj i wyginaj mi z wioski natychmiast \n";
                                ending = 4;
                                goto po_starcie;
                            case 2:
                            	system("cls");
                            	stats();
                                kreska();
                                cout<<"| Stebenia: To wspaniale! muszê powiedzieæ o tym wszystkim!";
                                pl_rep = pl_rep + 2;
                                pass = 1;
                                goto po_starcie;
                            case 3:
                            	goto money;
                        }
                        
				}
        }
        case 2:
			system("cls"); 
			stats();
            kreska();
            cout<<"|\n| Stebenia: Wygl¹dasz na s³abeusza, ale\n|           wys³uchaj mnie. Król Wojmir od\n";
            cout<<"|           jakiegoœ czasu atakuje wioski w \n|           krainie i kradnie wszystko co mamy.\n|           Potrzebujemy pomocy \n|\n";
            cout<<"| 1. I dlaczego akurat ja mam temu podo³aæ? \n";
            cout<<"| 2. Pieni¹dze nie rosn¹ na drzewach \n";
            cout<<"| 3. Nie mam zamiaru sie mieszaæ w wasze \n|    ch³opskie zabawy \n";
            kreska();
            int odp10;
            cin>>odp10;
            switch (check(odp10,3)){
                case 1:
                	system("cls");
                	stats();
                    kreska();
                    cout<<"|\n| Stebenia: Poniewa¿ masz tyle odwagi,\n|           ¿eby go ubiæ \n|\n";
                    cout<<"| 1. Dobra, wchodzê w to \n";
                    cout<<"| 2. WeŸcie se kogos innego\n";
                    kreska();
                    int odp11;
                    cin>>odp11;
                    switch (check(odp11,2)){
                        case 1:
                        	system("cls");
                        	stats();
                            kreska();
                            cout<<"| Stebenia: Dziêkujê, muszê powiedzieæ o tym ca³ej wiosce! \n";
                            pl_rep = pl_rep + 2;
                            pass = 1;
                            goto po_starcie;
                        case 2:
                        	system("cls");
                        	stats();
                            kreska();
                            cout<<"|\n| Stebenia: Badz przeklety!\n";
                            ending = 1;
                            goto po_starcie;
                    }
                case 2:
					goto money;
                case 3:
                	system("cls");
                	stats();
                    kreska();
                    cout<<"| Stebenia: W takim razie panu dziêkujemy \n";
                    ending = 2;
                    goto po_starcie;
            }
        case 3:
        	system("cls");
        	stats();
        	kreska();
        	cout<<"| Stebenia: Odejdz ode mnie zwyrolu \n|\n";
        	int stebenia = walka(1);
        	system("cls");
        	stats();
     		kreska();
        	switch (stebenia){
            	case 1:
					pl_cash = pl_cash + 30;
            		pass = 1;
            		cout<<"|\n| Stebenia: Niech ciê piorun strzeli! \n| Ukradziono 30$\n";
            		break;
   				case 2: 
					cout<<"|\n| Stebenia: Nawet ze mn¹ przegra³eœ? XD wypad mi st¹d\n";
					pass = 1;
					break;
				case 3:
					cout<<"|\n| Stebenia: Uciekasz? Masz ty rozum i godnoœæ\n|           cz³owieka? XD\n";
					pass = 1;	
					break;
			}
            goto po_starcie;    
    }
    po_starcie:
        if (pass != 0){  //miejsce ktore konczy petle dialogu wstepnego gdy powiedzie sie on
        	cout<<"| \n";
            Sleep(2000);
            cout<<"| Historia zaczyna sie w³aœnie tutaj";
            for (int i=1; i<6; i++){
                Sleep(700);
                cout<<".";
            }
            system("cls"); 
    }  
}
int litynia(){
		system("pause");
		litynia:
		system("cls");
		stats();
		kreska();
		cout<<"|\n| Gdzie chcesz siê udaæ?\n";
		cout<<"|\n| 1. Rozmawiaj z Bindarem\n";
		cout<<"| 2. Kantyna\n";
		cout<<"| 3. WyjdŸ z Litynii\n";
		kreska();
		int lit;
		cin>>lit;
		switch (check(lit,3)){
			case 1:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Bindar: W czym mogê ci pomóc?\n";
			cout<<"|\n| 1. Kto mo¿e mnie czegoœ nauczyæ?\n";
			cout<<"| 2. Potrzebujê pieniêdzy\n";
			cout<<"| 3. Jeszcze tu wrócê..\n";
			kreska();
			int odp6;
			cin>>odp6;
			switch (check(odp6,3)){
				case 1:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Bindar: W kantynie spotkasz Zaj¹s³awa\n";	
					cout<<"|         który pomo¿e ci zwiêkszyæ swoj¹ si³ê.\n";
					cout<<"|         On napewno ci pomo¿e. Powodzenia!\n";
					kreska();
					system("pause");
					goto litynia;
				case 2:
					system("cls");
					if (pl_rep > 2){
						if (bindar_cash == 1){
							stats();
							kreska();	
							cout<<"|\n| Bindar: Ju¿ ci da³em pieni¹dze.\n";	
							kreska();
							system("pause");
						} else {
							pl_cash = pl_cash + 50;
							bindar_cash = 1;
							stats();
							kreska();
							cout<<"|\n| Bindar: Mogê ci daæ 50 z³otych\n";
							cout<<"|\n| Otrzymano 50 z³otych\n";
							kreska();	
							system("pause");
						}
					} else {	
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Bindar: Nie ufam ci, udowodnij\n";
						cout<<"|         mi ¿e nie wydasz ich na piwo\n";
						cout<<"|\n| Brak ci reputacji\n";
						kreska();
						system("pause");
					}
					goto litynia;	
				case 3:
					goto litynia;	
					break;
			}
			case 2:
				kantyna:		
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Wchodzisz do kantyny Pod Drabin¹\n";			
				cout<<"|\n| 1. PodejdŸ do lady\n";
				cout<<"| 2. Rozmawiaj z Zaj¹s³awem\n";
				cout<<"| 3. WyjdŸ\n";
				kreska();
				int odp7;
				cin>>odp7;
				switch (check(odp7,3)){
					case 1:
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Michniard: Witaj nieznajomy! Co ciê\n";
						cout<<"|            do nas sprowadza?\n";
						michniart:
						cout<<"|\n| 1. O czym mówi¹ ludzie?\n";
						cout<<"| 2. Napi³bym siê piwa (10$)\n";
						cout<<"| 3. Gdzie znajdê kowala?\n";
						cout<<"| 4. Wrócê póŸniej..\n";
						kreska();
						int odp8;
						cin>>odp8;
						switch (check(odp8,4)){
							case 1:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Michniard: Wiem wiele, ale nie widzê\n";
								cout<<"|            w twoich rêkach sakiewki\n";
								cout<<"|\n| 1. Kup info (20$)\n";
								cout<<"| 2. Odpuszczê sobie...\n";
								kreska();
								int odp9;
								cin>>odp9;
								switch (check(odp9,2)){
									case 1:
										if (pl_cash > 20){
											if (michniard_tip == 0){
												system("cls");
												pl_cash = pl_cash - 20;
												stats();
												kreska();
								   	   	   		cout<<"|\n| Michniard: Król Wojmir stacjonuje w\n";
											   	cout<<"|            centrum krainy Bielsanii,\n";
												cout<<"|            w Bielogrodzie\n";
											   	kreska();
											   	michniard_tip++;
											   	goto michniart;
											} else if (michniard_tip == 1){
												system("cls");
												pl_cash = pl_cash - 20;
												stats();
												kreska();
								   	   	   		cout<<"|\n| Michniard: Król Wojmir jest podatny\n";
												cout<<"|            na obra¿enia z w³óczni,\n";
												cout<<"|            miedzianej. Sprzedaje tak¹ kowal\n";
												kreska();
												michniard_tip++;
											   	goto michniart;
											} else if (michniard_tip == 2){
												system("cls");
												pl_cash = pl_cash - 20;
												stats();
												kreska();
								   	   	   		cout<<"|\n| Michniard: Król Wojmir nie spodziewa\n";
												cout<<"|            siê ataku z kuchni. Zakradnij\n";
												cout<<"|            siê i wykorzystaj chwilê!\n";
												kreska();
												michniard_tip++;
											   	goto michniart;
											} else if (michniard_tip == 3){
												system("cls");
												stats();
												kreska();
								   	   	   		cout<<"|\n| Michniard: Powiedzia³em ci ju¿ wszystko!\n";
												kreska();
											   	goto michniart;
											}
										} else {
											system("cls");
											stats();
											kreska();
								   	   	   	cout<<"|\n| Michniard: Nie mogê ci niczego\n";
											cout<<"|            powiedzieæ, brak ci\n";
											cout<<"|            pieniêdzy. Wróæ póŸniej\n";
											kreska();
											goto michniart;
										}
									case 2:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Michniard: Jak sobie chcesz!\n";
										goto michniart;
								}
							case 2:	
								system("cls");
								if (pl_cash > 10){
									pl_cash = pl_cash - 10;
									pl_hp = pl_hp + 8;
									stats();
									kreska();
								   	cout<<"|\n| Michniard: Zdrowie!\n";
									cout<<"|            W czym mogê pomóc?\n";
									goto michniart;
								} else {
									stats();
									kreska();
									cout<<"|\n| Michniard: Przykro mi, nie staæ ciê!\n";
									goto michniart;	
								}
							case 3:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Michniard: Kowal stacjonuje w\n";
								cout<<"|            Godziburgu. Ma bardzo tanie,\n";
								cout<<"|            trwa³e zbroje i miecze.\n";
								goto michniart;
							case 4:	
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Michniard: Do zobaczenia!\n";
								kreska();
								system("pause");
								goto kantyna;
						}
					case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Zaj¹s³aw: Streszczaj siê, czego chcesz?\n";
					cout<<"|\n| 1. Chcê staæ siê silniejszym..\n";
					cout<<"| 2. Co ty mi bedziesz rozkazywa³\n";
					cout<<"| 3. Wrócê tu jeszcze\n";
					kreska();
					int odp10;
					cin>>odp10;
					switch (check(odp10,3)){
						case 1:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Zaj¹s³aw: I dlaczego s¹dzisz ¿e ci pomogê?\n";
							zajas:
							cout<<"|\n| 1. Chce zat³uc króla, pomo¿esz?\n";
							cout<<"| 2. <potrz¹œnij sakiewk¹ z pieniêdzmi>\n";
							cout<<"| 3. Chyba przywale ci w mordê\n";
							cout<<"| 4. Wrócê tu póŸniej\n";
							kreska();
							int odp11;
							cin>>odp11;
							switch (check(odp11,4)){
								case 1:
									if (wola_zajaslawa == 1){
										system("cls");
										pl_dmg = pl_dmg + 10;
										wola_zajaslawa = 0;
									   	stats();
									   	kreska();
										cout<<"|\n| Zaj¹s³aw: Z dobrej woli tyle ciê nauczê.\n";
										cout<<"|           Jeœli chcesz wiêcej sypnij z³otem\n";
										cout<<"|\n| Nauczono +10 DMG\n";
										kreska();
										goto zajas;
									} else {
									   	system("cls");
									   	stats();
									   	kreska();
									   	cout<<"|\n| Zaj¹s³aw: Moja dobroæ siê skoñczy³a,\n";
										cout<<"|           Chcesz umieæ? To dawaj kasê\n"; 
										kreska();
										goto zajas;  	
									}
								case 2:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Zaj¹s³aw: Widzê ¿e siê rozumiemy hehe\n";
									cout<<"|\n| 1. 10 DMG - 50$\n";
									cout<<"| 2. 5 DMG - 25$\n";
									cout<<"| 3. Kurde nie mam przy sobie z³ota\n";
									kreska();
									int odp12;
									cin>>odp12;
									switch (check(odp12,3)){
										case 1:
											system("cls");
											if (pl_cash >= 50){
												pl_dmg = pl_dmg + 10;
											   	pl_cash = pl_cash - 50;
									   		   	stats();
									   			kreska();
												cout<<"|\n| Zaj¹s³aw: Jesteœ teraz o wiele silniejszy\n";
											   	kreska();
												goto zajas;
											} else {
									   		   	stats();
									   		   	kreska();
												cout<<"|\n| Zaj¹s³aw: Nie masz tyle z³ota\n";
												kreska();
												goto zajas;	
											}
										case 2:
											system("cls");
											if (pl_cash >= 25){
												pl_dmg = pl_dmg + 5;
											   	pl_cash = pl_cash - 25;
									   		   	stats();
									   			kreska();
												cout<<"|\n| Zaj¹s³aw: Jesteœ teraz silniejszy\n";
											   	kreska();
												goto zajas;
											} else {
									   		   	stats();
									   		   	kreska();
												cout<<"|\n| Zaj¹s³aw: Nie masz tyle z³ota\n";
												kreska();
												goto zajas;	
											}
										case 3:
											system("cls");
											stats();
											kreska();
											goto zajas;	
									}
								case 3:
								zajas_war:	
								switch (walka(4)){
									case 1:
										system("cls");
										pl_cash = pl_cash + 400;
										stats();
										kreska();
										cout<<"|\n| Zaj¹s³aw: Nie powiedzia³em ostatniego s³owa\n";
										cout<<"|\n| Ukradziono 400$\n";
										goto zajas;
									case 2:	
										system("cls");
										stats();
										kreska();
										wola_zajaslawa = 0;
										cout<<"|\n| Zaj¹s³aw: Zniknij mi z oczu natychmiast.\n";
										goto zajas;
									case 3:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Zaj¹s³aw: Ty tchórzu!\n";
										goto zajas;
								}
								case 4:
									  goto kantyna;	
							}
						case 2:
							goto zajas_war;
						case 3:
							goto kantyna;
					}
					case 3:
						goto litynia;
				}
			case 3:	
				system("cls");
				ch1ptl:
	   	   	   	stats();
				kreska();
				cout<<"|\n| Dok¹d chcesz siê udaæ?\n";
				cout<<"|\n| 1. Litynia\n";
	   	   	   	cout<<"| 2. OdwiedŸ Spordana\n";
	   	   	   	cout<<"| 3. Godziburg\n";
				kreska();
				int wander;
				cin>>wander;
				switch (check(wander,3)){
					case 1:
						goto litynia;
					case 2:
						system("cls");
						stats();
						kreska();
						cout<<"|\n";
						spordan();
						system("pause");
						system("cls");
						goto ch1ptl;
					case 3:
						system("cls");
						stats();
						kreska();
						break;
				}
		}
ch1end:;
			
}
void house(){
	system("cls");
	stats();
	kreska();
	srand(time(NULL));
	int money = rand() % 500 + 50;
	int rep = rand() % 3 + 0;
	cout<<"|\n| Do ukradniêcia: "<<money<<"$\n";
	cout<<"| Szansa na zwyciêstwo: "<<rand() % 100 + 1<<"%\n";
	cout<<"| Ujemna reputacja: -"<<rep<<" REP\n";
	kreska();
	cout<<"|\n";
	cout<<"|                __\n";
	cout<<"|               _||____\n";
	cout<<"|              / ||    \\\n";
	cout<<"|             /_________\\\n";
	cout<<"|             |  _   _  |\n";
	cout<<"|   O         | | | | | |\n";
	cout<<"|  /|\\        | /// | | |\n";
	cout<<"|  / \\        ===========\n";
	kreska();
	cout<<"|\n| 1. Kradnij\n";
	cout<<"| 2. Odpuœæ sobie\n";
	kreska();
	int rob;
	cin>>rob;
	switch(check(rob,2)){
		case 1:
			switch(rand() % 2 + 0){
				case 0:
					system("cls");
					pl_cash = pl_cash + money;
					pl_rep = pl_rep - rep;
					stats();
					kreska();
					cout<<"|\n| Ukradiono pomyœlnie "<<money<<"$\n";
					cout<<"|\n| Utracono "<<rep<<" REP\n";
					kreska();
					break;
				case 1:
					system("cls");
					pl_rep = pl_rep - rep;
					stats();
					kreska();
					cout<<"|\n| Nie uda³o ci siê okraœæ domu\n";
					cout<<"|\n| Utracono "<<rep<<" REP\n";
					kreska();
					break;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Nie uda³o ci siê okraœæ domu\n";
					cout<<"| Ale uda³o ci siê uciec\n";
					cout<<"|\n| Utracono 0 REP\n";
					kreska();
					break;					
			}
			break;
		case 2:
			break;
	}
	system("pause");
}
void godziburg() {
	
	godziburg:
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Gdzie chcesz siê udaæ?\n";
	cout<<"|\n| 1. Kowal\n";
	cout<<"| 2. Koœció³\n";
	cout<<"| 3. Okradnij dom\n";
	cout<<"| 4. WyjdŸ\n";
	kreska();
	int odp1;
	cin>>odp1;
	switch (check(odp1,4)){
		case 1:
			system("cls");
			stats();
			kreska();
			if (kowal == 0){
				kowal = 1;	
				cout<<"|\n| Wchodzisz do izby kowalskiej. ¯ar bucha ci\n";
				cout<<"| w twarz. Odzywa siê jeden z dwóch kowali\n";
				cout<<"| stoj¹cych nad rozgrzanym piecem\n";
				cout<<"|\n| Stefir: Dzieñ niehandlowy, nie przyjmujemy\n";
				cout<<"|         nowych zamówieñ\n";
				cout<<"|\n| 1. Mo¿e zrobicie wyj¹tek dla wybawiciela?\n";
				cout<<"| 2. Ktoœ tutaj chyba chce dostaæ w szczêkê\n";
				cout<<"| 3. A-aha.. a kiedy mo¿na przyjœæ?\n";
				kreska();
				int odp2;
				cin>>odp2;
				switch (check(odp2,3)){
					case 1:
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Stefir odwraca siê na piêcie i spogl¹da\n";
						cout<<"| na ciebie z pogard¹\n";
						cout<<"|\n| Stefir: Ty? haha! Od czego takie coœ\n";
						cout<<"|         mo¿e nas wybawiæ?\n";
						cout<<"|\n| 1. Od najazdów Wojmira\n";
						cout<<"| 2. Ciebie chyba delikatnie zêby swêdz¹\n";
						kreska();
						int odp3;
						cin>>odp3;
						switch (check(odp3,2)){
							case 1:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Stefir: Strasznie zaciêty jesteœ jak na\n";
								cout<<"|         niedzielnego ³owcê zwierzyn\n";
								cout<<"|\n| 1. Kurdi balans bêdziesz komplikowa³ czy\n";
								cout<<"|    pomo¿esz?\n";
								cout<<"| 2. Masz z tym jakiœ problem?\n";
								kreska();
								int odp4;
								cin>>odp4;
								switch (check(odp4,2)){
									case 1:
									stefir_szyderczy:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Stefir: Widzê ¿e dobrze wiesz czego chcesz\n";
									cout<<"|\n| W tej chwili odwróci³ siê drugi kowal\n";
									cout<<"|\n| Kopbard: No proszê, wygl¹da na to ¿e mamy\n";
									cout<<"|          do czynienia z buntownikiem.\n";
									cout<<"|          Dlaczego s¹dzisz ¿e ci siê uda?\n";
									cout<<"|\n| 1. Poniewa¿ wiem ¿e mi pomo¿ecie\n";
									cout<<"| 2. Poniewa¿ wiem jak go przechytrzyæ\n";
									cout<<"| 3. Bo tylko ja mogê poœwiêciæ ¿ycie za wolnoœc\n";
									kreska();
									int odp5;
									cin>>odp5;
									switch (check(odp5,3)){
										case 1:
											system("cls");
											stats();
									   	   	kreska();
									   	   	cout<<"|\n| Stefir: Cholera sk¹d ty wszystko wiesz.\n";
									   	   	cout<<"|         S³uchaj, masz o tym nikomu nie mówiæ\n";
									   	   	miecz:
									   	   	cout<<"|\n| Drugi kowal Kopbard podchodzi i chwyta\n| ciê za ramiona\n";
									   	   	cout<<"|\n| Kopbard: Jeœli chcesz broñ, któr¹ napewno\n";
									   	   	cout<<"|          pokonasz Wojmira, musisz udaæ siê\n";
									   	   	cout<<"|          na wyprawê do podziemnego miasta w\n";
									   	   	cout<<"|          którym czas p³ynie wolniej. Mam na\n";
									   	   	cout<<"|          myœli Serweniê. Wejœcie do niej\n";
									   	   	cout<<"|          jest strze¿one, a œrodek pe³en jest\n";
									   	   	cout<<"|          niebezpiecznych pu³apek, ale w\n";
						   	   				cout<<"|          grocie która podpisana bêdzie cyfr¹\n";
						   	   				cout<<"|          211, odnajdziesz rudê miedzi dziêki\n";
											cout<<"|	   której wykujê ci miecz lepszy od\n";
											cout<<"|          tego który ma Wojmir\n";
											cout<<"|\n| 1. Zdobêdê miedzian¹ rudê!\n";
											cout<<"| 2. Dacie mi jakieœ wyposa¿enie na\n";
											cout<<"|    t¹ wyprawê? Mogê zgin¹æ.\n";
						   	   				kreska();
						   	   				int odp6;
						   	   				cin>>odp6;
						   	   				switch(check(odp6,2)){
											case 1:
												system("cls");
												pl_rep = pl_rep + 2;
												stats();
												kreska();
												cout<<"|\n| Stefir: Wspaniale! Ruszaj jak najszybciej\n";
												cout<<"|         kolejny konwój Wojmira nied³ugo tu bêdzie!\n";
												kreska();
												cout<<"\n ";
												system("pause");
												system("cls");
												stats();
												kreska();
												goto godziburg;
											case 2:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Stefir: <westchn¹³> niech ci bêdzie.\n";
												if (pl_dmg >= 25){
													pl_kev = 3;
													pl_kev_health = 160;
													cout<<"|\n| Stefir: Jesteœ doœæ silny wiêc\n";
													cout<<"|         dostaniesz lepsz¹ zbrojê\n";
													kreska();
													system("pause");
												} else {
													pl_weap = 2;
													pl_dmg = pl_dmg + 10;
													cout<<"|\n| Stefir: Trzymaj ten miecz, nim\n";
													cout<<"|         pokonasz niemal ka¿dego\n";
													kreska();
													system("pause");
												}
												system("cls");
												stats();
												kreska();
												goto godziburg;	  		  
											}
										case 2:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Stefir: Dobra zasadzka nie wystarczy\n";
											goto miecz;
										case 3:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Stefir: Ohoho no jaki z ciebie bohater hehe\n";
											goto miecz;
									}
									case 2:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Stefir: Dziwi mnie to ¿e tak ci zale¿y\n";
										cout<<"|         na czyimœ ¿yciu, równie dobrze mo¿esz\n";
										cout<<"|         okradaæ domy razem z ludŸmi króla\n";
										cout<<"|\n| 1. Muszê go pokonaæ!\n";
										cout<<"| 2. Serio? jak do niego do³¹czyæ??\n";
										kreska();
										int odp7;
										cin>>odp7;
										switch (check(odp7,2)){
											case 1:
												system("cls");
												stats();
												kreska();
												goto miecz;
											case 2:
												woymir:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Stefir: Ty pijawko!\n";
												cout<<"|\n| Zosta³eœ wygoniony\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto godziburg;
										}
										break;
								}
							case 2:	
								kowal_walka:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Stefir: Ty sie dobrze czujesz? Jestem\n";
								cout<<"|         kowalem, jak ci przywale to ciê\n";
								cout<<"|         wywali na plantacjê betonu w\n";
								cout<<"|         Czechigrodzie\n";
								cout<<"|\n| 1. Zapomnijmy o sprawie, mo¿ecie mi pomóc?\n";
								cout<<"| 2. Pracujesz tu tylko dlatego ¿eby móc\n";
								cout<<"|    poca³owaæ Wojmira w dupê!\n";
								kreska();
								int odp8;
								cin>>odp8;
								switch (check(odp8,2)){
									case 1:
										system("cls");
										stats();
										kreska();
										goto miecz;
									case 2:
										switch (walka(5)){
											case 1:
												system("cls");
												pl_cash = pl_cash + 600;
												stats();
												kreska();
												cout<<"|\n| Stefir: Nie doceni³em ciê\n";
												cout<<"|\n| Ukradziono 600$\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												cout<<"|\n";
												goto godziburg;
											case 2:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Stefir: Jeszcze raz wpadniesz mi pod\n";
												cout<<"|         rêkê a rozwa³kujê ci mordê\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto godziburg;
											case 3:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Stefir: ¯ebym ciê tu wiêcej nie widzia³!\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto godziburg;
										}
								}
						}
					case 2:
					goto kowal_walka;
					case 3:
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Stefir: Nie jesteœ ca³kiem bystry, co?\n";
						cout<<"|\n| 1. Mo¿esz mówiæ wprost o co ci chodzi?\n";
						cout<<"| 2. Sugerujesz ¿e NIC NIE UMIEM?\n";
						cout<<"| 3. Skoro tutaj trafi³em to znaczy ¿e myœlê\n";
						kreska();
						int odp9;
						cin>>odp9;
						system("cls");
						stats();
						kreska();
						switch(check(odp9,3)){
							case 1:
								cout<<"|\n| Stefir: To tylko niepoznaka ¿eby\n";
								cout<<"|         ludzie Wojmira siê nas nie czepiali\n";
								cout<<"|\n| 1. A ja w³aœnie chce go pokonaæ!\n";
								cout<<"| 2. Jestem ciekaw co na to ¿o³nierze Wojmira\n";
								kreska();
								int odp10;
								cin>>odp10;
								system("cls");
								stats();
								kreska();
								switch (check(odp10,2)){
									case 1:
										goto stefir_szyderczy;
									case 2:
										goto woymir;
								}
							case 2:
								cout<<"|\n| Stefir: TAK!!\n";
								cout<<"|\n| 1. JA CI ZARA..!\n";
								cout<<"| 2. Spostrzegawczy jesteœ.\n";
								kreska();
								int odp11;
								cin>>odp11;
								switch(check(odp11,2)){
									case 1:
										goto kowal_walka;
									case 2:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Stefir: Co nie zmienia faktu ¿e mo¿esz\n";
										cout<<"|         nam siê przydaæ\n";
										goto miecz;
								}
							case 3:
								cout<<"|\n| Stefir: To fakt, wytrzymaæ w Bielsanii\n";
								cout<<"|         wiêcej ni¿ godzinê to ju¿ jazda bez\n";
								cout<<"|         trzymanki\n";
								cout<<"|\n| 1. Dlatego chcê wam pomóc i obaliæ króla\n";
								cout<<"| 2. Chyba przywalê ci w mordê\n";
								kreska();
								int odp12;
								cin>>odp12;
								switch(check(odp12,2)){
									case 1:
										goto stefir_szyderczy;
									case 2:
										goto kowal_walka;
								}
						}
				}
			} else {
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Stefir: Czego potrzeba?\n";
				coval:
				cout<<"| 1. Jeszcze tu wróciê\n";
				kreska();
				int odp13;
				cin>>odp13;
				switch(check(odp13,1)){
					case 1:
						system("cls");
						stats();
						kreska();
						goto godziburg;
				}
			}
		case 2:; //kosciol
			system("cls"); 
			stats();
			kreska();
			cout<<"|\n| Wchodzisz do koœcio³a. WyraŸnie czuæ\n";
			cout<<"| kadzid³o. Co chcesz zrobiæ?\n";
			church:
			cout<<"|\n| 1. Módl siê\n";
			cout<<"| 2. Rozmawiaj z kap³anem\n";
			cout<<"| 3. WyjdŸ\n";
			kreska();
			int odp13;
			cin>>odp13;
			switch (check(odp13,3)){
				case 1:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Innos dziêkuje ci za modlitwê\n";
					if (innos <= 2){
					innos++;
					pl_rep = pl_rep + 2;
					cout<<"|\n| Otrzymano +2 REP\n";
					}
					goto church;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Ks. Stanomir: Œwiat³y wêdrowcze\n";
					cout<<"|               b¹dŸ pochwalony!\n";
					ksiadz:
					cout<<"|\n| 1. Mo¿esz mnie pob³ogos³awiæ?\n";
					cout<<"| 2. Gomez nie wiedzia³ o zabójstwie\n";
					cout<<"|    magów ognia\n";
					cout<<"| 3. Jeszcze tu wrócê\n";
					kreska();
					int ks1;
					cin>>ks1;
					switch(check(ks1,3)){
						case 1:
							if (adanos == 2){
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Stanomir: Adanos ju¿ ciê\n";
								cout<<"|           nie blogos³awi! ¯¹dasz\n";
								cout<<"|           zbyt wiele!\n";
								goto ksiadz;
							}
							if (pl_rep > 5){
								adanos++;
								system("cls");
								pl_hp = pl_hp + 30;
								stats();
								kreska();
								cout<<"|\n| Stanomir: B³ogos³awiê ciê w\n";
								cout<<"|           imieniu Adanosa\n";
								goto ksiadz;
								
							} else {
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Stanomir: Przykro mi ale\n";
								cout<<"|           nie ufam ci.\n";
								cout<<"|\n| Masz za ma³o reputacji\n";
								goto ksiadz;
							}
						case 2:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Stanomir: WIEDZIA£ TYLKO\n";
							cout<<"|           STARY OBÓZ WSZYSTKO\n";
							cout<<"|           TUSZUJE!\n";
							goto ksiadz;
						case 3:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Stanomir: Obyœ wróci³ ca³y\n";
							cout<<"|           i zdrowy.\n";
							goto godziburg;
						
					}
				case 3:
					system("cls");
					stats();
					kreska();
					goto godziburg;
				
			}
		case 3://kradziez domu
		   	house();
			goto godziburg; 			
		case 4:  //wyjscie
			system("cls"); 
			stats();
			kreska();
			godziburg_rozstaj:
	   	   	cout<<"|\n| Dok¹d chcesz siê udaæ?\n";
			cout<<"|\n| 1. Litynia\n";
	   	   	cout<<"| 2. Serwenia/Bielenia\n";
	   	   	cout<<"| 3. Godziburg\n";
	   	   	kreska();
			int wander;
			cin>>wander;
			switch (check(wander,3)){
				case 1:
					litynia();
					break;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Rozpocznie siê kolejny rozdzia³,\n";
					cout<<"| nie bêdzie mo¿liwoœci ³atwego powrotu\n";
					cout<<"|\n| 1. Zrozumia³em\n";
					cout<<"| 2. Nie zrozumia³em\n";
					int alert;
					cin>>alert;
					switch (check(alert,2)){
						case 1:
							break;
						case 2:	
							system("cls");
							stats();
							kreska();
							goto godziburg_rozstaj;
					}
					ch2 = 1;
					break;
				case 3:	
					goto godziburg;	
			}
	}
}
void chapter1(){		//rozdzial 1
	tytul();
	cout<<"\n|    ROZDZIAL 1: W DRODZE DO LITYNII \n";
	kreska();
	cout<<"\n  ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Przemierzasz drogê z Czechigrodu do Litynii\n|\n";
	cout<<"| Spotka³eœ handlarza\n|\n";
	spordan();
	Sleep(3000);
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Docierasz do Litynii. Wioska jest pogr¹¿ona\n";
	cout<<"| w chaosie. W bramie spotykasz Bindara\n";
	cout<<"|\n| Bindar: Ach moje ramie!\n";
	cout<<"|\n| 1. Cholera cz³owieku co ty narobi³eœ?\n";
	cout<<"| 2. Nie przejmuj siê rêk¹, najwy¿ej\n";
	cout<<"|    zrobimy now¹ z drewna\n";
	kreska();
	int odp1;
	cin>>odp1;
	switch (check(odp1,2)){
		case 1:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Bindar: Chcia³em z³apaæ chocia¿by jednego\n";
			cout<<"|         z tych skurczybyków Wojmira ale on\n";
			cout<<"|         wyj¹³ miecz szybciej i mnie obi³\n";
			cout<<"|\n| 1. <pomó¿ zabanda¿owaæ ranê>\n";
			cout<<"| 2. Jakim kalek¹ trzeba byæ ¿eby\n|    przegraæ z jakimœ pionkiem króla?\n";
			kreska();
			int odp2;
			cin>>odp2;
			switch (check(odp2,2)){
				case 1:
					bandaz:
					system("cls");
					pl_rep = pl_rep + 1;
					stats();
					kreska();
					cout<<"|\n| Bindar: Oh dziêkujê ci... Nastêpnym razem\n";
					cout<<"|         pozabijam ich wszystkich moim\n";
					cout<<"|         bagnetem francuskim\n";
					cout<<"|\n| 1. Nie szalej, prawie sie wykrwawi³eœ\n";
					cout<<"| 2. Mo¿esz mi pomóc w wyprawie na\n|    króla Wojmira?\n";
					cout<<"| 3. Drzewo podwa¿a mur korzeniami\n";
					kreska();
					int odp3;
					cin>>odp3;
					switch (check(odp3,3)){
						case 1:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Bindar: Mn¹ siê nie przejmuj. Co tu robisz?\n";
							cout<<"|\n| 1. Idê zabiæ Króla\n";
							cout<<"| 2. Zbieram maliny\n";
							cout<<"| 3. Przysy³a mnie siara, mam odebraæ \n|    ostatni¹ ratê\n";
							kreska();
							int odp4;
							cin>>odp4;
							switch(check(odp4,3)){
								case 1:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Bindar: Cholera niez³y jesteœ. Jeœli chcesz\n";
									cout<<"|         zwiêkszyæ swoj¹ si³ê, udaj siê do\n";
									cout<<"|         Zaj¹s³awa. Siedzi w kantynie.\n";
									cout<<"|         Powodzenia!\n";
									kreska();
									goto litynia;
								case 2:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Bindar: Maliny czy ostrê¿yny?\n";
									cout<<"|\n| 1. Maliny.\n";
									cout<<"| 2. Ostrê¿yny.\n";
									kreska();
									int picture;
									cin>>picture;
									switch (check(picture,2)){
										case 1:
											system("cls");
											pl_hp = 1;
											stats();
											kreska();
											cout<<"|\n| Bindar: ZGINIESZ\n";
											cout<<"|\n| Bindar: Jeszcze raz powiesz komuœ takie bzdury \n";
											cout<<"|        a ciê osobiœcie powieszê\n";
											kreska();
											goto litynia;
										case 2:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Bindar: Wiêc trzymaj. Czuj\n";
											cout<<"|         siê u nas jak u siebie!\n|\n| Otrzymano koszyk ostrê¿yn\n";
											kreska();
											pl_food = pl_food + 1;
											goto litynia;										
									}
								case 3:
									system("cls");
									pl_cash = pl_cash + 50;
									stats();
									kreska();
									cout<<"|\n| Bindar: n-nie chcia³em niepokoiæ Pana\n|         Siarzewskiego, proszê...\n";
									cout<<"|\n| Otrzymano 50$\n";
									kreska();		
									goto litynia;							
							}
						case 2:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Bindar: Có¿, ja wiele nie mogê ci daæ\n";
							cout<<"|         ale w kantynie spotkasz Zaj¹s³awa\n";	
							cout<<"|         który pomo¿e ci zwiêkszyæ swoj¹ si³ê.\n";
							cout<<"|         On napewno ci pomo¿e. Powodzenia!\n";
							kreska();
							goto litynia;
						case 3:
							system("cls");
							stats();
							kreska();	
							cout<<"|\n| Bindar: Wyjaœni³bym ci coœ ale s¹siedzi.\n";
							cout<<"|         Bierz te 2 kebaby i idŸ w swoj¹ strone\n";
							pl_food = pl_food + 2;
							kreska();
							goto litynia;
					}
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Bindar: Ten kaleka mo¿e ci zaraz\n";
					cout<<"|         wybiæ wszystkie zêby\n";
					cout<<"|\n| 1. Spokojnie, poka¿ mi t¹ rêkê\n";
					cout<<"| 2. Tak? To zobaczymy kto straci zêby\n";
					kreska();
					int odp5;
					cin>>odp5;
					switch (check(odp5,2)){
						case 1:
							goto bandaz;
						case 2:
							bindar_war:
							switch (walka(3)){
								case 1: 
									system("cls");
									pl_cash = pl_cash + 50;
									pl_food = pl_food + 2;
									stats();
									kreska();
									cout<<"|\n| Bindar: Zapamiêtam sobie twoj¹\n";
									cout<<"|         buŸkê cwaniaku...\n";
									cout<<"|\n| Ukradziono 50$\n";
									cout<<"| Otrzymano: 2 koszyki ostrê¿yn\n";
									kreska();
									goto litynia;
								case 2:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Bindar: Nigdy wiêcej tego\n";
									cout<<"|         nie próbuj.\n";
									kreska();
									goto litynia;
								case 3:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Bindar: Jeszcze cie dorwê!\n";
									kreska();
									goto litynia;	
							}
					}
			}		
			case 2:
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Bindar: Chcesz dostaæ w szczêkê?\n";
				cout<<"|\n| 1. Nie.. <pomó¿ opatrzyæ ranê>\n";
				cout<<"| 2. Poka¿ mi na co ciê staæ\n";
				kreska();
				int odp6;
				cin>>odp6;
				switch (check(odp6,2)){
					case 1:
						goto bandaz;
						break;
					case 2:
						goto bindar_war;
						break;
				}
	}		
	litynia:
	litynia();
					
}
void chapter2 (){
	system("cls");
	tytul();
	cout<<"\n|   ROZDZIA£ 2: GODZIBURG - W STRONÊ KRÓLA \n";
	kreska();
	cout<<"\n  ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Docierasz do Godziburga. Osada s³ynie\n";
	cout<<"| z wysokiej przestêpczoœci, poniewa¿\n";
	cout<<"| w wysokim tempie kwitnie tu przemys³\n";
	kreska();
	system("pause");
	do {
	system("cls");
	stats();
	kreska();	
	godziburg();
	} while (ch2 == 0);
}
void chapter3(){
	
	int helfen = 0; //zmienna okresla czy kubis³awa i lesniomir pomoga nam w serwenii
	int grota21 = 0; //okresla czy user byl juz w tej grocie
	int grota211 = 0; //okresla czy user byl juz w tej grocie
	int grota213 = 0; //okresla czy user byl juz w tej grocie
	int ruda211 = 0; //okresla czy wykopano rude w grocie 211
	int ruda213 = 0;//okresla czy wykopano rude w grocie 213
	
	system("cls");
	tytul();
	kreska();
	cout<<"\n|  ROZDZIA£ 3: DO MISTYCZNEJ KRAINY SERWENII  \n";
	kreska();
	system("pause");
	system("cls");
	stats();
	kreska();
	rozstaj:
	cout<<"|\n| 1. Bielogród\n";
	cout<<"| 2. Serwenia\n";
	cout<<"| 3. Zobacz mapê\n";
	kreska();
	int odp1;
	cin>>odp1;
	switch (check(odp1,3)){
		case 1:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| To zbyt niebezpieczne,\n";
			cout<<"| masz za s³aby sprzêt.\n";
			goto rozstaj;
		case 2:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Docierasz do wrót podziemnej\n";
			cout<<"| osady. Zatrzymuje ciê Leœniomir z Kubis³aw¹\n";
			cout<<"|\n| Leœniomir: O ch³opie ty siê dobrze czujesz?\n";
			cout<<"|\n| 1. Spokojnie, wiem co mnie czeka\n";
			cout<<"| 2. O czym ty do mnie govorisz?\n";
			kreska();
			int odp2;
			cin>>odp2;
			switch (check(odp2,2)){
				case 1:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Leœniomir: Nie wiesz! Za bram¹\n";
					cout<<"|            dzieje siê istne piek³o!\n";
					cout<<"|\n| 1. Rozjaœnisz?\n";
					cout<<"| 2. Nie interesuje mnie to, wchodzê\n";
					kreska();
					int odp3;
					cin>>odp3;
					switch (check(odp3,2)){
						case 1:
							kubislawa:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Kubis³awa: Stoimy na stra¿y tych wrót\n";
							cout<<"|            poniewa¿ od 2 tygodni nie\n";
							cout<<"|            wróci³a stamt¹d pewna mieszczanka \n";
							cout<<"|            wiêc nie mo¿emy pozwoliæ ¿eby\n";
							cout<<"|            ludzie ginêli w niewyjaœnionych\n";
							cout<<"|            okolicznoœciach.\n";
							cout<<"|\n| 1. Co mog³o j¹ zabiæ?\n";
							cout<<"| 2. Nic sie nie bój to jest przebój\n";
							kreska();
							int odp4;
							cin>>odp4;
							switch (check(odp4,2)){
								case 1:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Leœniomir: Wedle podañ, Serwenia\n";
									cout<<"|            opanowana jest przez stworzenia\n";
									cout<<"|            które skrêcaj¹ sobie cia³a z \n";
									cout<<"|            miedzi która roœnie w tutejszych\n";
									cout<<"|            jaskiniach. To bardzo wymagaj¹cy\n";
									cout<<"|            wrogowie, nie ka¿dy da se z nimi radê\n";
									cout<<"|\n| 1. Pomoglibyœcie mi?\n";
									cout<<"| 2. Wystarczy, wchodzê\n";
									kreska();
									int odp5;
									cin>>odp5;
									switch (check(odp5,2)){
										case 1:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Oboje spojrzeli na siebie i kiwnêli\n";
											cout<<"|\n| Kubis³awa: Wiêc chodŸmy!\n";
											kreska();
											cout<<"\n  ";
											helfen = 1;
											goto serwenia;
										case 2:
											samozwaniec:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Leœniomir: ¯yczê mi³ej œmierci!\n";
											kreska();
											cout<<"\n  ";
											goto serwenia;
									}
								case 2:
									goto samozwaniec;
							}
						case 2:
							goto samozwaniec;
					}
				case 2:	
					goto kubislawa;
			}
		case 3:
			if (pl_map == 0){
				system("cls");
				stats();
				kreska();
				cout<<"| Nie masz mapy!\n";
				goto rozstaj;
			} else {
				system("cls");
				stats();
				mapa();
				goto rozstaj;
			}
	}
	serwenia:
	system("pause");
	system("cls");
	cout<<"\n   ";
	Sleep(700);
	cout<<"c ";
	Sleep(700);
	cout<<"i ";
	Sleep(700);
	cout<<"s ";
	Sleep(700);
	cout<<"z ";
	Sleep(700);
	cout<<"a ";
	Sleep(700);
	cout<<". ";
	Sleep(700);
	cout<<". ";
	Sleep(700);
	cout<<". ";
	Sleep(2000);
	system("cls");
	cout<<"\n  Serwenia to niesamowite miejsce, pe³ne\n";
	cout<<"  grot, ciszy oraz";
	Sleep(2000);
	cout<<"...";
	Sleep(2000);
	cout<<" miedzi";
	Sleep(2000);
	cout<<"...";
	Sleep(2000);
	system("cls");
	stats();
	kreska();
	if (helfen == 1){
	   	cout<<"|\n| Trafiacie na rozstaj\n";
	   	cout<<"|\n| Kubis³awa: My przeszukamy grotê 21,\n|          wygl¹da podejrzanie\n";
	} else {
		cout<<"|\n| Trafiasz na rozstaj\n";
	}	
	rozjazd:
	cout<<"|\n| 1. W stronê groty 211\n";
	cout<<"| 2. W stronê groty 21\n";
	cout<<"| 3. W stronê groty 213\n";
	cout<<"| 4. WyjdŸ\n";
	kreska();
	int serw1;
	cin>>serw1;
	switch (check(serw1,4)){
		case 1:
			if (ruda211 == 1){
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Ju¿ przeszuka³eœ ten rejon!";
				goto rozjazd;
			}
			if (grota211 == 1){
				goto grot211;
			}
			grota211 = 1;
			system("cls");
			Sleep(2000);
			cout<<"\n  powoli idziesz w kierunku groty 211\n";
			Sleep(4000);
			system("cls");
			Sleep(1200);
			cout<<"\n  A N I";
			Sleep(700);
			cout<<"   K R O K U";
			Sleep(700);
			cout<<"   D A L E J\n\n";
			Sleep(1200);
			cout<<" 1. ...\n";
			cin>>serw1;
			system("cls");
			Sleep(1000);
			cout<<"tup.";
			Sleep(1000);
			system("cls");
			Sleep(1000);
			cout<<"tup.";
			Sleep(1000);
			system("cls");
			Sleep(1000);
			cout<<"tup.";
			Sleep(1000);
			system("cls");
			cout<<"\n oj arturze... czegó¿ mo¿esz szkuaæ w takim miejscu?\n";
			Sleep(4000);
			cout<<"\n  z mroku wyjawia siê ludzka sylwetka\n";
			Sleep(2000);
			cout<<"\n chyba nie s¹dzi³eœ ¿e pójdzie tak ³atwo?\n";
			Sleep(2000);
			cout<<"\n  zaczynasz rozpoznawaæ jego rysy twarzy, to cz³owiek\n";
			Sleep(2000);
			cout<<"\n 1. Gadzimyœle...\n";
			cin>>serw1;
			system("cls");
			cout<<"\n Gadzimys³: Pamiêæ jeszcze pracuje, jaka szkoda\n";
			cout<<"            ¿e na niewiele ci siê ju¿ zda\n\n";
			cout<<" 1. <zainicjuj gardê>\n";
			cin>>serw1;
			switch (walka(6)){
				case 1:
					system("cls");
					cout<<" Gadzimys³: Ogl¹daj siê za plecy...\n";
					Sleep(4000);
					system("cls");
					stats();
					kreska();
					goto grot211;
				case 2:
					if (helfen == 1){
						system("cls");
						cout<<"\n  Na miejsce przybieg³ Leœniomir\n";
						cout<<"  i dobi³ Gadzimys³a\n";
						cout<<"\n Leœniomir: Cz³owieku uwa¿aj bardziej!\n";	
						system("pause");
						goto grot211;
					} else {
						lachudra:
						system("cls");
						cout<<"\n Gadzimys³: i ty chcesz pokonaæ Wojmira?\n";
						cout<<"            haha! ty ³achudro!\n";
						cout<<"\n  1. <zaufaj mi>\n";
						cin>>serw1;
						system("cls");
						Sleep(1000);
						cout<<"\n  cofasz siê ";
						Sleep(700);
						cout<<"i bierzesz rozpêd ";
						Sleep(2000);
						system("cls");
						cout<<" ~AAAA!";
						Sleep(1000);
						cout<<"\n\n oboje upadacie";
						Sleep(1000);
						cout<<", zauwa¿asz ka³u¿ê krwi";
						Sleep(2000);
						cout<<"\n\n Gadzimys³: ty....";
						Sleep(2000);
						cout<<"\n\n umar³.";
						Sleep(2000);
						system("cls");
						cout<<"\n Podnosisz siê i zmierzasz ku grocie 211";
						Sleep(3000);
						system("cls");
						switch (walka(7)){
							case 1:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Docierasz do groty 211, po\n";
								cout<<"| lewej stronie œwieci siê ruda,\n";
								cout<<"| na wprost zaœ stoi biurko\n";
								grot211:
								cout<<"|\n| 1. IdŸ po rudê\n";
								cout<<"| 2. IdŸ do biurka\n";
								cout<<"| 3. Wracaj na rozstaj\n";
								kreska();
								int serw2;
								cin>>serw2;
								switch (check(serw2,3)){
									case 1:
										if (ruda211 == 1){
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Ju¿ wykopa³eœ t¹ rudê!\n";
											goto grot211;
										}
										system("cls");
										stats();
										kreska();
										ruda211 = 1;
										cout<<"|\n| Uda³o ci siê wykopaæ rudê\n";
										goto grot211;
									case 2:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Przy biurku siedz¹ Wronis³aw i Biergar\n";
										cout<<"| Graj¹ w szachy\n";
										cout<<"|\n| 1. Tam ch³op mnie prawie rozwa³kowa³\n";
										cout<<"|    a wy se w szachy gracie?\n";
										cout<<"| 2. Mogê siê do³¹czyæ?\n";
										kreska();
										int serw4;
										cin>>serw4;
										switch(check(serw4,2)){
											case 1:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Wronis³aw uœmiech¹³ sie i powiedzia³:\n";
												cout<<"|\n| Jak nasz wybawca móg³by zgin¹æ w drodze tutaj\n";
												cout<<"| Arturze, jesteœmy wiêŸniami tej krainy.\n";
												cout<<"| Nigdy jej nie opuœcimy dlatego proszê,\n";
												cout<<"| Zrób wszystko ¿eby uwolniæ Bielsaniê\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto grot211;
											case 2:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Biergar: Nie, nie dlatego ¿e jesteœ s³aby\n";
												cout<<"|          ale twoim zadaniem jest nas ocaliæ.\n";
												cout<<"|          A teraz idŸ i ocal krainê!\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto grot211;
										}
										case 3:
											goto rozjazd;
								}
							case 2:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Potwór przewróci³ sie i umar³\n";
								goto grot211;
							case 3:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Potwór wystraszy³ siê ciebie gdy\n";
								cout<<"| ucieka³eœ i sam uciek³\n";
								goto grot211;
						}
					}
					break;
				case 3:
					goto lachudra;
			}
		case 2:;
			if (helfen == 1){
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Kubis³awa: My tam idziemy, nie \n|            musisz nam pomagaæ!\n";
				goto rozjazd;
			} else {
				system("cls");
				cout<<"\n Grota wydaje siê pusta. Zawracasz...\n\n  ";
				system("pause");
				switch (walka(7)){
					case 1:
						system("cls");
						stats();
						kreska();
						goto rozjazd;
					case 2:
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Da³eœ siê pobiæ potworowi...\n";
						goto rozjazd;
					case 3:
						system("cls");
						stats();
						kreska();
						goto rozjazd;
				}
			}
		case 3:
			if (ruda213 == 1){
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Ju¿ przeszuka³eœ ten rejon!";
				goto rozjazd;
			}
			grota213 = 1;
			system("cls");
			Sleep(2000);
			cout<<"\n  <kaszel>";
			Sleep(1000);
			system("cls");
			cout<<"\n  c-cz³owiek..?";
			Sleep(1000);
			system("cls");
			cout<<"\n  naprawdê ktoœ mnie znalaz³?";
			Sleep(2000);
			cout<<"\n\n jakaœ kobieta le¿y pod grot¹";
			Sleep(2000);
			cout<<"\n\n obok niej le¿y miecz i zwój";
			Sleep(3000);
			system("cls");
			Sleep(1000);
			cout<<"\n to Œmigienia.";
			Sleep(2000);
			cout<<"\n podbiegasz do niej\n";
			cout<<"\n 1. co ci siê sta³o?\n";
			cin>>serw1;
			system("cls");
			cout<<"\n Œmigienia: planowa³am powstrzymaæ Wojmira\n";
			cout<<"            przed objêciem tronu, dlatego wyruszy³am\n";
			cout<<"            w stronê groty 213 poniewa¿ jest tam";
			Sleep(6000);
			cout<<".";
			Sleep(1000);
			cout<<".";
			Sleep(1000);
			cout<<".";
			Sleep(1000);
			system("cls");
			cout<<"\n ...";
			Sleep(3000);
			cout<<"\n Œmigienia osunê³¹ siê na ziemiê.\n";
			Sleep(3000);
			cout<<"\n 1. Podnieœ zwój\n";
			cin>>serw1;
			system("cls");
			kreska();
			cout<<"\n        LEGENDA O SKRÊTKOWYM KSIÊCIU\n\n";
			cout<<"\n| Dawno dawno temu ¿y³ sobie w Bielsanii\n";
			cout<<"| Skrêtkowy Ksi¹¿e który kocha³ swoich ludzi\n";
			cout<<"| a oni kochali jego. Lecz pewnego dnia\n";
			cout<<"| Margniew bardzo siê zdenerwowa³ na to,\n";
			cout<<"| jak wszystko dzia³a w idealnej harmonii.\n";
			cout<<"| Postanowi³ on podstêpem zabiæ ksiêcia tak,\n";
			cout<<"| aby to on zosta³ w³adc¹, i ¿eby móg³\n";
			cout<<"| wprowadziæ chaos w ca³ej krainie. Ale\n";
			cout<<"| Skrêtkowy Ksi¹¿e obawia³ siê, ¿e pewnego\n";
			cout<<"| dnia, ktoœ zbuntuje siê przeciwko ³adowi,\n";
			cout<<"| dlatego uprosi³ najlepszego maga w ca³ej\n";
			cout<<"| krainie, niejakiego Parchewita, by ten\n";
			cout<<"| zostawi³ czêœæ swej mocy dla cz³owieka\n";
			cout<<"| który bêdzie chcia³ uratowaæ krainê przed\n";
			cout<<"| z³em, które kiedyœ nadejdzie. Tak oto\n";
			cout<<"| powsta³a miedziana ruda, któr¹ postanowlil\n";
			cout<<"| ulokowaæ w jaskini, w której wszystko \n";
			cout<<"| wygl¹da jak miedziana ruda. Jedynie \n";
			cout<<"| wyzwoliciel, osoba,która ma serce czyste,\n";
			cout<<"| i wiedzê ca³ego œwiata jest w stanie \n";
			cout<<"| prawdziwie znaleŸæ magiczn¹ rudê. Ten kto\n";
			cout<<"| posiadnie obie rudy i przekuje je na miecz\n";
			cout<<"| i zbrojê, mo¿e powstrzymaæ z³o na wieki.\n";
			kreska();
			cout<<"\n ";
			system("pause");
			system("cls");
			cout<<"\n Wêdrujesz dalej wg³¹b jaskini\n";
			Sleep(3000);
			system("cls");
			switch (walka(7)){
				case 1:
					system("cls");
					stats();
					kreska();
					grot213:
					cout<<"|\n| Docierasz do Groty 213. Na wprost\n";
					cout<<"| widzisz œwiec¹c¹ siê rudê miedzi\n";
					cout<<"| 1. Wykop j¹\n";
					kreska();
					int serw3;
					cin>>serw3;
					system("cls");
					stats();
					kreska();
					ruda213 = 1;
					cout<<"|\n| Zdobywasz: Magiczna ruda miedzi\n";
					kreska();
					system("pause");
					system("cls");
					stats();
					kreska();
					goto rozjazd;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Potwór przewróci³ siê i umar³\n";
					goto grot213;
				case 3:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Potwór przestraszy³ sie uciekaj¹cego\n";
					cout<<"| ciebie i sam uciek³\n";
					goto grot213;
			}
		case 4:
			if (ruda211 == 0 || ruda213 == 0){
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Nie mo¿esz opuœciæ Serwenii dopóki nie\n";
				cout<<"| zdobêdziesz dwóch rud miedzi\n";
				goto rozjazd;
			}	
	}
}
void chapter4() {
	system("cls");
	tytul();
	kreska();
	cout<<"|\n|             ROZDZIA£ 4: FINA£\n";
	kreska();
	cout<<"\n ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Przy wyjœciu z Serwenii spotykasz \n| Kubis³awê i Leœniomira\n";
	cout<<"|\n| Kubis³awa: Ca³kiem nieŸle ci posz³o! Teraz\n";
	cout<<"| bierz te rudy i leæmy do kowala w Godziburgu!\n";
	kreska();
	cout<<"\n ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Kubis³awa wraz z Leœniomirem przetransportowali\n";
	cout<<"| ciê do Godziburga, prosto do kowala\n";
	cout<<"|\n| Stefir: Niesamowite! Zdoby³eœ a¿ dwie??\n";
	cout<<"|\n| 1. Znalaz³em te¿ Gadzimys³a i Œmigieniê...\n";
	cout<<"| 2. Dobra nie gadaj tylko rób ten miecz i zbrojê\n";
	kreska();
	int odp1;
	cin>>odp1;
	switch (check(odp1,2)){
		case 1:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Stefir: Gadzimys³ zosta³ porwany\n";
			cout<<"|         i przeszkolony do bycia po stronie\n";
			cout<<"|         króla. Szkoda ¿e tak skoñczy³, ale\n";
			cout<<"|         co ze Œmigieni¹?\n";
			cout<<"|\n| 1. Nie ¿yje...\n";
			cout<<"| 2. Zosta³a uwiêziona\n";
			kreska();
			int odp4;
			cin>>odp4;
			switch(check(odp4,2)){
				case 1:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Niech Innos ma j¹ w swojej opiece...\n";
					kreska();
					Sleep(4000);
					goto robienie_miecza;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Obawiam siê ¿e jej ju¿ nie uratujemy...\n";
					kreska();
					Sleep(4000);
					goto robienie_miecza;
			}
		case 2:	
			robienie_miecza:
			system("cls");
			pl_dmg = pl_dmg + 100;
			pl_kev = 5;
			pl_kev_health = 500;
			stats();
			kreska();
			cout<<"|\n| Kopbard: Daj mi t¹ miedŸ.\n";
			cout<<"|\n| Po sali roznosi³ siê zapach\n";
			cout<<"| gor¹cego metalu i spalonych przewodów\n";
			cout<<"|\n| Kopbard: Uda³o siê!\n";
			cout<<"|\n| Otrzymujesz: Miedziany Rozpo³awiacz\n";
			cout<<"| Otrzymujesz: Miedziana zbroja skrêtkowca\n";
			cout<<"|\n| 1. Dziêkujê! <wyjdŸ>\n";
			cout<<"| 2. Ciekawe czy teraz móg³bym obrabowaæ wioskê\n";
			kreska();
			int odp2;
			cin>>odp2;
			switch (check(odp2,2)){
				case 1:
					system("cls");
					stats();
					kreska();
					eksit:
					cout<<"|\n| Wychodz¹c za ramiê chwyta ciê Kubis³awa\n";
					cout<<"|\n| Kubis³awa: Nie pójdziesz sam.\n";
					cout<<"|\n| Przed kowalem stanêli: Stebenia, Spordan\n";
					cout<<"| Michniard, Zaj¹s³aw, Bindar i ks. Stanomir\n";
					cout<<"|\n| Kubis³awa: Zrobimy to razem\n";
					cout<<"| 1. Wiêc zróbmy dym w Bielogrodzie!\n";
					kreska();
					int odp3;
					cin>>odp3;
					goto bielogrod;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Stefir: Tylko spróbuj a znikniesz na zawsze\n";
					goto eksit;
			}
	}
	bielogrod:
		system("cls");
		tytul();
		kreska();
		cout<<"\n|           DYM W BIELOGRODZIE\n";
		kreska();
		cout<<"\n ";
		system("pause");
		system("cls");
		stats();
		kreska();
		cout<<"|\n| Docieraj¹c do Bielogrodu musicie\n| powstrzymaæ stra¿ników.\n";
		cout<<"|\n| Spordan wyj¹³ ³uk i odstrzeli³ ich obu.\n";
		cout<<"|\n| Spordan: Ruszcie siê, ja obstawiê ty³y.\n";
		kreska();
		cout<<"\n ";
		system("pause");
		system("cls");
		stats();
		kreska();
		cout<<"|\n| W Bielogrodzie rozpêta³y siê zamieszki, wszyscy\n";
		cout<<"| poczuli wolê walki i postanowili obaliæ króla. Ten\n";
		cout<<"| jednak nie dawa³ za wygran¹ i wysy³a³ coraz ciê¿sze\n";
		cout<<"| jazdy na buntuj¹cych siê mieszkañców\n";
		cout<<"|\n| Michniard: Zorganizujê ludzi i otoczymy zamek\n";
		kreska();
		cout<<"\n ";
		system("pause");
		system("cls");
		cout<<"\n S£UCHAJCIE S£UCHAJCIE MIESZKAÑCY BIELOGRODU\n";
		cout<<" NA ROZKAZ WIELMO¯NEGO KRÓLA WOJMIRA OG£ASZA SIÊ\n";
		cout<<" STAN WOJENNY NA TERENIE CA£EJ KRAINY\n";
		cout<<"\n Bindar: To dzia³a! Boj¹ siê nas! Szybko, musimy\n";
		cout<<" wykorzystaæ ich s³aboœæ!\n\n ";
		system("pause");
		system("cls");
		stats();
		kreska();
		cout<<"|\n| Docieracie do zamku Wojmira. Konstrukcja\n";
		cout<<"| solidna, nie do rozwalenia byle armat¹\n";
		cout<<"|\n| 1. Zaatakuj g³owne wejœcie\n";
		cout<<"| 2. WejdŸ od kuchni\n";
		cout<<"| 3. IdŸ od piwnic\n";
		kreska();
		int odp5;
		cin>>odp5;
		switch (check(odp5,3)){
			case 1:
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Zaj¹s³aw: nie, to zbyt ryzykowne!\n";
				cout<<"|           Tam zastawiona jest ca³a gwardia.\n";
				cout<<"|           ChodŸmy kuchni¹\n";
				kreska();
				system("pause");
				goto kuchnia;
			case 2:
				kuchnia:
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Wchodzicie kuchni¹. W niej jest 20 kucharzy\n";
				cout<<"| i ka¿dy z nich ma tasak\n";
				cout<<"|\n| Bindar: Zostawcie to mi!\n";
				kreska();
				cout<<"\n ";
				system("pause");
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Trafiacie na g³owny korytarz.\n";
				cout<<"| jeszcze jest pusty.\n\n";
				cout<<"| Stebenia: Na górê! Tam napewno jest Wojmir!\n";
				cout<<"|           Ja zostanê tutaj na czatach\n";
				kreska();
				cout<<"\n ";
				system("pause");
				system("cls");
				cout<<"\n docierasz na górê\n";
				Sleep(2000);
				cout<<"\n tabliczka: DR. GRONY, NIE WCHODZIÆ\n";
				Sleep(2000);
				cout<<"\n 1. wejdŸ.";
				Sleep(2000);
				cin>>odp5;
				system("cls");
				cout<<"\n Proszê proszê... Artur! Œmiesz tak\n";
				cout<<" po prostu wchodziæ mi do zamku i mnie\n";
				cout<<" pokonywaæ?\n\n";
				cout<<" 1. Dawaj dawaj nie udawaj\n";
				cin>>odp5;
				system("cls");
				cout<<"\n  Ludzie nie rozumiej¹ wiedzy... Te ksiêgi i\n";
				cout<<"  zwoje to wieczna m¹droœæ\n";
				cout<<"\n 1. Skoñcz ju¿ gadaæ i wyci¹gaj broñ\n";
				cin>>odp5;
				system("cls");
				cout<<"\n Wojmir: Zmów pacierz!\n";
				Sleep(5000);
				switch (walka(8)){
					case 1:
						system("cls");
						cout<<"\n NIE! MOJA BIELSANIA! TY MENDO!!!\n";
						cout<<"\n 1. Zdejmuj t¹ plandekê i ulotnij\n";
						cout<<"   siê. Skubana rasa...\n";
						cin>>odp5;
						system("cls");
						koncowka:
						cout<<"\n <Wojmir zostaje uwiêziony i sprowadzony\n";
						cout<<"  do serwenii na wieczne wiêzienie>\n";
						Sleep(4000);
						system("cls");
						cout<<"\n Wróci³eœ do reszty. Nie ma siê czego baæ.\n";
						cout<<" Bielsania jest znów wolna. Królem zostaje \n";
						cout<<" Artur I, Œwiat³y Wódz\n";
						kreska();
						cout<<"\n ";
						system("pause");
						goto koniec;
					case 2:	
						system("cls");
						cout<<"\n Wojmir: Ty parchu! Nie umiesz nawet";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<"\n\n Wojmir opad³ na ziemiê.\n";
						Sleep(1000);
						cout<<" Spordan: Widzia³em ¿e potrzebujesz pomocy.\n";
						cout<<"          Nigdy nie w¹tp w potêgê Sparty m³ody\n";
						goto koncowka;
					case 3:
						system("cls");
						cout<<"\n Wojmir: Ty parchu! Nie umiesz nawet";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<"\n\n Wojmir opad³ na ziemiê.\n";
						Sleep(1000);
						cout<<" Spordan: Widzia³em ¿e potrzebujesz pomocy.\n";
						cout<<"          Nigdy nie w¹tp w potêgê Sparty m³ody\n";
						goto koncowka;
				}
			case 3:
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Zaj¹s³aw: nie, to zbyt ryzykowne!\n";
				cout<<"|           Tam zastawiona jest ca³a gwardia.\n";
				cout<<"|           ChodŸmy kuchni¹\n";
				kreska();
				system("pause");
				goto kuchnia;
		}	
	koniec:;
}
void menu(){			//menu gry
	string detale="Wysokie";
	wuwu:
	system("cls");
	tytul();
	cout<<"\n| 1. Zacznij gre \n";
	cout<<"| 2. Ustawienia \n";
	cout<<"| 3. Informacje o grze \n";
	cout<<"| 4. Wyjscie \n";
	kreska();
	int men_chc;
	cin>>men_chc;
	switch (check(men_chc,4)){
		case 1:	
			system("cls");
			goto starting;
        case 2:
        	settings:
        	system("cls");
        	tytul();
        	kreska();
        	cout<<"\n| 1. Grafika: "<<detale<<"\n"; //to nic nie zmienia
        	cout<<"| 2. HUD: "<<HUD<<" \n";
        	cout<<"| 3. exit \n";
        	kreska();
        	int graf;
			cin>>graf;
			switch (check(graf,3)){
				case 1:
					if (detale == "Wysokie"){
						detale = "Niskie";
						goto settings;
					} else {
						detale = "Wysokie";
						goto settings;
					}
				case 2:
					if (HUD == "ON"){
						HUD = "OFF";
					}	else {
						HUD = "ON";
					}
					goto settings;
                case 3:
					goto wuwu;
			}
  	    case 3:
  	    	system("cls");
  	    	tytul();
  	    	kreska();
  	    	cout<<"\n";
  	    	cout<<"| Bielsania Adventure to gra RPG. Nazywasz sie\n";
			cout<<"| Artur i trafiasz do wioski Czechigród w \n";
			cout<<"| której spotykasz Stebeniê, ktora wprowadzi\n";
  	    	cout<<"| ciê do gry. Nastêpnie udasz siê do Litynii \n";
  	    	cout<<"| w celu przygotowania do walki a na koñcu \n";
  	    	cout<<"| stoczysz walkê z Wojmirem. Wszystko le¿y \n";
  	    	cout<<"| w twoich rêkach! \n";
  	    	kreska();
  	    	cout<<"\n  ";
  	    	system("pause");
  	    	goto wuwu;
    	case 4:
    		wyjdz = 1;
    		goto starting;
	}
	starting:;
}
int main() {			//main
	setlocale(LC_CTYPE, "Polish");
	disclaimer();
	menu();
	start_game:
	if (wyjdz != 1){
    start();
	} else {
		goto end;
	}
    while (ending != 0){
        kreska();
        cout<<"|\n| Gra zakoñczona! \n|\n";
        switch (ending){
            case 1:
                cout<<"| Pieni¹dze ending \n";
                kreska();
                ending = 0;
                goto end;
            case 2:
                cout<<"| Olanie Stebenii ending \n";
                kreska();
                ending = 0;
                goto end;
            case 3:
                cout<<"| Good ending\n";
                kreska();
                ending = 0;
                goto end;
            case 4:
                cout<<"| Unranked ending \n";
                kreska();
                ending = 0;
                goto end;
        }
    }
    chapter1();
    chapter2();
    chapter3();
    chapter4();
    system("cls");
    cout<<"\n Good ending, Bielsania jest znowu wolna.";
	Sleep(5000);
	cout<<"\n Dziêkujê za zagranie. Liczê ¿e bawiliœcie\n";
	cout<<" siê dobrze.\n                    ~Janusz";
    Sleep(10000);
	end: 
    	cout<<"\n Wychodzenie z gry.\n";
        Sleep(2000);
    return 0;
}