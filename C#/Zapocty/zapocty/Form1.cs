using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace zapocty
{
    public partial class Form1 : Form
    {

        private StudentList list;

        public Form1()
        {
            InitializeComponent();
            this.list = new StudentList();
            this.LoadViewData();            //naplnění listView ze struktury this.list
        }

        //načte data ze struktury
        private void LoadViewData()
        {
            this.listView.Items.Clear();
            this.list.Sort(new AlphabeticalComparer()); //seřazení (v tomto případě podle abecedy)
            foreach(Student student in this.list)
            {
                this.AddToView(student);
            }
        }

        //přidá položku do listView
        private void AddToView(Student student)
        {
            string zapocet = student.HasPassed ? "ano" : "ne";

            string[] row = { student.Login, student.Points.ToString(), zapocet };
            ListViewItem listRow = new ListViewItem(row);
            this.listView.Items.Add(listRow);
        }

        //přidání nového studenta
        private void AddNewStudent(object sender, MouseEventArgs e)
        {
            if(!this.CheckLoginError(this.textBoxLogin.Text, this.labelAddError)) { return; }   //login error
            if(!this.CheckPointsError(this.textBoxPoints.Text, this.labelAddError)) { return; } //points error

            Student newStudent;
            if (int.TryParse(this.textBoxPoints.Text, out int pnts))
            {
                newStudent = new Student(this.textBoxLogin.Text.ToUpper(), pnts);   //vytvoření novévo studenta s points = pnts
            }
            else
            {
                newStudent = new Student(this.textBoxLogin.Text.ToUpper(), null);   //vytvoření nového studenta s points = null
            }

            this.list.AddNewStudent(newStudent);    //přidání studenta do struktury
            this.LoadViewData();
            this.textBoxLogin.Clear();
            this.textBoxPoints.Clear();
        }

        //kontrola změny zvolené položky v seznamu
        private void listView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listView.SelectedItems.Count > 0)
            {
                this.buttonDelete.Enabled = true;
                this.modifyButton.Enabled = true;
            }
        }

        //odstranení zvoleného studenta
        private void RemoveStudent(object sender, MouseEventArgs e)
        {
            this.list.RemoveStudent(this.listView.SelectedItems[0].Text);
            this.listView.SelectedItems[0].Remove();

            this.buttonDelete.Enabled = false;
            this.modifyButton.Enabled = false;
        }

        //editace studenta
        private void ModifyStudent(object sender, MouseEventArgs e)
        {

            if(this.textBoxModifyLogin.Text != this.listView.SelectedItems[0].SubItems[0].Text)         //pokud je login stejný jako v seznamu, legin se nezměnil
            {
                if (!this.CheckLoginError(this.textBoxModifyLogin.Text, this.labelModifyError)) { return; } //login error
            }
            if(!this.CheckPointsError(this.textBoxModifyPoints.Text, this.labelModifyError)) { return; }    //points error

            if (int.TryParse(this.textBoxModifyPoints.Text, out int pnts))
            {
                this.list.ModifyStudent(this.listView.SelectedItems[0].SubItems[0].Text, this.textBoxModifyLogin.Text, int.Parse(this.textBoxModifyPoints.Text));   //points = pnts
            }
            else
            {
                this.list.ModifyStudent(this.listView.SelectedItems[0].SubItems[0].Text, this.textBoxModifyLogin.Text, null);   //points = null
            }

            this.LoadViewData();
            this.groupModify.Visible = false;
            this.buttonDelete.Enabled = false;
            this.modifyButton.Enabled = false;
        }

        //zobrazení editačního menu
        private void EnableModifyMenu(object sender, MouseEventArgs e)
        {
            this.groupModify.Visible = true;
            this.textBoxModifyLogin.Text = this.listView.SelectedItems[0].SubItems[0].Text;
            this.textBoxModifyPoints.Text = this.listView.SelectedItems[0].SubItems[1].Text;
        }

        //kontrola chyb v loginu
        private bool CheckLoginError(string login, Label errorLabel)
        {
            errorLabel.Visible = false;

            //ošetření prázdného loginu
            if (login == "")
            {
                errorLabel.Text = "Login nesmí být prázdný!";
                errorLabel.Visible = true;
                return false;
            }
            //ověření dostupnosti loginu
            else if (!this.list.isLoginAvailable(login.ToUpper()))
            {
                errorLabel.Text = "Tento login již existuje!";
                errorLabel.Visible = true;
                return false;
            }
            else { return true; }
        }

        //kontrola chyb v bodech
        private bool CheckPointsError(string textPoints, Label errorLabel)
        {
            errorLabel.Visible = false;

            //ošetření vložených bodů
            if (int.TryParse(textPoints, out int points))
            {
                if (points < 0 || points > 100)
                {
                    errorLabel.Text = "Body nejsou v intervalu 0-100!";
                    errorLabel.Visible = true;
                    return false;
                }
                else { return true; }
            }
            else
            {
                if(textPoints == "") { return true; }           //points dovoluje i null hodnoty!
                errorLabel.Text = "Neplatná hodnota bodů!";
                errorLabel.Visible = true;
                return false;
            }
            
        }
    }
}
