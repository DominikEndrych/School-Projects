using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;

namespace zapocty
{
    class XmlHandler
    {
        private XmlDocument myDocument;

        public string Path { get; set; }        //cesta k XML souboru

        public XmlHandler()
        {
            myDocument = new XmlDocument();
        }

        //načtení dat z XML souboru
        public List<Student> LoadData()
        {
            List<Student> data = new List<Student>();

            //proměnné pro uložení načtených dat z XML
            string login = null;
            int? points = null;
            int tmpPoints = 0;

            if (File.Exists(this.Path))
            {
                this.myDocument.Load(this.Path);

                foreach (XmlNode node in this.myDocument.DocumentElement.ChildNodes)
                {
                    login = node.Attributes["login"].InnerText;

                    //zjištění, jestli je Points číslo nebo null
                    points = null;
                    if (int.TryParse(node["Points"].InnerText, out tmpPoints))
                    {
                        points = tmpPoints;
                    }

                    data.Add(new Student(login, points));
                }
                return data;
            }
            else { return null; }
        }

        //přidání nového uzlu
        public void AddNewNode(Student newStudent)
        {
            XmlElement newNode = this.myDocument.CreateElement("Student");
            XmlNode points = this.myDocument.CreateElement("Points");
            XmlNode hasPassed = this.myDocument.CreateElement("HasPassed");

            newNode.SetAttribute("login", newStudent.Login);
            points.InnerText = newStudent.Points.ToString();
            hasPassed.InnerText = newStudent.HasPassed.ToString();

            newNode.AppendChild(points);
            newNode.AppendChild(hasPassed);
            this.myDocument.DocumentElement.AppendChild(newNode);
            this.myDocument.Save(this.Path);
        }

        //odebrání uzlu
        public void RemoveNode(string login)
        {
            XmlNode node = this.FindNode(login);
            if(node != null)
            {
                node.ParentNode.RemoveChild(node);
            }
            this.myDocument.Save(this.Path);
        }

        //změna vybraného uzlu
        public void ModifyNode(string oldLogin, string newLogin, int? newPoints)
        {
            XmlNode node = this.FindNode(oldLogin);
            if(node != null)
            {
                node.Attributes["login"].InnerText = newLogin;
                node["Points"].InnerText = newPoints.ToString();
                node["HasPassed"].InnerText = newPoints >= 51 ? "True" : "False";
            }
            this.myDocument.Save(this.Path);
        }

        //nalezení daného uzlu pomocí loginu
        private XmlNode FindNode(string login)
        {
            foreach (XmlNode node in this.myDocument.DocumentElement.ChildNodes)
            {
                if (node.Attributes["login"].InnerText == login)
                {
                    return node;
                }
            }
            return null;
        }

    }
}
