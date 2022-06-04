#include <vector>
#include <algorithm>
#include "array2vec.h"

vector<int> array2vec(int size, int* array)
{
  vector<int> vec;

  for (int i = 0; i < size; i++)
    vec.push_back(array[i]);

  return vec;
}

vector<int> array2vecs(int size, int* array, int order) // 1 = crescente; -1 = decrescente
{
  vector<int> vec;

  for (int i = 0; i < size; i++)
    vec.push_back(array[i]);

  sort (vec.begin(), vec.end());

  if (order == -1)
    reverse (vec.begin(),vec.end());

  return vec;
}

int array2vecmax(int size, int* array)
{
  vector<int> vec;

  for (int i = 0; i < size; i++)
    vec.push_back(array[i]);

  return *max_element(vec.begin(), vec.end());
}

int array2vecfind(int size, int* array, int value)
{
  vector<int> vec;
  vector<int>::iterator j;

  for (int i = 0; i < size; i++)
    vec.push_back(array[i]);

  j = find (vec.begin(), vec.end(), 7);

  if (j != vec.end())
      return distance(vec.begin(), j);
    else
      return -1;
}
