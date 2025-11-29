#include "aliencrew.hpp"
#include <stdexcept> 

AlienCrew::AlienCrew(std::string fn, std::string ln,
                     float ts, int apt, unsigned int id,
                     std::string world,
                     TelepathicLinkTest t)
{
    //initialize base fields via base setters
    try {
        setFirstName(fn);
        setLastName(ln);
        setTrainingScore(ts);
        setMissionAptitude(apt);
        setId(id);
    } catch (const std::invalid_argument& e) {
        throw; //rethrow to signal invalid construction
    }

    ttest = t;            //assign test object
    setHomeworld(world);  //validate
}

void AlienCrew::setHomeworld(const std::string& w) {
    if (w.empty()) throw std::invalid_argument("homeworld empty"); // check
    homeworld = w; //set
}

std::ostream& operator<<(std::ostream& os, const AlienCrew& a) {
    os << "Alien Crew Member\n"
       << "-----------------\n"
       << "Name: " << a.getFirstName() << " " << a.getLastName() << "\n"
       << "Training Score: " << a.getTrainingScore() << "\n"
       << "Mission Aptitude: " << a.getMissionAptitude() << "\n"
       << "ID: " << a.getId() << "\n"
       << "Homeworld: " << a.getHomeworld() << "\n";

    const TelepathicLinkTest& t = a.getTelepathicLinkTest();

    os << "Telepathic Test:\n"
       << "   Signal Strength: "      << t.getSignalStrength() << "\n"
       << "   Cognitive Link: "       << t.getCognitiveLink() << "\n"
       << "   Empathic Overlay: "     << t.getEmpathicOverlay() << "\n"
       << "   Cognitive Resistance: " << t.getCognitiveResistance() << "\n"
       << "   Total Score: "          << t.getTotal() << "\n";

    return os;
}
