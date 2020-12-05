#include <map>
#include <iostream>
#include <functional>
#include <list>
#include <algorithm>
#include "lfu.hpp"

template <typename Key, typename Value>
using lfu_cache = cache::LFUCache<Key, Value>;

template <typename Key, typename Value>
using test = cache::Test<Key, Value>;

int main(int argc, char const *argv[])
{
  /*ErrorCheck(argc < 3, "No cache size or number of keys or keys!");
  int size = strtol(argv[1], NULL, 10);
  int num = strtol(argv[2], NULL, 10);
  ErrorCheck(argc - 3 != num, "Wrong number of keys!");*/

  int key = 0, size = 0, num = 0;

  std::cin >> size;
  std::cin >> num;

  lfu_cache<int, int> cache(size);
  test<int, int> tt;

  for(int i = 0; i < num; i++)
  {
    std::cin >> key;
    //int key = strtol(argv[i+3], NULL, 10);
    cache.Put(key, key);
  }

  //cache.Print();
  std::cout << cache.GetHit() << std::endl;

  return 0;
}
