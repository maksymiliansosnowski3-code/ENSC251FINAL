#include "telepathiclinktest.hpp"

TelepathicLinkTest::TelepathicLinkTest() {
    updateTotal();
}

TelepathicLinkTest::TelepathicLinkTest(int s, int c, int e, int r)
    : signal_strength(s),
      cognitive_link(c),
      empathic_overlay(e),
      cognitive_resistance(r)
{
    updateTotal();
}

void TelepathicLinkTest::setSignalStrength(int v) {
    if (v < 0 || v > 10) throw std::invalid_argument("invalid signal");
    signal_strength = v;
    updateTotal();
}

void TelepathicLinkTest::setCognitiveLink(int v) {
    if (v < 0 || v > 10) throw std::invalid_argument("invalid cognitive");
    cognitive_link = v;
    updateTotal();
}

void TelepathicLinkTest::setEmpathicOverlay(int v) {
    if (v < 0 || v > 10) throw std::invalid_argument("invalid empathic");
    empathic_overlay = v;
    updateTotal();
}

void TelepathicLinkTest::setCognitiveResistance(int v) {
    if (v < 0 || v > 10) throw std::invalid_argument("invalid resistance");
    cognitive_resistance = v;
    updateTotal();
}
