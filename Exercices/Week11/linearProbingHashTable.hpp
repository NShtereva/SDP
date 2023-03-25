#ifndef __LINEAR_PROBING_HASH_TABLE_HPP
#define __LINEAR_PROBING_HASH_TABLE_HPP

#include <iostream>
#include <vector>

template <typename Key>
using HashFunc = unsigned int (*) (const Key&);

template <typename Key, typename Value, HashFunc<Key> hashFunction>
class LinearProbingHashTable
{
    private:
        struct KeyValuePair
        {
            Key key;
            Value value;
            bool empty;

            KeyValuePair() : empty(true)
            {}
            
            KeyValuePair(const Key& key, const Value& value, bool empty = true) 
                : key(key), value(value), empty(empty)
            {}
        };

        using KVP = KeyValuePair;

        static const size_t INITIAL_CAPACITY = 16;
        static const size_t INCREASE_STEP = 2;

        std::vector<KVP> table;

        size_t elements;
        size_t capacity;

        unsigned int hash(const Key& key, const size_t _capacity) const
        {
            return hashFunction(key) % _capacity;
        }

        void rehash()
        {
            const size_t newCapacity = this->capacity * INCREASE_STEP;
            std::vector<KVP> newTable(newCapacity);

            for(const KVP& kvp : this->table)
            {
                if(!kvp.empty)
                {
                    unsigned int hashCode = this->hash(kvp.key, newCapacity);

                    while(!newTable[hashCode].empty)
                    {
                        hashCode = (hashCode + 1) % newCapacity;
                    }

                    newTable[hashCode].key = kvp.key;
                    newTable[hashCode].value = kvp.value;
                    newTable[hashCode].empty = false;
                }
            }

            this->capacity = newCapacity;
            this->table = newTable;
        }

    public:
        LinearProbingHashTable() : elements(0), capacity(INITIAL_CAPACITY), table(INITIAL_CAPACITY)
        { }

        LinearProbingHashTable(const LinearProbingHashTable& other) = default;
        ~LinearProbingHashTable() = default;
        LinearProbingHashTable& operator = (const LinearProbingHashTable& other) = default;

        bool insert(const Key& key, const Value& value)
        {
            if(this->contains(key))
            {
                return false;
            }

            if(this->loadFactor() > 0.5)
            {
                this->rehash();
            }

            unsigned int hashCode = this->hash(key, this->capacity);

            while(!this->table[hashCode].empty)
            {
                hashCode = (hashCode + 1) % this->capacity;
            }

            this->table[hashCode].key = key;
            this->table[hashCode].value = value;
            this->table[hashCode].empty = false;

            this->elements++;
            return true;
        }
        
        bool erase(const Key& key)
        {
            if(!this->contains(key))
            {
                return false;
            }

            unsigned int hashCode = this->hash(key, this->capacity);

            while(this->table[hashCode].key != key)
            {
                hashCode = (hashCode + 1) % this->capacity;
            }

            this->table[hashCode].empty = true;

            hashCode = (hashCode + 1) % this->capacity;
            while(!this->table[hashCode].empty)
            {
                Key keyToRehash = this->table[hashCode].key;
                Value valueToRehash = this->table[hashCode].value;

                this->table[hashCode].empty = true;
                this->elements--;

                this->insert(keyToRehash, valueToRehash);
                hashCode = (hashCode + 1) % this->capacity;
            }

            this->elements--;
            return true;
        }

        bool contains(const Key& key) const
        {
            return this->lookup(key) != nullptr;
        }

        Value* lookup(const Key& key)
        {
            unsigned int hashCode = this->hash(key, this->table.size());
            for(int i = hashCode; !this->table[i].empty; i = (i + 1) % this->capacity)
            {
                if(this->table[i].key == key)
                {
                    return &this->table[i].value;
                }
            }
            return nullptr;
        }

        const Value* lookup(const Key& key) const
        {
            unsigned int hashCode = this->hash(key, this->table.size());
            for(int i = hashCode; !this->table[i].empty; i = (i + 1) % this->capacity)
            {
                if(this->table[i].key == key)
                {
                    return &this->table[i].value;
                }
            }
            return nullptr;
        }

        size_t size() const
        {
            return this->elements;
        }

        double loadFactor() const
        {
            return (double)this->elements / this->capacity;
        }

        std::vector<Key> keys() const
        {
            std::vector<Key> result;
            for(const KVP& kvp : this->table)
            {
                if(!kvp.empty)
                {
                    result.push_back(kvp.key);
                }
            }
            return result;
        }

        std::vector<Value> values() const
        {
            std::vector<Value> result;
            for(const KVP& kvp : this->table)
            {
                if(!kvp.empty)
                {
                    result.push_back(kvp.value);
                }
            }
            return result;
        }

        void info(std::ostream& out = std::cout) const
        {
            out << "elements: " << this->elements 
                << ", capacity: " << this->capacity
                << std::endl;
        }
};

#endif
