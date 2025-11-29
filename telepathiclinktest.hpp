#ifndef TELEPATHICLINKTEST_HPP
#define TELEPATHICLINKTEST_HPP

#include <stdexcept>

class TelepathicLinkTest {
public:
    TelepathicLinkTest();

    TelepathicLinkTest(int s, int c, int e, int r);

    int getSignalStrength() const { return signal_strength; }
    int getCognitiveLink() const { return cognitive_link; }
    int getEmpathicOverlay() const { return empathic_overlay; }
    int getCognitiveResistance() const { return cognitive_resistance; }
    int getTotal() const { return total; }

    void setSignalStrength(int v);
    void setCognitiveLink(int v);
    void setEmpathicOverlay(int v);
    void setCognitiveResistance(int v);

private:
    void updateTotal() { total = signal_strength + cognitive_link + empathic_overlay + cognitive_resistance; }

    int signal_strength = 0;
    int cognitive_link = 0;
    int empathic_overlay = 0;
    int cognitive_resistance = 0;
    int total = 0;
};

#endif
