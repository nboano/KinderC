#include "../../kinderc.hpp"

struct Person
{
    const char* Name;
    const char* Surname;
    int BirthYear;

    FIELDS(Person,
        FIELD(Person, Name),
        FIELD(Person, Surname),
        FIELD(Person, BirthYear)
    )
};


int main() {
    Person p1;

    p1.Name = "Lorenzo";
    p1.Surname = "Rossi";
    p1.BirthYear = 2003;

    printf(JSON::SerializeObjectOfType<Person>(p1));
}