#include "model.hpp"

int main() {
    const char* _FPATH = "./example.json";

    fetch(_FPATH).then([](Response& resp) {
        Person p = JSON::DeserializeObjectAs<Person>(resp.Text());
        Address addr = p.Address;
        JSON::TypisedArray<SocialEntry> socials = p.Socials;

        printf("<h2>%s %s</h2>", p.Name.Get(), p.Surname.Get());
        printf("%s, <b>%s</b><br><br>", addr.Address.Get(), addr.City.Get());

        for(SocialEntry sc : socials) {
            printf("<a href='%s'>%s</a><br>", sc.Link.Get(), sc.Name.Get());
        }

        printf("<br>Interessi: ");

        for(const char* intr : p.Interests.Get()) {
            printf("<b>%s</b>; ", intr);
        }
    });
}