#pragma once

#include "ID.h"

#include <cstdint>
#include <iterator>
#include <list>
#include <memory>
#include <string>


class ID_Pool {
public:
    std::unique_ptr<ID> borrowID();
    void giveBackID(std::unique_ptr<ID> id);

    std::string getEntirePoolAsText() const;

    // Singleton
    ID_Pool(const ID_Pool& other) = delete;
    ID_Pool& operator=(const ID_Pool& other) = delete;
    static ID_Pool& getInstance();
private:
    ID_Pool();

    void insertID_SortedByLowestFirst(std::unique_ptr<ID> id);
    void moveID_ToBeginningOfPool(std::unique_ptr<ID> id);
    void moveID_BeforeFirstGreaterElement(
        uint32_t positionBeforeFirstGreaterElement,
        std::unique_ptr<ID> id);
    void regeneratePool();

    const int64_t INITIAL_POOL_CAPACITY = 3;
    int64_t lastGeneratedNumber;
    int64_t numberOfRegenerations;
    std::list<std::unique_ptr<ID>> poolOfIDs;
};
