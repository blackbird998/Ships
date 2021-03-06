#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Plansza.h"

class Statek : public sf::Drawable {
	private:
		short punktyZycia=3;
		short dlugoscStatku = 3;
		Kierunek kierunek = polnoc;
		Punkt pozycjaRufy = {};
		Plansza* _planszaGraczaLudzkiego = nullptr;

		sf::RectangleShape rufa;
		sf::RectangleShape kadlub[3];
		sf::RectangleShape dziob;

		//Metoda rysujaca elementy statku
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			target.draw(rufa);
			for (int i = 0; i < dlugoscStatku-2; ++i) {
				if (kierunek != wschod && kierunek != poludnie) target.draw(kadlub[i]);
				else if (kierunek == 1 && pozycjaRufy.x + i + 1 <= 9) target.draw(kadlub[i]);
				else if (kierunek == 2 && int(pozycjaRufy.y) - 'A' + i + 1 <= 9) target.draw(kadlub[i]);
			}
			if (kierunek != wschod && kierunek != poludnie) target.draw(dziob);
			else if (kierunek == 1 && pozycjaRufy.x + dlugoscStatku - 1 <= 9) target.draw(dziob);
			else if (kierunek == 2 && int(pozycjaRufy.y) - 'A' + dlugoscStatku - 1 <= 9) target.draw(dziob);
		}

	public:
//KONSTRUKTORY============================================================================

		Statek() : dlugoscStatku(3) {}
		
		//ustawia parametry graficzne statku
		Statek(short dlugosc, Plansza* planszaGraczaLudzkiego) : dlugoscStatku(dlugosc), punktyZycia(dlugosc), kierunek(Kierunek::polnoc), _planszaGraczaLudzkiego(planszaGraczaLudzkiego) {			
			rufa.setSize({ 80, 80 });
			rufa.setFillColor(sf::Color::White);

			for (int i = 2; i < dlugoscStatku; ++i) {
				sf::RectangleShape nowyKadlub;
				nowyKadlub.setSize({ 80, 80 });
				nowyKadlub.setFillColor(sf::Color::White);
				kadlub[i - 2] = nowyKadlub;
			}

			dziob.setSize({ 80, 80 });
			dziob.setFillColor(sf::Color::White);

			setPozycjaRufy({ 4, 'E'}, 0);
		}
//SETERY==================================================================================

		//ustawia pozycje rufy na planszy
		void setPozycjaRufy(Punkt pozycja, bool gracz) {
			pozycjaRufy = pozycja;
			if (gracz == 0) renderStatku(dlugoscStatku, kierunek);
		}

		//ustawia kierunek statku
		void setKierunek(Kierunek podanyKierunek, bool gracz) {
			kierunek = podanyKierunek;			
			if (gracz == 0) if (_planszaGraczaLudzkiego->sprawdzCzyWolne(dlugoscStatku, pozycjaRufy, kierunek, 0)) renderStatku(dlugoscStatku, kierunek);
		}


//GETERY=================================================================================

		//pobiera dlugosc statku
		int getDlugoscStatku() const {
			return dlugoscStatku;
		}

		//pobiera kierunek statku
		Kierunek getKierunek() const {
			return kierunek;
		}

		//pobiera pozycje statku
		Punkt getPozycja() const {
			return pozycjaRufy;
		}

//METODY==================================================================================

		//przelicza pozycje statku na px pod render
		void renderStatku(short dlugoscStatku, Kierunek kierunek) {
			short i;
			if (kierunek == polnoc) {
				rufa.setPosition({ float(pozycjaRufy.x * 80), float(((int)pozycjaRufy.y - 'A') * 80) });
				for (i = 0; i < dlugoscStatku; ++i) {
					kadlub[i].setPosition({ float((pozycjaRufy.x) * 80),float((int)(pozycjaRufy.y - 'A') * 80 - (i+1) * 80) });					
				}
				dziob.setPosition({ float((pozycjaRufy.x) * 80), float((int)(pozycjaRufy.y - 'A')*80 - (dlugoscStatku-1) * 80) });
			}
			else if (kierunek == wschod) {
				rufa.setPosition({ float(pozycjaRufy.x * 80),float(((int)pozycjaRufy.y - 'A') * 80 )});
				for (i = 0; i < dlugoscStatku; ++i) {
					kadlub[i].setPosition({ float((pozycjaRufy.x) * 80 + (i+1) * 80),float(((int)pozycjaRufy.y - 'A') * 80) });
				}
				dziob.setPosition({ (float)((pozycjaRufy.x) * 80 + (dlugoscStatku - 1) * 80),float(((int)pozycjaRufy.y - 'A') * 80) });
			}
			else if (kierunek == poludnie) {
				rufa.setPosition({ float(pozycjaRufy.x * 80),float(((int)pozycjaRufy.y - 'A') * 80) });
				for (i = 0; i < dlugoscStatku; ++i) {
					kadlub[i].setPosition({ (float)((pozycjaRufy.x) * 80),float(((int)pozycjaRufy.y - 'A') * 80 + (i + 1) * 80) });
				}
				dziob.setPosition({ float((pozycjaRufy.x) * 80),float(((int)pozycjaRufy.y - 'A') * 80 + (dlugoscStatku - 1) * 80) });
			}
			else {//zachod
				rufa.setPosition({ float(pozycjaRufy.x * 80),float(((int)pozycjaRufy.y - 'A') * 80) });
				for (i = 0; i < dlugoscStatku; ++i) {
					kadlub[i].setPosition({ float((pozycjaRufy.x) * 80 - (i + 1) * 80),float(((int)pozycjaRufy.y - 'A') * 80) });
				}
				dziob.setPosition({ float((pozycjaRufy.x) * 80 - (dlugoscStatku - 1) * 80),float(((int)pozycjaRufy.y - 'A') * 80) });
			}
		}

		//dekrementuje HP
		void trafienie() {
			punktyZycia--;
		}

};