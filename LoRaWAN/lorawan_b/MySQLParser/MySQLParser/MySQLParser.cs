using MySql.Data.MySqlClient;
using System.ComponentModel;

namespace MySQLParser
{

    public partial class MySQLParser : Form
    {
        public partial class DBModel
        {
            public int id { get; set; }
            public string Timestamp { get; set; }
            public string Sensor { get; set; }
            public string Reading { get; set; }
        }

        public MySQLParser()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btn_QueryDatabase_Click(object sender, EventArgs e)
        {
            try
            {
                MySqlConnection conn = new MySqlConnection("server=" + txt_DatabaseIP.Text
                            + ";user id=" + txt_DatabaseUsername.Text + ";password="
                            + txt_DatabasePassword.Text + ";database=" + txt_DatabaseName.Text);

                conn.Open();
                String query = txt_QueryDatabase.Text;
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
                    var bindingList = new BindingList<DBModel>(dbModel);
                    var source = new BindingSource(bindingList, null);
                    grid_DataView.DataSource = source;

                }
                reader.Close();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }
    }
}