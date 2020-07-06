#include "ID.h"

#include <iostream>

ID::ID(int64_t id) : id(id) {}

int64_t ID::getID() const {
    return id;
}

std::string ID::getID_AsText() const {
    return std::to_string(this->id);
}

bool ID::operator==(const ID& otherID) const {
    return this->id == otherID.id;
}

bool ID::operator<(const ID& otherID) const {
    return this->id < otherID.id;
}

bool ID::operator>(const ID& otherID) const {
    return this->id > otherID.id;
}

std::ostream& operator<<(std::ostream& out, const ID& id) {
    out << id.getID();
    return out;
}
