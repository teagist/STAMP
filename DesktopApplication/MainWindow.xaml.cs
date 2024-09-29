//****************************************************************************
//  C# File for the User Login Window.
//  Programmed by: Houston Brown.
//  Last Compiled Date: 10/20/2023
//
//  Copyright (c) 2023 by The Three Masters Co.
//
//	Permission is hereby granted to any person that obtains a copy of this
//	software and associated documentation files (the "Software"), to deal
//	within the Software for free and without restriction.  Including the
//	rights to use, copy, modify, merge, publish, redistribute, sublicense,
//	and/or sell copies of the Software.  Furthermore, to the people who the
//	Software is furnished to do so, subject to the following:
//
//	The above copyright notice and this permission notice shall be included
//	in all copies or substantial portions of the Software.
//
//	The Software is provided "as is", without any warranty of any kind,
//	express or implied, including but not limited to the warranties of 
//	merchantability, fitness for a particular purpose and noninfringement.
//	In not event shall the liability, whether in action of contract, tort or
//	otherwise, arising from, out of or in connection with the Software or the
//	use or other dealings in the Software.
//****************************************************************************

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Data.SqlClient;

namespace StudentTutorAppointmentSystem
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //********************************************************************
        //  METHOD NAME: Constructor
        //********************************************************************
        public MainWindow()
        {
            InitializeComponent();
        }

        //********************************************************************
        //  METHOD NAME: Get_DB_Connection
        //
        //  DESCRIPTION: Returns the Sql Connection to the User Database. 
        //********************************************************************
        public static SqlConnection Get_DB_Connection()
        {
            string cn_String = Properties.Settings.Default.connection_Str;
            SqlConnection sqlCon = new SqlConnection(cn_String);

            if (sqlCon.State != System.Data.ConnectionState.Open)
            {
                sqlCon.Open();
            }

            return sqlCon;
        }

        //********************************************************************
        //  METHOD NAME: LoginButton_Click
        //
        //  DESCRIPTION: Once the user clicks the "Login" button, then the
        //               entered information in the Username and Password 
        //               fields will be queried against the database for a 
        //               match.  If one is found, then the user dashboard 
        //               will be displayed.  Otherwise, an appropriate 
        //               message will be displayed to the user, prompting 
        //               them to try again.  
        //********************************************************************
        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            SqlConnection sqlCon = Get_DB_Connection(); ;
            try
            {
                string query = "SELECT role FROM Users WHERE " +
                               "username=@Username AND password=@Password";

                SqlCommand sqlCmd = new SqlCommand(query, sqlCon);
                sqlCmd.CommandType = System.Data.CommandType.Text;

                sqlCmd.Parameters.AddWithValue("@Username",
                                                UsernameText.Text);

                sqlCmd.Parameters.AddWithValue("@Password",
                                                PasswordText.Password);

                string role = Convert.ToString(sqlCmd.ExecuteScalar());

                if (role == "admin")
                {
                    AdminDashboard adminWindow = new AdminDashboard();
                    adminWindow.Show();
                    this.Close();
                }
                else if (role == "faculty")
                {
                    FacultyDashboard facWindow = new FacultyDashboard();
                    facWindow.Show();
                    this.Close();
                }
                else if (role == "tutor")
                {
                    TutorDashboard tutorWindow = new TutorDashboard();
                    tutorWindow.Show();
                    this.Close();
                }
                else if (role == "student")
                {
                    StudentDashboard studentWindow = new StudentDashboard();
                    studentWindow.Show();
                    this.Close();
                }
                else
                {
                    UsernameText.Clear();
                    PasswordText.Clear();
                    MessageBox.Show("Invalid username or password");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                sqlCon.Close();
            }
        }

        private void RegisterButton_Click(object sender, RoutedEventArgs e)
        {
            Register regWin = new Register();
            regWin.Show();
            this.Close();
        }
    }
}
