#include "ID_Pool.h"
#include "NoIDs_InID_Pool.h"

#include <sstream>

std::unique_ptr<ID> ID_Pool::borrowID() {
    bool areAllIDsInUse = this->poolOfIDs.empty();
    if (areAllIDsInUse) {

        // throw NoIDs_InID_Pool(); // Scenario - Limited number of elements:
                                    // - throw an exception to notify client that no further elements are availible

        this->regeneratePool();     // Scenario - Regenerating pool:
                                    // - generate new elements when all elements are in use, thus the pool is empty
    }

    auto selectedID = std::move(this->poolOfIDs.front());

    this->poolOfIDs.pop_front();
    return selectedID;
}

void ID_Pool::giveBackID(std::unique_ptr<ID> id) {
    if (this->poolOfIDs.empty()) {
        this->poolOfIDs.emplace_front(std::move(id));
        return;
    }

    insertID_SortedByLowestFirst(std::move(id));
}


void ID_Pool::insertID_SortedByLowestFirst(std::unique_ptr<ID> id) {
    bool hasPoolOnlyOneElement = this->poolOfIDs.size() == 1;
    bool isID_SmallerThanTheOnlyElementOfPool = *id < *(this->poolOfIDs.front());
    if (hasPoolOnlyOneElement && isID_SmallerThanTheOnlyElementOfPool) {
        moveID_ToBeginningOfPool(std::move(id));
        return;
    }

    uint32_t positionBeforeFirstGreaterElement{};
    for (const auto& currentID : this->poolOfIDs) {
        bool isID_Duplicate = *id == *currentID;
        if (isID_Duplicate) {
            return;
        }

        if (*id > *currentID) {
            ++positionBeforeFirstGreaterElement;
            continue;
        }

        moveID_BeforeFirstGreaterElement(positionBeforeFirstGreaterElement, std::move(id));
        return;
    }
}

void ID_Pool::moveID_ToBeginningOfPool(std::unique_ptr<ID> id) {
    this->poolOfIDs.emplace(this->poolOfIDs.begin(), std::move(id));
}

void ID_Pool::moveID_BeforeFirstGreaterElement(
        uint32_t positionBeforeFirstGreaterElement,
        std::unique_ptr<ID> id)
{
    const std::list<std::unique_ptr<ID>>::iterator iteratorPositionBeforeFirstGreaterElement = std::next(this->poolOfIDs.begin(), positionBeforeFirstGreaterElement);
    this->poolOfIDs.emplace(iteratorPositionBeforeFirstGreaterElement, std::move(id));
}

std::string ID_Pool::getEntirePoolAsText() const {
    std::stringstream output;

    output << "size = " << this->poolOfIDs.size() << "\n";

    if (this->poolOfIDs.empty()) {
        return "Pool is empty";
    }

    for (const auto& id : this->poolOfIDs) {
        output << *id << "; ";
    }

    return output.str();
}

ID_Pool& ID_Pool::getInstance() {
    struct ID_PoolDerived : public ID_Pool{};
    static auto idPoolInstance = std::make_shared<ID_PoolDerived>(); // make_shared doesn't have access to private member function by default, unless we

    // static std::shared_ptr<ID_Pool> idPoolInstance(new ID_Pool()); // Meyer's Singleton implementation

    return *idPoolInstance;
}

ID_Pool::ID_Pool() :
        nextGeneratedNumber(0),
        poolOfIDs()
{
    this->regeneratePool();
}

void ID_Pool::regeneratePool() {
    for (   int64_t idNumber = this->nextGeneratedNumber;
            idNumber < this->nextGeneratedNumber + this->INITIAL_POOL_CAPACITY;
            ++idNumber) {
        auto id = std::make_unique<ID>(idNumber);
        this->poolOfIDs.push_back(std::move(id));
    }

    this->nextGeneratedNumber += this->INITIAL_POOL_CAPACITY;
}
