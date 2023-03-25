#ifndef __SEPARATE_CHAINING_HASH_TABLE_HPP
#define __SEPARATE_CHAINING_HASH_TABLE_HPP

#include <iostream>
#include <forward_list>
#include <vector>

template <typename Key>
using HashFunction = unsigned int (*) (const Key&);

template <typename Key, typename Value, HashFunction<Key> hashFunction>
class SeparateChainingHashTable
{
    private:
        struct KeyValuePair
        {
            Key key;
            Value value;
        };

        using KVP = KeyValuePair;
        using Bucket = std::forward_list<KVP>;

        static const size_t INITIAL_CAPACITY = 16;
        static const size_t INCREASE_STEP = 2;

        std::vector<Bucket> table;

        size_t buckets;
        size_t elements;
        size_t collisions;

        unsigned int hash(const Key& key, const size_t capacity) const
        {
            return hashFunction(key) % capacity;
        }

        void rehash()
        {
            const size_t newCapacity = this->table.size() * INCREASE_STEP;
            std::vector<Bucket> newTable(newCapacity);

            this->elements = 0;
            this->buckets = 0;
            this->collisions = 0;

            for(const Bucket& bucket : this->table)
            {
                for(const KVP& kvp : bucket)
                {
                    unsigned int hashCode = this->hash(kvp.key, newCapacity);

                    if(newTable[hashCode].empty())
                    {
                        this->buckets++;
                    }
                    else
                    {
                        this->collisions++;
                    }

                    newTable[hashCode].push_front(kvp);
                    this->elements++;
                }
            }

            this->table = newTable;
        }

    public:
        SeparateChainingHashTable() : buckets(0), elements(0), collisions(0), table(INITIAL_CAPACITY)
        { }

        SeparateChainingHashTable(const SeparateChainingHashTable& other) = default;
        ~SeparateChainingHashTable() = default;
        SeparateChainingHashTable& operator = (const SeparateChainingHashTable& other) = default;

        bool insert(const Key& key, const Value& value)
        {
            if(this->lookup(key) != nullptr)
            {
                return false;
            }

            if(this->loadFactor() > 1)
            {
                this->rehash();
            }

            unsigned int hashCode = this->hash(key, this->table.size());

            if(this->table[hashCode].empty())
            {
                this->buckets++;
            }
            else
            {
                this->collisions++;
            }

            this->table[hashCode].push_front(KVP{key, value});
            this->elements++;

            return true;
        }
        
        bool erase(const Key& key)
        {
            unsigned int hashCode = this->hash(key, this->table.size());

            typename Bucket::iterator prev = this->table[hashCode].before_begin();
            typename Bucket::iterator curr = this->table[hashCode].begin();

            for(; curr != this->table[hashCode].end(); ++prev, ++curr)
            {
                if(curr->key == key)
                {
                    this->table[hashCode].erase_after(prev);

                    this->elements--;
                    if(this->table[hashCode].empty())
                    {
                        this->buckets--;
                    }
                    else
                    {
                        this->collisions--;
                    }

                    return true;
                }
            }

            return false;
        }

        bool contains(const Key& key) const
        {
            return this->lookup(key) != nullptr;
        }

        Value* lookup(const Key& key)
        {
            for(Bucket& bucket : this->table)
            {
                for(KVP& kvp : bucket)
                {
                    if(kvp.key == key)
                        return &kvp.value;
                }
            }
            return nullptr;
        }

        const Value* lookup(const Key& key) const
        {
            for(const Bucket& bucket : this->table)
            {
                for(const KVP& kvp : bucket)
                {
                    if(kvp.key == key)
                        return &kvp.value;
                }
            }
            return nullptr;
        }

        size_t size() const
        {
            return this->elements;
        }

        size_t bucketCount() const
        {
            return this->buckets;
        }

        double loadFactor() const
        {
            return (double)this->elements / this->table.size();
        }

        std::vector<Key> keys() const
        {
            std::vector<Key> result;
            for(const Bucket& bucket : this->table)
            {
                for(const KVP& kvp : bucket)
                {
                    result.push_back(kvp.key);
                }
            }
            return result;
        }

        std::vector<Value> values() const
        {
            std::vector<Value> result;
            for(const Bucket& bucket : this->table)
            {
                for(const KVP& kvp : bucket)
                {
                    result.push_back(kvp.value);
                }
            }
            return result;
        }

        void info(std::ostream& out = std::cout) const
        {
            out << "elements: " << this->elements 
                << ", buckets: " << this->buckets
                << ", collisions: " << this->collisions
                << std::endl;
        }
};

#endif
