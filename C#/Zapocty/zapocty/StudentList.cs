using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zapocty
{
    class StudentList
    {
        private List<Student> data;
        private XmlHandler xmlHandler;

        //indexer
        public Student this[int index]
        {
            get { return this.data[index]; }
            set { this.data[index] = value; }
        }

        public StudentList()
        {
            xmlHandler = new XmlHandler();
            this.xmlHandler.Path = "../../Resources/students.xml";
            this.data = new List<Student>();
            foreach (Student item in xmlHandler.LoadData())
            {
                this.data.Add(item);
            }
            this.Sort(new AlphabeticalComparer());
        }

        private void Add(Student item)
        {
            this.data.Add(item);
        }

        public void Remove(Student item)
        {
            this.data.Remove(item);
        }

        public void AddNewStudent(Student newStudent)
        {
            this.Add(newStudent);
            this.xmlHandler.AddNewNode(newStudent);
        }

        //zjistí, jestli je login dostupný
        public bool isLoginAvailable(string login)
        {
            foreach(Student item in this.data)
            {
                if(item.Login == login) { return false; }
            }

            return true;
        }

        //najde studenta se zadaným loginem
        private Student FindStudent(string login)
        {
            Student student = this.data.Find(s => s.Login == login);
            return student;
        }

        //odebere studenta se zadaným loginem
        public void RemoveStudent(string login)
        {
            Student student = this.FindStudent(login);
            if(student != null)
            {
                this.data.Remove(student);
                this.xmlHandler.RemoveNode(login);
            }
            
        }

        //editace studenta se zadaným loginem
        public void ModifyStudent(string oldLogin, string newLogin, int? newPoints)
        {
            Student student = this.FindStudent(oldLogin);
            student.Login = newLogin;
            student.Points = newPoints;
            this.xmlHandler.ModifyNode(oldLogin, newLogin, newPoints);

        }

        //seřazení
        public void Sort(IComparer<Student> comparer)
        {
            this.data.Sort(comparer);
        }

        //enumerator pro procházení v cyklu
        public IEnumerator<Student> GetEnumerator()
        {
            foreach(Student item in this.data)
            {
                yield return item;
            }
        }


    }
}
