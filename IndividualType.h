
#ifndef OOP_INDIVIDUALTYPE_H
#define OOP_INDIVIDUALTYPE_H

#include <string>

enum IndividualType {
    INDIVIDUAL_TYPE_BEGIN,
    CLAIRVOYANT_TYPE,
    ASCENDANT_TYPE,
    KEYSTONE_TYPE,
    SUITOR_TYPE,
    REDBULL_TYPE,
    INDIVIDUAL_TYPE_END
};

std::string individualTypeToString(IndividualType type);

#endif //OOP_INDIVIDUALTYPE_H
