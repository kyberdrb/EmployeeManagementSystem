#pragma once

#include <cstdint>
#include <iosfwd>

class ID {
public:
    explicit ID(int64_t id);
    
    ID(const ID& other) = delete;
    ID& operator=(const ID& other) = delete;

    int64_t getID() const;
    std::string getID_AsText() const;

    bool operator==(const ID& otherID) const;
    bool operator<(const ID& otherID) const;
    bool operator>(const ID& otherID) const;

    friend std::ostream& operator<<(std::ostream& out, const ID& id);

private:
    int64_t id;
};
