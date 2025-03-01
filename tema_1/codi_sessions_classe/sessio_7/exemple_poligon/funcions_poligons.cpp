#include "Poligon.h"

bool interiorRectangle(Punt& pt, Punt& supEsq, Punt& infDreta)
{
	return ((pt.getX() >= supEsq.getX()) && (pt.getX() <= infDreta.getX()) &&
		(pt.getY() >= supEsq.getY()) && (pt.getY() <= infDreta.getY()));
}

bool interseccioPoligons(const Poligon& p1, const Poligon& p2)
{
	Punt supEsq1, infDreta1, supEsq2, infDreta2;
	bool interseccio = false;

	supEsq1 = p1.getTopLeft();
	infDreta1 = p1.getBottomRight();
	supEsq2 = p2.getTopLeft();
	infDreta2 = p2.getBottomRight();

	Punt supDreta1, infEsq1;
	supDreta1.setX(infDreta1.getX());
	supDreta1.setY(supEsq1.getX());
	infEsq1.setX(supEsq1.getX());
	infEsq1.setY(infDreta1.getY());

	interseccio = interiorRectangle(supEsq1, supEsq2, infDreta2);
	interseccio = interseccio || interiorRectangle(supDreta1, supEsq2, infDreta2);
	interseccio = interseccio || interiorRectangle(infEsq1, supEsq2, infDreta2);
	interseccio = interseccio || interiorRectangle(infDreta1, supEsq2, infDreta2);

	return interseccio;
}