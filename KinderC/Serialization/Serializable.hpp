#pragma once
#include "KinderC.Serialization.hpp"

namespace KinderC::Serialization {

    class Serializable : public JSON::Object {
        public:
            Serializable() {

            }
            Serializable(JSON::Object obj) {
                for(JSON::Field f : obj) {
                    this->operator[](f.Key) = f.Value;
                }
            }
    };

}