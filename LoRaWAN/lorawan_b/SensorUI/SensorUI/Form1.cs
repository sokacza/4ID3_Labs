using MySql.Data.MySqlClient;

namespace SensorUI
{
    public partial class Form1 : Form
    {
        public partial class DBModel
        {
            public int id { get; set; }
            public string Timestamp { get; set; }
            public string Sensor { get; set; }
            public string Reading { get; set; }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                MySqlConnection conn = new MySqlConnection("server=" + "localhost"
                            + ";user id=" + "root" + ";password="
                            + "fireball" + ";database=" + "GroupA");

                conn.Open();
                String query = "SELECT * FROM DeviceA WHERE Sensor = \"Temperature\" AND id = ( SELECT MAX(id) FROM DeviceA );";
                MySqlCommand cmd = new MySqlCommand(query, conn);
                MySqlDataReader reader = cmd.ExecuteReader();


                List<DBModel> dbModel = new List<DBModel>();

                while (reader.Read())
                {
                    for (int i = 0; i < reader.FieldCount; i += 5)
                    {


                        Console.WriteLine(reader.GetValue(i));

                        dbModel.Add(new DBModel()
                        {
                            id = int.Parse(reader.GetValue(i).ToString()),
                            Timestamp = reader.GetValue(i + 1).ToString(),
                            Sensor = reader.GetValue(i + 2).ToString(),
                            Reading = reader.GetValue(i + 3).ToString()
                        });
                        Console.WriteLine(dbModel[i].ToString());

                    }

                }
                reader.Close();
                label1.Text = dbModel[0].Sensor;
                label2.Text = dbModel[0].Timestamp;
                label3.Text = dbModel[0].Reading;

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            try
            {
                MySqlConnection conn = new MySqlConnection("server=" + "localhost"
                            + ";user id=" + "root" + ";password="
                            + "fireball" + ";database=" + "GroupA");

                conn.Open();
                String query = "SELECT * FROM DeviceA WHERE Sensor = \"Humidity\" AND id = ( SELECT MAX(id) - 1 FROM DeviceA );";
                MySqlCommand cmd = new MySqlCommand(query, conn);
                MySqlDataReader reader = cmd.ExecuteReader();


                List<DBModel> dbModel = new List<DBModel>();

                while (reader.Read())
                {
                    for (int i = 0; i < reader.FieldCount; i += 5)
                    {


                        Console.WriteLine(reader.GetValue(i));

                        dbModel.Add(new DBModel()
                        {
                            id = int.Parse(reader.GetValue(i).ToString()),
                            Timestamp = reader.GetValue(i + 1).ToString(),
                            Sensor = reader.GetValue(i + 2).ToString(),
                            Reading = reader.GetValue(i + 3).ToString()
                        });
                        Console.WriteLine(dbModel[i].ToString());

                    }

                }
                reader.Close();
                label4.Text = dbModel[0].Sensor;
                label5.Text = dbModel[0].Timestamp;
                label6.Text = dbModel[0].Reading;

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }


        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}