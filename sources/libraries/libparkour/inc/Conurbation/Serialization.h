namespace Conurbation {
    
    class ISerializable;
    
    class Serialization {
        public:
            virtual void AddUint8 (char* name, uint8_t value) = 0;
            virtual void AddUint16 (char* name, uint16_t value) = 0;
            virtual void AddUint32 (char* name, uint32_t value) = 0;
            virtual void AddUint64 (char* name, uint64_t value) = 0;
            virtual void AddInt8 (char* name, int8_t value) = 0;
            virtual void AddInt16 (char* name, int16_t value) = 0;
            virtual void AddInt32 (char* name, int32_t value) = 0;
            virtual void AddInt64 (char* name, int64_t value) = 0;
            virtual void AddFloat (char* name, float_t value) = 0;
            virtual void AddDouble (char* name, double_t value) = 0;
            virtual void AddBool (char* name, bool_t value) = 0;
            virtual void AddString (char* name, char* value) = 0;
            virtual void AddSubobject (char* name, Serialization& value) = 0;
            virtual void AddSubobject (char* name, ISerializable& value) = 0;
            virtual void AddArray (char* name, Serialization& value) = 0;
            virtual void AddGuid (char* name, guid_t* value) = 0;
            virtual void AddBinary (char* name, uintptr_t length, void* value) = 0;
            virtual void AddDateTime (char* name, datetime_t value) = 0;
            
    }
    
    
    
    class ISerializable {
        public:
            virtual void Serialize(Serialization& writeTo) = 0;
    }
    
}