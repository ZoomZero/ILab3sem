#include "lfu.hpp"

template <typename Key, typename Value>
using lfu_cache = cache::LFUCache<Key, Value>;

template <typename Key, typename Value>
using test = cache::Test<Key, Value>;

int main(int argc, char const *argv[])
{
  ErrorCheck(argc != 2, "No cache size!");

  int size = strtol(argv[1], NULL, 10);

  lfu_cache<int, int> cache(size);
  test<int, int> tt;

  cache.Put(1, 10);
  cache.Get(1);
  cache.Put(2, 20);
  cache.Put(3, 30);
  cache.Put(4, 40);
  tt.ExpectingInCache(1, 4);
  cache.Get(2);
  cache.Get(2);
  cache.Get(3);
  cache.Get(3);
  cache.Print();
  cache.Put(5, 50);
  cache.Print();

  return 0;
}
