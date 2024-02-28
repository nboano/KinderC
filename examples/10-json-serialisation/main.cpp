#include "../../kinderc.hpp"

using namespace KinderC::Serialization;

class Address;
class SocialEntry;

class Person : public Serializable {
    public:
        using Serializable::Serializable;

        Field<const char*> Name {this, "name"};
        Field<const char*> Surname {this, "surname"};
        Field<const char*> Thumbnail {this, "thumbnail"};
        Field<Address> Address {this, "address"};
        Field<JSON::TypisedArray<const char*>> Interests {this, "interests"};
        Field<JSON::TypisedArray<SocialEntry>> Socials {this, "socials"};
};

class Address : public Serializable {
    public:
        using Serializable::Serializable;

        Field<const char*> Address {this, "address"};
        Field<const char*> City {this, "city"};
        Field<const char*> PostalCode {this, "postalCode"};
};

class SocialEntry : public Serializable {
    public:
        using Serializable::Serializable;

        Field<const char*> Name {this, "name"};
        Field<const char*> Link {this, "link"};
        Field<const char*> Image {this, "img"};
};


int main() {
    Person p1;

    p1.Name = "Lorenzo";
    p1.Surname = "Rossi";

    document << "<pre id='jsonContainer'></pre>";
    $("#jsonContainer") << JSON::SerializeObject(p1);
}