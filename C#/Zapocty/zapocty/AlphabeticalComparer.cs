using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/* Komparátor podle abecedy */

namespace zapocty
{
    class AlphabeticalComparer : IComparer<Student>
    {
        int IComparer<Student>.Compare(Student x, Student y)
        {
            char[] a = x.Login.ToCharArray();
            char[] b = y.Login.ToCharArray();

            for(int i = 0; i < a.Length; i++)
            {
                if(a[i].CompareTo(b[i]) > 0) { return 1; }
                else if (a[i].CompareTo(b[i]) < 0) { return -1; }
            }
            return 0;
        }
    }
}
