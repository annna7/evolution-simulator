#include "IndividualType.h"
#include "string"

std::string individualTypeToString(IndividualType type) {
    switch (type) {
        case CLAIRVOYANT_TYPE:
            return "Clairvoyant";
        case ASCENDANT_TYPE:
            return "Ascendant";
        case KEYSTONE_TYPE:
            return "Keystone";
        case SUITOR_TYPE:
            return "Suitor";
        case REDBULL_TYPE:
            return "RedBull";
        case INDIVIDUAL_TYPE_BEGIN:
            return "Begin Placeholder";
        case INDIVIDUAL_TYPE_END:
            return "End Placeholder";
    }
}