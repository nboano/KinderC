#include "model.hpp"


int main() {
    Person p1;
    Address addr;
    SocialEntry test;
    test.Image = "https://test.com/image.png";
    test.Name = "Facebook";
    test.Destroyable = false;

    addr.Address = "Test Address";
    addr.PostalCode = "1234";

    p1.Name = "Lorenzo";
    p1.Surname = "Rossi";
    p1.Address = addr;
    p1.Interests = {"Basket", "Programming", "C++"};
    p1.Socials = {test};

    document << "<pre id='jsonContainer'></pre>";
    $("#jsonContainer") << JSON::SerializeObject(p1, true);
}