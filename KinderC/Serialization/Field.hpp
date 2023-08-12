#pragma once
#include "../../kinderc.hpp"
#include "JSON.hpp"
#include "Serializable.hpp"

namespace KinderC::Serialization {

    template<typename T>
    class Field {
        private:
            JSON::Value* inner_value;
        public:
            operator T() {
                return (T)*inner_value;
            }
            void operator =(T value) {
                *inner_value = value;
            }

            Field(Serializable* obj, const char* field_name) : inner_value(&(*obj)[field_name]) {
                
            }
    };
    
}