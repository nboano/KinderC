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
            T Get() {
                return (T)*inner_value;
            }

            void Set(T value) {
                *inner_value = value;
            }

            operator T() {
                return Get();
            }
            void operator =(T value) {
                Set(value);
            }


            Field(Serializable* obj, const char* field_name) : inner_value(&(*obj)[field_name]) {
                
            }
    };
    
}