#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

int build_compare = 0;
int search_compare = 0;

typedef int itemType;
typedef int infoType;

class RBtree
{
private:
   struct node
   {
      itemType key, tag;
      infoType Info;
      struct node *l, *r;
      node(itemType k, infoType i, itemType t, struct node *ll, struct node *rr)
      {
         key = k;
         Info = i;
         tag = t;
         l = ll;
         r = rr;
      }
   };
   struct node *head, *tail, *x, *p, *g, *gg, *z;

public:
   RBtree()
   {
      z = new node(0, infoNIL, black, NULL, NULL);
      z->l = z;
      z->r = z;
      head = new node(itemMIN, infoNIL, black, z, z);
   }

   void insert(itemType k, infoType info)
   {
      x = head;
      p = head;
      g = head;
      while (x != z)
      {
         gg = g;
         g = p;
         p = x;
         x = (k < x->key) ? x->l : x->r;
         build_compare++;
         if (x->l->tag && x->r->tag)
            split(k);
      }
      x = new node(k, info, red, z, z);
      if (k < p->key)
         p->l = x;
      else
         p->r = x;
      build_compare++;
      split(k);
      head->r->tag = black;
   }

   struct node *rotate(itemType k, struct node *y)
   {
      struct node *high, *low;
      high = (k < y->key) ? y->l : y->r;
      build_compare++;
      if (k < high->key)
      {
         low = high->l;
         high->l = low->r;
         low->r = high;
      }
      else
      {
         low = high->r;
         high->r = low->l;
         low->l = high;
      }
      build_compare++;
      if (k < y->key)
         y->l = low;
      else
         y->r = low;
      build_compare++;
      return low;
   }

   void split(itemType k)
   {
      x->tag = red;
      x->l->tag = black;
      x->r->tag = black;
      if (p->tag)
      {
         g->tag = red;
         if (k < g->key != k < p->key)
            p = rotate(k, g);
         build_compare++;
         x = rotate(k, gg);
         x->tag = black;
      }
   }

   infoType search(itemType k)
   {
      struct node *s = head->r;
      z->key = k;
      while (++search_compare && k != s->key)
      {
         s = (k < s->key) ? s->l : s->r;
      }
      return s->Info;
   }
};

class Hash_table
{
private:
   int size;
   struct table
   {
      itemType key = itemMIN;
      infoType info = 0;
      struct table *next = NULL;
   };
   struct table **table;

public:
   Hash_table(int max)
   {
      this->size = max;
      table = new struct table *[size]
      { NULL };
   }

   int hash_value(itemType value)
   {
      return (value % size);
   }

   void insert_table(itemType value)
   {
      int hash = hash_value(value);
      if (table[hash] == NULL)
      {
         table[hash] = new struct table;
         table[hash]->key == value;
         table[hash]->info == 1;
         table[hash]->next == NULL;
      }
      else
      {
         struct table *ptr = table[hash];
         while (ptr->next != NULL)
         {
            ptr = ptr->next;
         }
         ptr->next = new struct table;
         ptr->next->key = value;
         ptr->next->info = 1;
         ptr->next->next = NULL;
      }
   }

   int search_table(itemType value)
   {
      int hash = hash_value(value);
      struct table *ptr = table[hash];

      while (ptr != NULL)
      {
         if (ptr->key == value)
            return ptr->info;
         else
            ptr = ptr->next;
         ++search_compare;
      }

      return 0;
   }

   int get_size()
   {
      return this->size;
   }
};

void swap(itemType *a, itemType *b)
{
   itemType *tmp;
   tmp = a;
   a = b;
   b = tmp;
}

int partition(itemType **a, int left, int right)
{
   int p, v, index, l = left, r = right;
   p = left, v = a[p][0], index = a[p][1];
   while (1)
   {
      while (a[++l][0] < v)
      {
         if (l >= right)
            break;
      }
      while (a[--r][0] > v)
      {
         if (r <= left)
            break;
      }
      if (l < r)
         swap(a[l], a[r]);
      else
         break;
   }
   a[p][0] = a[r][0];
   a[p][1] = a[r][1];
   a[r][0] = v;
   a[r][1] = index;
   return r;
}

void quick_sort(itemType **a, int left, int right)
{
   int k;
   if (right > left)
   {
      k = partition(a, left, right);
      quick_sort(a, left, k - 1);
      quick_sort(a, k + 1, right);
   }
}

void make_random(int *arr, int n)
{
   itemType **a = new itemType *[n];
   srand((unsigned)time(NULL));
   for (int i = 0; i < n; i++)
   {
      a[i] = new itemType[2];
      a[i][0] = (1 + rand() % n);
      a[i][1] = i + 1;
   }

   quick_sort(a, 0, n - 1);

   for (int i = 0; i < n; i++)
      arr[i] = a[i][1];

   for (int i = 0; i < n; i++)
      delete[] a[i];
   delete[] a;
}

int main()
{
   int n;
   itemType *arr;
   RBtree T3;
   Hash_table hash_case[3] = {11, 101, 1009};
   cin >> n;

   arr = new itemType[n];
   make_random(arr, n);

   for (int i = 0; i < n; i++)
   {
      T3.insert(arr[i], 1);
   }

   cout << build_compare / (double)n << " (T3의 구축 시 평균 비교 회수)\n";
   build_compare = 0;

   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < n; j++)
      {
         hash_case[i].insert_table(arr[j]);
      }
      cout << build_compare / (double)n << " (Hash Table 크기가 " << hash_case[i].get_size() << "인 경우의 구축 시 평균 비교 횟수)\n";
      build_compare = 0;
   }

   cout << endl;

   for (int i = 0; i < n; i++)
   {
      T3.search(i);
   }

   cout << search_compare / (double)n << " (T3의 비교 회수)\n";
   search_compare = 0;

   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < n; j++)
      {
         hash_case[i].search_table(j);
      }
      cout << search_compare / (double)n << " (Hash Table 크기가 " << hash_case[i].get_size() << "인 경우 평균 비교 횟수)\n";
      search_compare = 0;
   }
}