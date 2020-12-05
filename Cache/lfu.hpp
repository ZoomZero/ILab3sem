#ifndef LFU_HPP
#define LFU_HPP

#include <map>
#include <iostream>
#include <functional>
#include <list>
#include <algorithm>

namespace cache
{
  template <class Key, class Value>
  class LFUCache
  {
  private:

    std::map<Key, std::pair<Value, int>> lfu_storage;
    std::map<int, std::list<Key>> freq_storage;
    size_t max_cache_size;
    int hit;

  public:

    explicit LFUCache(size_t max_size) : max_cache_size(max_size), hit(0)
    {
      if (max_cache_size == 0) max_cache_size = std::numeric_limits<size_t>::max();
    }

    ~LFUCache() = default;

    void Put(const Key key, Value val)
    {
      auto elem_it = lfu_storage.find(key);

      if (elem_it != lfu_storage.end())
      {
        Get(key);
        hit++;
      }
      else if (lfu_storage.size() >= max_cache_size)
      {
          Replace(key, val);
      }
      else
      {
        InsertElem(key, val);
        Get(key);
      }

    }

    const Value Get(const Key key)
    {
      auto elem_it = lfu_storage.find(key);

      if (elem_it == lfu_storage.end())
      {
        std::cout << "No such elem" << std::endl;
      }

      (elem_it->second).second++;
      //std::cout << "Getting elem = " << (elem_it->second).first << " with freq = " << (elem_it->second).second
      //<< " key = " << key << std::endl;

      Update(elem_it->first, (elem_it->second).second);

      return (elem_it->second).first;
    }

    void Replace(const Key key, Value val)
    {
      auto freq_it = freq_storage.begin();

      EraseElem(freq_it->second.front());
      freq_it->second.pop_front();

      if (freq_it->second.empty())
      {
        EraseFreq(freq_it->first);
      }

      InsertElem(key, val);
      Get(key);

    }

    void Update(const Key key, int freq)
    {
      auto freq_it = freq_storage.find(freq - 1);

      if(freq_it != freq_storage.end())
      {
        auto old_list = &(freq_it->second);
        auto old_freq = std::find(old_list->begin(), old_list->end(), key);

        if (old_freq != old_list->end())
        {
          old_list->remove(key);

          if (old_list->empty())
          {
            EraseFreq(freq_it->first);
          }
        }
      }

      freq_it = freq_storage.find(freq);

      if(freq_it != freq_storage.end())
      {
        auto new_list = &(freq_it->second);
        new_list->push_back(key);
      }
      else
      {
        InsertFreq(key, freq);
      }
    }

    void InsertElem(const Key key, Value val)
    {
      lfu_storage.insert(std::pair<Key, std::pair<Value, int>>(key, std::pair<Value, int>(val, 0)));
    }

    void InsertFreq(const Key key, int freq)
    {
      freq_storage.insert(std::pair<int, std::list<Key>>(freq, std::list<Key>{ key }));
    }

    void EraseElem(const Key key)
    {
      lfu_storage.erase(key);
    }

    void EraseFreq(const Key key)
    {
      freq_storage.erase(key);
    }

    void Print()
    {
      for (auto i : freq_storage)
      {
        std::cout << "freq: " << i.first << " keys:" ;
        for (auto v : i.second)
        {
          std::cout << " " << v;
        }
        std::cout << std::endl;
      }
      std::cout << "Hit = " << hit << std::endl;
    }

    int GetHit()
    {
      return hit;
    }
  };

  template <class Key, class Value>
  class Test
  {
  public:
    Test() = default;
    ~Test() = default;

    void ExpectingInCache(int freq, Key key)
    {
      int got_smth = 0;
      if (got_smth == 0)
      {
        std::cout << "Check failed" << std::endl;
      }
      else
      {
        std::cout << "Check OK" << std::endl;
      }
    }
  };
}

void ErrorCheck(bool err, const char * description)
{
  if(err)
  {
    printf("%s\n", description);
    exit(EXIT_FAILURE);
  }
}

#endif
