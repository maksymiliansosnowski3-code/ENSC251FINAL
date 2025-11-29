#include "telepathiclinktest.hpp"

void TelepathicLinkTest::setSignalStrength(int v) {
    if (v < 0 || v > 10) throw std::invalid_argument("signal_strength out of range"); // check
    signal_strength = v; //set
    updateTotal(); //recalculate
}

void TelepathicLinkTest::setCognitiveLink(int v) {
    if (v < 0 || v > 10) throw std::invalid_argument("cognitive_link out of range"); // check
    cognitive_link = v; //set
    updateTotal(); //recalculate
}

void TelepathicLinkTest::setEmpathicOverlay(int v) {
    if (v < 0 || v > 10) throw std::invalid_argument("empathic_overlay out of range"); // check
    empathic_overlay = v; //set
    updateTotal(); //recalculate
}

void TelepathicLinkTest::setCognitiveResistance(int v) {
    if (v < 0 || v > 10) throw std::invalid_argument("cognitive_resistance out of range"); // check
    cognitive_resistance = v; //set
    updateTotal(); //recalculate
}

TelepathicLinkTest::TelepathicLinkTest(int s, int c, int e, int r)
{
    //use setters so range checks apply
    setSignalStrength(s);
    setCognitiveLink(c);
    setEmpathicOverlay(e);
    setCognitiveResistance(r);
}

int TelepathicLinkTest::getTotal() const {
    return total;
}