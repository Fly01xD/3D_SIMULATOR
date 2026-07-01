#include <iostream>
#include "cline.h"
#include <string>
#include <cmath>

std::string relationToString(CLine::relation rel) {
    switch (rel) {
    case CLine::parallel:     return "Rownolegle (parallel)";
    case CLine::skew:         return "Skosne (skew)";
    case CLine::identical:    return "Tozsame (identical)";
    case CLine::intersecting: return "Przecinajace sie (intersecting)";
    case CLine::unknown:      return "Nieznana (unknown)";
    }
    return "Nieznana";
}

// Automatyczny bocznik testowy
void runTest(int testNum, const std::string& description, CLine* l1, CLine* l2, CLine::relation expected) {
    std::cout << "[TEST " << testNum << "] " << description << "\n";

    // Wywołanie Twojej metody obliczeniowej
    CLine* result = l1->calculatePoint(l2);

    CLine::relation actual = l1->getRelation();

    std::cout << "  Oczekiwano: " << relationToString(expected) << "\n";
    std::cout << "  Otrzymano:  " << relationToString(actual) << "\n";

    if (actual == expected) {
        std::cout << "  WYNIK: PASSED (Sukces)\n";
    } else {
        std::cout << "  WYNIK: FAILED (Blad!)\n";
    }

    // Bezpieczne czyszczenie pamieci
    // W Twoim kodzie dla 'identical' zwracany jest wskaznik na druga prosta (_line),
    // wiec usuwamy tylko wtedy, gdy zwrocono nowy obiekt dynamiczny.
    if (result && result != l2) {
        delete result;
    }
    std::cout << "------------------------------------------------------------------\n";
}

int main() {
    std::cout << "==================================================================\n";
    std::cout << "      KOMPLEKSOWE TESTY RELACJI I PRZECIECIA PROSTYCH 3D         \n";
    std::cout << "==================================================================\n\n";

    // --- GRUPA 1: PROSTE PRZECINAJĄCE SIĘ ---

    // Próba 1: Klasyczne przeciecie osi OX i OY w punkcie (0,0,0)
    CLine p1_l1(CLine::axis::OX);
    CLine p1_l2(CLine::axis::OY);
    runTest(1, "Przeciecie osi OX i OY w poczatku ukladu wspolrzednych", &p1_l1, &p1_l2, CLine::intersecting);

    // Próba 2: Przeciecie w dowolnym punkcie przestrzeni
    // L1 przechodzi przez (1,1,1) w kierunku [1,1,1] -> zawiera punkt (2,2,2)
    // L2 przechodzi przez (2,0,2) w kierunku [0,1,0] -> tez zawiera punkt (2,2,2)
    CLine p2_l1(CPoint(1.0f, 1.0f, 1.0f), CVector(1.0f, 1.0f, 1.0f));
    CLine p2_l2(CPoint(2.0f, 0.0f, 2.0f), CVector(0.0f, 1.0f, 0.0f));
    runTest(2, "Przeciecie dwoch prostych w punkcie (2,2,2)", &p2_l1, &p2_l2, CLine::intersecting);


    // --- GRUPA 2: PROSTE RÓWNOLEGŁE (NIEPOKRYWAJĄCE SIĘ) ---

    // Próba 3: Proste rownoległe wzdłuż osi OX, przesuniete w pionie
    CLine p3_l1(CPoint(0.0f, 0.0f, 0.0f), CVector(1.0f, 0.0f, 0.0f));
    CLine p3_l2(CPoint(0.0f, 4.0f, 0.0f), CVector(1.0f, 0.0f, 0.0f));
    runTest(3, "Proste rownolegle wzdłuz osi OX (przesuniecie o Y=4)", &p3_l1, &p3_l2, CLine::parallel);

    // Próba 4: Proste rownoległe, gdzie wektory maja przeciwny zwrot i inna dlugosc
    // L1 kierunek: [1, 2, 3]
    // L2 kierunek: [-2, -4, -6] (mnoznik -2, czyli ten sam kierunek geometryczny)
    CLine p4_l1(CPoint(0.0f, 0.0f, 0.0f), CVector(1.0f, 2.0f, 3.0f));
    CLine p4_l2(CPoint(1.0f, 1.0f, 1.0f), CVector(-2.0f, -4.0f, -6.0f));
    runTest(4, "Rownolegle z wektorami o przeciwnych zwrotach i innych modulach", &p4_l1, &p4_l2, CLine::parallel);


    // --- GRUPA 3: PROSTE TOŻSAME (POKRYWAJĄCE SIĘ) ---

    // Próba 5: Identyczne definicje (Oś OZ i Oś OZ)
    CLine p5_l1(CLine::axis::OZ);
    CLine p5_l2(CLine::axis::OZ);
    runTest(5, "Tozsame proste - ta sama os OZ", &p5_l1, &p5_l2, CLine::identical);

    // Próba 6: Pokrywajace sie proste, ale zdefiniowane przez zupelnie inne punkty i skale wektora
    // L1: od (0,0,0) do (1,1,1) -> kierunek [1,1,1]
    // L2: startuje w (2,2,2) (ktory lezy na L1) i ma kierunek [3,3,3]
    CLine p6_l1(CPoint(0.0f, 0.0f, 0.0f), CPoint(1.0f, 1.0f, 1.0f));
    CLine p6_l2(CPoint(2.0f, 2.0f, 2.0f), CVector(3.0f, 3.0f, 3.0f));
    runTest(6, "Tozsame proste zdefiniowane przez rozne punkty startowe i skale", &p6_l1, &p6_l2, CLine::identical);


    // --- GRUPA 4: PROSTE SKOŚNE (NIE RÓWNOLEGŁE, NIE PRZECINAJĄCE SIĘ) ---

    // Próba 7: Klasyczne proste skosne (jak mijajace sie wiadukty)
    // L1: lezy na podlodze (Z=0) i idzie wzdluz osi OX
    // L2: lezy na suficie (Z=2) i idzie wzdluz osi OY
    CLine p7_l1(CPoint(0.0f, 0.0f, 0.0f), CVector(1.0f, 0.0f, 0.0f));
    CLine p7_l2(CPoint(0.0f, 0.0f, 2.0f), CVector(0.0f, 1.0f, 0.0f));
    runTest(7, "Klasyczne proste skosne (przemieszczone w osi OZ o 2)", &p7_l1, &p7_l2, CLine::skew);

    // Próba 8: Losowe proste skosne w przestrzeni
    CLine p8_l1(CPoint(1.0f, 0.0f, -1.0f), CVector(1.0f, 2.0f, 3.0f));
    CLine p8_l2(CPoint(2.0f, 5.0f, 1.0f), CVector(-1.0f, 1.0f, 4.0f));
    runTest(8, "Dowolne proste skosne w przestrzeni 3D", &p8_l1, &p8_l2, CLine::skew);

    std::cout << "==================================================================\n";
    std::cout << "                      KONIEC TESTOWANIA                           \n";
    std::cout << "==================================================================\n";

    return 0;
}
