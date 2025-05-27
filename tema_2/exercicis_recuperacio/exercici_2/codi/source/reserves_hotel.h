#ifndef RESERVES_HOTEL_H
#define RESERVES_HOTEL_H

#include "reserva.h"

class ReservesHotel
{
public:
	ReservesHotel();
	ReservesHotel(const string& nom, float preu, int nHabitacions, int nMaxReserves);
	ReservesHotel(const ReservesHotel &reserves);
	~ReservesHotel() { delete[] m_reserves; }

	ReservesHotel &operator=(const ReservesHotel& reserves);
	void llegeixReserves(const string &nomFitxer);
	int nReservesDia(const Data& dia);
	bool afegeixReserva(const string &nomClient, const Data &entrada, int nDies, int nHabitacions);
	bool consultaReserva(const string &nomClient, const Data &entrada, Data &sortida, int &nHabitacions, float &preu);
private:
	string m_nom;
	float m_preuDia;
	int m_nHabitacions;
	Reserva *m_reserves;
	int m_nReserves;
	int m_maxReserves;
};

#endif 
