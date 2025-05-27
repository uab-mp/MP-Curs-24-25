#include "jugador.h"

void Jugador::afegeixCarta(const Carta& carta)
{

	// afegeix una carta al conjunt de cartes del jugador

}



bool Jugador::tiraCarta(const Carta& cartaTirada, Carta& cartaATirar)
{

	// Aquest mètode ha de seleccionar una de les cartes de les que té el jugador per poder tirar en el seu torn.
	// En el paràmetre cartaTirada  rep la carta que ha tirat el jugador anterior i que està a dalt de tot 
	// de les cartes jugades.
	// Si té alguna carta que es pugui tirar segons les regles del joc, 
	// la retornarà al paràmetre per referència cartaATirar i retornarà true com a resultat de la funció.
	// Si no té cap carta per tirar retornarà false.
	// En qualsevol dels dos casos s’ha d’actualitzar l’atribut que indica si el jugador ha pogut tirar o no en el seu torn.
	// Si el jugador té més d’una carta que es pot tirar, la carta a tirar es seleccionarà seguint aquest ordre de prioritat:
		// Carta especial de robar 2 del color de l’última carta tirada.
		// Carta especial de canvi de torn del color de l’última carta tirada.
		// Carta especial de saltar torn del color de l’última carta tirada.
		// Una carta normal del mateix color de l’última carta tirada.Si en tenim més d’una, 
		// tirarem la que tingui el valor més petit.
		// Una carta normal del mateix valor de l’última carta tirada, però de diferent color.
		// Si en tenim més d’una tirarem la que tingui el codi de color més petit segons les 
		// constants de color declarades al fitxer “Carta.h”.



}