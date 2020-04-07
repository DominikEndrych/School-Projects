using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zapocty
{
    class Student
    {

        private int? points;    //points dovoluje i null hodnoty

        public Student(string login, int? points)
        {
            this.Login = login;
            this.Points = points;
        }

        public string Login { get; set; }
        public bool HasPassed { get; set; }
        public int? Points
        {
            get { return this.points; }
            set
            {
                points = value;
                this.HasPassed = this.points >= 51 ? true : false;
            }
        }

        public override string ToString()
        {
            return this.Login;
        }
    }
}
