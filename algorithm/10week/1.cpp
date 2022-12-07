#include <iostream>
#include <cstring>
using namespace std;

const int q = 33554393;
const int d = 26;

void brutesearch(string p, string a)
{
   int count = 0;
   int i, j, m = p.length(), n = a.length();
   for (i = 0; i < n - m + 1; i++)
   {
      for (j = 0; j < m; j++)
      {
         count++;
         if (a[i + j] != p[j])
            break;
      }
      if (j == m)
      {
         cout << i << ", ";
      }
   }
   cout << count;
}

void rksearch(string p, string t)
{
   int count = 0;
   int i, j, dM = 1, h1 = 0, h2 = 0, flag;
   int m = p.length(), n = t.length();
   for (i = 1; i < m; i++)
      dM = (d * dM) % q;

   for (i = 0; i < m; i++)
   {
      h1 = (h1 * d + p[i]) % q;
      h2 = (h2 * d + t[i]) % q;
   }

   for (i = 0; i < n - m + 1; i++)
   {
      // count++;
      if (h1 == h2)
      {
         flag = 1;
         for (j = i; j < m + i; j++)
         {
            count++;
            if (t[j] != p[j - i])
            {
               flag = 0;
               break;
            }
         }
         if (flag)
         {
            cout << i << ", ";
         }
      }

      if (i < n - m)
      {
         h2 = (h2 - t[i] * dM) % q;

         if (h2 < 0)
            h2 = h2 % q + q;

         h2 = (h2 * d + t[i + m]) % q;
      }
   }
   cout << count;
}

int *SP;
int initSP(string p)
{
   int count = 0;
   int i, j, m = p.length();
   SP = new int[m];
   SP[0] = -1;
   for (i = 1, j = -1; i <= m - 1; i++)
   {
      while ((j >= 0) &&++count&& (p[j + 1] != p[j]))
         j = SP[j];
      if (++count&&p[j + 1] == p[i])
         j++;
      SP[i] = j;
   } return count;
}

void kmpsearch(string p, string a)
{
   int count = 0;
   int i, j, m = p.length(), n = a.length();
   count+=initSP(p);
   for (i = 0, j = -1; i <= n - 1; i++)
   {
      while ((j >= 0) && ++count&& (p[j + 1] != a[i]))
         j = SP[j];
      if (++count&&p[j + 1] == a[i]) j++;
      if (j == m - 1)
      {
         cout << i - j << ", ";
         j = SP[j];
      }
   }
   cout << count;
}

int main()
{
   string t, p;
   getline(cin, t);
   getline(cin, p);

   brutesearch(p, t);
   cout << "(Brute-Force)" << endl;

   kmpsearch(p, t);
   cout << "(KMP)" << endl;

   rksearch(p, t);
   cout << "(Rabin-Karp)" << endl;

   return 0;
}